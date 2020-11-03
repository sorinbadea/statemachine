#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H
#include <assert.h>
#include <list>
#include <future>
#include <thread>

template <bool>
struct compile_error;

template <>
struct compile_error<true> {
};

#define check_type(expr)(expr?true:false)

template <typename T>
class state_machine {
    
   /* private
    * object instance for method calls */
   T* p_obj_instance;

   /* private
    * typedef of pointer to methods belonging 
    * to the test class */
   typedef int (T::*p_methods_t)(void);

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

public:

   state_machine() = delete;

   /* initialize the class instance which will 
    * be used by the state machine */
   explicit state_machine(T* instance)
   {
       assert(instance != NULL);
       p_obj_instance = instance;
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
               *p_it,
               p_obj_instance);

           /**
	    * p_result.get() will block
	    * until the end of the above thread
	    **/
           std::cout << p_result.get() << std::endl;
           p_it++;
	   result = 1;
       }
       else
       {
          /* mark the end of iterations */
          result = 0;
       }
       return result;
   }

   /* callback for the end of each step; 
    * will be called by the test class */
   void operator()()
   {
      std::cout << "calling Elvis.." << std::endl;
   }

};

#endif

