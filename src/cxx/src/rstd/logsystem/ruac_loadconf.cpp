/**
 * C/C++ Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * Line Limit: Recommend line breaks at col: 96, force line breaks at col: 120
 * Date Time: 2026-07-21 20:06:18
 * Author: ohmycode-cn(ohcode@163.com)
 * Header File : include/rstd/logsystem/ruac_loadconf.hpp
 * Source File : src/rstd/logsystem/ruac_loadconf.cpp
 *
 * File Function Description:
 *   Provides three anonymous-namespace helpers: emitLoadMessage() for
 *   unified diagnostic output with severity control, loadFileBuffer()
 *   for validated file loading into a byte buffer, and
 *   parserConfigFile() for extracting key-value pairs from
 *   configuration content with comment and quote handling.
 */

#include "rstd/logsystem/ruac_message_entrust.hpp"
#include "rstd/logsystem/ruac_loadconf.hpp"
#include "rstd/logsystem/ruac_logkeys.hpp"
#include "rstd/logsystem/ruac_logtype.hpp"
#include <ios>
#include <iostream>
#include <fstream>
#include <cstddef>
#include <sstream>
#include <string_view>

namespace ruac::rstd::logsystem {

    namespace {

        constexpr std::string_view G_FORMAT_PLACEHOLDER{"                        "}; // 24 spaces
        constexpr std::string_view G_LOAD_CONFIG{"LOAD CONFIG "};

        void emitLoadMessage(const logtype::boln &enable_, bool is_error, std::string_view detail_,
                             std::string_view default_hint_) {

            if (!enable_) {
                return;
            }

            std::stringstream ss;
            ss << detail_ << "\n"
               << G_FORMAT_PLACEHOLDER << default_hint_;

            MessageEntrustParam param{std::string(G_LOAD_CONFIG), ss.str()};

            if (is_error) {
                MessageEntrust::instance().stdoutError(param);
            } else {
                MessageEntrust::instance().stdoutWarning(param);
            }
        }

        /**
         * @brief Loads a configuration file into a byte buffer with validation.
         *
         * @param file_buffer_  Output vector to store the file contents.
         * @param full_path_  The full filesystem path to the configuration file.
         * @param enable_load_msg_  If false, suppresses diagnostic output.
         *
         * @return true if the file was successfully loaded; false otherwise with
         *         diagnostic output to stdout (if enabled).
         */
        auto loadFileBuffer(std::vector<std::byte> &file_buffer_, std::filesystem::path &full_path_,
                            const logtype::boln &enable_load_msg_) -> logtype::boln {

            constexpr std::string_view kDefaultHint = "Will use default inner parameter configuration !";

            if (!std::filesystem::exists(full_path_)) {
                std::stringstream ss;
                ss << "Not found file: " << full_path_.string();
                emitLoadMessage(enable_load_msg_, false, ss.str(), kDefaultHint);
                return false;
            }

            if (!std::filesystem::is_regular_file(full_path_)) {
                std::stringstream ss;
                ss << "Not a regular file: " << full_path_.string();
                emitLoadMessage(enable_load_msg_, true, ss.str(), kDefaultHint);
                return false;
            }

            std::ifstream file(full_path_, std::ios::binary | std::ios::ate);
            if (!file) {
                std::stringstream ss;
                ss << "Failed to open file: " << full_path_.string();
                emitLoadMessage(enable_load_msg_, true, ss.str(), kDefaultHint);
                return false;
            }

            const std::streamsize file_size = file.tellg();
            if (file_size <= 0) {
                std::stringstream ss;
                ss << "Configuration file is empty: " << full_path_.string();
                emitLoadMessage(enable_load_msg_, true, ss.str(), kDefaultHint);
                return false;
            }

            file_buffer_.resize(static_cast<std::size_t>(file_size));
            file.seekg(0);
            file.read(reinterpret_cast<char *>(file_buffer_.data()), file_size);
            file.close();
            return true;
        }

        /**
         * @brief Parses a configuration file buffer into a key-value map.
         *
         * Skips empty lines and comment lines (starting with #).
         * Extracts key=value pairs, handling quoted values and semicolon comments.
         *
         * @param file_buffer  The raw byte buffer containing the configuration file contents.
         *
         * @return A map of configuration key-value pairs.
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
     * @brief Constructs a LoadConf and initializes with the given configuration path.
     *
     * @param rfpath_  The directory path containing the configuration file.
     * @param rfname_  The configuration file name.
     * @param enable_load_msg_  If false, suppresses load diagnostic messages.
     */
    LoadConf::LoadConf(const logtype::strg &rfpath_,
                       const logtype::strg &rfname_,
                       const logtype::boln &enable_load_msg_) {
        m_enable_load_msg = enable_load_msg_;
        init(rfpath_, rfname_);
    }

    /**
     * @brief Initializes the configuration loader with path and file name.
     *
     * Emits a warning and retains the default value if path or file name is
     * empty. Otherwise, overrides the default with the provided value.
     *
     * @param rfpath_  The directory path containing the configuration file.
     * @param rfname_  The configuration file name.
     */
    void LoadConf::init(const logtype::strg &rfpath_, const logtype::strg &rfname_) {

        if (rfpath_.empty()) {
            std::stringstream ss;
            ss << "Invalid configuration file path: " << rfpath_;
            std::stringstream hint;
            hint << "Use default file path: " << pathconf::G_LOG_DEFAULT_READ_FILE_PATH;
            emitLoadMessage(m_enable_load_msg, false, ss.str(), hint.str());
        } else {
            m_rfpath = rfpath_;
        }

        if (rfname_.empty()) {
            std::stringstream ss;
            ss << "Invalid configuration file name: " << rfname_;
            std::stringstream hint;
            hint << "Use default file name: " << pathconf::G_LOG_DEFAULT_READ_FILE_NAME;
            emitLoadMessage(m_enable_load_msg, false, ss.str(), hint.str());
        } else {
            m_rfname = rfname_;
        }
    }

    /**
     * @brief Loads and parses the configuration file into a key-value map.
     *
     * Constructs the full path from the stored directory path and file name,
     * loads the file buffer, and parses it into a map of configuration
     * key-value pairs.
     *
     * @return A map of configuration key-value pairs, or an empty map if
     *         the file cannot be loaded.
     */
    auto LoadConf::getConfigMap() -> logtype::smap {

        m_full_path = std::filesystem::path(m_rfpath) / m_rfname;
        if (!loadFileBuffer(m_file_buffer, m_full_path,
                            m_enable_load_msg)) {
            return {};
        }

        return parserConfigFile(m_file_buffer);
    }

} // namespace ruac::rstd::logsystem
