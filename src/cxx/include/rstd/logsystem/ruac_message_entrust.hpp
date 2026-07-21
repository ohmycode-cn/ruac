/**
 * C/C++ Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * Line Limit: Recommend line breaks at col: 96, force line breaks at col: 120
 * Date Time: 2026-07-21 19:13:49
 * Author: ohmycode-cn(ohcode@163.com)
 * Header File : include/rstd/logsystem/ruac_message_entrust.hpp
 * Source File : src/rstd/logsystem/ruac_message_entrust.cpp
 *
 * File Function Description:
 *   Declares the MessageEntrust singleton and its parameter struct.
 *   MessageEntrust delegates colored terminal output to
 *   transformer::Message, exposing three convenience methods —
 *   stdoutAllow, stdoutWarning, stdoutError — that accept a
 *   MessageEntrustParam struct with default empty-string values.
 */

#pragma once
#ifndef RUAC_MESSAGE_ENTRUST_HPP
#define RUAC_MESSAGE_ENTRUST_HPP

#include <string>

namespace ruac::rstd::logsystem {

    /**
     * @brief Parameter struct for MessageEntrust output methods.
     *        Both fields default to empty strings.
     */
    struct MessageEntrustParam {
        std::string m_prefix{""};
        std::string m_content{""};
    };

    /**
     * @brief Thread-safe singleton that delegates colored stdout output
     *        to transformer::Message.
     */
    class MessageEntrust {
      private:
        struct Impl;
        Impl *m_impl{nullptr};

      private:
        MessageEntrust();
        ~MessageEntrust();
        MessageEntrust(const MessageEntrust &) = delete;
        MessageEntrust &operator=(const MessageEntrust &) = delete;

      public:
        static auto instance() -> MessageEntrust &;

      public:
        void init(const bool enable_ce_ = true, const bool enable_ht_ = false, const bool enable_bf_ = false);
        void stdoutAllow(const MessageEntrustParam &param_ = {});
        void stdoutWarning(const MessageEntrustParam &param_ = {});
        void stdoutError(const MessageEntrustParam &param_ = {});
    }; // class MessageEntrust

} // namespace ruac::rstd::logsystem

#endif // RUAC_MESSAGE_ENTRUST_HPP
