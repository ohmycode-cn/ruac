/**
 * C/C++ Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * Line Limit: Recommend line breaks at col: 96, force line breaks at col: 120
 * Date Time: 2026-07-18 21:44:45
 * Author: ohmycode-cn(ohcode@163.com)
 * Header File : include/test/ruac_test_logsystem.hpp
 * Source File : src/test/ruac_test_logsystem.cpp
 *
 * File Function Description:
 *
 *
 */

#include "test/ruac_test_logsystem.hpp"
#include "rstd/logsystem/ruac_format_json.hpp"
#include "rstd/logsystem/ruac_logkeys.hpp"
#include "rstd/logsystem/ruac_logtime.hpp"
#include <iostream>

namespace ruac::test {
    void testFormatJson() {
        ruac::rstd::logsystem::FormatJson obj = ruac::rstd::logsystem::FormatJson();
        auto msg = obj.format(ruac::rstd::logsystem::logkeys::maps::G_KW_MAP_TEMPLATE,
                              ruac::rstd::logsystem::logtime::safeTimeString26(),
                              "debug", 9223372036854775807LL,
                              "This is json format test",
                              __FILE__,
                              __LINE__);
        std::cout << msg << std::endl;
    }
} // namespace ruac::test
