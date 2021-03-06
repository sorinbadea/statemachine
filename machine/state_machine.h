#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H
#include <assert.h>
#include <list>
#include <future>
#include <thread>
#include <mutex>

enum class StepsSuiteReady {
   YES = 0, NO=1
};

/**
 *ensure that the callback indicating the end
  of the thread is called after the thread ends 
 */
template <typename T, typename TResult>
class thread_guard
{
   /* private
    * state machine instance */
    T* p_obj_instance;

    /** test result type */
    TResult p_res;

    thread_guard<T, TResult>(const thread_guard&);
    thread_guard<T, TResult> operator=(const thread_guard&);

public:
    thread_guard() = delete;

    /**
     * thread guard constructor
     * \@param instance state_machine instance
     * \@param res test result */
    explicit thread_guard(T* instance, TResult res) : 
       p_obj_instance(instance), p_res(res)
    {}

    ~thread_guard()
    {
       /** state_machine callback */
       (*p_obj_instance)(p_res);
    }
};

/**
 * takes a test class instance and it's method pointers
 * and call them one after another;
 * Implements a full async behaviour, each tests are 
 * ran one after another and does not block the caller;
 * T -> test class instance
 * TResult -> test result type
 */
template <typename T, typename TResult>
class state_machine {

   /* typedef of pointer to methods belonging 
    * to the test class */
   typedef TResult (T::*p_methods_t)(void);

   /* private
    * object instance for method calls */
   T* p_obj_instance;


   /* private 
    * vector of pointers to methods */
   std::list<p_methods_t> p_methods;

    /**
     * private 
     * vector iterator through pointers to methods */
    typename std::list<p_methods_t>::iterator p_it;

    /**
     * private
     * async result of method call via a thread */
    std::future<void> p_result;

    /** private
     * indicates the end of the thread */
    std::atomic<bool> p_task_done;

    /** private
     * sync the thread runningh the test with the parent thread */
    std::mutex p_sync_threads;

    /**
     * private
     * results list */
    std::list<TResult> p_result_list;

public:

   state_machine() = delete;

   /* initialize the class instance which will 
    * be used by the state machine 
    * \@param instance target class instance */
   explicit state_machine(T* instance)
   {
       assert(instance != NULL);
       p_obj_instance = instance;
       p_task_done = true;
   }

   /* update the step method, initialize the iterator 
    * through the list of methods pointers 
    * \@param step_method  test method in target class */
   void set_step(p_methods_t step_method) 
   {
       assert(step_method != NULL);
       p_methods.push_back(step_method);
       if (p_methods.size() == 1) {
          /*
           * initialize the list iterator 
           **/
          p_it = p_methods.begin();
      }
   }

   /* call each recorded steps */
   StepsSuiteReady step()
   {

       std::unique_lock<std::mutex> lock(p_sync_threads);
       StepsSuiteReady result = StepsSuiteReady::NO;

       if (p_it != p_methods.end())
       {
           if (p_task_done)
	   {
               p_task_done = false;

	       /**
		* launch the thread running the test
		**/
               p_result = std::async(
                    std::launch::async, 
                        [this] {
			/**
			 * test call 
			 **/
                        TResult res = (p_obj_instance->**p_it)();

			/** 
			 * the destructor of thread_guard will
			 * trigger the callback when the therad ends
			 */
                        thread_guard<state_machine, TResult> th(this, res);
                    }
	       );
	   }

	   /** iterations still remains */
           result = StepsSuiteReady::NO;
       }
       else
       {
           result = p_task_done?StepsSuiteReady::YES:StepsSuiteReady::NO;
       }
       return result;
   }

   /* callback for the end of each test; 
    * it is called by the guard_thread by it's destructor
    * \@param result  test result */
   void operator()(TResult test_result)
   {
       std::unique_lock<std::mutex> lock(p_sync_threads);
       ++p_it;
       p_task_done = true;
       p_result_list.push_back(test_result);
   }

   /**
    * Getter, return the results */
   std::list<TResult> get_results(void) const {
       return p_result_list;
   }

};

#endif
