/**
 * C/C++ Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * Line Limit: Recommend line breaks at col: 96, force line breaks at col: 120
 * Date Time: 2026-07-20 20:56:51
 * Author: ohmycode-cn(ohcode@163.com)
 * Header File : include/rstd/logsystem/ruac_factory.hpp
 * Source File : src/rstd/logsystem/ruac_factory.cpp
 *
 * File Function Description:
 *
 *
 */

#pragma once
#ifndef RUAC_FACTORY_HPP
#define RUAC_FACTORY_HPP

namespace ruac::rstd::logsystem {

    /**
     * @brief
     */
    class Factory {
      public:
        Factory() = default;
        ~Factory() = default;

      public:
        void write();
        void reinit();
    }; // class Factory

} // namespace ruac::rstd::logsystem

#endif // RUAC_FACTORY_HPP
