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

#pragma once
#ifndef RUAC_TEST_LOGSYSTEM_HPP
#define RUAC_TEST_LOGSYSTEM_HPP

namespace ruac::test {
    void foreatch(void (*func)());
    void testFormatJson();
    void testFormatText();
    void testFormatXML();
} // namespace ruac::test

#endif // RUAC_TEST_LOGSYSTEM_HPP
