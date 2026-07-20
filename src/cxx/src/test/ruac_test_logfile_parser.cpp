/**
 * C/C++ Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * Line Limit: Recommend line breaks at col: 96, force line breaks at col: 120
 * Date Time: 2026-07-20 10:42:23
 * Author: ohmycode-cn(ohcode@163.com)
 * Header File : include/test/ruac_test_logfile_parser.hpp
 * Source File : src/test/ruac_test_logfile_parser.cpp
 *
 * File Function Description:
 *
 *
 */

#include "test/ruac_test_logfile_parser.hpp"
#include "rstd/logsystem/ruac_loadconf.hpp"
#include <iostream>

namespace ruac::test {

    void testLogfileParser00() {

        auto loadconf = new ruac::rstd::logsystem::LoadConf("/home/repox/Engineering/ruacdbv01/ruacdb/config",
                                                            "ruacdb.log.conf");
        if (!loadconf->ret()) {
            return;
        }

        auto confmap = loadconf->getConfigMap();

        delete loadconf;
        loadconf = nullptr;

        if (confmap.empty()) {
            return;
        }

        for (auto &item : confmap) {
            std::cout << item.first << " = " << item.second << std::endl;
        }
    }

} // namespace ruac::test
