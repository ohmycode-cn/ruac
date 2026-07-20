/**
 * C/C++ Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * Line Limit: Recommend line breaks at col: 96, force line breaks at col: 120
 * Date Time: 2026-07-17 21:19:53
 * Author: ohmycode-cn(ohcode@163.com)
 * Header File : include/rstd/logsystem/ruac_logkeys.hpp
 * Source File : src/rstd/logsystem/ruac_logkeys.cpp
 *
 * File Function Description:
 *   Centralizes constant string keys and token definitions for the RUAC log
 *   system configuration and log-record formatting pipeline.
 *   The logkeys::words namespace declares compile-time constant keys for
 *   configuration-file directives (e.g., output mode, format mode, terminal
 *   rendering flags) and literal token values (delimiters, boolean literals,
 *   output-target and format-type identifiers) consumed by the config parser.
 *   The logkeys::maps namespace defines whitespace padding constants, named
 *   punctuation / syntax tokens, and structured-log field-name identifiers
 *   (sequence, time, level, message, file, line). A master keyword-to-literal
 *   mapping template (G_KW_MAP_TEMPLATE) is provided as the canonical lookup
 *   table that resolves symbolic token names to their rendered character
 *   representations during log-format expansion and serialization.
 */

#pragma once
#ifndef RUAC_LOGKEYS_HPP
#define RUAC_LOGKEYS_HPP

#include "rstd/logsystem/ruac_logtype.hpp"

namespace ruac::rstd::logsystem {

    namespace logkeys {

        namespace words {

            const logtype::strg G_ENABLE_TERM_COMPATIBLE_MODE{"ENABLE_TERM_COMPATIBLE_MODE"};
            const logtype::strg G_ENABLE_TERM_HIGHLIGHT_MODE{"ENABLE_TERM_HIGHLIGHT_MODE"};
            const logtype::strg G_ENABLE_TERM_BOLD_FONT_MODE{"ENABLE_TERM_BOLD_FONT_MODE"};
            const logtype::strg G_LOG_TERM_FORMAT_MODE{"LOG_TERM_FORMAT_MODE"};
            const logtype::strg G_LOG_FILE_FORMAT_MODE{"LOG_FILE_FORMAT_MODE"};
            const logtype::strg G_LOG_OUTPUT_MODE{"LOG_OUTPUT_MODE"};
            const logtype::strg G_LOG_WRITE_PATH{"LOG_WRITE_PATH"};
            const logtype::strg G_LOG_WRITE_FILE{"LOG_WRITE_FILE"};
            const logtype::strg G_LOG_FILE_SIZE_LIMIT{"LOG_FILE_SIZE_LIMIT"};
            const logtype::strg G_LOG_LEVEL_FILTER{"LOG_LEVEL_FILTER"};
            const logtype::strg G_LOG_LEVEL_DEBUG{"debug"};
            const logtype::strg G_LOG_LEVEL_INFO{"info"};
            const logtype::strg G_LOG_LEVEL_WARNING{"warning"};
            const logtype::strg G_LOG_LEVEL_ERROR{"error"};
            const logtype::strg G_LOG_LEVEL_FATAL{"fatal"};
            const logtype::strg G_COMMENT{"#"};
            const logtype::strg G_SEMICOLON{";"};
            const logtype::strg G_EQUAL{"="};
            const logtype::strg G_QUOTE{"\""};
            const logtype::strg G_CONSOLE{"console"};
            const logtype::strg G_FILE{"file"};
            const logtype::strg G_BOTH{"both"};
            const logtype::strg G_TEXT{"text"};
            const logtype::strg G_JSON{"json"};
            const logtype::strg G_XML{"xml"};
            const logtype::strg G_FALSE{"false"};
            const logtype::strg G_TRUE{"true"};

        } // namespace words

        namespace maps {

            const logtype::strg G_NEXT_LINE{"\n"};
            const logtype::strg G_SPACE_08{"        "};
            const logtype::strg G_SPACE_04{"    "};
            const logtype::strg G_SPACE_03{"   "};
            const logtype::strg G_SPACE_02{"  "};
            const logtype::strg G_SPACE_01{" "};

            const logtype::strg G_LEFT_BRACE{"left_brace"};                     // {
            const logtype::strg G_RIGHT_BRACE{"right_brace"};                   // }
            const logtype::strg G_LEFT_SQUARE_BRACKET{"left_square_bracket"};   // [
            const logtype::strg G_RIGHT_SQUARE_BRACKET{"right_square_bracket"}; // ]
            const logtype::strg G_LEFT_PARENTHESIS{"left_parenthesis"};         // (
            const logtype::strg G_RIGHT_PARENTHESIS{"right_parenthesis"};       // )
            const logtype::strg G_SEQUENCE{"sequence"};                         // SEQUENCE
            const logtype::strg G_TIME{"time"};                                 // TIME
            const logtype::strg G_LEVEL{"level"};                               // LEVEL
            const logtype::strg G_MESSAGE{"message"};                           // MESSAGE
            const logtype::strg G_FILE{"file"};                                 // FILE
            const logtype::strg G_LINE{"line"};                                 // LINE
            const logtype::strg G_COLON{"colon"};                               // :
            const logtype::strg G_COMMA{"comma"};                               // ,
            const logtype::strg G_EQUAL{"equal"};                               // =
            const logtype::strg G_QUOTE{"quote"};                               // "
            const logtype::strg G_GT{"gt"};                                     // >
            const logtype::strg G_LT{"lt"};                                     // <
            const logtype::strg G_SLASH{"slash"};                               // /
            const logtype::strg G_QUESTION{"question"};                         // ?
            const logtype::strg G_DEBUG{"DEBUG"};                               // DEBUG
            const logtype::strg G_INFO{"INFO"};                                 // INFO
            const logtype::strg G_WARN{"WARNING"};                              // WARNING
            const logtype::strg G_ERROR{"ERROR"};                               // ERROR
            const logtype::strg G_FATAL{"FATAL"};                               // FATAL
            const logtype::strg G_XML_RECORD{"xml_record"};                     // xml_record
            const logtype::strg G_XML_TIME{"xml_time"};                         // xml_time
            const logtype::strg G_XML_LEVEL{"xml_level"};                       // xml_level
            const logtype::strg G_XML_MESSAGE{"xml_message"};                   // xml_message
            const logtype::strg G_XML_SEQUENCE{"xml_sequence"};                 // xml_sequence
            const logtype::strg G_XML_FILE{"xml_file"};                         // xml_file
            const logtype::strg G_XML_LINE{"xml_line"};                         // xml_line

            const logtype::smap G_KW_MAP_TEMPLATE{
                {G_LEFT_BRACE, "{"},
                {G_RIGHT_BRACE, "}"},
                {G_LEFT_SQUARE_BRACKET, "["},
                {G_RIGHT_SQUARE_BRACKET, "]"},
                {G_LEFT_PARENTHESIS, "("},
                {G_RIGHT_PARENTHESIS, ")"},
                {G_SEQUENCE, "SEQUENCE"},
                {G_TIME, "TIME"},
                {G_LEVEL, "LEVEL"},
                {G_MESSAGE, "MESSAGE"},
                {G_FILE, "FILE"},
                {G_LINE, "LINE"},
                {G_COLON, ":"},
                {G_COMMA, ","},
                {G_EQUAL, "="},
                {G_QUOTE, "\""},
                {G_GT, ">"},
                {G_LT, "<"},
                {G_SLASH, "/"},
                {G_QUESTION, "?"},
                {G_DEBUG, "DEBUG"},
                {G_INFO, "INFO"},
                {G_WARN, "WARNING"},
                {G_ERROR, "ERROR"},
                {G_FATAL, "FATAL"},
                {G_XML_RECORD, "record"},
                {G_XML_TIME, "time"},
                {G_XML_LEVEL, "level"},
                {G_XML_MESSAGE, "message"},
                {G_XML_SEQUENCE, "sequence"},
                {G_XML_FILE, "file"},
                {G_XML_LINE, "line"},
            };

        } // namespace maps

    } // namespace logkeys

} // namespace ruac::rstd::logsystem

#endif // RUAC_LOGKEYS_HPP
