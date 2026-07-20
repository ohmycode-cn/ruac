/**
 * C/C++ Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * Line Limit: Recommend line breaks at col: 96, force line breaks at col: 120
 * Date Time: 2026-07-19 22:03:42
 * Author: ohmycode-cn(ohcode@163.com)
 * Header File : include/rstd/logsystem/ruac_loadconf.hpp
 * Source File : src/rstd/logsystem/ruac_loadconf.cpp
 *
 * File Function Description:
 *   Implements the configuration loading logic for the RUAC log system.
 *   Provides three anonymous-namespace helpers: outStringStream() for
 *   diagnostic output, loadFileBuffer() for validated file loading into
 *   a byte buffer, and parserConfigFile() for extracting key-value pairs
 *   from configuration content with comment and quote handling. The public
 *   LoadConf interface orchestrates these helpers to load and parse
 *   configuration files that specify log output targets, format modes,
 *   terminal rendering flags, and file writing parameters.
 */

#include "rstd/logsystem/ruac_loadconf.hpp"
#include "rstd/logsystem/ruac_logtype.hpp"
#include <ios>
#include <iostream>
#include <fstream>
#include <cstddef>
#include <sstream>

namespace ruac::rstd::logsystem {

    namespace {

        /**
         * Outputs the contents of a stringstream to stdout.
         *
         * Args:
         *   ss_: The stringstream whose contents to output.
         */
        void outStringStream(std::stringstream &ss_) {
            std::cout << ss_.str() << std::endl;
        }

        /**
         * Loads a configuration file into a byte buffer with validation.
         *
         * Args:
         *   file_buffer_: Output vector to store the file contents.
         *   full_path_: The full filesystem path to the configuration file.
         *
         * Returns:
         *   true if the file was successfully loaded; false otherwise with
         *   diagnostic output to stdout.
         */
        auto loadFileBuffer(std::vector<std::byte> &file_buffer_, std::filesystem::path &full_path_) -> logtype::boln {

            logtype::strg default_line{"             Will use default configuration"};
            std::stringstream ss;

            if (!std::filesystem::exists(full_path_)) {
                ss << "[LOAD ERROR] Not found file: " << full_path_.string() << "\n"
                   << default_line;
                outStringStream(ss);
                return false;
            }

            if (!std::filesystem::is_regular_file(full_path_)) {
                ss << "[LOAD ERROR] Not a regular file: " << full_path_.string() << "\n"
                   << default_line;
                outStringStream(ss);
                return false;
            }

            std::ifstream file(full_path_, std::ios::binary | std::ios::ate);
            if (!file) {
                ss << "[LOAD ERROR] Failed to open file: " << full_path_.string() << "\n"
                   << default_line;
                outStringStream(ss);
                return false;
            }

            const std::streamsize file_size = file.tellg();
            if (file_size <= 0) {
                ss << "[LOAD ERROR] Configuration file is empty: " << full_path_.string() << "\n"
                   << default_line;
                outStringStream(ss);
                return false;
            }

            file_buffer_.resize(static_cast<std::size_t>(file_size));
            file.seekg(0);
            file.read(reinterpret_cast<char *>(file_buffer_.data()), file_size);
            file.close();
            return true;
        }

        /**
         * Parses a configuration file buffer into a key-value map.
         *
         * Skips empty lines and comment lines (starting with #).
         * Extracts key=value pairs, handling quoted values and semicolon comments.
         *
         * Args:
         *   file_buffer: The raw byte buffer containing the configuration file contents.
         *
         * Returns:
         *   A map of configuration key-value pairs.
         */
        auto parserConfigFile(std::vector<std::byte> &file_buffer) -> logtype::smap {
            logtype::smap confmap;
            std::string content(reinterpret_cast<const char *>(file_buffer.data()), file_buffer.size());
            std::istringstream stream(content);
            std::string line;

            while (std::getline(stream, line)) {

                if (line.empty() || line.find(logkeys::words::G_COMMENT) == 0) {
                    continue;
                }

                auto eq_pos = line.find(logkeys::words::G_EQUAL);
                if (eq_pos == std::string::npos) {
                    continue;
                }

                std::string key = line.substr(0, eq_pos);
                std::string value = line.substr(eq_pos + 1);

                key.erase(key.find_last_not_of(" \t") + 1);

                auto quote_start = value.find(logkeys::words::G_QUOTE);
                auto quote_end = value.rfind(logkeys::words::G_QUOTE);
                if (quote_start != std::string::npos && quote_end != std::string::npos && quote_start != quote_end) {
                    value = value.substr(quote_start + 1, quote_end - quote_start - 1);
                }

                auto semicolon_pos = value.find(logkeys::words::G_SEMICOLON);
                if (semicolon_pos != std::string::npos) {
                    value = value.substr(0, semicolon_pos);
                }
                value.erase(value.find_last_not_of(" \t") + 1);

                confmap[key] = value;
            }

            return confmap;
        }

    } // namespace

    /**
     * Constructs a LoadConf and initializes with the given configuration path.
     *
     * Args:
     *   rfpath_: The directory path containing the configuration file.
     *   rfname_: The configuration file name.
     */
    LoadConf::LoadConf(const logtype::strg &rfpath_, const logtype::strg &rfname_) {
        init(rfpath_, rfname_);
    }

    /**
     * Initializes the configuration loader with path and file name.
     *
     * Sets internal flags if path or file name is empty, which will cause
     * subsequent operations to fail gracefully.
     *
     * Args:
     *   rfpath_: The directory path containing the configuration file.
     *   rfname_: The configuration file name.
     */
    void LoadConf::init(const logtype::strg &rfpath_, const logtype::strg &rfname_) {
        if (rfpath_.empty()) {
            m_is_empty_rfpath = true;
            return;
        }
        if (rfname_.empty()) {
            m_is_empty_rfname = true;
            return;
        }
        m_rfpath = rfpath_;
        m_rfname = rfname_;
    }

    /**
     * Validates the configuration path and file name.
     *
     * Returns:
     *   true if both path and file name are non-empty; false otherwise with
     *   diagnostic output to stdout.
     */
    auto LoadConf::ret() -> logtype::boln {
        if (m_is_empty_rfpath || m_is_empty_rfname) {
            std::stringstream ss;
            ss << "[LOAD ERROR] Invalid configuration path or file name: " << m_rfpath << " " << m_rfname;
            outStringStream(ss);
            return false;
        }
        return true;
    }

    /**
     * Loads and parses the configuration file into a key-value map.
     *
     * Constructs the full path, loads the file buffer, and parses it
     * into a map of configuration key-value pairs.
     *
     * Returns:
     *   A map of configuration key-value pairs, or an empty map if
     *   the path is invalid or the file cannot be loaded.
     */
    auto LoadConf::getConfigMap() -> logtype::smap {

        if (m_is_empty_rfpath || m_is_empty_rfname) {
            return {};
        }

        m_full_path = std::filesystem::path(m_rfpath) / m_rfname;
        if (!loadFileBuffer(m_file_buffer, m_full_path)) {
            return {};
        }

        return parserConfigFile(m_file_buffer);
    }

} // namespace ruac::rstd::logsystem
