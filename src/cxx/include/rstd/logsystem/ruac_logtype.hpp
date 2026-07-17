/**
 * C/C++ Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * Line Limit: Recommend line breaks at col: 96, force line breaks at col: 120
 * Date Time: 2026-07-17 21:11:21
 * Author: ohmycode-cn(ohcode@163.com)
 * Header File : include/rstd/logsystem/ruac_logtype.hpp
 * Source File : src/rstd/logsystem/ruac_logtype.cpp
 *
 * File Function Description:
 *   Provides canonical type aliases for the RUAC log system subsystem.
 *   Defines a set of abbreviated type aliases (strg, smap, boln, udit, sdit,
 *   udll, sdll) within the ruac::rstd::logsystem::logtype namespace that map
 *   to standard C++ fundamental and library types. These aliases enforce a
 *   uniform type vocabulary across log-related modules, improving readability
 *   and reducing verbosity when specifying parameter and return types in log
 *   formatting, serialization, and sink configuration interfaces.
 *
 */

#pragma once
#ifndef RUAC_LOGTYPE_HPP
#define RUAC_LOGTYPE_HPP

#include <unordered_map>
#include <string>

namespace ruac::rstd::logsystem {

    namespace logtype {

        using strg = std::string;
        using smap = std::unordered_map<std::string, std::string>;
        using boln = bool;
        using udit = unsigned int;
        using sdit = signed int;
        using udll = unsigned long long;
        using sdll = signed long long;

    } // namespace logtype

} // namespace ruac::rstd::logsystem

#endif // RUAC_LOGTYPE_HPP
