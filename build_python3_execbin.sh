#!/bin/bash
# *********************************************************************************************
# | Limit Line Length: Suggest wrapping in column 96 and forcing wrapping in column 120.
# | Author: .author
# | Date: 2026-07-17 18:00
# | Bash: Recommended using bash version 5.0 or higher
# | Bash Style Guide: RUAC-BASH-STYLE-GUIDE.md
# | Bash Style Inherited From: https://github.com/ohmycode-cn/codestyle/OMC-BASH-STYLE-GUIDE.md
# | Description: Compile a Python3 source file into a standalone, dependency-free
# |              executable binary via Nuitka. All build artifacts are confined to
# |              the build_py3 directory; the final binary is placed in
# |              src/cxx/include/rstd/flib/ without a .bin suffix.
# | Usage:
# |      1 - bash build_python3_execbin.sh <file_name> [force]
# |          Example: bash build_python3_execbin.sh "ruac_py3_getosinfo"
# |          Example: bash build_python3_execbin.sh "ruac_py3_getosinfo" force
# |          Note: <file_name> and [force] can be in any order.
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

# Function Description: Set up an isolated Python virtual environment in the build
#    directory and install Nuitka and its dependencies into it. Skips creation if
#    the venv already exists.
#
# Args:
#    - param1: The build directory path where the venv will be created.
# Returns: 0 on success, 1 on failure.
function setup_venv() {
    local build_dir="${1}"
    local venv_dir="${build_dir}/venv"

    if [[ -d "${venv_dir}" ]]; then
        msg_info "Virtual environment already exists, skipping creation."
        return 0
    fi

    msg_info "Creating isolated virtual environment in build_py3/venv ..."
    if ! python3 -m venv "${venv_dir}" 2>&1; then
        msg_fatal "Failed to create virtual environment."
        return 1
    fi

    msg_info "Installing Nuitka and dependencies into venv ..."
    if ! "${venv_dir}/bin/pip" install --quiet nuitka psutil patchelf 2>&1; then
        msg_fatal "Failed to install Nuitka or dependencies."
        return 1
    fi

    msg_info "Virtual environment ready."
    return 0
}

# Function Description: Compile a Python source file into a standalone onefile
#    executable using Nuitka. The binary is placed in the specified output
#    directory with the given name (no extension). All intermediate artifacts
#    are confined to the build directory.
#
# Args:
#    - param1: Absolute path to the Python source file.
#    - param2: The build directory for intermediate artifacts.
#    - param3: The output directory for the final binary.
#    - param4: The output binary name (without extension).
# Returns: 0 on success, 1 on failure.
function compile_python() {
    local src_file="${1}"
    local build_dir="${2}"
    local output_dir="${3}"
    local bin_name="${4}"
    local venv_dir="${build_dir}/venv"

    msg_info "Compiling ${src_file} via Nuitka ..."

    local ret
    ret=1
    # Ensure venv binaries are on PATH so Nuitka can find patchelf
    PATH="${venv_dir}/bin:${PATH}" \
        "${venv_dir}/bin/python" -m nuitka \
        --onefile \
        --standalone \
        --output-dir="${build_dir}" \
        --output-filename="${bin_name}" \
        --remove-output \
        --no-progress \
        "${src_file}" 2>&1
    ret=${?}

    if [[ ${ret} -ne 0 ]]; then
        msg_fatal "Nuitka compilation failed."
        return 1
    fi

    if [[ ! -f "${build_dir}/${bin_name}" ]]; then
        msg_fatal "Compiled binary not found: ${build_dir}/${bin_name}"
        return 1
    fi

    cp "${build_dir}/${bin_name}" "${output_dir}/${bin_name}"
    ret=${?}
    if [[ ${ret} -ne 0 ]]; then
        msg_fatal "Failed to copy binary to output directory."
        return 1
    fi

    chmod +x "${output_dir}/${bin_name}"
    msg_info "Build successful: ${output_dir}/${bin_name}"
    return 0
}

# Function Description: Clean the build directory, removing all contents except
#    the virtual environment directory to avoid redundant reinstallation.
#
# Args:
#    - param1: The build directory path.
# Returns: 0 on success.
function clean_build_dir() {
    local build_dir="${1}"

    if [[ ! -d "${build_dir}" ]]; then
        return 0
    fi

    msg_info "Cleaning build directory: ${build_dir}"
    local item
    for item in "${build_dir}"/*; do
        if [[ ! -e "${item}" ]]; then
            continue
        fi
        local base_name
        base_name="$(basename "${item}")"
        if [[ "${base_name}" == "venv" ]]; then
            continue
        fi
        rm -rf "${item}"
    done

    msg_info "Build directory cleaned (venv preserved)."
    return 0
}

# Function Description: Entry point of the Python3 binary build script. Parses
#    arguments (order-independent), validates paths, cleans the build directory,
#    checks for existing output binary, and orchestrates compilation.
#
# Args:
#    - param1: The Python file name without .py extension, or "force".
#    - param2: Optional; the other of file_name or "force".
# Returns: 0 on success, 1 on failure.
function main() {
    local file_name=""
    local force_mode=0

    # Parse arguments: identify file_name and force flag (order-independent)
    local arg
    for arg in "${@}"; do
        if [[ "${arg}" == "force" ]]; then
            force_mode=1
        else
            file_name="${arg}"
        fi
    done

    if [[ -z "${file_name}" ]]; then
        msg_error "No file name parameter provided."
        msg_info "Usage: bash build_python3_execbin.sh <file_name> [force]"
        msg_info "Example: bash build_python3_execbin.sh \"ruac_py3_getosinfo\""
        msg_info "Example: bash build_python3_execbin.sh \"ruac_py3_getosinfo\" force"
        return 1
    fi

    local root_path
    root_path="$(pwd)"

    local src_dir="${root_path}/src/rpy"
    local src_file="${src_dir}/${file_name}.py"
    local build_dir="${root_path}/build_py3"
    local output_dir="${root_path}/flib"
    local output_bin="${output_dir}/${file_name}"

    if [[ ! -f "${src_file}" ]]; then
        msg_error "Source file not found: ${src_file}"
        return 1
    fi

    if [[ ! -d "${output_dir}" ]]; then
        msg_error "Output directory not found: ${output_dir}"
        return 1
    fi

    # Check if output binary already exists
    if [[ -f "${output_bin}" ]]; then
        if [[ ${force_mode} -eq 1 ]]; then
            msg_warning "Output binary already exists, force mode enabled. Removing: ${output_bin}"
            rm -f "${output_bin}"
        else
            msg_error "Output binary already exists: ${output_bin}"
            msg_info "Please manually delete it first:"
            msg_info "  rm -f \"${output_bin}\""
            msg_info "Or use force mode to auto-delete:"
            msg_info "  bash build_python3_execbin.sh \"${file_name}\" force"
            return 1
        fi
    fi

    # Clean build directory (preserve venv)
    clean_build_dir "${build_dir}"

    if [[ ! -d "${build_dir}" ]]; then
        mkdir -p "${build_dir}"
    fi

    local ret
    ret=1
    setup_venv "${build_dir}"
    ret=${?}
    if [[ ${ret} -ne 0 ]]; then
        return 1
    fi

    init_pid "draw_spinner" "Compiling ${file_name}"
    compile_python "${src_file}" "${build_dir}" "${output_dir}" "${file_name}"
    local compile_ret=${?}
    kill_pid

    if [[ ${compile_ret} -ne 0 ]]; then
        return 1
    fi

    return 0
}
main "$@"
exit 0
