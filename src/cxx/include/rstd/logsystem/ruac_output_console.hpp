/**
 * C/C++ Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * Line Limit: Recommend line breaks at col: 96, force line breaks at col: 120
 * Date Time: 2026-07-19 11:50:15
 * Author: ohmycode-cn(ohcode@163.com)
 * Header File : include/rstd/logsystem/ruac_output_console.hpp
 * Source File : src/rstd/logsystem/ruac_output_console.cpp
 *
 * File Function Description:
 *   Declares the OutputConsole class, a concrete implementation of the
 *   Output interface for the RUAC log system. OutputConsole writes
 *   formatted log messages to standard output using synchronized streams
 *   to ensure thread-safe console output.
 */

#pragma once
#ifndef RUAC_OUTPUT_CONSOLE_HPP
#define RUAC_OUTPUT_CONSOLE_HPP

#include "rstd/logsystem/ruac_output.hpp"

namespace ruac::rstd::logsystem {

    /**
     * @brief Console-output sink that writes formatted log messages to stdout.
     *        Uses std::osyncstream for thread-safe output synchronization.
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
