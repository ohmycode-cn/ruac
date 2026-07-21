/**
 * C/C++ Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * Line Limit: Recommend line breaks at col: 96, force line breaks at col: 120
 * Date Time: 2026-07-20 20:24:09
 * Author: ohmycode-cn(ohcode@163.com)
 * Header File : include/rstd/logsystem/ruac_logger.hpp
 * Source File : src/rstd/logsystem/ruac_logger.cpp
 *
 * File Function Description:
 *   Declares the Logger class, the top-level entry point of the RUAC log
 *   system.  Logger owns a raw-pointer Factory and a Config instance.
 *   On the first init() call it loads the configuration file, creates the
 *   Factory, and stores the resulting confmap.  Subsequent init() calls
 *   perform a terminal-side hot reload only: the format style (text / json /
 *   xml), rendering flags (compatible, highlight, bold-font), and the
 *   terminal-output toggle can all be changed at runtime, while the file-
 *   sink chain and the overall output-mode setting remain fixed.
 *
 */

#pragma once
#ifndef RUAC_LOGGER_HPP
#define RUAC_LOGGER_HPP

#include "rstd/logsystem/ruac_logenum.hpp"
#include "rstd/logsystem/ruac_logtype.hpp"
#include "rstd/logsystem/ruac_logstc.hpp"
#include "rstd/logsystem/ruac_config.hpp"
#include "rstd/logsystem/ruac_factory.hpp"

namespace ruac::rstd::logsystem {

    /**
     * @brief Top-level log system entry point.  Owns a Factory (raw pointer)
     *        and a Config instance.  Supports terminal-side hot reload via
     *        repeated init() calls.
     */
    class Logger {
      private:
        Factory *m_factory{nullptr};
        Config m_config;
        logtype::smap m_confmap;

      public:
        Logger() = default;
        ~Logger();

      public:
        void write(const logenum::Level level_, const logtype::strg &message_, const logtype::strg &file_,
                   const logtype::sdit line_);
        void init(const LogParamList &params_ = {});
    }; // class Logger

} // namespace ruac::rstd::logsystem

#endif // RUAC_LOGGER_HPP
