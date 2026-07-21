/**
 * C/C++ Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * Line Limit: Recommend line breaks at col: 96, force line breaks at col: 120
 * Date Time: 2026-07-21 15:00:44
 * Author: ohmycode-cn(ohcode@163.com)
 * Header File : include/rlib/log/ruac_log_runtime.hpp
 * Source File : src/rlib/log/ruac_log_runtime.cpp
 *
 * File Function Description:
 *
 *
 */

#pragma once
#ifndef RUAC_LOG_RUNTIME_HPP
#define RUAC_LOG_RUNTIME_HPP

#include "rstd/logsystem/ruac_logger.hpp"

namespace ruac::rlib::log {

    /**
     * @brief
     */
    class Runtime {
      private:
        Runtime() = default;
        ~Runtime() = default;
        Runtime(const Runtime &) = delete;
        Runtime &operator=(const Runtime &) = delete;

      private:
        ruac::rstd::logsystem::Logger m_logger;

      public:
        static auto obtain() -> Runtime &;
        auto get() -> ruac::rstd::logsystem::Logger &;
    }; // class Runtime

} // namespace ruac::rlib::log

#define RUAC_LOG_RUNTIME(level_, message_) ruac::rlib::log::Runtime::obtain().get().write(level_, message_, __FILE__, __LINE__);
#define RUAC_LOG_RUNTIME_DEBUG(message_) RUAC_LOG_RUNTIME(ruac::rstd::logsystem::logenum::Level::DEBUG, message_)
#define RUAC_LOG_RUNTIME_INFO(message_) RUAC_LOG_RUNTIME(ruac::rstd::logsystem::logenum::Level::INFO, message_)
#define RUAC_LOG_RUNTIME_WARNING(message_) RUAC_LOG_RUNTIME(ruac::rstd::logsystem::logenum::Level::WARNING, message_)
#define RUAC_LOG_RUNTIME_ERROR(message_) RUAC_LOG_RUNTIME(ruac::rstd::logsystem::logenum::Level::ERROR, message_)
#define RUAC_LOG_RUNTIME_FATAL(message_) RUAC_LOG_RUNTIME(ruac::rstd::logsystem::logenum::Level::FATAL, message_)

#endif // RUAC_LOG_RUNTIME_HPP
