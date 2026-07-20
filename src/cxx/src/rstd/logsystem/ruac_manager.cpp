/**
 * C/C++ Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * Line Limit: Recommend line breaks at col: 96, force line breaks at col: 120
 * Date Time: 2026-07-20 13:18:52
 * Author: ohmycode-cn(ohcode@163.com)
 * Header File : include/rstd/logsystem/ruac_manager.hpp
 * Source File : src/rstd/logsystem/ruac_manager.cpp
 *
 * File Function Description:
 *   Implements the Manager class for the RUAC log system. Provides seven
 *   anonymous-namespace helpers: setBool() for boolean config parsing,
 *   setLevel() for log-level enum mapping, setFormat() for format-mode
 *   selection, setOutput() for output-target selection, setString() for
 *   string assignment, setColoredMap() for ANSI-colored keyword-map
 *   generation, and tm() as a timestamp accessor. The public Manager
 *   interface coordinates initialization, resource cleanup, runtime
 *   reconfiguration, and multi-sink log dispatch with per-level sequencing.
 */

#include "rstd/logsystem/ruac_logkeys.hpp"
#include "rstd/logsystem/ruac_output_console.hpp"
#include "rstd/logsystem/ruac_output_file.hpp"
#include "rstd/logsystem/ruac_format_text.hpp"
#include "rstd/logsystem/ruac_format_json.hpp"
#include "rstd/logsystem/ruac_format_xml.hpp"
#include "rstd/logsystem/ruac_logenum.hpp"
#include "rstd/logsystem/ruac_logtype.hpp"
#include "rstd/logsystem/ruac_manager.hpp"
#include "rstd/logsystem/ruac_logtime.hpp"
#include "rstd/logsystem/ruac_colors.hpp"

namespace ruac::rstd::logsystem {

    namespace {

        /**
         * @brief Parses a string value and sets a boolean configuration member.
         *
         * @param mbr_  Reference to the boolean member to set.
         * @param key_  The string value to parse ("true" or other).
         */
        void setBool(logtype::boln &mbr_, logtype::strg key_) {
            ("true" == key_) ? mbr_ = true : mbr_ = false;
        }

        /**
         * @brief Parses a string value and sets a log-level enum member.
         *
         * Maps "info", "warning", "error", "fatal" to corresponding levels.
         * Defaults to INFO for unrecognized values.
         *
         * @param mbr_  Reference to the Level enum member to set.
         * @param key_  The string value to parse.
         */
        void setLevel(logenum::Level &mbr_, const logtype::strg &key_) {
            if ("info" == key_) {
                mbr_ = logenum::Level::INFO;
            } else if ("warning" == key_) {
                mbr_ = logenum::Level::WARNING;
            } else if ("error" == key_) {
                mbr_ = logenum::Level::ERROR;
            } else if ("fatal" == key_) {
                mbr_ = logenum::Level::FATAL;
            } else {
                mbr_ = logenum::Level::INFO;
            }
        }

        /**
         * @brief Parses a string value and sets a format-mode enum member.
         *
         * Maps "json", "xml" to corresponding formats.
         * Defaults to TEXT for unrecognized values.
         *
         * @param mbr_  Reference to the Format enum member to set.
         * @param key_  The string value to parse.
         */
        void setFormat(logenum::Format &mbr_, const logtype::strg &key_) {
            if ("json" == key_) {
                mbr_ = logenum::Format::JSON;
            } else if ("xml" == key_) {
                mbr_ = logenum::Format::XML;
            } else {
                mbr_ = logenum::Format::TEXT;
            }
        }

        /**
         * @brief Parses a string value and sets an output-target enum member.
         *
         * Maps "file", "both" to corresponding targets.
         * Defaults to CONSOLE for unrecognized values.
         *
         * @param mbr_  Reference to the Output enum member to set.
         * @param key_  The string value to parse.
         */
        void setOutput(logenum::Output &mbr_, const logtype::strg &key_) {
            if ("file" == key_) {
                mbr_ = logenum::Output::FILE;
            } else if ("both" == key_) {
                mbr_ = logenum::Output::BOTH;
            } else {
                mbr_ = logenum::Output::CONSOLE;
            }
        }

        /**
         * @brief Assigns a string value to a configuration member.
         *
         * @param mbr_  Reference to the string member to set.
         * @param key_  The string value to assign.
         */
        void setString(logtype::strg &mbr_, const logtype::strg &key_) {
            mbr_ = key_;
        }

        /**
         * @brief Generates an ANSI-colored keyword map for terminal output.
         *
         * Creates a Colors instance with the specified rendering options and
         * builds a map with colored versions of all log keywords, delimiters,
         * and field names.
         *
         * @param mbr_  Reference to the map to populate with colored entries.
         * @param enable_ce_  Enable legacy terminal-compatible mode.
         * @param enable_ht_  Enable terminal highlight rendering.
         * @param enable_bf_  Enable bold font output.
         */
        void setColoredMap(logtype::smap &mbr_, const logtype::boln &enable_ce_, const logtype::boln &enable_ht_,
                           const logtype::boln &enable_bf_) {
            Colors cr(enable_ce_, enable_ht_, enable_bf_);
            mbr_.clear();
            mbr_ = {
                {logkeys::maps::G_LEFT_BRACE, cr.y("{")},
                {logkeys::maps::G_RIGHT_BRACE, cr.y("}")},
                {logkeys::maps::G_LEFT_SQUARE_BRACKET, cr.m("[")},
                {logkeys::maps::G_RIGHT_SQUARE_BRACKET, cr.m("]")},
                {logkeys::maps::G_LEFT_PARENTHESIS, cr.m("(")},
                {logkeys::maps::G_RIGHT_PARENTHESIS, cr.m(")")},
                {logkeys::maps::G_SEQUENCE, cr.y("SEQUENCE")},
                {logkeys::maps::G_TIME, cr.r("TIME")},
                {logkeys::maps::G_LEVEL, cr.m("LEVEL")},
                {logkeys::maps::G_MESSAGE, cr.g("MESSAGE")},
                {logkeys::maps::G_FILE, cr.b("FILE")},
                {logkeys::maps::G_LINE, cr.c("LINE")},
                {logkeys::maps::G_COLON, cr.w(":")},
                {logkeys::maps::G_COMMA, cr.r(",")},
                {logkeys::maps::G_EQUAL, cr.w("=")},
                {logkeys::maps::G_QUOTE, cr.y("\"")},
                {logkeys::maps::G_GT, cr.c(">")},
                {logkeys::maps::G_LT, cr.c("<")},
                {logkeys::maps::G_SLASH, cr.r("/")},
                {logkeys::maps::G_QUESTION, cr.d("?")},
                {logkeys::maps::G_DEBUG, cr.d("DEBUG")},
                {logkeys::maps::G_INFO, cr.c("INFO")},
                {logkeys::maps::G_WARNING, cr.y("WARNING")},
                {logkeys::maps::G_ERROR, cr.m("ERROR")},
                {logkeys::maps::G_FATAL, cr.r("FATAL")},
                {logkeys::maps::G_XML_RECORD, cr.b("record")},
                {logkeys::maps::G_XML_TIME, cr.r("time")},
                {logkeys::maps::G_XML_LEVEL, cr.y("level")},
                {logkeys::maps::G_XML_MESSAGE, cr.g("message")},
                {logkeys::maps::G_XML_SEQUENCE, cr.y("sequence")},
                {logkeys::maps::G_XML_FILE, cr.b("file")},
                {logkeys::maps::G_XML_LINE, cr.c("line")}};
        }

        /**
         * @brief Returns the current formatted timestamp string.
         *
         * @return A formatted local-time string in "YYYY-MM-DD-HH-MM-SS" format.
         */
        auto tm() -> logtype::strg {
            return logtime::safeTimeString26();
        }

    } // namespace

    /// Static flag to ensure file path/name are set only once across instances.
    logtype::boln Manager::m_is_once_lock{false};

    /**
     * @brief Constructs a Manager and initializes from the configuration map.
     *
     * @param confmap_  Parsed configuration key-value pairs.
     */
    Manager::Manager(const logtype::smap &confmap_) {
        m_confmap = confmap_;
        initMbr();
        init();
    }

    /**
     * Destroys the Manager and releases all allocated resources.
     */
    Manager::~Manager() {
        over();
    }

    /**
     * @brief Increments a per-level sequence counter.
     *
     * @param seq_  Reference to the counter to increment.
     */
    void Manager::counter(logtype::udll &seq_) {
        seq_++;
    }

    /**
     * Initializes member variables from the configuration map.
     *
     * Parses boolean flags, log levels, format modes, output targets,
     * and file paths. Generates colored keyword map if highlighting is enabled.
     */
    void Manager::initMbr() {
        setBool(m_enable_term_compatible, m_confmap.at(logkeys::words::G_ENABLE_TERM_COMPATIBLE_MODE));
        setBool(m_enable_term_highlight, m_confmap.at(logkeys::words::G_ENABLE_TERM_HIGHLIGHT_MODE));
        setBool(m_enable_term_bold_font, m_confmap.at(logkeys::words::G_ENABLE_TERM_BOLD_FONT_MODE));
        setBool(m_enable_term_log_print, m_confmap.at(logkeys::words::G_ENABLE_TERM_LOG_PRINT_MODE));
        setLevel(m_term_log_level, m_confmap.at(logkeys::words::G_LOG_TERM_LEVEL_FILTER));
        setLevel(m_file_log_level, m_confmap.at(logkeys::words::G_LOG_FILE_LEVEL_FILTER));
        setLevel(m_log_min_level, m_confmap.at(logkeys::words::G_LOG_MIN_LEVEL_FILTER));
        setFormat(m_term_format, m_confmap.at(logkeys::words::G_LOG_TERM_FORMAT_MODE));
        setFormat(m_file_format, m_confmap.at(logkeys::words::G_LOG_FILE_FORMAT_MODE));
        if (!m_is_once_lock) {
            setString(m_write_file_path, m_confmap.at(logkeys::words::G_LOG_WRITE_PATH));
            setString(m_write_file_name, m_confmap.at(logkeys::words::G_LOG_WRITE_FILE));
            m_is_once_lock = true;
        }
        if (m_enable_term_highlight) {
            setColoredMap(m_map_clr, m_enable_term_compatible, m_enable_term_highlight,
                          m_enable_term_bold_font);
        } else {
            m_map_clr = logkeys::maps::G_KW_MAP_TEMPLATE;
        }
    }

    /**
     * Initializes Format and Output polymorphic instances based on configuration.
     *
     * Creates console/file output sinks and format renderers according to
     * the configured output target and format mode. Uses raw pointers for
     * performance (see header note).
     */
    void Manager::init() {

        switch (m_log_output) {
        case logenum::Output::FILE:
            if (nullptr == m_ptr_file_output && !m_ptr_output_once_lock) {
                m_ptr_file_output = new OutputFile(m_write_file_path, m_write_file_name);
                m_ptr_output_once_lock = true;
            }
            break;
        case logenum::Output::BOTH:
            if (nullptr == m_ptr_file_output && !m_ptr_output_once_lock) {
                m_ptr_file_output = new OutputFile(m_write_file_path, m_write_file_name);
                m_ptr_output_once_lock = true;
            }
            if (nullptr == m_ptr_term_output) {
                m_ptr_term_output = new OutputConsole();
            }
            break;
        default:
            if (nullptr == m_ptr_term_output) {
                m_ptr_term_output = new OutputConsole();
            }
            break;
        }

        if (nullptr == m_ptr_term_format) {
            switch (m_term_format) {
            case logenum::Format::JSON:
                m_ptr_term_format = new FormatJson();
                break;
            case logenum::Format::XML:
                m_ptr_term_format = new FormatXML();
                break;
            default:
                m_ptr_term_format = new FormatText();
                break;
            }
        }

        if (nullptr == m_ptr_file_output && !m_ptr_output_once_lock) {
            switch (m_file_format) {
            case logenum::Format::JSON:
                m_ptr_file_format = new FormatJson();
                break;
            case logenum::Format::XML:
                m_ptr_file_format = new FormatXML();
                break;
            default:
                m_ptr_file_format = new FormatText();
                break;
            }
            m_ptr_format_once_lock = true;
        }
    }

    /**
     * Releases all allocated Format and Output instances.
     *
     * Deletes console and file output sinks and format renderers,
     * setting pointers to nullptr after deletion.
     */
    void Manager::over() {
        if (nullptr != m_ptr_term_output) {
            delete m_ptr_term_output;
            m_ptr_term_output = nullptr;
        }
        if (nullptr != m_ptr_file_output) {
            delete m_ptr_file_output;
            m_ptr_file_output = nullptr;
        }
        if (nullptr != m_ptr_term_format) {
            delete m_ptr_term_format;
            m_ptr_term_format = nullptr;
        }
        if (nullptr != m_ptr_file_format) {
            delete m_ptr_file_format;
            m_ptr_file_format = nullptr;
        }
    }

    /**
     * Releases console-specific Format and Output instances.
     *
     * Used during runtime reconfiguration to clear console pointers
     * before reinitializing with new settings.
     */
    void Manager::overConsolePtr() {
        if (nullptr != m_ptr_term_format) {
            delete m_ptr_term_format;
            m_ptr_term_format = nullptr;
        }
        if (nullptr != m_ptr_term_output) {
            delete m_ptr_term_output;
            m_ptr_term_output = nullptr;
        }
    }

    /**
     * @brief Formats and outputs a log message through the specified sink.
     *
     * Uses the Format instance to render the log entry, then dispatches
     * it through the Output instance. Silently returns if either pointer
     * is null.
     *
     * @param format_  The Format instance to render the log entry.
     * @param output_  The Output instance to dispatch the rendered string.
     * @param map_  The keyword-to-literal mapping for formatting.
     * @param level_  The log level string (e.g., "DEBUG", "INFO").
     * @param sequence_  The per-level sequence number.
     * @param message_  The log message content.
     * @param file_  The source file name.
     * @param line_  The source line number.
     */
    void Manager::outLogStringStream(Format *format_, Output *output_, logtype::smap &map_, const logtype::strg &level_,
                                     const logtype::udll &sequence_, const logtype::strg &message_,
                                     const logtype::strg &file_, const logtype::sdit &line_) {
        if (nullptr == output_ || nullptr == format_) {
            return;
        }
        auto logstr = format_->format(
            map_,
            tm(),
            level_,
            sequence_,
            message_,
            file_,
            line_);
        output_->output(logstr);
    }

    /**
     * @brief Reconfigures console log format and rendering options at runtime.
     *
     * Releases existing console pointers, updates configuration, and
     * reinitializes console output with new settings.
     *
     * @param enable_ce_  Enable legacy terminal-compatible mode.
     * @param enable_ht_  Enable terminal highlight rendering.
     * @param enable_bf_  Enable bold font output.
     * @param enanle_tr_  Enable terminal log printing.
     * @param format_tr_  The format mode string ("text", "json", "xml").
     * @param termlv_tr_  The terminal log level filter string.
     * @param min_level_  The minimum log level to output.
     */
    void Manager::reinitConsoleLogFormat(const logtype::boln &enable_ce_, const logtype::boln &enable_ht_,
                                         const logtype::boln &enable_bf_, const logtype::boln &enanle_tr_,
                                         const logtype::strg &format_tr_, const logtype::strg &termlv_tr_,
                                         const logenum::Level min_level_) {
        m_enable_term_compatible = enable_ce_;
        m_enable_term_highlight = enable_ht_;
        m_enable_term_bold_font = enable_bf_;
        m_enable_term_log_print = enanle_tr_;
        setFormat(m_term_format, format_tr_);
        setFormat(m_file_format, termlv_tr_);
        m_log_min_level = min_level_;
        overConsolePtr();
        init();
    }

    /**
     * @brief Writes a log message to configured output sinks.
     *
     * Dispatches the message to both terminal and file outputs (if configured)
     * with appropriate format and color settings. Increments the per-level
     * sequence counter after successful output. Silently returns if the
     * message level is below the minimum threshold.
     *
     * @param level_  The log level (DEBUG, INFO, WARNING, ERROR, FATAL).
     * @param message_  The log message content.
     * @param file_  The source file name where the log was emitted.
     * @param line_  The source line number where the log was emitted.
     */
    void Manager::write(logenum::Level level_, const logtype::strg &message_, const logtype::strg &file_,
                        const logtype::sdit &line_) {

        if (level_ < m_log_min_level) {
            return;
        }

        switch (level_) {
        case logenum::Level::DEBUG:
            outLogStringStream(m_ptr_term_format, m_ptr_term_output, m_map_clr,
                               m_map_clr.at(logkeys::maps::G_DEBUG), m_seq_debug,
                               message_, file_, line_);
            outLogStringStream(m_ptr_file_format, m_ptr_file_output, m_map_org,
                               m_map_org.at(logkeys::maps::G_DEBUG), m_seq_debug,
                               message_, file_, line_);
            counter(m_seq_debug);
            break;
        case logenum::Level::INFO:
            outLogStringStream(m_ptr_term_format, m_ptr_term_output, m_map_clr,
                               m_map_clr.at(logkeys::maps::G_INFO), m_seq_info,
                               message_, file_, line_);
            outLogStringStream(m_ptr_file_format, m_ptr_file_output, m_map_org,
                               m_map_org.at(logkeys::maps::G_INFO), m_seq_info,
                               message_, file_, line_);
            counter(m_seq_info);
            break;
        case logenum::Level::WARNING:
            outLogStringStream(m_ptr_term_format, m_ptr_term_output, m_map_clr,
                               m_map_clr.at(logkeys::maps::G_WARNING), m_seq_warning,
                               message_, file_, line_);
            outLogStringStream(m_ptr_file_format, m_ptr_file_output, m_map_org,
                               m_map_org.at(logkeys::maps::G_WARNING), m_seq_warning,
                               message_, file_, line_);
            counter(m_seq_warning);
            break;
        case logenum::Level::ERROR:
            outLogStringStream(m_ptr_term_format, m_ptr_term_output, m_map_clr,
                               m_map_clr.at(logkeys::maps::G_ERROR), m_seq_error,
                               message_, file_, line_);
            outLogStringStream(m_ptr_file_format, m_ptr_file_output, m_map_org,
                               m_map_org.at(logkeys::maps::G_ERROR), m_seq_error,
                               message_, file_, line_);
            counter(m_seq_error);
            break;
        case logenum::Level::FATAL:
            outLogStringStream(m_ptr_term_format, m_ptr_term_output, m_map_clr,
                               m_map_clr.at(logkeys::maps::G_FATAL), m_seq_fatal,
                               message_, file_, line_);
            outLogStringStream(m_ptr_file_format, m_ptr_file_output, m_map_org,
                               m_map_org.at(logkeys::maps::G_FATAL), m_seq_fatal,
                               message_, file_, line_);
            counter(m_seq_fatal);
            break;
        }
    }

} // namespace ruac::rstd::logsystem
