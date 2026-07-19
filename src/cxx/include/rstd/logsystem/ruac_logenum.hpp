/**
 * C/C++ Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * Line Limit: Recommend line breaks at col: 96, force line breaks at col: 120
 * Date Time: 2026-07-19 11:16:06
 * Author: ohmycode-cn(ohcode@163.com)
 * Header File : include/rstd/logsystem/ruac_logenum.hpp
 * Source File : src/rstd/logsystem/ruac_logenum.cpp
 *
 * File Function Description:
 *   Declares enumeration types for the RUAC log system. Defines three scoped
 *   enum classes within the logenum namespace: Level (log severity from DEBUG
 *   to FATAL), Format (serialization format: TEXT, JSON, XML), and Output
 *   (destination target: CONSOLE, FILE, BOTH).
 *
 */

#pragma once
#ifndef RUAC_LOGENUM_HPP
#define RUAC_LOGENUM_HPP

namespace ruac::rstd::logsystem {

    namespace logenum {

        /**
         * @brief Log severity levels, ordered from least to most severe.
         */
        enum class Level {
            DEBUG = 0, ///< Detailed diagnostic information for development.
            INFO,      ///< General operational messages.
            WARNING,   ///< Unexpected conditions that do not impair functionality.
            ERROR,     ///< Failures that may allow the program to continue.
            FATAL      ///< Critical failures that terminate the program.
        };

        /**
         * @brief Supported log output serialization formats.
         */
        enum class Format {
            TEXT = 0, ///< Plain-text two-line human-readable format.
            JSON,     ///< Structured JSON object format.
            XML       ///< Structured XML element format.
        };

        /**
         * @brief Supported log output destination targets.
         */
        enum class Output {
            CONSOLE = 0, ///< Write logs to standard output only.
            FILE,        ///< Write logs to file only.
            BOTH         ///< Write logs to both console and file.
        };

    } // namespace logenum

} // namespace ruac::rstd::logsystem

#endif // RUAC_LOGENUM_HPP
