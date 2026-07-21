/**
 * C/C++ Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * Line Limit: Recommend line breaks at col: 96, force line breaks at col: 120
 * Date Time: 2026-07-21 19:13:49
 * Author: ohmycode-cn(ohcode@163.com)
 * Header File : include/rstd/logsystem/ruac_message_entrust.hpp
 * Source File : src/rstd/logsystem/ruac_message_entrust.cpp
 *
 * File Function Description:
 *   Implements the MessageEntrust singleton that owns a
 *   transformer::Message instance via the pimpl idiom and delegates
 *   colored stdout output through three struct-based methods.
 */

#include "rstd/logsystem/ruac_message_entrust.hpp"
#include "rstd/transformer/ruac_message.hpp"

namespace ruac::rstd::logsystem {

    struct MessageEntrust::Impl {
        transformer::Message m_msg;
    };

    MessageEntrust::MessageEntrust() {
        if (nullptr == m_impl) {
            m_impl = new Impl{};
        }
    }

    MessageEntrust::~MessageEntrust() {
        if (nullptr != m_impl) {
            delete m_impl;
            m_impl = nullptr;
        }
    }

    auto MessageEntrust::instance() -> MessageEntrust & {
        static MessageEntrust inst;
        return inst;
    }

    void MessageEntrust::init(const bool enable_ce_, const bool enable_ht_, const bool enable_bf_) {
        m_impl->m_msg.reset(transformer::MessageANSIControlList{
            enable_ce_,
            enable_ht_,
            enable_bf_});
    }

    void MessageEntrust::stdoutAllow(const MessageEntrustParam &param_) {
        m_impl->m_msg.stdoutAllow(param_.m_prefix, param_.m_content);
    }

    void MessageEntrust::stdoutWarning(const MessageEntrustParam &param_) {
        m_impl->m_msg.stdoutWarning(param_.m_prefix, param_.m_content);
    }

    void MessageEntrust::stdoutError(const MessageEntrustParam &param_) {
        m_impl->m_msg.stdoutError(param_.m_prefix, param_.m_content);
    }

} // namespace ruac::rstd::logsystem
