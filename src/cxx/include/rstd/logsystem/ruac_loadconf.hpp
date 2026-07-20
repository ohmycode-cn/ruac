/**
 * C/C++ Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * Line Limit: Recommend line breaks at col: 96, force line breaks at col: 120
 * Date Time: 2026-07-19 22:03:42
 * Author: ohmycode-cn(ohcode@163.com)
 * Header File : include/rstd/logsystem/ruac_loadconf.hpp
 * Source File : src/rstd/logsystem/ruac_loadconf.cpp
 *
 * File Function Description:
 *   Declares the LoadConf class for the RUAC log system configuration
 *   loading. Provides a skeleton interface for parsing configuration
 *   files that define log output targets, format modes, terminal
 *   rendering options, and file writing parameters.
 */

#pragma once
#include <cstddef>
#ifndef RUAC_LOADCONF_HPP
#define RUAC_LOADCONF_HPP

#include "rstd/logsystem/ruac_pathconf.hpp"
#include "rstd/logsystem/ruac_nullproc.hpp"
#include "rstd/logsystem/ruac_logtype.hpp"
#include "rstd/logsystem/ruac_logkeys.hpp"
#include <filesystem>
#include <vector>

namespace ruac::rstd::logsystem {

    /**
     * @brief Configuration loader for the RUAC log system.
     *        Parses configuration files to initialize log output targets,
     *        format modes, terminal rendering options, and file parameters.
     */
    class LoadConf {
      private:
        std::filesystem::path m_full_path{nullproc::nostr()};
        logtype::strg m_rfpath{nullproc::nostr()};
        logtype::strg m_rfname{nullproc::nostr()};
        std::vector<std::byte> m_file_buffer;
        logtype::boln m_is_empty_rfpath{false};
        logtype::boln m_is_empty_rfname{false};

      private:
        void init(const logtype::strg &rfpath_, const logtype::strg &rfname_);

      public:
        LoadConf(const logtype::strg &rfpath_, const logtype::strg &rfname_);
        ~LoadConf() = default;

      public:
        auto ret() -> logtype::boln;
        auto getConfigMap() -> logtype::smap;

    }; // class LoadConf

} // namespace ruac::rstd::logsystem

#endif // RUAC_LOADCONF_HPP
