#!/bin/bash
# *********************************************************************************************
# | Limit Line Length: Suggest wrapping in column 96 and forcing wrapping in column 120.
# | Author: .author
# | Date: 2026-07-15 17:31
# | Bash: Recommended using bash version 5.0 or higher
# | Bash Style Guide: RUAC-BASH-STYLE-GUIDE.md
# | Bash Style Inherited From: https://github.com/ohmycode-cn/codestyle/OMC-BASH-STYLE-GUIDE.md
# | Description: Initialize the project C source and header files.
# | Usage:
# |      1 - bash mkfc.sh [path] [file_name]
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

function main() {
    local root_path
    root_path="$(pwd)"
    local inc="${root_path}/src/cxx/include"
    local src="${root_path}/src/cxx/src"

    local file_name_prefix="ruac_c_"
    local file="${file_name_prefix}${2}"
    local path="${1}"

    if [[ -z "${path}" ]]; then
        msg_warning "No path parameter, use default path: src/cc{include/ and src/}"
    else
        msg_info "Use path: src/cc{include/${path} and src/cc/src/${path}}"
        inc="${inc}/${path}"
        src="${src}/${path}"

    fi

    if [[ -z "${file}" ]]; then
        msg_error "No file parameter! You must provide a file name."
        return 1
    fi

    if [[ ! -d "${inc}" || ! -d "${src}" ]]; then
        msg_error "Include path 'src/cc/include/${path}' or src path 'src/cc/src/${path}' not exist!"
        return 1
    fi

    if [[ -f "${src}/${file}.c" || -f "${inc}/${file}.h" ]]; then
        msg_error "File ${file}.c or ${file}.h already exists, aborting."
        return 1
    fi

    local n_time
    n_time="$(date '+%Y-%m-%d %H:%M:%S')"

    local whoami
    whoami="$(cat .current_author.config | tr -d '\n\r\t')"

    local publuc_init_content=(
        "/**"
        " * C/C++ Style Guide: RUAC-CCXX-STYLE-GUIDE.md"
        " * Line Limit: Recommend line breaks at col: 96, force line breaks at col: 120"
        " * Date Time: ${n_time}"
        " * Author: ${whoami}"
        " * Header File : include/${path}/${file}.h"
        " * Source File : src/${path}/${file}.c"
        " * "
        " * File Function Description:"
        " * "
    )

    local upper_case_file_name="${file^^}_H"
    local header_init_content=(
        " * "
        " */"
        ""
        "#pragma once"
        "#ifndef ${upper_case_file_name}"
        "#define ${upper_case_file_name}"
        ""
        "#ifdef __cplusplus"
        "extern \"C\" {"
        "#endif"
        ""
        ""
        "#ifdef __cplusplus"
        "}"
        "#endif"
        ""
        "#endif /* ${upper_case_file_name} */"
    )

    local source_init_content=(
        " * "
        " */"
        ""
        "#include \"${path}/${file}.h\""
        ""
    )

    # init header file
    printf '%s\n' "${publuc_init_content[@]}" >"${inc}/${file}.h"
    printf '%s\n' "${header_init_content[@]}" >>"${inc}/${file}.h"

    # init source file
    printf '%s\n' "${publuc_init_content[@]}" >"${src}/${file}.c"
    printf '%s\n' "${source_init_content[@]}" >>"${src}/${file}.c"

    msg_info "Init done! (c and h){file: ${file}}"
}
main "$@"
exit 0
