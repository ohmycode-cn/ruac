/**
 * C/C++ Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * Line Limit: Recommend line breaks at col: 96, force line breaks at col: 120
 * Date Time: 2026-07-18 21:44:08
 * Author: ohmycode-cn(ohcode@163.com)
 * Header File : include/test/ruac_test.hpp
 * Source File : src/test/ruac_test.cpp
 *
 * File Function Description:
 *
 *
 */

#include "test/ruac_test.hpp"
#include "test/ruac_test_logsystem.hpp"

namespace ruac::test {
    void testMain() {
        foreatch(&testFormatJson);
        foreatch(&testFormatText);
        foreatch(&testFormatXML);
    }
} // namespace ruac::test
