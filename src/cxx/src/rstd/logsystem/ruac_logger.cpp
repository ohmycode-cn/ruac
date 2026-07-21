/**
 * C/C++ Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * Line Limit: Recommend line breaks at col: 96, force line breaks at col: 120
 * Date Time: 2026-07-20 20:24:09
 * Author: ohmycode-cn(ohcode@163.com)
 * Header File : include/rstd/logsystem/ruac_logger.hpp
 * Source File : src/rstd/logsystem/ruac_logger.cpp
 *
 * File Function Description:
 *   Implements the Logger class.  The first init() call loads the log
 *   configuration file via Config and creates the Factory with the full
 *   confmap (output mode, both format styles, level filters, rendering
 *   flags).  Every subsequent init(params) call is a terminal-side hot
 *   reload: only the terminal format style, rendering flags, and the
 *   terminal-output toggle are forwarded to Factory::reloadTermConfig();
 *   the file-sink chain and output-mode setting are never touched.
 *
 */

#include "rstd/logsystem/ruac_logger.hpp"

namespace ruac::rstd::logsystem {

    /**
     * @brief Destroys the owned Factory pointer.
     */
    Logger::~Logger() {
        delete m_factory;
        m_factory = nullptr;
    }

    /**
     * @brief Initializes (or hot-reloads) the log system.
     *
     * On the first call the configuration file is loaded via Config and a
     * new Factory is created with the resulting confmap.  On every later
     * call the terminal-side settings in params_ are forwarded to
     * Factory::reloadTermConfig(), allowing the format style, rendering
     * flags, and output toggle to be changed at runtime.  The file-sink
     * chain and the overall output-mode are never touched by hot reload.
     *
     * @param params_  Terminal display parameters for hot reload (optional).
     */
    void Logger::init(const LogParamList &params_) {
        if (!m_factory) {
            m_confmap = m_config.fromFileGetConfigMap("", "");
            m_factory = new Factory(m_confmap);
        } else {
            m_factory->reloadTermConfig(
                params_.m_format_term_sl,
                params_.m_enable_term_ce,
                params_.m_enable_term_ht,
                params_.m_enable_term_bf,
                params_.m_enable_term_ot);
        }
    }

    /**
     * @brief Delegates a log record to the owned Factory.
     *
     * @param level_  The log level (DEBUG, INFO, WARNING, ERROR, FATAL).
     * @param message_  The log message content.
     * @param file_  The source file name where the log was emitted.
     * @param line_  The source line number where the log was emitted.
     */
    void Logger::write(const logenum::Level level_, const logtype::strg &message_,
                       const logtype::strg &file_, const logtype::sdit line_) {
        if (m_factory) {
            m_factory->write(level_, message_, file_, line_);
        }
    }

} // namespace ruac::rstd::logsystem
