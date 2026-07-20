/**
 * C/C++ Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * Line Limit: Recommend line breaks at col: 96, force line breaks at col: 120
 * Date Time: 2026-07-18 20:36:16
 * Author: ohmycode-cn(ohcode@163.com)
 * Header File : include/rstd/logsystem/ruac_format_text.hpp
 * Source File : src/rstd/logsystem/ruac_format_text.cpp
 *
 * File Function Description:
 *
 *
 */

#include "rstd/logsystem/ruac_format_text.hpp"
#include "rstd/logsystem/ruac_logkeys.hpp"
#include "rstd/logsystem/ruac_logtype.hpp"
#include <sstream>

namespace ruac::rstd::logsystem {

    /**
     * @brief Formats a single log entry as a plain-text line pair.
     *
     * @param kmap_    Key-value map containing formatting tokens (colons, braces, etc.).
     * @param time_    Timestamp string for the log entry header.
     * @param level_   Log level string (e.g. "INFO", "ERROR", ....).
     * @param sequence_  Monotonically increasing sequence number for the log entry.
     * @param message_ The log message content.
     * @param file_    Source file name where the log was emitted.
     * @param line_    Source line number where the log was emitted.
     *
     * @return A formatted plain-text log segment as a string.
     *
     * @details e.g.
     * time level sequence line:file<next_line>
     * <space:8>{MESSAGE}:<space:1>message
     */
    auto FormatText::format(const logtype::smap &kmap_,
                            const logtype::strg &time_,
                            const logtype::strg &level_,
                            const logtype::udll &sequence_,
                            const logtype::strg &message_,
                            const logtype::strg &file_,
                            const logtype::sdit &line_) -> logtype::strg {
        std::stringstream ss;

        ss << time_;
        ss << logkeys::tokens::G_SPACE_01;
        ss << level_;
        ss << logkeys::tokens::G_SPACE_01;
        ss << sequence_;
        ss << logkeys::tokens::G_SPACE_01;
        ss << line_;
        ss << kmap_.at(logkeys::tokens::G_COLON);
        ss << file_;
        ss << logkeys::tokens::G_NEXT_LINE;
        ss << logkeys::tokens::G_SPACE_08;
        ss << kmap_.at(logkeys::tokens::G_LEFT_BRACE);
        ss << kmap_.at(logkeys::tokens::G_MESSAGE);
        ss << kmap_.at(logkeys::tokens::G_RIGHT_BRACE);
        ss << kmap_.at(logkeys::tokens::G_COLON);
        ss << logkeys::tokens::G_SPACE_01;
        ss << message_;
        return ss.str();
    }
} // namespace ruac::rstd::logsystem
