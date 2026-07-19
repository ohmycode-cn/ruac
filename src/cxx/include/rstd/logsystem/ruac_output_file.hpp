/**
 * C/C++ Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * Line Limit: Recommend line breaks at col: 96, force line breaks at col: 120
 * Date Time: 2026-07-19 11:50:19
 * Author: ohmycode-cn(ohcode@163.com)
 * Header File : include/rstd/logsystem/ruac_output_file.hpp
 * Source File : src/rstd/logsystem/ruac_output_file.cpp
 *
 * File Function Description:
 *
 *
 */

#pragma once
#ifndef RUAC_OUTPUT_FILE_HPP
#define RUAC_OUTPUT_FILE_HPP

#include "rstd/logsystem/ruac_output.hpp"

namespace ruac::rstd::logsystem {

    /**
     * @brief
     */
    class OutputFile : public Output {
      public:
        OutputFile() = default;
        ~OutputFile() = default;

      public:
    }; // class OutputFile

} // namespace ruac::rstd::logsystem

#endif // RUAC_OUTPUT_FILE_HPP
