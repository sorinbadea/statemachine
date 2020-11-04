#include <iostream>
#include <thread>
#include "test_class.h"

int test_class::test1(void)
{
   std::cout << "test_engine::test1" << std::endl;
   std::this_thread::sleep_for(std::chrono::milliseconds(2000));

   return 1;
}

int test_class::test2(void)
{
   std::cout << "test_engine::test2" << std::endl;

   return 1;
}

int test_class::test3(void)
{
   std::cout << "test_engine::test3" << std::endl;
   std::this_thread::sleep_for(std::chrono::milliseconds(1000));

   return 0;
}
