#include <iostream>
#include <thread>
#include "test_class.h"

int test_class1::test1(void)
{
   std::cout << "test_engine::test1" << std::endl;
   std::this_thread::sleep_for(std::chrono::milliseconds(2000));

   return 1;
}

int test_class1::test2(void)
{
   std::cout << "test_engine::test2" << std::endl;

   return 1;
}

int test_class1::test3(void)
{
   std::cout << "test_engine::test3" << std::endl;
   std::this_thread::sleep_for(std::chrono::milliseconds(1000));

   return 0;
}

std::string test_class2::test1(void)
{
   std::string s1 = "s1";
   std::cout << "test_engine::test1" << std::endl;
   std::this_thread::sleep_for(std::chrono::milliseconds(2000));

   return s1;
}

std::string test_class2::test2(void)
{
   std::string s2 = "s2";
   std::cout << "test_engine::test2" << std::endl;

   return s2;
}

std::string test_class2::test3(void)
{
   std::string s3 = "s3";
   std::cout << "test_engine::test3" << std::endl;
   std::this_thread::sleep_for(std::chrono::milliseconds(1000));

   return s3;
}
