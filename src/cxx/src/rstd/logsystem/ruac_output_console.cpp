/**
 * C/C++ Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * Line Limit: Recommend line breaks at col: 96, force line breaks at col: 120
 * Date Time: 2026-07-19 11:50:15
 * Author: ohmycode-cn(ohcode@163.com)
 * Header File : include/rstd/logsystem/ruac_output_console.hpp
 * Source File : src/rstd/logsystem/ruac_output_console.cpp
 *
 * File Function Description:
 *
 *
 */

#include "rstd/logsystem/ruac_output_console.hpp"
#include <syncstream>
#include <iostream>

namespace ruac::rstd::logsystem {

    void OutputConsole::output(const logtype::strg &message_) {
        std::osyncstream(std::cout) << message_ << std::endl;
    }

} // namespace ruac::rstd::logsystem
