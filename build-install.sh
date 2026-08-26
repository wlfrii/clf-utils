#!/usr/bin/env bash
set -euo pipefail

project_root="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
install_dir="${project_root}/../install"
cd "$project_root"

build_usage() {
    echo ">>> BUILD clf-utils: usage: $0 [-x] [-t]"
    echo "    [-x] clears existing build directories before building"
    echo "    [-t] builds the corresponding test project"
}
build_usage

build_dir="build"
need_rebuild=false
need_build_test=false
while getopts "xt" opt; do
    case "$opt" in
        x)
            need_rebuild=true
            echo ">>> BUILD in clean mode."
            ;;
        t)
            need_build_test=true
            echo ">>> BUILD in test mode."
            ;;
        *)
            echo "Unknown input argument."
            exit 1
            ;;
    esac
done

if [[ "$need_rebuild" == "true" && -d "$build_dir" ]]; then
    echo "Start a clean rebuild of clf-utils"
    cmake -E remove_directory "$build_dir"
fi

# Build project
cmake -S . -B "$build_dir" -DCMAKE_INSTALL_PREFIX="$install_dir"
cmake --build "$build_dir" --parallel
cmake --install "$build_dir"

# Check whether need to build corresponding test project.
if [[ "$need_build_test" == "true" ]]; then
    test_build_dir="test/$build_dir"
    if [[ "$need_rebuild" == "true" && -d "$test_build_dir" ]]; then
        cmake -E remove_directory "$test_build_dir"
    fi

    cmake -S test -B "$test_build_dir"
    cmake --build "$test_build_dir" --parallel
fi
