#!/bin/bash
# *********************************************************************************************
# | Limit Line Length: Suggest wrapping in column 96 and forcing wrapping in column 120.
# | Author: .author
# | Date: 2026-07-15 17:31
# | Bash: Recommended using bash version 5.0 or higher
# | Bash Style Guide: RUAC-BASH-STYLE-GUIDE.md
# | Bash Style Inherited From: https://github.com/ohmycode-cn/codestyle/OMC-BASH-STYLE-GUIDE.md
# | Description: Initialize the project directory structure.
# |
# | Usage:
# |      1 - bash mkd.sh
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

inc="src/cxx/include"
src="src/cxx/src"
dir_name="${1}"
DIR_LIST=(
    "${inc}/${dir_name}"
    "${src}/${dir_name}"
)

# Function Description: Check if the target directory already exists or if the directory name is empty.
#
# Args: None.
# Returns: 0 if directory does not exist and name is valid, 1 otherwise.
function is_exist_directory() {
    if [[ -z "${dir_name}" ]]; then
        msg_fatal "You must provide a directory name."
        return 1
    fi

    for dir in "${DIR_LIST[@]}"; do
        if [[ -d "${dir}" ]]; then
            msg_fatal "Directory already exist you must provide a different directory name: ${dir_name}"
            return 1
        fi
    done

    return 0
}

# Function Description: Create the include and source directory structure under src/cxx/.
#
# Args: None.
# Returns: 0 on success, 1 if any directory creation fails.
function create_directory() {

    for dir in "${DIR_LIST[@]}"; do
        if ! mkdir -p "${dir}"; then
            msg_fatal "Failed to create directory: \"${dir}\"."
            return 1
        fi
    done

    msg_info "Directory structure created successfully."
    msg_info "-d include: ${inc}"
    msg_info "-d source : ${src}"
    return 0
}

# Function Description: Entry point that validates input and creates the project directory structure.
#
# Args: None.
# Returns: 0 on success, 1 on failure.
function main() {
    if ! is_exist_directory; then
        return 1
    fi
    create_directory
    return 0
}
main
exit 0
