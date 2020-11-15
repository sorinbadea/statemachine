#include <iostream>
#include "state_machine.h"
#include "test_class.h"
#include "results.h"
#include "results.cpp"

void main_loop(void)
{
   /**
    * Other jobs could be started here
    */
   //std::cout << "other jobs.." << std::endl;
}

int main(void) {

    {
        /** test class1 instanciation */
        test_class1 foo;

	 /* test methods returnig an int */
         state_machine<test_class1, int> engine(&foo);

         /** add methods to be tested */
         engine.set_step(&test_class1::test1);
         engine.set_step(&test_class1::test2);
         engine.set_step(&test_class1::test3);
  
         /* expected results */	 
	 std::list<int> expected = {1, 1, 1};

	 /* ran and test the results */
         if (run_steps<test_class1, int>(engine, expected, main_loop))
         {
             std::cout << "steps suite passed" << std::endl;
         }
         else
         {
             std::cout << "steps suite failed" << std::endl;
         }
         std::cout << std::endl;
    }

    {
         /** test class2 instanciation */
         test_class2 foo;

	 /* test methods returning a std::string */
         state_machine<test_class2, std::string> engine(&foo);

         /** add methods to be tested */
         engine.set_step(&test_class2::test1);
         engine.set_step(&test_class2::test2);
         engine.set_step(&test_class2::test3);

	 /* expected results */
	 std::list<std::string> expected = {"s1", "s2", "s33"};

	 /* ran and test the results */
	 if (run_steps<test_class2, std::string>(engine, expected, main_loop))
         {
             std::cout << "steps suite passed" << std::endl;
         }
         else
         {
             std::cout << "steps suite failed" << std::endl;
         }
         std::cout << std::endl;
    }

    return 0;
}

