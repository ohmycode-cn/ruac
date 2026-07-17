#include <iostream>
#include "test/ruac_c_tmp.h"

int main(void) {
    std::cout << "This is c++ base test: hello" << std::endl;
    c_test_hello();
    std::cout << "This is Py3 base test: hello" << std::endl;
    system("/home/repox/Engineering/ruacdbv01/ruacdb/flib/ruac_py3_getosinfo");
    return 0;
}