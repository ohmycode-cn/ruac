/**
 * C/C++ Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * Line Limit: Recommend line breaks at col: 96, force line breaks at col: 120
 * Date Time: 2026-07-20 17:24:01
 * Author: ohmycode-cn(ohcode@163.com)
 * Header File : include/rstd/logsystem/ruac_logtoken_mapper.hpp
 * Source File : src/rstd/logsystem/ruac_logtoken_mapper.cpp
 *
 * File Function Description:
 *
 *
 */

#include "rstd/logsystem/ruac_logtoken_mapper.hpp"
#include "rstd/logsystem/ruac_logkeys.hpp"
#include "rstd/logsystem/ruac_logtype.hpp"
#include "rstd/logsystem/ruac_colors.hpp"

namespace ruac::rstd::logsystem {

    namespace logtoken_mapper {

        namespace {

            const logtype::strg G_TOKEN_L_BRACE{"{"};
            const logtype::strg G_TOKEN_R_BRACE{"}"};
            const logtype::strg G_TOKEN_L_SQUARE_BRACKET{"["};
            const logtype::strg G_TOKEN_R_SQUARE_BRACKET{"]"};
            const logtype::strg G_TOKEN_L_PARENTHESIS{"("};
            const logtype::strg G_TOKEN_R_PARENTHESIS{")"};
            const logtype::strg G_TOKEN_SEQUENCE{"SEQUENCE"};
            const logtype::strg G_TOKEN_TIME{"TIME"};
            const logtype::strg G_TOKEN_LEVEL{"LEVEL"};
            const logtype::strg G_TOKEN_MESSAGE{"MESSAGE"};
            const logtype::strg G_TOKEN_FILE{"FILE"};
            const logtype::strg G_TOKEN_LINE{"LINE"};
            const logtype::strg G_TOKEN_COLON{":"};
            const logtype::strg G_TOKEN_COMMA{","};
            const logtype::strg G_TOKEN_EQUAL{"="};
            const logtype::strg G_TOKEN_QUOTE{"\""};
            const logtype::strg G_TOKEN_GT{">"};
            const logtype::strg G_TOKEN_SLASH{"/"};
            const logtype::strg G_TOKEN_LT{"<"};
            const logtype::strg G_TOKEN_QUESTION{"?"};
            const logtype::strg G_TOKEN_DEBUG{"DEBUG"};
            const logtype::strg G_TOKEN_INFO{"INFO"};
            const logtype::strg G_TOKEN_WARNING{"WARNING"};
            const logtype::strg G_TOKEN_ERROR{"ERROR"};
            const logtype::strg G_TOKEN_FATAL{"FATAL"};
            const logtype::strg G_TOKEN_XML_RECORD{"record"};
            const logtype::strg G_TOKEN_XML_TIME{"time"};
            const logtype::strg G_TOKEN_XML_LEVEL{"level"};
            const logtype::strg G_TOKEN_XML_MESSAGE{"message"};
            const logtype::strg G_TOKEN_XML_SEQUENCE{"sequence"};
            const logtype::strg G_TOKEN_XML_FILE{"file"};
            const logtype::strg G_TOKEN_XML_LINE{"line"};

        } // namespace

        auto tokenmapHT(const logtype::boln &enable_ce_, const logtype::boln &enable_ht_,
                        const logtype::boln &enable_bf_) -> logtype::smap {

            Colors cr(enable_ce_, enable_ht_, enable_bf_);

            logtype::smap map{
                {logkeys::tokens::G_LEFT_BRACE, cr.y(G_TOKEN_L_BRACE)},
                {logkeys::tokens::G_RIGHT_BRACE, cr.y(G_TOKEN_R_BRACE)},
                {logkeys::tokens::G_LEFT_SQUARE_BRACKET, cr.m(G_TOKEN_L_SQUARE_BRACKET)},
                {logkeys::tokens::G_RIGHT_SQUARE_BRACKET, cr.m(G_TOKEN_R_SQUARE_BRACKET)},
                {logkeys::tokens::G_LEFT_PARENTHESIS, cr.m(G_TOKEN_L_PARENTHESIS)},
                {logkeys::tokens::G_RIGHT_PARENTHESIS, cr.m(G_TOKEN_R_PARENTHESIS)},
                {logkeys::tokens::G_SEQUENCE, cr.y(G_TOKEN_SEQUENCE)},
                {logkeys::tokens::G_TIME, cr.r(G_TOKEN_TIME)},
                {logkeys::tokens::G_LEVEL, cr.m(G_TOKEN_LEVEL)},
                {logkeys::tokens::G_MESSAGE, cr.g(G_TOKEN_MESSAGE)},
                {logkeys::tokens::G_FILE, cr.b(G_TOKEN_FILE)},
                {logkeys::tokens::G_LINE, cr.c(G_TOKEN_LINE)},
                {logkeys::tokens::G_COLON, cr.w(G_TOKEN_COLON)},
                {logkeys::tokens::G_COMMA, cr.r(G_TOKEN_COMMA)},
                {logkeys::tokens::G_EQUAL, cr.w(G_TOKEN_EQUAL)},
                {logkeys::tokens::G_QUOTE, cr.y(G_TOKEN_QUOTE)},
                {logkeys::tokens::G_GT, cr.c(G_TOKEN_GT)},
                {logkeys::tokens::G_LT, cr.c(G_TOKEN_LT)},
                {logkeys::tokens::G_SLASH, cr.r(G_TOKEN_SLASH)},
                {logkeys::tokens::G_QUESTION, cr.d(G_TOKEN_QUESTION)},
                {logkeys::tokens::G_DEBUG, cr.d(G_TOKEN_DEBUG)},
                {logkeys::tokens::G_INFO, cr.c(G_TOKEN_INFO)},
                {logkeys::tokens::G_WARNING, cr.y(G_TOKEN_WARNING)},
                {logkeys::tokens::G_ERROR, cr.m(G_TOKEN_ERROR)},
                {logkeys::tokens::G_FATAL, cr.r(G_TOKEN_FATAL)},
                {logkeys::tokens::G_XML_RECORD, cr.b(G_TOKEN_XML_RECORD)},
                {logkeys::tokens::G_XML_TIME, cr.r(G_TOKEN_XML_TIME)},
                {logkeys::tokens::G_XML_LEVEL, cr.y(G_TOKEN_XML_LEVEL)},
                {logkeys::tokens::G_XML_MESSAGE, cr.g(G_TOKEN_XML_MESSAGE)},
                {logkeys::tokens::G_XML_SEQUENCE, cr.y(G_TOKEN_XML_SEQUENCE)},
                {logkeys::tokens::G_XML_FILE, cr.b(G_TOKEN_XML_FILE)},
                {logkeys::tokens::G_XML_LINE, cr.c(G_TOKEN_XML_LINE)}};

            return map;
        }

        auto tokenmapOL() -> logtype::smap {

            const logtype::smap MAP{
                {logkeys::tokens::G_LEFT_BRACE, G_TOKEN_L_BRACE},
                {logkeys::tokens::G_RIGHT_BRACE, G_TOKEN_R_BRACE},
                {logkeys::tokens::G_LEFT_SQUARE_BRACKET, G_TOKEN_L_SQUARE_BRACKET},
                {logkeys::tokens::G_RIGHT_SQUARE_BRACKET, G_TOKEN_R_SQUARE_BRACKET},
                {logkeys::tokens::G_LEFT_PARENTHESIS, G_TOKEN_L_PARENTHESIS},
                {logkeys::tokens::G_SEQUENCE, G_TOKEN_SEQUENCE},
                {logkeys::tokens::G_TIME, G_TOKEN_TIME},
                {logkeys::tokens::G_LEVEL, G_TOKEN_LEVEL},
                {logkeys::tokens::G_MESSAGE, G_TOKEN_MESSAGE},
                {logkeys::tokens::G_FILE, G_TOKEN_FILE},
                {logkeys::tokens::G_LINE, G_TOKEN_LINE},
                {logkeys::tokens::G_COLON, G_TOKEN_COLON},
                {logkeys::tokens::G_COMMA, G_TOKEN_COMMA},
                {logkeys::tokens::G_EQUAL, G_TOKEN_EQUAL},
                {logkeys::tokens::G_QUOTE, G_TOKEN_QUOTE},
                {logkeys::tokens::G_GT, G_TOKEN_GT},
                {logkeys::tokens::G_LT, G_TOKEN_LT},
                {logkeys::tokens::G_SLASH, G_TOKEN_SLASH},
                {logkeys::tokens::G_QUESTION, G_TOKEN_QUESTION},
                {logkeys::tokens::G_DEBUG, G_TOKEN_DEBUG},
                {logkeys::tokens::G_INFO, G_TOKEN_INFO},
                {logkeys::tokens::G_WARNING, G_TOKEN_WARNING},
                {logkeys::tokens::G_ERROR, G_TOKEN_ERROR},
                {logkeys::tokens::G_FATAL, G_TOKEN_FATAL},
                {logkeys::tokens::G_XML_RECORD, G_TOKEN_XML_RECORD},
                {logkeys::tokens::G_XML_TIME, G_TOKEN_XML_TIME},
                {logkeys::tokens::G_XML_LEVEL, G_TOKEN_XML_LEVEL},
                {logkeys::tokens::G_XML_MESSAGE, G_TOKEN_XML_MESSAGE},
                {logkeys::tokens::G_XML_SEQUENCE, G_TOKEN_XML_SEQUENCE},
                {logkeys::tokens::G_XML_FILE, G_TOKEN_XML_FILE},
                {logkeys::tokens::G_XML_LINE, G_TOKEN_XML_LINE}};

            return MAP;
        }

    } // namespace logtoken_mapper

} // namespace ruac::rstd::logsystem
