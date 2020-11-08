#ifndef TEST_CLASS_H
#define TEST_CLASS_H

#include <iostream>
#include <string>
#include "state_machine.h"

/**
 * ordinary test class in test
 */
class test_class1
{
public:
    /* public:
     * workers methods
     */
    int test1(void);
    int test2(void);
    int test3(void);
};

/**
 * ordinary test class in test
 */
class test_class2
{
public:
    /* public:
     * workers methods
     */
    std::string test1(void);
    std::string test2(void);
    std::string test3(void);
};

#endif
