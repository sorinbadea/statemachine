#include <iostream>
#include "state_machine.h"
#include "test_class.h"

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
        //do something else
	//std::cout << "processing.." << std::endl;
        stop = engine.step();
        //std::this_thread::sleep_for(std::chrono::milliseconds(1000));	
    }
    
    return 0;
}
