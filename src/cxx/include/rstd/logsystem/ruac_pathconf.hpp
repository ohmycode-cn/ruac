/**
 * C/C++ Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * Line Limit: Recommend line breaks at col: 96, force line breaks at col: 120
 * Date Time: 2026-07-20 08:40:44
 * Author: ohmycode-cn(ohcode@163.com)
 * Header File : include/rstd/logsystem/ruac_pathconf.hpp
 * Source File : src/rstd/logsystem/ruac_pathconf.cpp
 *
 * File Function Description:
 *   Declares platform-specific default path constants for the RUAC log system.
 *   Defines the default log file directory path (G_LOG_DEFAULT_WRITE_FILE_PATH)
 *   with conditional compilation for Linux (/var/log/ruacdb) and Windows
 *   (C:\Users\RuacDB\Logs), and the default log file name
 *   (G_LOG_DEFAULT_WRITE_FILE_NAME) used when no user-specified path is provided.
 */

#pragma once
#ifndef RUAC_PATHCONF_HPP
#define RUAC_PATHCONF_HPP

#include "rstd/logsystem/ruac_logtype.hpp"

namespace ruac::rstd::logsystem {

    namespace pathconf {

        /// Default log file directory path, platform-specific.
#if defined(__linux__)
        const logtype::strg G_LOG_DEFAULT_WRITE_FILE_PATH{"/var/log/ruacdb"};
        const logtype::strg G_LOG_DEFAULT_READ_FILE_PATH{"/etc/ruacdb"};

#elif defined(__WIN32__) || defined(__WIN64__)
        const logtype::strg G_LOG_DEFAULT_WRITE_FILE_PATH{"C:\\Users\\RuacDB\\Logs"};
        const logtype::strg G_LOG_DEFAULT_READ_FILE_PATH{"C:\\Users\\RuacDB\\Config"};
#endif
        /// Default log file name used when no user-specified file name is provided.
        const logtype::strg G_LOG_DEFAULT_WRITE_FILE_NAME{"ruacdb.default.log.txt"};
        const logtype::strg G_LOG_DEFAULT_READ_FILE_NAME{"ruacdb.log.conf"};

    } // namespace pathconf

} // namespace ruac::rstd::logsystem

#endif // RUAC_PATHCONF_HPP
