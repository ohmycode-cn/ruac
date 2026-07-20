/**
 * C/C++ Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * Line Limit: Recommend line breaks at col: 96, force line breaks at col: 120
 * Date Time: 2026-07-20 17:24:01
 * Author: ohmycode-cn(ohcode@163.com)
 * Header File : include/rstd/logsystem/ruac_logtoken_mapper.hpp
 * Source File : src/rstd/logsystem/ruac_logtoken_mapper.cpp
 *
 * File Function Description:
 *   Declares token-mapping factory functions for the RUAC log system.
 *   Provides two functions within the logtoken_mapper namespace:
 *   tokenmapHT builds a keyword-to-literal mapping table for terminal
 *   rendering (with configurable compatible, highlight, and bold-font
 *   modes), and tokenmapOL builds a mapping table for online-style
 *   (non-highlight) rendering. Both tables are consumed by the format
 *   pipeline during log-record serialization.
 */

#pragma once
#ifndef RUAC_LOGTOKEN_MAPPER_HPP
#define RUAC_LOGTOKEN_MAPPER_HPP

#include "rstd/logsystem/ruac_logtype.hpp"

namespace ruac::rstd::logsystem {

    namespace logtoken_mapper {

        /**
         * @brief Builds a keyword-to-literal mapping table for terminal
         *        rendering with configurable compatible, highlight, and
         *        bold-font modes.
         */
        auto tokenmapHT(const logtype::boln &enable_ce_ = true, const logtype::boln &enable_ht_ = true,
                        const logtype::boln &enable_bf_ = false) -> logtype::smap;

        /**
         * @brief Builds a keyword-to-literal mapping table for online-style
         *        (non-highlight) rendering.
         */
        auto tokenmapOL() -> logtype::smap;

    } // namespace logtoken_mapper

} // namespace ruac::rstd::logsystem

#endif // RUAC_LOGTOKEN_MAPPER_HPP
