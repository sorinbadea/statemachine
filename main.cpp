#include <iostream>
#include "state_machine.h"
#include "test_class.h"
#include "results.h"
#include "results.cpp"

int main(void) {


    {
        /** test class1 instanciation */
        test_class1 foo;

        /**
         * instanciate the test machine 
	 * methods returnng int */
         state_machine<test_class1, int> engine(&foo);

        /** add methods to be tested */
        engine.set_step(&test_class1::test1);
        engine.set_step(&test_class1::test2);
        engine.set_step(&test_class1::test3);
    
        TestSuiteDone stop = TestSuiteDone::NO;
        while(stop == TestSuiteDone::NO)
        {
            /** 
	    * non blocking call regardless 
	    * of test behaviour */
            stop = engine.step();
        }

        /**
        * results display
        */
        {
            Results<int> r;
            std::list<int> results = engine.get_results();
            std::list<int>::iterator it = results.begin();
    
            r.compare(1, *it++);
            r.compare(1, *it++);
            r.compare(1, *it);
        }
    }

    {

        /** test class2 instanciation 
	 * methods returning std::string */
        test_class2 foo;
        state_machine<test_class2, std::string> engine(&foo);

        /** add methods to be tested */
        engine.set_step(&test_class2::test1);
        engine.set_step(&test_class2::test2);
        engine.set_step(&test_class2::test3);
    
        TestSuiteDone stop = TestSuiteDone::NO;
        while(stop == TestSuiteDone::NO)
        {
            /** 
	    * non blocking call regardless 
	    * of test behaviour */
            stop = engine.step();
        }

        /**
        * results display
        */
        {
            Results< std::string > r;
            std::list< std::string > results = engine.get_results();
            std::list< std::string >::iterator it = results.begin();
    
            r.compare("s1", *it++);
            r.compare("s2", *it++);
            r.compare("s3", *it);
        }
    }
    
    return 0;
}
