#include <iostream>
#include "state_machine.h"
#include "engine.h"

int test_class::test1(void)
{
   std::cout << "test_engine::test1" << std::endl;
   std::this_thread::sleep_for(std::chrono::milliseconds(2000));
   return 1;
}

int test_class::test2(void)
{
   static int res;
   std::cout << "test_engine::test2" << std::endl;
   return res++;
}

/*
int test_engine::step_test_engine(void)
{
    int res;
    if (p_it != p_methods.end())
    {
        res = p_state_machine->update_state_machine(*p_it);
        if (res)
        {
            p_it++;
        }
    }
    return res;
}*/

