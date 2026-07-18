/**
 * C/C++ Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * Line Limit: Recommend line breaks at col: 96, force line breaks at col: 120
 * Date Time: 2026-07-18 20:36:16
 * Author: ohmycode-cn(ohcode@163.com)
 * Header File : include/rstd/logsystem/ruac_format_text.hpp
 * Source File : src/rstd/logsystem/ruac_format_text.cpp
 *
 * File Function Description:
 *
 *
 */

#include "rstd/logsystem/ruac_format_text.hpp"
#include "rstd/logsystem/ruac_logkeys.hpp"
#include "rstd/logsystem/ruac_logtype.hpp"
#include <sstream>

namespace ruac::rstd::logsystem {
    auto FormatText::format(const logtype::smap &kmap_,
                            const logtype::strg &time_,
                            const logtype::strg &level_,
                            const logtype::udll &sequence_,
                            const logtype::strg &message_,
                            const logtype::strg &file_,
                            const logtype::sdit &line_) -> logtype::strg {
        std::stringstream ss;
        return ss.str();
    }
} // namespace ruac::rstd::logsystem
