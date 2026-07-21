/**
 * C/C++ Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * Line Limit: Recommend line breaks at col: 96, force line breaks at col: 120
 * Date Time: 2026-07-17 22:24:48
 * Author: ohmycode-cn(ohcode@163.com)
 * Header File : include/rstd/logsystem/ruac_colors.hpp
 * Source File : src/rstd/logsystem/ruac_colors.cpp
 *
 * File Function Description:
 *   Implements the Colors class that builds ANSI terminal color escape
 *   sequences from compatibility, highlight, and bold-font flags. Provides
 *   a shared wrap() helper used by single-letter color methods (d/r/g/y/
 *   b/m/c/w) to conditionally wrap text with color and reset codes.
 *
 */

#include "rstd/logsystem/ruac_colors.hpp"
#include "rstd/logsystem/ruac_logtype.hpp"

namespace ruac::rstd::logsystem {

    /**
     * @brief Constructs a Colors instance and initializes ANSI escape sequences.
     *
     * @param enable_ce_  Whether to enable legacy terminal-compatible mode.
     * @param enable_ht_  Whether to enable terminal highlight rendering.
     * @param enable_bf_  Whether to enable bold font output.
     */
    Colors::Colors(const logtype::boln &enable_ce_, const logtype::boln &enable_ht_, const logtype::boln &enable_bf_) {
        init(enable_ce_, enable_ht_, enable_bf_);
    }

    /**
     * @brief Stores the highlight flag and builds all color escape sequences
     *        from the terminal capability flags using static constexpr constants.
     *
     * @param enable_ce_  Whether to enable legacy terminal-compatible mode.
     * @param enable_ht_  Whether to enable terminal highlight rendering.
     * @param enable_bf_  Whether to enable bold font output.
     */
    void Colors::init(const logtype::boln &enable_ce_, const logtype::boln &enable_ht_,
                      const logtype::boln &enable_bf_) {
        m_enable_term_highlight = enable_ht_;

        logtype::strg ANSI_TERM = enable_ce_ ? M_ANSI_TERM_OLD : M_ANSI_TERM_NEW;
        logtype::strg FONT_TYPE = enable_bf_ ? M_FONT_BOLD : M_FONT_ORGD;

        m_reset = ANSI_TERM + FONT_TYPE + M_SEQ_ID[0] + M_CHAR_M;
        m_dark = ANSI_TERM + FONT_TYPE + M_SEQ_ID[1] + M_CHAR_M;
        m_red = ANSI_TERM + FONT_TYPE + M_SEQ_ID[2] + M_CHAR_M;
        m_green = ANSI_TERM + FONT_TYPE + M_SEQ_ID[3] + M_CHAR_M;
        m_yellow = ANSI_TERM + FONT_TYPE + M_SEQ_ID[4] + M_CHAR_M;
        m_blue = ANSI_TERM + FONT_TYPE + M_SEQ_ID[5] + M_CHAR_M;
        m_magenta = ANSI_TERM + FONT_TYPE + M_SEQ_ID[6] + M_CHAR_M;
        m_cyan = ANSI_TERM + FONT_TYPE + M_SEQ_ID[7] + M_CHAR_M;
        m_white = ANSI_TERM + FONT_TYPE + M_SEQ_ID[8] + M_CHAR_M;
    }

    /**
     * @brief Re-initializes color sequences, allowing runtime reconfiguration.
     *
     * @param enable_ce_  Whether to enable legacy terminal-compatible mode.
     * @param enable_ht_  Whether to enable terminal highlight rendering.
     * @param enable_bf_  Whether to enable bold font output.
     */
    void Colors::reinit(const logtype::boln &enable_ce_, const logtype::boln &enable_ht_,
                        const logtype::boln &enable_bf_) {
        init(enable_ce_, enable_ht_, enable_bf_);
    }

    /**
     * @brief Wraps a string with the given ANSI color escape sequences.
     *
     * @param color_  The ANSI color prefix string.
     * @param strline_  The text content to be colorized.
     * @param enable_ht_  Whether highlight rendering is enabled.
     *
     * @return The input string wrapped with color and reset sequences.
     */
    auto Colors::wrap(const logtype::strg &color_, const logtype::strg &strline_,
                      const logtype::boln &enable_ht_) -> logtype::strg {
        if (!enable_ht_ || !m_enable_term_highlight) {
            return strline_;
        }
        return color_ + strline_ + m_reset;
    }

    /// @brief Wraps text with dark (gray) color via wrap().
    auto Colors::d(const logtype::strg &strline_, const logtype::boln &enable_ht_) -> logtype::strg {
        return wrap(m_dark, strline_, enable_ht_);
    }

    /// @brief Wraps text with red color via wrap().
    auto Colors::r(const logtype::strg &strline_, const logtype::boln &enable_ht_) -> logtype::strg {
        return wrap(m_red, strline_, enable_ht_);
    }

    /// @brief Wraps text with green color via wrap().
    auto Colors::g(const logtype::strg &strline_, const logtype::boln &enable_ht_) -> logtype::strg {
        return wrap(m_green, strline_, enable_ht_);
    }

    /// @brief Wraps text with yellow color via wrap().
    auto Colors::y(const logtype::strg &strline_, const logtype::boln &enable_ht_) -> logtype::strg {
        return wrap(m_yellow, strline_, enable_ht_);
    }

    /// @brief Wraps text with blue color via wrap().
    auto Colors::b(const logtype::strg &strline_, const logtype::boln &enable_ht_) -> logtype::strg {
        return wrap(m_blue, strline_, enable_ht_);
    }

    /// @brief Wraps text with magenta color via wrap().
    auto Colors::m(const logtype::strg &strline_, const logtype::boln &enable_ht_) -> logtype::strg {
        return wrap(m_magenta, strline_, enable_ht_);
    }

    /// @brief Wraps text with cyan color via wrap().
    auto Colors::c(const logtype::strg &strline_, const logtype::boln &enable_ht_) -> logtype::strg {
        return wrap(m_cyan, strline_, enable_ht_);
    }

    /// @brief Wraps text with white color via wrap().
    auto Colors::w(const logtype::strg &strline_, const logtype::boln &enable_ht_) -> logtype::strg {
        return wrap(m_white, strline_, enable_ht_);
    }

} // namespace ruac::rstd::logsystem
