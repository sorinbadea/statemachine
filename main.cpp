#include <iostream>
#include "state_machine.h"
#include "test_class.h"
#include "results.h"
#include "results.cpp"

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
	 run_tests<test_class1, int>(engine, expected);
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
	 run_tests<test_class2, std::string>(engine, expected);
    }
    return 0;
}
