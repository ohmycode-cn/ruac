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
#include "rstd/logsystem/ruac_output_console.hpp"
#include <iostream>
#include <thread>
#include <chrono>

namespace ruac::test {

    namespace {

        template <typename T>
        void innerForeatch(T &obj, std::string (*func)(const int), int thread_id_) {
            for (int index{0}; index < 5; index++) {
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                obj.output(func(thread_id_));
            }
        }

        auto getFormatTextString(const int thread_id_) -> std::string {
            auto obj = ruac::rstd::logsystem::FormatText();
            auto msg = obj.format(ruac::rstd::logsystem::logkeys::maps::G_KW_MAP_TEMPLATE,
                                  ruac::rstd::logsystem::logtime::safeTimeString26(),
                                  ruac::rstd::logsystem::logkeys::maps::G_DEBUG,
                                  thread_id_,
                                  "This is text format test",
                                  __FILE__,
                                  __LINE__);
            return msg;
        }

    } // namespace

    void foreatch(void (*func_)()) {
        for (int index{0}; index < 5; index++) {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            func_();
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

    void testOutputConsole(const std::string &thread_name_) {
        auto obj_00 = ruac::rstd::logsystem::OutputConsole();
        int thread_id{};
        ("thread-1" == thread_name_) ? thread_id = 1 : thread_id = 0;
        innerForeatch(obj_00, getFormatTextString, thread_id);
        std::string green{"\033[1;32m"};
        std::string reset{"\033[0m"};
        std::cout << "[" << green << "OK" << reset << "] This is thread " << thread_name_ << " running done !\n";
    }

} // namespace ruac::test