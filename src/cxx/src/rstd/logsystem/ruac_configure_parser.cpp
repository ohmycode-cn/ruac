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

#include "rstd/logsystem/ruac_configure_parser.hpp"
#include "rstd/logsystem/ruac_loadconf.hpp"

namespace ruac::rstd::logsystem {

    namespace {

        auto retDefaultConfigureMap() -> logtype::smap {
            return {};
        }

    } // namespace

    auto ConfigureParser::getParserMap(const logtype::strg &rfpath_, const logtype::strg &rfname_) -> logtype::smap {
        LoadConf lc(rfpath_, rfname_);
        auto map = lc.getConfigMap();
        if (!map.empty()) {
            return map;
        }
        return retDefaultConfigureMap();
    }

} // namespace ruac::rstd::logsystem
