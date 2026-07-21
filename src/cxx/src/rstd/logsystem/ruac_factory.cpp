/**
 * C/C++ Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * Line Limit: Recommend line breaks at col: 96, force line breaks at col: 120
 * Date Time: 2026-07-20 20:56:51
 * Author: ohmycode-cn(ohcode@163.com)
 * Header File : include/rstd/logsystem/ruac_factory.hpp
 * Source File : src/rstd/logsystem/ruac_factory.cpp
 *
 * File Function Description:
 *   Implements the Factory class that owns raw pointers to Format and Output
 *   concrete objects. Parses the configuration map to determine output mode
 *   (console / file / both), format style (text / json / xml), level filters,
 *   and terminal rendering flags. Builds keyword-to-literal token maps for
 *   terminal and file sinks during construction, and routes each writer()
 *   call through the appropriate format → output pipeline with level gating.
 *
 */

#include "rstd/logsystem/ruac_factory.hpp"
#include "rstd/logsystem/ruac_logkeys.hpp"
#include "rstd/logsystem/ruac_logtoken_mapper.hpp"
#include "rstd/logsystem/ruac_logtime.hpp"
#include "rstd/logsystem/ruac_pathconf.hpp"
#include "rstd/logsystem/ruac_format_text.hpp"
#include "rstd/logsystem/ruac_format_json.hpp"
#include "rstd/logsystem/ruac_format_xml.hpp"
#include "rstd/logsystem/ruac_output_console.hpp"
#include "rstd/logsystem/ruac_output_file.hpp"

namespace ruac::rstd::logsystem {

    namespace {

        /**
         * @brief Parses a level string into a logenum::Level value.
         *
         * @param level_str_  The level string to parse (e.g., "debug", "info").
         *
         * @return The corresponding logenum::Level value.
         */
        auto parseLevel(const logtype::strg &level_str_) -> logenum::Level {
            if (level_str_ == logkeys::words::G_LOG_LEVEL_DEBUG)
                return logenum::Level::DEBUG;
            if (level_str_ == logkeys::words::G_LOG_LEVEL_INFO)
                return logenum::Level::INFO;
            if (level_str_ == logkeys::words::G_LOG_LEVEL_WARNING)
                return logenum::Level::WARNING;
            if (level_str_ == logkeys::words::G_LOG_LEVEL_ERROR)
                return logenum::Level::ERROR;
            if (level_str_ == logkeys::words::G_LOG_LEVEL_FATAL)
                return logenum::Level::FATAL;
            return logenum::Level::DEBUG;
        }

        /**
         * @brief Resolves a logenum::Level value to its rendered string form
         *        via the supplied token map.  Falls back to the raw token key
         *        when the key is absent from the map.
         *
         * @param level_  The log level to resolve.
         * @param kmap_  The keyword-to-literal mapping table.
         *
         * @return The rendered string form of the level.
         */
        auto levelToString(const logenum::Level &level_, const logtype::smap &kmap_) -> logtype::strg {
            logtype::strg key;
            switch (level_) {
            case logenum::Level::DEBUG:
                key = logkeys::tokens::G_DEBUG;
                break;
            case logenum::Level::INFO:
                key = logkeys::tokens::G_INFO;
                break;
            case logenum::Level::WARNING:
                key = logkeys::tokens::G_WARNING;
                break;
            case logenum::Level::ERROR:
                key = logkeys::tokens::G_ERROR;
                break;
            case logenum::Level::FATAL:
                key = logkeys::tokens::G_FATAL;
                break;
            default:
                key = logkeys::tokens::G_DEBUG;
                break;
            }
            auto it = kmap_.find(key);
            return (it != kmap_.end()) ? it->second : key;
        }

        /**
         * @brief Creates a concrete Format object from a mode string.
         *
         * @param mode_  The format mode string ("text", "json", "xml").
         *
         * @return A pointer to the newly created Format instance.
         */
        auto createFormat(const logtype::strg &mode_) -> Format * {
            if (mode_ == logkeys::words::G_JSON)
                return new FormatJson();
            if (mode_ == logkeys::words::G_XML)
                return new FormatXML();
            return new FormatText();
        }

        /**
         * @brief Returns true when level_ meets or exceeds filter_ severity.
         *
         * @param level_  The log level to check.
         * @param filter_  The minimum severity filter.
         *
         * @return true if level_ >= filter_, false otherwise.
         */
        auto levelPasses(const logenum::Level &level_, const logenum::Level &filter_) -> logtype::boln {
            return static_cast<int>(level_) >= static_cast<int>(filter_);
        }

        /**
         * @brief Extracts a string value from confmap with a fallback default.
         *
         * @param confmap_  The configuration map to search.
         * @param key_  The key to look up.
         * @param default_  The default value if key is not found.
         *
         * @return The value from confmap_ or default_ if not found.
         */
        auto confValue(const logtype::smap &confmap_, const logtype::strg &key_,
                       const logtype::strg &default_) -> logtype::strg {
            auto it = confmap_.find(key_);
            return (it != confmap_.end()) ? it->second : default_;
        }

    } // namespace

    /**
     * @brief Constructs a Factory by parsing confmap_ and allocating the
     *        appropriate Format / Output raw-pointer pairs.
     *
     * @param confmap_  The configuration map with log system parameters.
     */
    Factory::Factory(logtype::smap &confmap_) {
        auto output_mode = confValue(confmap_, logkeys::words::G_LOG_OUTPUT_MODE,
                                     logkeys::words::G_CONSOLE);
        auto term_fmt = confValue(confmap_, logkeys::words::G_LOG_TERM_FORMAT_MODE,
                                  logkeys::words::G_TEXT);
        auto file_fmt = confValue(confmap_, logkeys::words::G_LOG_FILE_FORMAT_MODE,
                                  logkeys::words::G_TEXT);

        m_term_level = parseLevel(
            confValue(confmap_, logkeys::words::G_LOG_TERM_LEVEL_FILTER,
                      logkeys::words::G_LOG_LEVEL_DEBUG));
        m_file_level = parseLevel(
            confValue(confmap_, logkeys::words::G_LOG_FILE_LEVEL_FILTER,
                      logkeys::words::G_LOG_LEVEL_DEBUG));
        m_min_level = parseLevel(
            confValue(confmap_, logkeys::words::G_LOG_MIN_LEVEL_FILTER,
                      logkeys::words::G_LOG_LEVEL_DEBUG));

        auto enable_ce = confValue(confmap_, logkeys::words::G_ENABLE_TERM_COMPATIBLE_MODE,
                                   logkeys::words::G_TRUE) == logkeys::words::G_TRUE;
        auto enable_ht = confValue(confmap_, logkeys::words::G_ENABLE_TERM_HIGHLIGHT_MODE,
                                   logkeys::words::G_FALSE) == logkeys::words::G_TRUE;
        auto enable_bf = confValue(confmap_, logkeys::words::G_ENABLE_TERM_BOLD_FONT_MODE,
                                   logkeys::words::G_FALSE) == logkeys::words::G_TRUE;

        m_term_kmap = logtoken_mapper::tokenmapHT(enable_ce, enable_ht, enable_bf);
        m_file_kmap = logtoken_mapper::tokenmapOL();

        if (output_mode == logkeys::words::G_CONSOLE || output_mode == logkeys::words::G_BOTH) {
            m_channels.m_term.m_fmt = createFormat(term_fmt);
            m_channels.m_term.m_out = new OutputConsole();
        }

        if (output_mode == logkeys::words::G_FILE || output_mode == logkeys::words::G_BOTH) {
            auto write_path = confValue(confmap_, logkeys::words::G_LOG_WRITE_PATH,
                                        pathconf::G_LOG_DEFAULT_WRITE_FILE_PATH);
            auto write_file = confValue(confmap_, logkeys::words::G_LOG_WRITE_FILE,
                                        pathconf::G_LOG_DEFAULT_WRITE_FILE_NAME);
            m_channels.m_file.m_fmt = createFormat(file_fmt);
            m_channels.m_file.m_out = new OutputFile(write_path, write_file);
        }

        for (auto &s : m_sequence) s = 0;
    }

    /**
     * @brief Destructor delegates to over() for raw-pointer cleanup.
     */
    Factory::~Factory() {
        over();
    }

    /**
     * @brief Placeholder — all initialization is performed in the constructor.
     */
    void Factory::init() {}

    /**
     * @brief Releases every raw pointer owned by m_channels and nullifies the slots.
     */
    void Factory::over() {
        delete m_channels.m_term.m_fmt;
        m_channels.m_term.m_fmt = nullptr;

        delete m_channels.m_term.m_out;
        m_channels.m_term.m_out = nullptr;

        delete m_channels.m_file.m_fmt;
        m_channels.m_file.m_fmt = nullptr;

        delete m_channels.m_file.m_out;
        m_channels.m_file.m_out = nullptr;
    }

    /**
     * @brief Hot-reloads terminal configuration: rebuilds the terminal token
     *        map and replaces the terminal Format / Output pointers.  Does
     *        NOT touch the file-sink chain or the output-mode setting.
     *
     * @param term_fmt_mode_  The terminal format mode string ("text", "json", "xml").
     * @param enable_ce_  Enable legacy terminal-compatible mode.
     * @param enable_ht_  Enable terminal highlight rendering.
     * @param enable_bf_  Enable bold font output.
     * @param enable_ot_  Enable terminal log output.
     */
    void Factory::reloadTermConfig(const logtype::strg &term_fmt_mode_, const logtype::boln &enable_ce_,
                                   const logtype::boln &enable_ht_, const logtype::boln &enable_bf_,
                                   const logtype::boln &enable_ot_) {
        m_term_kmap = logtoken_mapper::tokenmapHT(enable_ce_, enable_ht_, enable_bf_);

        if (enable_ot_) {
            delete m_channels.m_term.m_fmt;
            m_channels.m_term.m_fmt = createFormat(term_fmt_mode_);
            if (!m_channels.m_term.m_out) {
                m_channels.m_term.m_out = new OutputConsole();
            }
        } else {
            delete m_channels.m_term.m_fmt;
            m_channels.m_term.m_fmt = nullptr;
            delete m_channels.m_term.m_out;
            m_channels.m_term.m_out = nullptr;
        }
    }

    /**
     * @brief Formats a log record and dispatches it to the active output
     *        sinks, subject to level filtering.
     *
     * @param level_  The log level (DEBUG, INFO, WARNING, ERROR, FATAL).
     * @param message_  The log message content.
     * @param file_  The source file name where the log was emitted.
     * @param line_  The source line number where the log was emitted.
     */
    void Factory::write(const logenum::Level level_, const logtype::strg &message_, const logtype::strg &file_,
                        const logtype::sdit line_) {
        if (!levelPasses(level_, m_min_level)) {
            return;
        }

        auto time_str = logtime::safeTimeString26();
        auto level_idx = static_cast<int>(level_);
        auto seq = m_sequence[level_idx]++;

        if (m_channels.m_term.m_fmt && m_channels.m_term.m_out) {
            if (levelPasses(level_, m_term_level)) {
                auto level_str = levelToString(level_, m_term_kmap);
                auto msg = m_channels.m_term.m_fmt->format(
                    m_term_kmap, time_str, level_str, seq, message_, file_, line_);
                m_channels.m_term.m_out->output(msg);
            }
        }

        if (m_channels.m_file.m_fmt && m_channels.m_file.m_out) {
            if (levelPasses(level_, m_file_level)) {
                auto level_str = levelToString(level_, m_file_kmap);
                auto msg = m_channels.m_file.m_fmt->format(
                    m_file_kmap, time_str, level_str, seq, message_, file_, line_);
                m_channels.m_file.m_out->output(msg);
            }
        }
    }

} // namespace ruac::rstd::logsystem
