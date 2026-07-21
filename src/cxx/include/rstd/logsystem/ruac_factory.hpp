/**
 * C/C++ Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * Line Limit: Recommend line breaks at col: 96, force line breaks at col: 120
 * Date Time: 2026-07-20 20:56:51
 * Author: ohmycode-cn(ohcode@163.com)
 * Header File : include/rstd/logsystem/ruac_factory.hpp
 * Source File : src/rstd/logsystem/ruac_factory.cpp
 *
 * File Function Description:
 *   Declares the Factory class for the RUAC log system. Factory is
 *   responsible for creating and managing Format and Output polymorphic
 *   instances based on configuration. Provides methods for writing log
 *   messages and reloading terminal configuration at runtime.
 */

#pragma once
#ifndef RUAC_FACTORY_HPP
#define RUAC_FACTORY_HPP

#include "rstd/logsystem/ruac_logenum.hpp"
#include "rstd/logsystem/ruac_logtype.hpp"
#include "rstd/logsystem/ruac_format.hpp"
#include "rstd/logsystem/ruac_output.hpp"

namespace ruac::rstd::logsystem {

    namespace {
        struct SinkPair {
            Format *m_fmt{nullptr};
            Output *m_out{nullptr};
        };

        struct OutputChannels {
            SinkPair m_term;
            SinkPair m_file;
        };

    } // namespace

    /**
     * @brief Factory for creating and managing Format and Output instances.
     *        Creates terminal and file output sinks with appropriate format
     *        renderers based on configuration. Supports runtime terminal
     *        configuration reload.
     */
    class Factory {
      private:
        OutputChannels m_channels;
        logtype::smap m_term_kmap;
        logtype::smap m_file_kmap;
        logenum::Level m_term_level{logenum::Level::DEBUG};
        logenum::Level m_file_level{logenum::Level::DEBUG};
        logenum::Level m_min_level{logenum::Level::DEBUG};
        logtype::udll m_sequence[5]{};

        void init();
        void over();

      public:
        Factory(logtype::smap &confmap_);
        ~Factory();

      public:
        void write(const logenum::Level level_, const logtype::strg &message_, const logtype::strg &file_,
                   const logtype::sdit line_);
        void reloadTermConfig(const logtype::strg &term_fmt_mode_, const logtype::boln &enable_ce_,
                              const logtype::boln &enable_ht_, const logtype::boln &enable_bf_,
                              const logtype::boln &enable_ot_);
    }; // class Factory

} // namespace ruac::rstd::logsystem

#endif // RUAC_FACTORY_HPP
