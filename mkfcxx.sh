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
# |      1 - bash mkfcxx.sh [path] [file_name]
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
    local namespace="ruac"

    local file_name_prefix="ruac_"
    local file="${file_name_prefix}${2}"
    local path="${1}"

    if [[ -z "${path}" ]]; then
        msg_warning "No path parameter, use default path: src/cxx{include/ and src/}"
    else
        msg_info "Use path: src/cxx{include/${path} and src/cxx/src/${path}}"
        inc="${inc}/${path}"
        src="${src}/${path}"
        # change path '/' to '::', e.g a/b/c -> ruac::a::b::c
        namespace="ruac::${path//\//::}"
    fi

    if [[ -z "${file}" ]]; then
        msg_error "No file parameter! You must provide a file name."
        return 1
    fi

    if [[ ! -d "${inc}" || ! -d "${src}" ]]; then
        msg_error "Include path 'src/cxx/include/${path}' or src path 'src/cxx/src/${path}' not exist!"
        return 1
    fi

    if [[ -f "${src}/${file}.cpp" || -f "${inc}/${file}.hpp" ]]; then
        msg_error "File ${file}.cpp or ${file}.hpp already exists, aborting."
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
        " * Header File : include/${path}/${file}.hpp"
        " * Source File : src/${path}/${file}.cpp"
        " * "
        " * File Function Description:"
        " * "
    )

    local upper_case_file_name="${file^^}_HPP"
    local header_init_content=(
        " * "
        " */"
        ""
        "#pragma once"
        "#ifndef ${upper_case_file_name}"
        "#define ${upper_case_file_name}"
        ""
        "namespace ${namespace} {"
        ""
        "    /**"
        "     * @brief "
        "     */"
        "    class REPLACE_ME {"
        "       public:"
        "           REPLACE_ME() = default;"
        "           ~REPLACE_ME() = default;"
        "       public:"
        "    }; // class REPLACE_ME"
        ""
        "} // namespace ${namespace}"
        ""
        "#endif // ${upper_case_file_name}"
    )

    local source_init_content=(
        " * "
        " */"
        ""
        "#include \"${path}/${file}.hpp\""
        ""
        "namespace ${namespace} {"
        "} // namespace ${namespace}"
    )

    # init header file
    printf '%s\n' "${publuc_init_content[@]}" >"${inc}/${file}.hpp"
    printf '%s\n' "${header_init_content[@]}" >>"${inc}/${file}.hpp"

    # init source file
    printf '%s\n' "${publuc_init_content[@]}" >"${src}/${file}.cpp"
    printf '%s\n' "${source_init_content[@]}" >>"${src}/${file}.cpp"

    msg_info "Init done! (cpp and hpp){file: ${file}}"
}
main "$@"
exit 0
