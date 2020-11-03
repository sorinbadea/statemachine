#include <iostream>
#include <thread>
#include "test_class.h"

int test_class::test1(void)
{
   assert(p_state_machine != NULL);
   std::cout << "test_engine::test1" << std::endl;
   std::this_thread::sleep_for(std::chrono::milliseconds(2000));

   /**
    * inform the state machine that the task ended */
   (*p_state_machine)();
   return 1;
}

int test_class::test2(void)
{
   assert(p_state_machine != NULL);
   std::cout << "test_engine::test2" << std::endl;

   /**
    * inform the state machine that the task ended */
   (*p_state_machine)();
   return 1;
}

int test_class::test3(void)
{
   assert(p_state_machine != NULL);
   std::cout << "test_engine::test3" << std::endl;
   std::this_thread::sleep_for(std::chrono::milliseconds(1000));

   /**
    * inform the state machine that the task ended */
   (*p_state_machine)();
   return 0;
}

void test_class::set_callback(state_machine<test_class>* instance)
{
   assert(instance != NULL);
   p_state_machine = instance;
}
