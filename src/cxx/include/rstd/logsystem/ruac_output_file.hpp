/**
 * C/C++ Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * Line Limit: Recommend line breaks at col: 96, force line breaks at col: 120
 * Date Time: 2026-07-19 11:50:19
 * Author: ohmycode-cn(ohcode@163.com)
 * Header File : include/rstd/logsystem/ruac_output_file.hpp
 * Source File : src/rstd/logsystem/ruac_output_file.cpp
 *
 * File Function Description:
 *   Declares the OutputFile class, a concrete implementation of the Output
 *   interface for the RUAC log system. OutputFile writes formatted log
 *   messages to a specified file with support for shared static paths
 *   (single-file multi-instance) or per-instance paths (thread-separation),
 *   and includes file validation before opening.
 */

#pragma once
#ifndef RUAC_OUTPUT_FILE_HPP
#define RUAC_OUTPUT_FILE_HPP

#include "rstd/logsystem/ruac_output.hpp"
#include "rstd/logsystem/ruac_nullproc.hpp"
#include "rstd/logsystem/ruac_logtype.hpp"
#include <memory>
#include <fstream>

namespace ruac::rstd::logsystem {

    /**
     * @brief File-output sink that writes formatted log messages to disk.
     *        Supports shared static paths for single-file multi-instance
     *        logging or per-instance paths for thread-separation scenarios.
     */
    class OutputFile : public Output {
      private:
        std::unique_ptr<std::ofstream> m_ofs{nullptr};
        logtype::strg m_fpath{nullproc::nostr()};
        logtype::strg m_fname{nullproc::nostr()};
        static logtype::strg m_static_fpath;
        static logtype::strg m_static_fname;
        static logtype::boln m_is_lock_vals;

      private:
        logtype::boln m_is_check{false};
        logtype::boln m_is_openf{false};

      private:
        void init(const logtype::strg &fpath_, const logtype::strg &fname_,
                  const logtype::boln thread_separation_mode);
        void over();

      public:
        OutputFile(const logtype::strg &fpath_, const logtype::strg &fname_,
                   const logtype::boln thread_separation_mode = true);
        ~OutputFile();

      public:
        void output(const logtype::strg &message_);

    }; // class OutputFile

} // namespace ruac::rstd::logsystem

#endif // RUAC_OUTPUT_FILE_HPP
