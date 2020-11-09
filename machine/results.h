#ifndef RESULTS_H
#define RESULTS_H


/**
 * - class designed compare an expecetd results with 
 * a received results;
 * - count if the check id OK or NOK
 * - for more complex types the \"compare\" method
 *   shall be redefined
 *   */
template <typename T>
class Results 
{
    int p_ok;
    int p_nok;
    int p_tests;

public:
    /** private data initialization */
    Results(); 

    /**
     * compare expected result with received result;
     * The same code works for different types
     * i.e. double, float, std::string
     */
    void compare(T expected, T result);

    /**
     * destructor
     */
    ~ Results();
};

#endif
