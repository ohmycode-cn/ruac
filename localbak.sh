#!/bin/bash
# *********************************************************************************************
# | Limit Line Length: Suggest wrapping in column 96 and forcing wrapping in column 120.
# | Author: .author
# | Date: 2026-07-15 17:31
# | Bash: Recommended using bash version 5.0 or higher
# | Bash Style Guide: RUAC-BASH-STYLE-GUIDE.md
# | Bash Style Inherited From: https://github.com/ohmycode-cn/codestyle/OMC-BASH-STYLE-GUIDE.md
# | Description: Create a timestamped tar.gz archive of the project directory
# |              for local backup and disaster recovery purposes.
# | Usage:
# |      1 - bash localbak.sh              (default backup)
# |      2 - bash localbak.sh "hotfix"     (backup with custom suffix)
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

# Function Description: Create a compressed tar.gz archive of the project source
#    directory and store it under the configured backup destination path. The
#    archive filename includes a timestamp and an optional user-supplied suffix.
#
# Args:
#    - param1: Optional suffix string to append to the backup filename.
# Returns: 0 on success, 1 on failure.
function backup_project() {
    local backup_src="/home/repox/Engineering/ruac/ruacdb"
    local backup_dst="/home/repox/Engineering/ruac/backup"

    local backup_time
    backup_time="$(date '+%F-%H-%M-%S')"
    local backup_cnt="${1}"

    local backup_name="ruac-${backup_time}.tar.gz"

    if [[ ! -z "${backup_cnt}" ]]; then
        backup_name="ruac-${backup_time}-${backup_cnt}.tar.gz"
    fi

    if ! command -v tar &>/dev/null; then
        msg_error "tar command is not found. Please manually install it."
        return 1
    fi

    if ! tar -czf "${backup_dst}/${backup_name}" "${backup_src}"; then
        msg_error "tar command failed. Please check the command arguments."
        return 1
    fi

    msg_info "'${backup_name}' backup file is created !\n\tBackup path: ${backup_dst}"
    return 0
}

# Function Description: Entry point of the backup script.
#
# Args:
#    - param1: Optional suffix string for the backup filename.
# Returns: 0 on success, 1 on failure.
function main() {
    backup_project "${1}"
    return 0
}
main "${1}"
exit 0
