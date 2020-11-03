#include <iostream>
#include "state_machine.h"
#include "test_class.h"

int main(void) {

    test_class foo;

    state_machine<test_class> engine(&foo);
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
