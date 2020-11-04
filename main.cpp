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
    
    auto stop = 1;
    while(stop)
    {
        //do something else
	std::cout << "processing.." << std::endl;
        stop = engine.step();
    }
    
    return 0;
}
