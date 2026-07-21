/**
 * C/C++ Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * Line Limit: Recommend line breaks at col: 96, force line breaks at col: 120
 * Date Time: 2026-07-21 19:12:16
 * Author: ohmycode-cn(ohcode@163.com)
 * Header File : include/rstd/transformer/ruac_message.hpp
 * Source File : src/rstd/transformer/ruac_message.cpp
 *
 * File Function Description:
 *
 *
 */

#pragma once
#ifndef RUAC_MESSAGE_HPP
#define RUAC_MESSAGE_HPP

#include <string>

namespace ruac::rstd::transformer {

    struct MessageANSIControlList {
        bool m_enable_ce{true};
        bool m_enable_ht{false};
        bool m_enable_bf{false};
    };

    /**
     * @brief
     */
    class Message {
      private:
        const char *const M_ANSI_SEQ_ID[4]{"0", "31", "32", "33"};
        const char *const M_OLD_ANSI{"\033"};
        const char *const M_NEW_ANSI{"\x1b"};
        const char *const M_BOLD_FONT{"[1;"};
        const char *const M_ORGD_FONT{"[0;"};
        const char *const M_CHAR_M{"m"};

      private:
        std::string m_reset;
        std::string m_red;
        std::string m_green;
        std::string m_yellow;
        void init(const MessageANSIControlList &params_ = {});
        auto wrap(const std::string &color_, const std::string &msg_header_, const std::string &msg_) -> std::string;

      public:
        Message(const MessageANSIControlList &params_ = {});
        ~Message() = default;

      public:
        void stdoutWarning(const std::string &msg_prefix_ = "", const std::string &msg_content_ = "");
        void stdoutError(const std::string &msg_prefix_ = "", const std::string &msg_content_ = "");
        void stdoutAllow(const std::string &msg_prefix_ = "", const std::string &msg_content_ = "");

      public:
        void reset(const MessageANSIControlList &params_ = {});
    }; // class Message

} // namespace ruac::rstd::transformer

#endif // RUAC_MESSAGE_HPP
