/**
 * C/C++ Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * Line Limit: Recommend line breaks at col: 96, force line breaks at col: 120
 * Date Time: 2026-07-19 13:45:13
 * Author: ohmycode-cn(ohcode@163.com)
 * Header File : include/rstd/logsystem/ruac_nullproc.hpp
 * Source File : src/rstd/logsystem/ruac_nullproc.cpp
 *
 * File Function Description:
 *   Declares null-operation placeholder utilities for the RUAC log system.
 *   Provides two no-op functions within the nullproc namespace: nostr()
 *   returns an empty string as a null-output placeholder, and donot()
 *   serves as a null-callback placeholder. These utilities implement the
 *   null-object pattern, enabling optional log sinks and formatters to
 *   be safely omitted without conditional checks at call sites.
 */

#pragma once
#ifndef RUAC_NULLPROC_HPP
#define RUAC_NULLPROC_HPP

#include "rstd/logsystem/ruac_logtype.hpp"

namespace ruac::rstd::logsystem {

    namespace nullproc {

        /**
         * @brief Returns an empty string, used as a null-output placeholder.
         *
         * @return An empty logtype::strg instance.
         */
        auto nostr() -> logtype::strg;

        /**
         * @brief No-op function, used as a null-callback placeholder.
         */
        void donot();

    } // namespace nullproc

} // namespace ruac::rstd::logsystem

#endif // RUAC_NULLPROC_HPP
