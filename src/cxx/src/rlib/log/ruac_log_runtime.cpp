/**
 * C/C++ Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * Line Limit: Recommend line breaks at col: 96, force line breaks at col: 120
 * Date Time: 2026-07-21 15:00:44
 * Author: ohmycode-cn(ohcode@163.com)
 * Header File : include/rlib/log/ruac_log_runtime.hpp
 * Source File : src/rlib/log/ruac_log_runtime.cpp
 *
 * File Function Description:
 *   Implements the Runtime singleton.  obtain() returns a file-scope static
 *   Runtime reference (Meyers' singleton); the Logger held inside is
 *   lazily initialized via std::call_once on the first access so that
 *   configuration loading and Factory creation happen exactly once, even
 *   under concurrent access.  get() simply exposes the Logger reference
 *   for downstream write() / hot-reload calls.
 *
 */

#include "rlib/log/ruac_log_runtime.hpp"
#include <mutex>

namespace ruac::rlib::log {

    /**
     * @brief Returns the process-wide Runtime singleton.  The Logger is
     *        initialized exactly once via std::call_once.
     */
    auto Runtime::obtain() -> Runtime & {
        static Runtime instance;
        static std::once_flag init_flag;
        std::call_once(init_flag, [&]() { instance.m_logger.init(); });
        return instance;
    }

    /**
     * @brief Returns a reference to the Logger owned by this singleton.
     */
    auto Runtime::get() -> ruac::rstd::logsystem::Logger & {
        return m_logger;
    }

} // namespace ruac::rlib::log
