/**
 * C/C++ Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * Line Limit: Recommend line breaks at col: 96, force line breaks at col: 120
 * Date Time: 2026-07-17 21:56:41
 * Author: ohmycode-cn(ohcode@163.com)
 * Header File : include/rstd/logsystem/ruac_logtime.hpp
 * Source File : src/rstd/logsystem/ruac_logtime.cpp
 *
 * File Function Description:
 *   Declares timestamp formatting utilities for the RUAC log system.
 *   Provides a thread-safe helper (safeTimeString26) that leverages the
 *   C++26 chrono formatting facilities to produce a locale-independent
 *   timestamp string suitable for embedding in structured log records
 *   and ensuring consistent chronological ordering across log sinks.
 */

#pragma once
#ifndef RUAC_LOGTIME_HPP
#define RUAC_LOGTIME_HPP

#include "rstd/logsystem/ruac_logtype.hpp"

namespace ruac::rstd::logsystem {

    namespace logtime {

        /**
         * @brief Produces a locale-independent timestamp string using C++26
         *        chrono formatting facilities, suitable for embedding in
         *        structured log records.
         */
        auto safeTimeString26() -> logtype::strg;

    } // namespace logtime

} // namespace ruac::rstd::logsystem

#endif // RUAC_LOGTIME_HPP
