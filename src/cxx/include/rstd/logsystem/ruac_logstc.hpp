/**
 * C/C++ Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * Line Limit: Recommend line breaks at col: 96, force line breaks at col: 120
 * Date Time: 2026-07-20 21:14:56
 * Author: ohmycode-cn(ohcode@163.com)
 * Header File : include/rstd/logsystem/ruac_logstc.hpp
 * Source File : src/rstd/logsystem/ruac_logstc.cpp
 *
 * File Function Description:
 *   Declares the LogParamList structure for the RUAC log system.
 *   Aggregates terminal display parameters (compatible mode, highlight,
 *   bold font, output toggle, and format style) with default-initialized
 *   values, serving as the canonical parameter bundle for log terminal
 *   configuration.
 */

#pragma once
#ifndef RUAC_LOGSTC_HPP
#define RUAC_LOGSTC_HPP

#include "rstd/logsystem/ruac_logtype.hpp"

namespace ruac::rstd::logsystem {

    /**
     * @brief Aggregates terminal display parameters with default-initialized
     *        values, serving as the canonical parameter bundle for log
     *        terminal configuration.
     */
    struct LogParamList {
        logtype::boln m_enable_term_ce{false};  // E. enable console compatible mode
        logtype::boln m_enable_term_ht{false};  // E. enable highlight highlight mode
        logtype::boln m_enable_term_bf{false};  // E. enable bold font mode
        logtype::boln m_enable_term_ot{false};  // E. enable console output log print mode
        logtype::strg m_format_term_sl{"text"}; // E. format log string style
    };

} // namespace ruac::rstd::logsystem

#endif // RUAC_LOGSTC_HPP
