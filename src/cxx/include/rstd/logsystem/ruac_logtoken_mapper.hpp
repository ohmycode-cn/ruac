/**
 * C/C++ Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * Line Limit: Recommend line breaks at col: 96, force line breaks at col: 120
 * Date Time: 2026-07-20 17:24:01
 * Author: ohmycode-cn(ohcode@163.com)
 * Header File : include/rstd/logsystem/ruac_logtoken_mapper.hpp
 * Source File : src/rstd/logsystem/ruac_logtoken_mapper.cpp
 *
 * File Function Description:
 *
 *
 */

#pragma once
#ifndef RUAC_LOGTOKEN_MAPPER_HPP
#define RUAC_LOGTOKEN_MAPPER_HPP

#include "rstd/logsystem/ruac_logtype.hpp"

namespace ruac::rstd::logsystem {

    namespace logtoken_mapper {

        auto tokenmapHT(const logtype::boln &enable_ce_ = true, const logtype::boln &enable_ht_ = true,
                        const logtype::boln &enable_bf_ = false) -> logtype::smap;
        auto tokenmapOL() -> logtype::smap;

    } // namespace logtoken_mapper

} // namespace ruac::rstd::logsystem

#endif // RUAC_LOGTOKEN_MAPPER_HPP
