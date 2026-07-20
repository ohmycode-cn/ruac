/**
 * C/C++ Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * Line Limit: Recommend line breaks at col: 96, force line breaks at col: 120
 * Date Time: 2026-07-20 17:19:01
 * Author: ohmycode-cn(ohcode@163.com)
 * Header File : include/rstd/logsystem/ruac_configure_parser.hpp
 * Source File : src/rstd/logsystem/ruac_configure_parser.cpp
 *
 * File Function Description:
 *
 *
 */

#pragma once
#ifndef RUAC_CONFIGURE_PARSER_HPP
#define RUAC_CONFIGURE_PARSER_HPP

#include "rstd/logsystem/ruac_logtype.hpp"

namespace ruac::rstd::logsystem {

    /**
     * @brief
     */
    class ConfigureParser {
      public:
        ConfigureParser() = default;
        ~ConfigureParser() = default;

      public:
        auto getParserMap(const logtype::strg &rfpath_, const logtype::strg &rfname_) -> logtype::smap;

    }; // class ConfigureParser

} // namespace ruac::rstd::logsystem

#endif // RUAC_CONFIGURE_PARSER_HPP
