/**
 * C/C++ Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * Line Limit: Recommend line breaks at col: 96, force line breaks at col: 120
 * Date Time: 2026-07-17 22:24:48
 * Author: ohmycode-cn(ohcode@163.com)
 * Header File : include/rstd/logsystem/ruac_colors.hpp
 * Source File : src/rstd/logsystem/ruac_colors.cpp
 *
 * File Function Description:
 *
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
     * @brief Initializes all color escape sequences based on terminal capability flags.
     *
     * @param enable_ce_  Whether to enable legacy terminal-compatible mode.
     * @param enable_ht_  Whether to enable terminal highlight rendering.
     * @param enable_bf_  Whether to enable bold font output.
     */
    void Colors::init(const logtype::boln &enable_ce_, const logtype::boln &enable_ht_,
                      const logtype::boln &enable_bf_) {
        m_enable_term_compatible = enable_ce_;
        m_enable_term_highlight = enable_ht_;
        m_enable_term_bold_font = enable_bf_;

        logtype::strg ANSI_TERM = m_enable_term_compatible ? M_ANSI_TERM_OLD : M_ANSI_TERM_NEW;
        logtype::strg FONT_TYPE = m_enable_term_bold_font ? M_FONT_BOLD : M_FONT_ORGD;

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
    void Colors::overloadInit(const logtype::boln &enable_ce_, const logtype::boln &enable_ht_,
                              const logtype::boln &enable_bf_) {
        init(enable_ce_, enable_ht_, enable_bf_);
    }

    /**
     * @brief Wraps a string with dark (gray) ANSI color escape sequences.
     *
     * @param strline_  The text content to be colorized.
     * @param enable_ht_  Whether highlight rendering is enabled.
     *
     * @return The input string wrapped with dark color and reset sequences.
     */
    auto Colors::d(const logtype::strg &strline_, const logtype::boln &enable_ht_) -> logtype::strg {
        if (!enable_ht_ || !m_enable_term_highlight) {
            return strline_;
        }
        return m_dark + strline_ + m_reset;
    }

    /**
     * @brief Wraps a string with red ANSI color escape sequences.
     *
     * @param strline_  The text content to be colorized.
     * @param enable_ht_  Whether highlight rendering is enabled.
     *
     * @return The input string wrapped with red color and reset sequences.
     */
    auto Colors::r(const logtype::strg &strline_, const logtype::boln &enable_ht_) -> logtype::strg {
        if (!enable_ht_ || !m_enable_term_highlight) {
            return strline_;
        }
        return m_red + strline_ + m_reset;
    }

    /**
     * @brief Wraps a string with green ANSI color escape sequences.
     *
     * @param strline_  The text content to be colorized.
     * @param enable_ht_  Whether highlight rendering is enabled.
     *
     * @return The input string wrapped with green color and reset sequences.
     */
    auto Colors::g(const logtype::strg &strline_, const logtype::boln &enable_ht_) -> logtype::strg {
        if (!enable_ht_ || !m_enable_term_highlight) {
            return strline_;
        }
        return m_green + strline_ + m_reset;
    }

    /**
     * @brief Wraps a string with yellow ANSI color escape sequences.
     *
     * @param strline_  The text content to be colorized.
     * @param enable_ht_  Whether highlight rendering is enabled.
     *
     * @return The input string wrapped with yellow color and reset sequences.
     */
    auto Colors::y(const logtype::strg &strline_, const logtype::boln &enable_ht_) -> logtype::strg {
        if (!enable_ht_ || !m_enable_term_highlight) {
            return strline_;
        }
        return m_yellow + strline_ + m_reset;
    }

    /**
     * @brief Wraps a string with blue ANSI color escape sequences.
     *
     * @param strline_  The text content to be colorized.
     * @param enable_ht_  Whether highlight rendering is enabled.
     *
     * @return The input string wrapped with blue color and reset sequences.
     */
    auto Colors::b(const logtype::strg &strline_, const logtype::boln &enable_ht_) -> logtype::strg {
        if (!enable_ht_ || !m_enable_term_highlight) {
            return strline_;
        }
        return m_blue + strline_ + m_reset;
    }

    /**
     * @brief Wraps a string with magenta ANSI color escape sequences.
     *
     * @param strline_  The text content to be colorized.
     * @param enable_ht_  Whether highlight rendering is enabled.
     *
     * @return The input string wrapped with magenta color and reset sequences.
     */
    auto Colors::m(const logtype::strg &strline_, const logtype::boln &enable_ht_) -> logtype::strg {
        if (!enable_ht_ || !m_enable_term_highlight) {
            return strline_;
        }
        return m_magenta + strline_ + m_reset;
    }

    /**
     * @brief Wraps a string with cyan ANSI color escape sequences.
     *
     * @param strline_  The text content to be colorized.
     * @param enable_ht_  Whether highlight rendering is enabled.
     *
     * @return The input string wrapped with cyan color and reset sequences.
     */
    auto Colors::c(const logtype::strg &strline_, const logtype::boln &enable_ht_) -> logtype::strg {
        if (!enable_ht_ || !m_enable_term_highlight) {
            return strline_;
        }
        return m_cyan + strline_ + m_reset;
    }

    /**
     * @brief Wraps a string with white ANSI color escape sequences.
     *
     * @param strline_  The text content to be colorized.
     * @param enable_ht_  Whether highlight rendering is enabled.
     *
     * @return The input string wrapped with white color and reset sequences.
     */
    auto Colors::w(const logtype::strg &strline_, const logtype::boln &enable_ht_) -> logtype::strg {
        if (!enable_ht_ || !m_enable_term_highlight) {
            return strline_;
        }
        return m_white + strline_ + m_reset;
    }

} // namespace ruac::rstd::logsystem
