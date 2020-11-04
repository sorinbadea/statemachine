#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H
#include <assert.h>
#include <list>
#include <future>
#include <thread>

/**
 *ensure that the callback indicating the end
  of the thread is called after the thread ends 
 */
template <typename T>
class thread_guard
{
   /* private
    * object instance for method calls */
    T* p_obj_instance;

public:
    thread_guard() = delete;
    explicit thread_guard(T* instance) : p_obj_instance(instance) 
    {}
    ~thread_guard()
    {
       /** state_machine callback */
       (*p_obj_instance)();
    }
};

/**
 * takes a test class instance and it's method pointers
 * and call them one after another;
 * TODO add full async behaviour
 */
template <typename T>
class state_machine {

   /* typedef of pointer to methods belonging 
    * to the test class */
   typedef int (T::*p_methods_t)(void);

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
    std::future<int> p_result;

    /** indicates the end of the thread */
    bool p_task_done;

public:

   state_machine() = delete;

   /* initialize the class instance which will 
    * be used by the state machine */
   explicit state_machine(T* instance)
   {
       assert(instance != NULL);
       p_obj_instance = instance;
       p_task_done = false;
   }

   /* update the step method, initialize the iterator 
    * through the list of methods pointers */
   void set_step(p_methods_t step_method) 
   {
       assert(step_method != NULL);
       p_methods.push_back(step_method);
       if (p_methods.size() == 1) {
          /*
           * initialize the list iterator 
 	   * */
          p_it = p_methods.begin();
      }
   }

   /* call each recorded steps */
   int step()
   {
       int result = 0;
       if (p_it != p_methods.end())
       {
           p_result = std::async(
               std::launch::async, 
               [this] {
               thread_guard<state_machine> th(this);
               return (p_obj_instance->**p_it)();
               /**
                * the callback shall be callled only 
		* at the end of the scope of \"th\"
		* after the end of test call
                **/
               });

           /** this call still blocks */
           std::cout << p_result.get() << std::endl;

           p_it++;

	   /** still iterations to do */
           result = 1;
       }
       else
       {
          /* mark the end of iterations */
          result = 0;
       }
       return result;
   }

   /* callback for the end of each test; 
    * it is called by the guard_thread */
   void operator()()
   {
      p_task_done = true;
      std::cout << "calling Elvis.." << std::endl;
   }

};

#endif

