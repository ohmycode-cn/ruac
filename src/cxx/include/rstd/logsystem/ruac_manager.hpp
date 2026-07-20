/**
 * C/C++ Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * Line Limit: Recommend line breaks at col: 96, force line breaks at col: 120
 * Date Time: 2026-07-20 13:18:52
 * Author: ohmycode-cn(ohcode@163.com)
 * Header File : include/rstd/logsystem/ruac_manager.hpp
 * Source File : src/rstd/logsystem/ruac_manager.cpp
 *
 * File Function Description:
 *   Declares the Manager class, the central orchestrator for the RUAC log
 *   system. Manages terminal and file output sinks with configurable format
 *   modes (TEXT, JSON, XML), log level filtering, ANSI color rendering,
 *   and per-level sequence counting. Loads configuration from a parsed
 *   key-value map and coordinates Format and Output polymorphic instances.
 *
 *   Note: Raw pointers are used intentionally instead of C++ smart pointers
 *   (std::unique_ptr, std::shared_ptr) for Format and Output instances.
 *   This C-style approach prioritizes runtime performance (zero overhead
 *   from reference counting or control blocks) and explicit lifetime
 *   management clarity, which is justified for this hot-path logging layer.
 */

#pragma once
#ifndef RUAC_MANAGER_HPP
#define RUAC_MANAGER_HPP

#include "rstd/logsystem/ruac_nullproc.hpp"
#include "rstd/logsystem/ruac_logkeys.hpp"
#include "rstd/logsystem/ruac_logenum.hpp"
#include "rstd/logsystem/ruac_logtype.hpp"
#include "rstd/logsystem/ruac_format.hpp"
#include "rstd/logsystem/ruac_output.hpp"

namespace ruac::rstd::logsystem {

    /**
     * @brief Central log manager that orchestrates terminal and file output sinks.
     *        Loads configuration from a key-value map, manages Format and Output
     *        polymorphic instances, applies log level filtering, maintains per-level
     *        sequence counters, and supports runtime reconfiguration of console
     *        log format and rendering options.
     */
    class Manager {
      private:
        logtype::boln m_enable_term_compatible{true};
        logtype::boln m_enable_term_highlight{false};
        logtype::boln m_enable_term_bold_font{false};
        logtype::boln m_enable_term_log_print{true};
        logenum::Level m_term_log_level{logenum::Level::DEBUG};
        logenum::Level m_file_log_level{logenum::Level::DEBUG};
        logenum::Level m_log_min_level{logenum::Level::DEBUG};
        logenum::Format m_term_format{logenum::Format::TEXT};
        logenum::Format m_file_format{logenum::Format::TEXT};
        logtype::strg m_write_file_path{nullproc::nostr()};
        logtype::strg m_write_file_name{nullproc::nostr()};
        logenum::Output m_log_output{logenum::Output::CONSOLE};
        static logtype::boln m_is_once_lock;
        logtype::smap m_map_org{logkeys::maps::G_KW_MAP_TEMPLATE};
        logtype::smap m_map_clr{};
        logtype::boln m_ptr_output_once_lock{false};
        logtype::boln m_ptr_format_once_lock{false};

      private:
        logtype::udll m_seq_debug{0};
        logtype::udll m_seq_info{0};
        logtype::udll m_seq_warning{0};
        logtype::udll m_seq_error{0};
        logtype::udll m_seq_fatal{0};
        void counter(logtype::udll &seq_);

      private:
        logtype::smap m_confmap;
        Format *m_ptr_term_format{nullptr};
        Output *m_ptr_term_output{nullptr};
        Format *m_ptr_file_format{nullptr};
        Output *m_ptr_file_output{nullptr};
        void initMbr();
        void init();
        void over();
        void overConsolePtr();
        void outLogStringStream(Format *format_, Output *output_, logtype::smap &map_, const logtype::strg &level_,
                                const logtype::udll &sequence_, const logtype::strg &message_,
                                const logtype::strg &file_, const logtype::sdit &line_);

      public:
        Manager(const logtype::smap &confmap_);
        ~Manager();

      public:
        void reinitConsoleLogFormat(const logtype::boln &enable_ce_ = true,
                                    const logtype::boln &enable_ht_ = false,
                                    const logtype::boln &enable_bf_ = false,
                                    const logtype::boln &enanle_tr_ = true,
                                    const logtype::strg &format_tr_ = "text",
                                    const logtype::strg &termlv_tr_ = "debug",
                                    const logenum::Level min_level_ = logenum::Level::DEBUG);

        void write(logenum::Level level_, const logtype::strg &message_, const logtype::strg &file_,
                   const logtype::sdit &line_);
    }; // class Manager

} // namespace ruac::rstd::logsystem

#endif // RUAC_MANAGER_HPP
