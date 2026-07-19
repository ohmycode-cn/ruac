/**
 * C/C++ Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * Line Limit: Recommend line breaks at col: 96, force line breaks at col: 120
 * Date Time: 2026-07-19 11:50:19
 * Author: ohmycode-cn(ohcode@163.com)
 * Header File : include/rstd/logsystem/ruac_output_file.hpp
 * Source File : src/rstd/logsystem/ruac_output_file.cpp
 *
 * File Function Description:
 *   Implements the file-output sink for the RUAC log system. Provides a
 *   checkfile() validation helper in an anonymous namespace that verifies
 *   directory existence, file existence, and regular-file type before
 *   opening. Supports two initialization modes: shared static paths for
 *   single-file multi-instance logging, and per-instance paths for
 *   thread-separation scenarios.
 */

#include "rstd/logsystem/ruac_output_file.hpp"
#include "rstd/logsystem/ruac_logtype.hpp"
#include <filesystem>
#include <iostream>
#include <sstream>

namespace ruac::rstd::logsystem {

    namespace {

        /**
         * Validates the target file path and file existence and type.
         *
         * Args:
         *   fpath_: The directory path where the log file should reside.
         *   fname_: The log file name to validate.
         *
         * Returns:
         *   true if the path exists, the file exists, and it is a regular file;
         *   false otherwise with diagnostic output to stdout.
         */
        auto checkfile(const logtype::strg &fpath_, const logtype::strg &fname_) -> logtype::boln {

            namespace fs = std::filesystem;
            auto fpath = fs::path(fpath_);

            if (!fs::exists(fpath)) {
                std::stringstream ss;
                ss << "[PATH ERROR]: Target path not exists: \n";
                ss << "              Path: " << fpath;
                std::cout << ss.str() << std::endl;
                return false;
            }

            if (!fs::exists(fpath / fname_)) {
                std::stringstream ss;
                ss << "[FILE ERROR]: Target file not exists: \n";
                ss << "              Path: " << fpath << "\n";
                ss << "              File: " << fname_;
                std::cout << ss.str() << std::endl;
                return false;
            }

            if (!fs::is_regular_file(fpath / fname_)) {
                std::stringstream ss;
                ss << "[FILE ERROR]: Target file is not regular file ruac not permission handle it: \n";
                ss << "              Path: " << fpath << "\n";
                ss << "              File: " << fname_;
                std::cout << ss.str() << std::endl;
                return false;
            }

            return true;
        }

    } // namespace

    /// Shared directory path for non-thread-separation mode, locked after first assignment.
    logtype::strg OutputFile::m_static_fpath{nullproc::nostr()};
    /// Shared file name for non-thread-separation mode, locked after first assignment.
    logtype::strg OutputFile::m_static_fname{nullproc::nostr()};
    /// Flag indicating whether the shared static paths have been locked.
    logtype::boln OutputFile::m_is_lock_vals{false};

    /**
     * Constructs an OutputFile and initializes the file stream.
     *
     * Args:
     *   fpath_: The directory path for the log file.
     *   fname_: The log file name.
     *   thread_separation_mode: If true, each instance uses its own path;
     *                           if false, all instances share static paths.
     */
    OutputFile::OutputFile(const logtype::strg &fpath_, const logtype::strg &fname_,
                           const logtype::boln thread_separation_mode) {
        init(fpath_, fname_, thread_separation_mode);
    }

    /**
     * Destroys the OutputFile and closes the file stream.
     */
    OutputFile::~OutputFile() {
        over();
    }

    /**
     * Initializes the file stream with path validation and mode selection.
     *
     * In shared mode (thread_separation_mode=false), the first call locks the
     * static paths; subsequent calls reuse them. In separation mode, each
     * instance maintains its own path. Opens the file in binary append mode.
     *
     * Args:
     *   fpath_: The directory path for the log file.
     *   fname_: The log file name.
     *   thread_separation_mode: If true, uses instance-specific paths;
     *                           if false, uses shared static paths.
     */
    void OutputFile::init(const logtype::strg &fpath_, const logtype::strg &fname_,
                          const logtype::boln thread_separation_mode) {

        if (!thread_separation_mode && !m_is_lock_vals) {
            m_static_fpath = fpath_;
            m_static_fname = fname_;
            m_is_lock_vals = true;
        } else {
            m_fpath = fpath_;
            m_fname = fname_;
        }

        auto bin = std::ios::binary;
        auto out = std::ios::out;
        auto app = std::ios::app;

        logtype::strg file_path = (thread_separation_mode) ? m_fpath : m_static_fpath;
        logtype::strg file_name = (thread_separation_mode) ? m_fname : m_static_fname;

        m_is_check = (checkfile(file_path, file_name));
        if (!m_is_check) {
            return;
        }

        m_ofs = std::make_unique<std::ofstream>(file_path + "/" + file_name, out | app | bin);
        if (m_ofs->is_open()) {
            m_is_openf = true;
        }
    }

    /**
     * Closes the output file stream if it is open.
     */
    void OutputFile::over() {
        if (m_ofs && m_ofs->is_open()) {
            m_ofs->close();
        }
    }

    /**
     * Writes a log message to the output file.
     *
     * Args:
     *   message_: The formatted log message string to write.
     *
     * Note:
     *   Silently returns if the file is not open or validation failed.
     */
    void OutputFile::output(const logtype::strg &message_) {
        if (!m_is_openf || !m_is_check) {
            return;
        }
        m_ofs->write(message_.c_str(), message_.size());
    }

} // namespace ruac::rstd::logsystem
