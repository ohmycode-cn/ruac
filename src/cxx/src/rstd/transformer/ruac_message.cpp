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

#include "rstd/transformer/ruac_message.hpp"
#include <iostream>

namespace ruac::rstd::transformer {

    Message::Message(const MessageANSIControlList &params_) {
        init(params_);
    }

    void Message::init(const MessageANSIControlList &params_) {

        const char *const nullstr{""};
        if (!params_.m_enable_ht) {
            m_reset = nullstr;
            m_red = nullstr;
            m_green = nullstr;
            m_yellow = nullstr;
            return;
        }

        std::string font = (params_.m_enable_bf) ? M_BOLD_FONT : M_ORGD_FONT;
        std::string ansi = (params_.m_enable_ce) ? M_OLD_ANSI : M_NEW_ANSI;

        m_reset = ansi + font + M_ANSI_SEQ_ID[0] + M_CHAR_M;
        m_red = ansi + font + M_ANSI_SEQ_ID[1] + M_CHAR_M;
        m_green = ansi + font + M_ANSI_SEQ_ID[2] + M_CHAR_M;
        m_yellow = ansi + font + M_ANSI_SEQ_ID[3] + M_CHAR_M;
    }

    void Message::reset(const MessageANSIControlList &params_) {
        init(params_);
    }

    auto Message::wrap(const std::string &color_, const std::string &msg_header_, const std::string &msg_) -> std::string {
        return "[ " + color_ + msg_header_ + m_reset + " ] " + msg_;
    }

    void Message::stdoutWarning(const std::string &msg_prefix_, const std::string &msg_content_) {
        std::string msg_header = msg_prefix_ + "WARNING";
        std::cout << wrap(m_yellow, msg_header, msg_content_) << std::endl;
    }

    void Message::stdoutError(const std::string &msg_prefix_, const std::string &msg_content_) {
        std::string msg_header = msg_prefix_ + "ERROR:(";
        std::cout << wrap(m_red, msg_header, msg_content_) << std::endl;
    }

    void Message::stdoutAllow(const std::string &msg_prefix_, const std::string &msg_content_) {
        std::string msg_header = msg_prefix_ + "ALLOW:)";
        std::cout << wrap(m_green, msg_header, msg_content_) << std::endl;
    }

} // namespace ruac::rstd::transformer
