#include <iostream>
#include <thread>
#include <future>


class Test {
public:
    int func1(int x) { 
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
        return 6; 
    }
    int func2() { return 3; }
};


template <typename TestClass, typename TestParam>
class test_engine
{
    typedef int (TestClass::*p_methods_t)(TestParam);
    TestClass* test_instance;
    TestParam test_param;

public:
    test_engine() = delete;
    //
    // constructor
    //
    explicit test_engine(TestClass* ti, TestParam param)
    {
        test_instance = ti;
        test_param = param;
    }

    //
    //callback for the end of method call
    //
    void operator()()
    {
    }

};


int main() {

   Test t;

   test_engine<Test, int> test(&t, 10);

   /* get the method pointer */
   typedef int (Test::*p_methods_t)(int);
   p_methods_t pm = &Test::func1;

   /* start the thread with the func pointer */
   auto param = 1;
   std::future<int> fp_ret = std::async(std::launch::async, pm, &t, param);

   //do something else..
   std::cout << "processing.." << std::endl;

   fp_ret.wait();
   std::cout << fp_ret.get() << std::endl;

   // thread ends

   return 0;
}

