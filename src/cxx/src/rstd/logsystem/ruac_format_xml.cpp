/**
 * C/C++ Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * Line Limit: Recommend line breaks at col: 96, force line breaks at col: 120
 * Date Time: 2026-07-18 20:36:28
 * Author: ohmycode-cn(ohcode@163.com)
 * Header File : include/rstd/logsystem/ruac_format_xml.hpp
 * Source File : src/rstd/logsystem/ruac_format_xml.cpp
 *
 * File Function Description:
 *
 *
 */

#include "rstd/logsystem/ruac_format_xml.hpp"
#include "rstd/logsystem/ruac_logkeys.hpp"
#include "rstd/logsystem/ruac_logtype.hpp"
#include <sstream>

namespace ruac::rstd::logsystem {

    /**
     * @brief Formats a single XML element line with open/close tags and indentation.
     *
     * @tparam V   Type of the value to format (e.g. strg, udll, sdit).
     * @param kmap_  Key-value map containing formatting tokens (angle brackets, slash, etc.).
     * @param key_   The XML element name token (e.g. logkeys::tokens::G_XML_TIME).
     * @param val_   The value to be placed between the open and close tags.
     *
     * @return A formatted XML element line as a string.
     *
     * @details e.g.
     * <space:8><key>val</key>
     */
    template <typename V>
    auto FormatXML::convenientFormat(const logtype::smap &kmap_,
                                     const logtype::strg &key_,
                                     const V &val_) -> logtype::strg {
        std::stringstream ss;
        ss << logkeys::tokens::G_SPACE_08;
        ss << kmap_.at(logkeys::tokens::G_LT);
        ss << kmap_.at(key_);
        ss << kmap_.at(logkeys::tokens::G_GT);

        ss << val_;

        ss << kmap_.at(logkeys::tokens::G_LT);
        ss << kmap_.at(logkeys::tokens::G_SLASH);
        ss << kmap_.at(key_);
        ss << kmap_.at(logkeys::tokens::G_GT);
        return ss.str();
    }

    /**
     * @brief Formats a single log entry as an XML <record> element string.
     *
     * @param kmap_    Key-value map containing formatting tokens (angle brackets, slash, etc.).
     * @param time_    Timestamp string for the TIME child element.
     * @param level_   Log level string (e.g. "INFO", "ERROR") for the LEVEL child element.
     * @param sequence_  Monotonically increasing sequence number for the SEQUENCE child element.
     * @param message_ The log message content for the MESSAGE child element.
     * @param file_    Source file name for the FILE child element.
     * @param line_    Source line number for the LINE child element.
     *
     * @return A formatted XML <record> segment as a string, ready to be embedded
     *         in the parent log structure.
     *
     * @details e.g.
     * <space:4><record><next_line>
     * <space:4><space:4><time>time</time><next_line>
     * <space:4><space:4><level>level</level><next_line>
     * <space:4><space:4><sequence>sequence</sequence><next_line>
     * <space:4><space:4><message>message</message><next_line>
     * <space:4><space:4><file>file</file><next_line>
     * <space:4><space:4><line>line</line><next_line>
     * <space:4></record>
     */
    auto FormatXML::format(const logtype::smap &kmap_,
                           const logtype::strg &time_,
                           const logtype::strg &level_,
                           const logtype::udll &sequence_,
                           const logtype::strg &message_,
                           const logtype::strg &file_,
                           const logtype::sdit &line_) -> logtype::strg {
        std::stringstream ss;

        ss << logkeys::tokens::G_SPACE_04;
        ss << kmap_.at(logkeys::tokens::G_LT);
        ss << kmap_.at(logkeys::tokens::G_XML_RECORD);
        ss << kmap_.at(logkeys::tokens::G_GT);
        ss << logkeys::tokens::G_NEXT_LINE;

        // time.
        ss << convenientFormat(kmap_, logkeys::tokens::G_XML_TIME, time_);
        ss << logkeys::tokens::G_NEXT_LINE;

        // level.
        ss << convenientFormat(kmap_, logkeys::tokens::G_XML_LEVEL, level_);
        ss << logkeys::tokens::G_NEXT_LINE;

        // sequence.
        ss << convenientFormat(kmap_, logkeys::tokens::G_XML_SEQUENCE, sequence_);
        ss << logkeys::tokens::G_NEXT_LINE;

        // message.
        ss << convenientFormat(kmap_, logkeys::tokens::G_XML_MESSAGE, message_);
        ss << logkeys::tokens::G_NEXT_LINE;

        // file.
        ss << convenientFormat(kmap_, logkeys::tokens::G_XML_FILE, file_);
        ss << logkeys::tokens::G_NEXT_LINE;

        // line.
        ss << convenientFormat(kmap_, logkeys::tokens::G_XML_LINE, line_);
        ss << logkeys::tokens::G_NEXT_LINE;

        ss << logkeys::tokens::G_SPACE_04;
        ss << kmap_.at(logkeys::tokens::G_LT);
        ss << kmap_.at(logkeys::tokens::G_SLASH);
        ss << kmap_.at(logkeys::tokens::G_XML_RECORD);
        ss << kmap_.at(logkeys::tokens::G_GT);
        return ss.str();
    }
} // namespace ruac::rstd::logsystem
