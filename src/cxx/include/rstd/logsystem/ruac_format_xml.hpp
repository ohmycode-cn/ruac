/**
 * C/C++ Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * Line Limit: Recommend line breaks at col: 96, force line breaks at col: 120
 * Date Time: 2026-07-18 20:36:28
 * Author: ohmycode-cn(ohcode@163.com)
 * Header File : include/rstd/logsystem/ruac_format_xml.hpp
 * Source File : src/rstd/logsystem/ruac_format_xml.cpp
 *
 * File Function Description:
 *   Declares the FormatXML class, a concrete implementation of the Format
 *   interface for the RUAC log system. FormatXML serializes log entries into
 *   XML element strings, where each entry is wrapped in a <record> element
 *   containing TIME, LEVEL, SEQUENCE, MESSAGE, FILE, and LINE child elements.
 *   A private template helper convenientFormat generates paired open/close
 *   XML tags with consistent indentation.
 *
 */

#pragma once
#ifndef RUAC_FORMAT_XML_HPP
#define RUAC_FORMAT_XML_HPP

#include "rstd/logsystem/ruac_format.hpp"

namespace ruac::rstd::logsystem {

    /**
     * @brief XML log formatter that serializes log entries into structured
     *        XML element strings with configurable tag formatting.
     */
    class FormatXML : public Format {
      private:
        template <typename V>
        auto convenientFormat(const logtype::smap &kmap_, const logtype::strg &key_, const V &val_) -> logtype::strg;

      public:
        FormatXML() = default;
        ~FormatXML() = default;

      public:
        auto format(const logtype::smap &kmap_,
                    const logtype::strg &time_,
                    const logtype::strg &level_,
                    const logtype::udll &sequence_,
                    const logtype::strg &message_,
                    const logtype::strg &file_,
                    const logtype::sdit &line_) -> logtype::strg override;
    }; // class FormatXML

} // namespace ruac::rstd::logsystem

#endif // RUAC_FORMAT_XML_HPP
