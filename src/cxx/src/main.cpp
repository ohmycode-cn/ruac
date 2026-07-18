#include <iostream>
#include "test/ruac_c_tmp.h"
#include "test/ruac_test.hpp"

int main(void) {
    std::cout << "This is c++ base test: hello\n";
    c_test_hello();
    std::cout << "This is Py3 base test: hello\n";
    system("/home/repox/Engineering/ruacdbv01/ruacdb/flib/ruac_py3_getosinfo");
    std::cout << "\n\n";
    ruac::test::testMain();
    return 0;
}