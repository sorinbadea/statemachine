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
}

