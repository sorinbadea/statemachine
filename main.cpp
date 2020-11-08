#include <iostream>
#include "state_machine.h"
#include "test_class.h"
#include "results.h"
#include "results.cpp"

/**
 * run each state_machine until the end
 * compare the expected results wit the returned
 * \@param engine   test engine (state_machine)
 * \@param expected expected results
 */
template< typename T, typename TResult >
void run_tests(state_machine<T, TResult>& engine, std::list<TResult> expected)
{
   TestSuiteDone stop = TestSuiteDone::NO;
   while(stop == TestSuiteDone::NO)
   {
       /** 
        * non blocking call regardless 
        * of test behaviour */
       stop = engine.step();
    }

    std::list< TResult > results = engine.get_results();
    assert( expected.size() == results.size() );

    /** expected and results list iterators */
    typename std::list< TResult >::iterator it_r = results.begin();
    typename std::list< TResult >::iterator it_e = expected.begin();

    /**
     * check the expected and the returned results 
     * show statistics */
    Results<TResult> stat;
    for(; it_r != results.end(); it_r++, it_e++ )
    {
        stat.compare(*it_e, *it_r);
    }
}


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
    
	std::list<int> expected = {1, 1, 1};
	run_tests<test_class1, int>( engine, expected);
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

	std::list<std::string> expected = {"s1", "s2", "s33"};
	run_tests<test_class2, std::string>( engine, expected);
    }
    
    return 0;
}
