/**
 * C/C++ Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * Line Limit: Recommend line breaks at col: 96, force line breaks at col: 120
 * Date Time: 2026-07-21 16:32:05
 * Author: ohmycode-cn(ohcode@163.com)
 * Header File : include/component/ruac_welcome.hpp
 * Source File : src/component/ruac_welcome.cpp
 *
 * File Function Description:
 *
 *
 */

#pragma once
#ifndef RUAC_WELCOME_HPP
#define RUAC_WELCOME_HPP

namespace ruac::component {

    /**
     * @brief
     */
    class Welcome {
      public:
        Welcome() = default;
        ~Welcome() = default;

      public:
        void promptMessage();
    }; // class Welcome

} // namespace ruac::component

#endif // RUAC_WELCOME_HPP
