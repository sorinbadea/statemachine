#ifndef RESULTS_H
#define RESULTS_H

template <typename T>
class Results 
{
    int p_ok;
    int p_nok;
    int p_tests;

public:
    /**
     * private data initialization
     */
    Results(); 

    /**
     * compare expected results with received results
     */
    void compare(T expected, T result);

    /**
     * destructor
     */
    ~ Results();
};

#endif
