#!/bin/bash
# *********************************************************************************************
# | Limit Line Length: Suggest wrapping in column 96 and forcing wrapping in column 120.
# | Author: .author
# | Date: 2026-07-15 17:31
# | Bash: Recommended using bash version 5.0 or higher
# | Bash Style Guide: RUAC-BASH-STYLE-GUIDE.md
# | Bash Style Inherited From: https://github.com/ohmycode-cn/codestyle/OMC-BASH-STYLE-GUIDE.md
# | Description: Shared library script.
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

CONST_TIME="$(date '+%F-%T')"; readonly CONST_TIME

L_BRACKET="${CYAN}[${RESET}"
R_BRACKET="${CYAN}]${RESET}"

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
    echo -e "${L_BRACKET}${MAGENTA}INFO${R_BRACKET} ${WHITE}${1}${RESET}"
}

# Function Description: Print a WARNING level message with color formatting.
#
# Args:
#    - param: The message string to display.
# Returns: Prints formatted message to stdout.
function msg_warning() {
    echo -e "${L_BRACKET}${YELLOW}WARNING${R_BRACKET} ${WHITE}${1}${RESET}"
}

# Function Description: Print an ERROR level message with color formatting.
#
# Args:
#    - param: The message string to display.
# Returns: Prints formatted message to stdout.
function msg_error() {
    echo -e "${L_BRACKET}${RED}ERROR${R_BRACKET} ${WHITE}${1}${RESET}"
}

# Function Description: Print a FATAL level message with color formatting.
#
# Args:
#    - param: The message string to display.
# Returns: Prints formatted message to stdout.
function msg_fatal() {
    echo -e "${L_BRACKET}${RED}FATAL${R_BRACKET} ${WHITE}${1}${RESET}"
}
