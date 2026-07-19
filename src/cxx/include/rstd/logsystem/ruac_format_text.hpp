/**
 * C/C++ Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * Line Limit: Recommend line breaks at col: 96, force line breaks at col: 120
 * Date Time: 2026-07-18 20:36:16
 * Author: ohmycode-cn(ohcode@163.com)
 * Header File : include/rstd/logsystem/ruac_format_text.hpp
 * Source File : src/rstd/logsystem/ruac_format_text.cpp
 *
 * File Function Description:
 *   Declares the FormatText class, a concrete implementation of the Format
 *   interface for the RUAC log system. FormatText serializes log entries into
 *   plain-text line pairs, where the first line contains the timestamp, level,
 *   sequence number, and source location, and the second line indents the
 *   message content under a labeled brace tag.
 *
 */

#pragma once
#ifndef RUAC_FORMAT_TEXT_HPP
#define RUAC_FORMAT_TEXT_HPP

#include "rstd/logsystem/ruac_format.hpp"

namespace ruac::rstd::logsystem {

    /**
     * @brief Plain-text log formatter that serializes log entries into
     *        human-readable two-line text segments with consistent indentation.
     */
    class FormatText : public Format {
      public:
        FormatText() = default;
        ~FormatText() = default;

      public:
        auto format(const logtype::smap &kmap_,
                    const logtype::strg &time_,
                    const logtype::strg &level_,
                    const logtype::udll &sequence_,
                    const logtype::strg &message_,
                    const logtype::strg &file_,
                    const logtype::sdit &line_) -> logtype::strg override;
    }; // class FormatText

} // namespace ruac::rstd::logsystem

#endif // RUAC_FORMAT_TEXT_HPP
