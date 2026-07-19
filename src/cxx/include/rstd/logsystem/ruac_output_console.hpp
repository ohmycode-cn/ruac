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

#pragma once
#ifndef RUAC_OUTPUT_CONSOLE_HPP
#define RUAC_OUTPUT_CONSOLE_HPP

#include "rstd/logsystem/ruac_output.hpp"

namespace ruac::rstd::logsystem {

    /**
     * @brief
     */
    class OutputConsole : public Output {
      public:
        OutputConsole() = default;
        ~OutputConsole() = default;

      public:
        void output(const logtype::strg &message_);
    }; // class OutputConsole

} // namespace ruac::rstd::logsystem

#endif // RUAC_OUTPUT_CONSOLE_HPP
