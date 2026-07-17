/**
 * C/C++ Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * Line Limit: Recommend line breaks at col: 96, force line breaks at col: 120
 * Date Time: 2026-07-17 22:12:44
 * Author: ohmycode-cn(ohcode@163.com)
 * Header File : include/rstd/logsystem/ruac_format.hpp
 * Source File : src/rstd/logsystem/ruac_format.cpp
 *
 * File Function Description:
 *   Declares the abstract formatting interface for the RUAC log system.
 *   Defines the Format base class whose pure-virtual format() method serves
 *   as the extension point for concrete log-record renderers (e.g., plain
 *   text, json, xml, ...). Derived classes implement format() to transform a
 *   structured set of log fields — timestamp, level, sequence number,
 *   message, source file, and line — into a serialized string representation
 *   using the provided keyword-to-literal mapping table.
 */

#pragma once
#ifndef RUAC_FORMAT_HPP
#define RUAC_FORMAT_HPP

#include "rstd/logsystem/ruac_logtype.hpp"

namespace ruac::rstd::logsystem {

    /**
     * @brief Abstract base class defining the log-record formatting contract.
     *        Concrete formatters (text, json, xml, ...) derive from this and
     *        implement format() to serialize structured log fields into a
     *        target representation via a keyword-to-literal mapping table.
     */
    class Format {
      public:
        virtual auto format(const logtype::smap &kmap_,
                            const logtype::strg &time_,
                            const logtype::strg &level_,
                            const logtype::udll &sequence_,
                            const logtype::strg &message_,
                            const logtype::strg &file_,
                            const logtype::sdit &line_) -> logtype::strg = 0;
        virtual ~Format() = default;
    }; // class Format

} // namespace ruac::rstd::logsystem

#endif // RUAC_FORMAT_HPP
