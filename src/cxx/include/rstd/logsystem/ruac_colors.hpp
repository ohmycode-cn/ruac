/**
 * C/C++ Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * Line Limit: Recommend line breaks at col: 96, force line breaks at col: 120
 * Date Time: 2026-07-17 22:24:48
 * Author: ohmycode-cn(ohcode@163.com)
 * Header File : include/rstd/logsystem/ruac_colors.hpp
 * Source File : src/rstd/logsystem/ruac_colors.cpp
 *
 * File Function Description:
 *   Declares the ANSI terminal colorization interface for the RUAC log system.
 *   Defines the Colors class that encapsulates ANSI escape-sequence construction
 *   and provides single-letter color-wrapping helpers (d/r/g/y/b/m/c/w) for
 *   rendering colored text in terminals with configurable compatibility, highlight,
 *   and bold-font modes.
 */

#pragma once
#ifndef RUAC_COLORS_HPP
#define RUAC_COLORS_HPP

#include "rstd/logsystem/ruac_logtype.hpp"

namespace ruac::rstd::logsystem {

    /**
     * @brief Encapsulates ANSI terminal color escape sequences with configurable
     *        compatibility, highlight, and bold-font rendering modes.
     *        Provides single-letter color-wrapping helpers that conditionally
     *        apply color codes based on dual-layer highlight control (per-call
     *        and instance-level).
     */
    class Colors {
      private:
        logtype::boln m_enable_term_compatible{true};
        logtype::boln m_enable_term_highlight{false};
        logtype::boln m_enable_term_bold_font{false};

      private:
        const logtype::strg M_SEQ_ID[9]{"0", "30", "31", "32", "33", "34", "35", "36",
                                        "37"};
        const logtype::strg M_ANSI_TERM_OLD{"\033"};
        const logtype::strg M_ANSI_TERM_NEW{"\x1b"};
        const logtype::strg M_CHAR_M{"m"};
        const logtype::strg M_FONT_ORGD{"[0;"};
        const logtype::strg M_FONT_BOLD{"[1;"};

      private:
        logtype::strg m_reset;
        logtype::strg m_dark;
        logtype::strg m_red;
        logtype::strg m_green;
        logtype::strg m_yellow;
        logtype::strg m_blue;
        logtype::strg m_magenta;
        logtype::strg m_cyan;
        logtype::strg m_white;

      private:
        void init(const logtype::boln &enable_ce_, const logtype::boln &enable_ht_, const logtype::boln &enable_bf_);

      public:
        Colors(const logtype::boln &enable_ce_, const logtype::boln &enable_ht_, const logtype::boln &enable_bf_);
        ~Colors() = default;

      public:
        auto d(const logtype::strg &strline_, const logtype::boln &enable_ht_ = true) -> logtype::strg;
        auto r(const logtype::strg &strline_, const logtype::boln &enable_ht_ = true) -> logtype::strg;
        auto g(const logtype::strg &strline_, const logtype::boln &enable_ht_ = true) -> logtype::strg;
        auto y(const logtype::strg &strline_, const logtype::boln &enable_ht_ = true) -> logtype::strg;
        auto b(const logtype::strg &strline_, const logtype::boln &enable_ht_ = true) -> logtype::strg;
        auto m(const logtype::strg &strline_, const logtype::boln &enable_ht_ = true) -> logtype::strg;
        auto c(const logtype::strg &strline_, const logtype::boln &enable_ht_ = true) -> logtype::strg;
        auto w(const logtype::strg &strline_, const logtype::boln &enable_ht_ = true) -> logtype::strg;

      public:
        void reinit(const logtype::boln &enable_ce_ = true, const logtype::boln &enable_ht_ = false,
                    const logtype::boln &enable_bf_ = false);
    }; // class Colors

} // namespace ruac::rstd::logsystem

#endif // RUAC_COLORS_HPP
