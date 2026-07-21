/**
 * C/C++ Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * Line Limit: Recommend line breaks at col: 96, force line breaks at col: 120
 * Date Time: 2026-07-20 17:19:01
 * Author: ohmycode-cn(ohcode@163.com)
 * Header File : include/rstd/logsystem/ruac_config.hpp
 * Source File : src/rstd/logsystem/ruac_config.cpp
 *
 * File Function Description:
 *   Declares the Config class and LogParamOverride struct for the RUAC log
 *   system. Config provides methods to load configuration from a file and
 *   reset terminal rendering parameters. LogParamOverride aggregates optional
 *   override values for terminal display options (compatible, highlight, bold,
 *   output, and format style) used when re-initializing the terminal config.
 */

#pragma once
#ifndef RUAC_CONFIG_HPP
#define RUAC_CONFIG_HPP

#include "rstd/logsystem/ruac_logtype.hpp"
#include "rstd/logsystem/ruac_logstc.hpp"
#include <optional>

namespace ruac::rstd::logsystem {

    namespace {

        /**
         * @brief Aggregates optional override values for terminal display
         *        parameters, used when re-initializing the terminal config.
         */
        struct LogParamOverride {
            std::optional<logtype::boln> m_enable_term_ce;
            std::optional<logtype::boln> m_enable_term_ht;
            std::optional<logtype::boln> m_enable_term_bf;
            std::optional<logtype::boln> m_enable_term_ot;
            std::optional<logtype::strg> m_format_term_sl;
        };

    } // namespace

    /**
     * @brief Provides methods to load log system configuration from a file
     *        and to reset terminal rendering parameters with optional overrides.
     */
    class Config {
      private:
        logtype::boln m_once_lock{false};

      public:
        Config() = default;
        ~Config() = default;

      public:
        auto fromFileGetConfigMap(const logtype::strg &rfpath_, const logtype::strg &rfname_) -> logtype::smap;
        auto resetTermConfigMap(const LogParamOverride &ov_ops_ = {}) -> LogParamList;

    }; // class Config

} // namespace ruac::rstd::logsystem

#endif // RUAC_CONFIG_HPP
