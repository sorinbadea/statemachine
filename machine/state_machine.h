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
    * typedef of pointer to method of p_object_instance */
   typedef int (T::*p_methods_t)(void);

   /* private 
    * vector of pointers to methods */
   std::list<p_methods_t> p_methods;

    /**
     * private 
     * vector iterator through pointers to methods */
    typename std::list<p_methods_t>::iterator p_it;

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
           * initialize the vector iterator 
 	   * */
          p_it = p_methods.begin();
      }
   }

   /* call each recorded steps */
   int step()
   {

       if (p_it != p_methods.end())
       {
           std::future<int> result = std::async(
              std::launch::async, 
              *p_it,
               p_obj_instance);

           result.wait();
           std::cout << result.get() << std::endl;
           p_it++;
	   return 1;
       }
       /* mark the end of iterations */
       return 0;
   }

   /* callback for the end of each step */
   void operator()()
   {
   }

};

#endif

