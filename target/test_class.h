#ifndef TEST_CLASS_H
#define TEST_CLASS_H

#include <iostream>
#include "state_machine.h"

class test_class
{
/**
 * private
 * state machine reference
 */
    state_machine<test_class>* p_state_machine;

public:
    /* public:
     * workers methods
     */
    int test1(void);
    int test2(void);
    int test3(void);

    void set_callback(state_machine<test_class>* instance);
};

#endif
