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

#pragma once
#ifndef RUAC_FORMAT_XML_HPP
#define RUAC_FORMAT_XML_HPP

#include "rstd/logsystem/ruac_format.hpp"

namespace ruac::rstd::logsystem {

    /**
     * @brief
     */
    class FormatXML : public Format {
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
