#include <iostream>
#include "state_machine.h"
#include "test_class.h"
#include "results.h"
#include "results.cpp"

int main(void) {

    /** test class instanciation */
    test_class foo;

    /**
     * instanciate the test machine */
    state_machine<test_class> engine(&foo);

    /** add methods to be tested */
    engine.set_step(&test_class::test1);
    engine.set_step(&test_class::test2);
    engine.set_step(&test_class::test3);
    
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
    
    return 0;
}
