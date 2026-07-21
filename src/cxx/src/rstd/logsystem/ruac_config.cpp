/**
 * C/C++ Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * Line Limit: Recommend line breaks at col: 96, force line breaks at col: 120
 * Date Time: 2026-07-20 17:19:01
 * Author: ohmycode-cn(ohcode@163.com)
 * Header File : include/rstd/logsystem/ruac_config.hpp
 * Source File : src/rstd/logsystem/ruac_config.cpp
 *
 * File Function Description:
 *   Provides an anonymous-namespace helper retDefaultConfigureMap() that
 *   returns a hard-coded default configuration map covering all log system
 *   parameters as the fallback when file loading yields an empty map.
 */

#include "rstd/logsystem/ruac_loadconf.hpp"
#include "rstd/logsystem/ruac_logkeys.hpp"
#include "rstd/logsystem/ruac_logstc.hpp"
#include "rstd/logsystem/ruac_logtype.hpp"
#include "rstd/logsystem/ruac_config.hpp"

namespace ruac::rstd::logsystem {

    namespace {

        /**
         * @brief Returns a hard-coded default configuration map covering all
         *        log system parameters.
         *
         * @return A default configuration map with all log system parameters.
         */
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
                // This is temporary test path and file name.
                {logkeys::words::G_LOG_WRITE_PATH, "/home/repox/Engineering/ruacdbv01/ruacdb/tmp"},
                {logkeys::words::G_LOG_WRITE_FILE, "ruacdb.test.log"},
                {logkeys::words::G_LOG_FILE_SIZE_LIMIT, "128MB"},
            };
        }

    } // namespace

    /**
     * @brief Loads configuration from file via LoadConf; falls back to
     *        retDefaultConfigureMap() when the file yields an empty map.
     *
     * @param rfpath_  The directory path containing the configuration file.
     * @param rfname_  The configuration file name.
     *
     * @return A configuration map loaded from file or the default map.
     */
    auto Config::fromFileGetConfigMap(const logtype::strg &rfpath_, const logtype::strg &rfname_) -> logtype::smap {
        if (m_once_lock) {
            return {};
        }
        m_once_lock = true;
        LoadConf lc(rfpath_, rfname_);
        auto map = lc.getConfigMap();
        if (!map.empty()) {
            return map;
        }
        return retDefaultConfigureMap();
    }

    /**
     * @brief Resolves optional LogParamOverride values into a concrete
     *        LogParamList, using false/text as per-field defaults.
     *
     * @param ov_ops_  Optional override values for terminal display parameters.
     *
     * @return A concrete LogParamList with resolved values.
     */
    auto Config::resetTermConfigMap(const LogParamOverride &ov_ops_) -> LogParamList {

        LogParamList param;

        param.m_enable_term_ce = ov_ops_.m_enable_term_ce.value_or(logtype::boln{false});
        param.m_enable_term_ht = ov_ops_.m_enable_term_ht.value_or(logtype::boln{false});
        param.m_enable_term_bf = ov_ops_.m_enable_term_bf.value_or(logtype::boln{false});
        param.m_enable_term_ot = ov_ops_.m_enable_term_ot.value_or(logtype::boln{false});
        param.m_format_term_sl = ov_ops_.m_format_term_sl.value_or(logtype::strg{"text"});

        return param;
    }

} // namespace ruac::rstd::logsystem
