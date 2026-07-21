/**
 * C/C++ Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * Line Limit: Recommend line breaks at col: 96, force line breaks at col: 120
 * Date Time: 2026-07-18 21:44:08
 * Author: ohmycode-cn(ohcode@163.com)
 * Header File : include/test/ruac_test_main.hpp
 * Source File : src/test/ruac_test_main.cpp
 *
 * File Function Description:
 *
 *
 */

#include "rstd/logsystem/ruac_message_entrust.hpp"
#include "test/ruac_test_logfile_parser.hpp"
#include "test/ruac_test_main.hpp"
#include "test/ruac_test_logsystem.hpp"
// #include "test/ruac_c_tmp.h"
#include <iostream>
#include <thread>

namespace ruac::test {

    namespace {

        void testOutputConsoleAndThreadSafety() {
            std::jthread t0([] { testOutputConsole("thread-0"); });
            std::jthread t1([] { testOutputConsole("thread-1"); });
            std::cout << "This is thread 0 by join\n";
            t0.join();
            std::cout << "This is thread 1 by join\n";
            t1.join();
        }

        void testOutputFileAndThreadSafety() {
            std::jthread t0([] { testOutputFile("thread-0"); });
            std::jthread t1([] { testOutputFile("thread-1"); });
            std::cout << "This is thread 0 by join\n";
            t0.join();
            std::cout << "This is thread 1 by join\n";
            t1.join();
        }

    } // namespace
    void testMain() {
        ruac::rstd::logsystem::MessageEntrust::instance().init(true, true, false);
        // foreatch(&testFormatJson);
        // foreatch(&testFormatText);
        // foreatch(&testFormatXML);
        // testOutputConsoleAndThreadSafety();
        // testOutputFileAndThreadSafety();
        testLogfileParser00();
        testLogRuntime();
    }
} // namespace ruac::test
