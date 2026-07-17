/**
 * C/C++ Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * Line Limit: Recommend line breaks at col: 96, force line breaks at col: 120
 * Date Time: 2026-07-17 22:12:50
 * Author: ohmycode-cn(ohcode@163.com)
 * Header File : include/rstd/logsystem/ruac_output.hpp
 * Source File : src/rstd/logsystem/ruac_output.cpp
 *
 * File Function Description:
 *   Declares the abstract output-sink interface for the RUAC log system.
 *   Defines the Output base class whose pure-virtual output() method serves
 *   as the extension point for concrete log sinks (e.g., console, file,
 *   remote endpoint). Derived classes implement output() to dispatch a
 *   fully-formatted log message string to a specific destination backend.
 */

#pragma once
#ifndef RUAC_OUTPUT_HPP
#define RUAC_OUTPUT_HPP

#include "rstd/logsystem/ruac_logtype.hpp"

namespace ruac::rstd::logsystem {

    /**
     * @brief Abstract base class defining the log-output-sink contract.
     *        Concrete sinks (console, file, remote endpoint) derive from
     *        this and implement output() to dispatch a formatted log message
     *        to a specific destination backend.
     */
    class Output {
      public:
        virtual void output(const logtype::strg &message_) = 0;
        virtual ~Output() = default;

    }; // class Output

} // namespace ruac::rstd::logsystem

#endif // RUAC_OUTPUT_HPP
