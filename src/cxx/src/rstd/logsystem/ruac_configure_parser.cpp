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
#include "rstd/logsystem/ruac_logkeys.hpp"

namespace ruac::rstd::logsystem {

    namespace {

        auto retDefaultConfigureMap() -> logtype::smap {
            return {
                {logkeys::words::G_ENABLE_TERM_COMPATIBLE_MODE, logkeys::words::G_TRUE},
                {logkeys::words::G_ENABLE_TERM_HIGHLIGHT_MODE, logkeys::words::G_FALSE},
                {logkeys::words::G_ENABLE_TERM_BOLD_FONT_MODE, logkeys::words::G_FALSE},
                {logkeys::words::G_ENABLE_TERM_LOG_PRINT_MODE, logkeys::words::G_FALSE},
                {logkeys::words::G_LOG_TERM_LEVEL_FILTER, logkeys::words::G_LOG_LEVEL_DEBUG},
                {logkeys::words::G_LOG_FILE_LEVEL_FILTER, logkeys::words::G_LOG_LEVEL_DEBUG},
                {logkeys::words::G_LOG_MIN_LEVEL_FILTER, logkeys::words::G_LOG_LEVEL_DEBUG},
                {logkeys::words::G_LOG_TERM_FORMAT_MODE, logkeys::words::G_TEXT},
                {logkeys::words::G_LOG_FILE_FORMAT_MODE, logkeys::words::G_TEXT},
                {logkeys::words::G_LOG_OUTPUT_MODE, logkeys::words::G_CONSOLE},
                {logkeys::words::G_LOG_WRITE_PATH, "/home/repox/Engineering/ruacdbv01/ruacdb/tmp"},
                {logkeys::words::G_LOG_WRITE_FILE, "ruacdb.test.log"},
                {logkeys::words::G_LOG_FILE_SIZE_LIMIT, "128MB"},
            };
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
