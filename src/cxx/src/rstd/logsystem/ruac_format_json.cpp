/**
 * C/C++ Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * Line Limit: Recommend line breaks at col: 96, force line breaks at col: 120
 * Date Time: 2026-07-18 20:36:24
 * Author: ohmycode-cn(ohcode@163.com)
 * Header File : include/rstd/logsystem/ruac_format_json.hpp
 * Source File : src/rstd/logsystem/ruac_format_json.cpp
 *
 * File Function Description:
 *
 *
 */

#include "rstd/logsystem/ruac_format_json.hpp"
#include "rstd/logsystem/ruac_logkeys.hpp"
#include "rstd/logsystem/ruac_logtype.hpp"
#include <sstream>

namespace ruac::rstd::logsystem {

    /**
     * @brief Formats a single JSON key-value pair line with indentation.
     *
     * @tparam V   Type of the value to format (e.g. strg, udll, sdit).
     * @param kmap_  Key-value map containing formatting tokens (quotes, colons, etc.).
     * @param key_   The JSON property name token (e.g. logkeys::maps::G_TIME).
     * @param val_   The value to be serialized into the JSON property.
     *
     * @return A formatted JSON property line as a string.
     *
     * @details e.g.
     * <space:8>"key":<space:1>"value",<next_line>
     */
    template <typename V>
    auto FormatJson::convenientFormat(const logtype::smap &kmap_,
                                      const logtype::strg &key_,
                                      const V &val_) -> logtype::strg {
        std::stringstream ss;
        ss << logkeys::maps::G_SPACE_08;
        ss << kmap_.at(logkeys::maps::G_QUOTE);
        ss << kmap_.at(key_);
        ss << kmap_.at(logkeys::maps::G_QUOTE);
        ss << kmap_.at(logkeys::maps::G_COLON);
        ss << logkeys::maps::G_SPACE_01;
        ss << kmap_.at(logkeys::maps::G_QUOTE);
        ss << val_;
        ss << kmap_.at(logkeys::maps::G_QUOTE);
        ss << kmap_.at(logkeys::maps::G_COMMA);
        ss << logkeys::maps::G_NEXT_LINE;
        return ss.str();
    }

    /**
     * @brief Formats a single log entry as a JSON object string.
     *
     * @param kmap_    Key-value map containing formatting tokens (quotes, colons, braces, etc.).
     * @param time_    Timestamp string used as the JSON object key and the TIME field value.
     * @param level_   Log level string (e.g. "INFO", "ERROR").
     * @param sequence_  Monotonically increasing sequence number for the log entry.
     * @param message_ The log message content.
     * @param file_    Source file name where the log was emitted.
     * @param line_    Source line number where the log was emitted.
     *
     * @return A formatted JSON object segment as a string, ready to be embedded
     *         in the parent log structure.
     *
     * @details e.g.
     * <space:4>"time":<space:1>{<next_line>
     * <space:4><space:4>"TIME":<space:1>"time_",<next_line>
     * <space:4><space:4>"LEVEL":<space:1>"level_",<next_line>
     * <space:4><space:4>"SEQUENCE":<space:1>sequence_,<next_line>
     * <space:4><space:4>"MESSAGE":<space:1>"message_",<next_line>
     * <space:4><space:4>"FILE":<space:1>"file_",<next_line>
     * <space:4><space:4>"LINE":<space:1>line_,<next_line>
     * <space:4>}<next_line>
     */
    auto FormatJson::format(const logtype::smap &kmap_,
                            const logtype::strg &time_,
                            const logtype::strg &level_,
                            const logtype::udll &sequence_,
                            const logtype::strg &message_,
                            const logtype::strg &file_,
                            const logtype::sdit &line_) -> logtype::strg {
        std::stringstream ss;

        // start.
        ss << logkeys::maps::G_SPACE_04;
        ss << kmap_.at(logkeys::maps::G_QUOTE);
        ss << time_;
        ss << kmap_.at(logkeys::maps::G_QUOTE);
        ss << kmap_.at(logkeys::maps::G_COLON);
        ss << logkeys::maps::G_SPACE_01;
        ss << kmap_.at(logkeys::maps::G_LEFT_BRACE);
        ss << logkeys::maps::G_NEXT_LINE;

        // time.
        ss << convenientFormat(kmap_, logkeys::maps::G_TIME, time_);
        // levels.
        ss << convenientFormat(kmap_, logkeys::maps::G_LEVEL, level_);
        // sequence.
        ss << convenientFormat(kmap_, logkeys::maps::G_SEQUENCE, sequence_);
        // message.
        ss << convenientFormat(kmap_, logkeys::maps::G_MESSAGE, message_);
        // file.
        ss << convenientFormat(kmap_, logkeys::maps::G_FILE, file_);
        // line.
        ss << convenientFormat(kmap_, logkeys::maps::G_LINE, line_);

        // endof.
        ss << logkeys::maps::G_SPACE_04;
        ss << kmap_.at(logkeys::maps::G_RIGHT_BRACE);
        ss << logkeys::maps::G_NEXT_LINE;
        return ss.str();
    }
} // namespace ruac::rstd::logsystem
