/**
 * C/C++ Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * Line Limit: Recommend line breaks at col: 96, force line breaks at col: 120
 * Date Time: 2026-07-18 20:36:24
 * Author: ohmycode-cn(ohcode@163.com)
 * Header File : include/rstd/logsystem/ruac_format_json.hpp
 * Source File : src/rstd/logsystem/ruac_format_json.cpp
 *
 * File Function Description:
 *   Declares the FormatJson class, a concrete implementation of the Format
 *   interface for the RUAC log system. FormatJson serializes log entries into
 *   structured JSON object strings, where each entry is a keyed object
 *   containing TIME, LEVEL, SEQUENCE, MESSAGE, FILE, and LINE fields. A
 *   private template helper convenientFormat provides reusable key-value pair
 *   formatting with consistent indentation.
 *
 */

#pragma once
#ifndef RUAC_FORMAT_JSON_HPP
#define RUAC_FORMAT_JSON_HPP

#include "rstd/logsystem/ruac_format.hpp"

namespace ruac::rstd::logsystem {

    /**
     * @brief JSON log formatter that serializes log entries into structured
     *        JSON object strings with configurable key-value formatting.
     */
    class FormatJson : public Format {
      private:
        template <typename V>
        auto convenientFormat(const logtype::smap &kmap_, const logtype::strg &key_, const V &val_) -> logtype::strg;

      public:
        FormatJson() = default;
        ~FormatJson() = default;

      public:
        auto format(const logtype::smap &kmap_,
                    const logtype::strg &time_,
                    const logtype::strg &level_,
                    const logtype::udll &sequence_,
                    const logtype::strg &message_,
                    const logtype::strg &file_,
                    const logtype::sdit &line_) -> logtype::strg override;
    }; // class FormatJson

} // namespace ruac::rstd::logsystem

#endif // RUAC_FORMAT_JSON_HPP
