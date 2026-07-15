#!/bin/bash
# *********************************************************************************************
# | Limit Line Length: Suggest wrapping in column 96 and forcing wrapping in column 120.
# | Author: .author
# | Date: 2026-07-15 17:31
# | Bash: Recommended using bash version 5.0 or higher
# | Bash Style Guide: RUAC-BASH-STYLE-GUIDE.md
# | Bash Style Inherited From: https://github.com/ohmycode-cn/codestyle/OMC-BASH-STYLE-GUIDE.md
# | Description: Shared utility library providing color-coded terminal output,
# |              logging helpers, background process management, and spinner
# |              animation primitives for the RUAC project scripts.
# | Usage:
# |      1 - source .shared.sh
# *********************************************************************************************
# Function Description: Check if the script is loaded via source, exit if executed directly.
#
# Args: None.
# Returns: 0 if sourced correctly, 1 if executed directly.
function source_check() {
    if [[ "${0}" == "${BASH_SOURCE[0]}" ]]; then
        echo -e "[SOURCE ERROR]: You must use \"source .shared.sh\" to load this shared library script !"
        return 1
    fi
    return 0
}
source_check

# Define ANSI sequence: 0 and 30 ~ 37, style 0.

# shellcheck disable=SC2034
readonly RESET="\033[0;0m"
readonly BLACK="\033[0;30m"
readonly RED="\033[0;31m"
readonly GREEN="\033[0;32m"
readonly YELLOW="\033[0;33m"
readonly BLUE="\033[0;34m"
readonly MAGENTA="\033[0;35m"
readonly CYAN="\033[0;36m"
readonly WHITE="\033[0;37m"
readonly BOLD_BLACK="\033[1;30m"
readonly BOLD_RED="\033[1;31m"
readonly BOLD_GREEN="\033[1;32m"
readonly BOLD_YELLOW="\033[1;33m"
readonly BOLD_BLUE="\033[1;34m"
readonly BOLD_MAGENTA="\033[1;35m"
readonly BOLD_CYAN="\033[1;36m"
readonly BOLD_WHITE="\033[1;37m"

CONST_TIME="$(date '+%F-%T')"
L_BRACKET="${CYAN}[${RESET}"
R_BRACKET="${CYAN}]${RESET}"

# Count PID value. default is 0.
COUNT_SINGLETON_PID=0
# Found function name in func list.
FOUND_FUNCTION_NAME=1

# Function Description: Print current timestamp without color formatting.
#
# Args: None.
# Returns: Prints formatted timestamp to stdout.
function now_time_noh() {
    echo -e "[$(date '+%F-%T')]"
}

# Function Description: Print current timestamp with ANSI color formatting.
#
# Args: None.
# Returns: Prints colored formatted timestamp to stdout.
function now_time() {
    echo -e "${L_BRACKET}${MAGENTA}$(date '+%F-%T')${R_BRACKET}"
}

# Function Description: Print an INFO level message with color formatting.
#
# Args:
#    - param: The message string to display.
# Returns: Prints formatted message to stdout.
function msg_info() {
    echo -e "${L_BRACKET}${BOLD_MAGENTA}INFO${R_BRACKET} ${WHITE}${1}${RESET}"
}

# Function Description: Print a WARNING level message with color formatting.
#
# Args:
#    - param: The message string to display.
# Returns: Prints formatted message to stdout.
function msg_warning() {
    echo -e "${L_BRACKET}${BOLD_YELLOW}WARNING${R_BRACKET} ${YELLOW}${1}${RESET}"
}

# Function Description: Print an ERROR level message with color formatting.
#
# Args:
#    - param: The message string to display.
# Returns: Prints formatted message to stdout.
function msg_error() {
    echo -e "${L_BRACKET}${BOLD_RED}ERROR${R_BRACKET} ${RED}${1}${RESET}"
}

# Function Description: Print a FATAL level message with color formatting.
#
# Args:
#    - param: The message string to display.
# Returns: Prints formatted message to stdout.
function msg_fatal() {
    echo -e "${L_BRACKET}${BOLD_RED}FATAL${R_BRACKET} ${MAGENTA}${1}${RESET}"
}

# Function Description: Display a spinning moon animation with a message.
#
# Args:
#    - param: The message string to display alongside the spinner.
# Returns: Clears the spinner line upon completion.
function draw_spinner() {
    local spinner_moon=("🌑" "🌒" "🌓" "🌔" "🌕" "🌖" "🌗" "🌘")
    local message_strs="${1}"
    while true; do
        for item in "${spinner_moon[@]}"; do
            printf "\r %s %s" "${message_strs}" "${item}"
            sleep 0.1
        done
    done
    echo -en "$(printf "\r%49s" ' ')\r"
}

# Function Description: Start a function in background and store its PID for later cleanup.
#
# Args:
#    - param1: The function name to launch (must be in the allowed function list).
#    - param2: Optional arguments string to pass to the function.
# Returns: 0 on success, 1 if function name is invalid or empty.
function init_pid() {
    local func_list=("draw_spinner")
    local func_name="${1}"
    local func_args="${2}"

    if [[ -z "${func_name}" ]]; then
        msg_error "Function name is empty. You must provide a function name."
        return 1
    fi

    for item in "${func_list[@]}"; do
        if [[ "${item}" == "${func_name}" ]]; then
            FOUND_FUNCTION_NAME=0
            break
        fi
    done

    if [[ ${FOUND_FUNCTION_NAME} -eq 1 ]]; then
        msg_error "Function name ${func_name} is not in func list."
        return 1
    fi

    if [[ -z ${func_args} ]]; then
        func_args=""
    fi

    tput civis
    ${func_name} "${func_args}" &
    COUNT_SINGLETON_PID=${!}
}

# Function Description: Kill the background process by stored PID and restore cursor visibility.
#
# Args: None.
# Returns: 0 on success, 1 if PID is invalid or empty.
function kill_pid() {
    local pid=${COUNT_SINGLETON_PID}
    if [[ -z "${pid}" || ${pid} == 0 ]]; then
        msg_error "You did not provide a valid pid, it is empty."
        return 1
    fi

    kill -9 "${pid}" 2>/dev/null
    wait "${pid}" 2>/dev/null
    printf "\r%$(tput cols)s\r"
    tput cnorm
    COUNT_SINGLETON_PID=0
}

# Function Description: Sleep for a specified number of seconds. If no argument
#    is provided or the argument is empty, defaults to 1 second.
#
# Args:
#    - param1: Optional number of seconds to sleep; defaults to 1.
# Returns: 0 on success.
function wait_seconds() {
    if [[ -z "${1}" ]]; then
        sleep 1
    else
        sleep "${1}"
    fi
}
