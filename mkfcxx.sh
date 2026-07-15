#!/bin/bash
# *********************************************************************************************
# | Limit Line Length: Suggest wrapping in column 96 and forcing wrapping in column 120.
# | Author: .author
# | Date: 2026-07-15 17:31
# | Bash: Recommended using bash version 5.0 or higher
# | Bash Style Guide: RUAC-BASH-STYLE-GUIDE.md
# | Bash Style Inherited From: https://github.com/ohmycode-cn/codestyle/OMC-BASH-STYLE-GUIDE.md
# | Description: Initialize the project c++ source and header files.
# | Usage:
# |      1 - bash mkfcxx.sh
# *********************************************************************************************
if [[ "${0}" != "${BASH_SOURCE[0]}" ]]; then
    echo -e "[EXECUTE ERROR]: Correct execute method is \"bash ${0}\""
    return 1 &>/dev/null
fi

readonly SHARED_LIB=".shared.sh"

if [[ ! -f "${SHARED_LIB}" ]]; then
    echo -e "[SOURCE ERROR]: Not found \"${SHARED_LIB}\" file. This is an important resource."
    return 1 &>/dev/null
elif [[ ! -r "${SHARED_LIB}" ]]; then
    echo -e "[SOURCE ERROR]: \"${SHARED_LIB}\" file is not readable. Please check the file permissions."
    return 1 &>/dev/null
fi

ONCE_RET=0
#shellcheck source=.shared.sh
source "${SHARED_LIB}"
ONCE_RET=${?}
if [[ ${ONCE_RET} -ne 0 ]]; then
    echo -e "[SOURCE ERROR]: Failed to source \"${SHARED_LIB}\" file. Please check the file content."
    return 1 &>/dev/null
fi
unset ONCE_RET # delete global variable ONCE_RET
