/**
 * C/C++ Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * Line Limit: Recommend line breaks at col: 96, force line breaks at col: 120
 * Date Time: 2026-07-17 21:56:41
 * Author: ohmycode-cn(ohcode@163.com)
 * Header File : include/rstd/logsystem/ruac_logtime.hpp
 * Source File : src/rstd/logsystem/ruac_logtime.cpp
 *
 * File Function Description:
 *
 *
 */

#include "rstd/logsystem/ruac_logtime.hpp"
#include <chrono>
#include <format>

namespace ruac::rstd::logsystem {

    namespace logtime {

        /**
         * @brief Generates a formatted local-time string in C++26 chrono style.
         *
         * @return Formatted timestamp string in "YYYY-MM-DD-HH-MM-SS" format.
         */
        auto safeTimeString26() -> logtype::strg {
            auto now = std::chrono::system_clock::now();
            auto ltm = std::chrono::current_zone()->to_local(now);
            return std::format("{:%Y-%m-%d-%H-%M-%S}", ltm);
        }

    } // namespace logtime

} // namespace ruac::rstd::logsystem
