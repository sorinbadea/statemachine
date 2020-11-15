#include <iostream>
#include "results.h"

template <typename T>
Results<T>::Results() : p_ok(0), p_nok(0), p_tests(0)
{}

template <typename T>
void Results<T>::compare(T expected, T result)
{
   (expected == result)?++p_ok:++p_nok;
   ++p_tests;
}

template <typename T>
Results<T>::~Results()
{
    std::cout << std::endl;
    std::cout << "test suite results" << std::endl;
    std::cout << "==================" << std::endl;
    std::cout << "tests  " << p_tests << std::endl;
    std::cout << "passed " << p_ok << std::endl;
    std::cout << "failed " << p_nok << std::endl;
    std::cout << std::endl;
}

/**
 * run each functor stored in the state machine;
 * compare the expected results wit the returned results;
 * \@param engine   test engine (state_machine)
 * \@param expected expected results
 * \@pparam callback calls an exterior main loop
 *          allowing other jobs to run
 */
template< typename T, typename TResult >
void run_steps(
    state_machine<T, TResult>& engine, 
    std::list<TResult> expected,
    void (*callback)(void))
{
   TestSuiteDone stop = TestSuiteDone::NO;
   while(stop == TestSuiteDone::NO)
   {
       /**
        * non blocking call regardless
        * of test behaviour */
       stop = engine.step();

       /* give control to other jobs */
       callback();
    }

    /* get the returned results */
    std::list< TResult > results = engine.get_results();
    assert( expected.size() == results.size() );

    /** expected and results list iterators */
    typename std::list< TResult >::iterator it_r = results.begin();
    typename std::list< TResult >::iterator it_e = expected.begin();

    /**
     * compare the expected and the received results
     * show statistics */
    Results<TResult> stat;
    for(; it_r != results.end(); it_r++, it_e++ )
    {
        stat.compare(*it_e, *it_r);
    }
}

