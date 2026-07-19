/**
 * C/C++ Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * Line Limit: Recommend line breaks at col: 96, force line breaks at col: 120
 * Date Time: 2026-07-19 13:45:13
 * Author: ohmycode-cn(ohcode@163.com)
 * Header File : include/rstd/logsystem/ruac_nullproc.hpp
 * Source File : src/rstd/logsystem/ruac_nullproc.cpp
 *
 * File Function Description:
 *
 *
 */

#include "rstd/logsystem/ruac_nullproc.hpp"

namespace ruac::rstd::logsystem {

    namespace nullproc {

        /**
         * @brief Returns an empty string, used as a null-output placeholder.
         *
         * @return An empty logtype::strg instance.
         */
        auto nostr() -> logtype::strg {
            return "";
        }

        /**
         * @brief No-op function, used as a null-callback placeholder.
         */
        void donot() {
            return;
        }

    } // namespace nullproc

} // namespace ruac::rstd::logsystem
