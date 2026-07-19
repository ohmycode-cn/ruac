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
#include "rstd/logsystem/ruac_format_text.hpp"
#include "rstd/logsystem/ruac_format_xml.hpp"
#include "rstd/logsystem/ruac_logkeys.hpp"
#include "rstd/logsystem/ruac_logtime.hpp"
#include <iostream>
#include <thread>
#include <chrono>

namespace ruac::test {

    void foreatch(void (*func)()) {
        for (int index{0}; index < 5; index++) {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            func();
        }
    }

    void testFormatJson() {
        auto obj = ruac::rstd::logsystem::FormatJson();
        auto msg = obj.format(ruac::rstd::logsystem::logkeys::maps::G_KW_MAP_TEMPLATE,
                              ruac::rstd::logsystem::logtime::safeTimeString26(),
                              ruac::rstd::logsystem::logkeys::maps::G_DEBUG,
                              9223372036854775807LL,
                              "This is json format test",
                              __FILE__,
                              __LINE__);
        std::cout << msg << std::endl;
    }

    void testFormatText() {
        auto obj = ruac::rstd::logsystem::FormatText();
        auto msg = obj.format(ruac::rstd::logsystem::logkeys::maps::G_KW_MAP_TEMPLATE,
                              ruac::rstd::logsystem::logtime::safeTimeString26(),
                              ruac::rstd::logsystem::logkeys::maps::G_DEBUG,
                              123234234768324,
                              "This is text format test",
                              __FILE__,
                              __LINE__);
        std::cout << msg << std::endl;
    }

    void testFormatXML() {
        auto obj = ruac::rstd::logsystem::FormatXML();
        auto msg = obj.format(ruac::rstd::logsystem::logkeys::maps::G_KW_MAP_TEMPLATE,
                              ruac::rstd::logsystem::logtime::safeTimeString26(),
                              ruac::rstd::logsystem::logkeys::maps::G_DEBUG,
                              123234234768324,
                              "This is xml format test",
                              __FILE__,
                              __LINE__);
        std::cout << msg << std::endl;
    }

} // namespace ruac::test