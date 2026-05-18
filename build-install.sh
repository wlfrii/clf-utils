#!/bin/bash
clear

function build_vision_usage() {
    echo ">>> BUILD clf-project: usage: $0 [-t]"
    echo "    [-t] denotes that build corresponding test project"
}
build_vision_usage $0

build_dir="build"
need_build_test=false
while getopts "t" opt; do
    case $opt in        
        t)
            need_build_test=true
            ;;
        *)
            echo "Unknown input argument."
            exit 1
            ;;
    esac
done

# Build project
cmake -B "${build_dir}/" || exit 1
cd "${build_dir}/"
make -j8 || exit 1
make install
cd ../

# Check whether need to build corresponding test project.
if [ $need_build_test == "true" ]; then
    cd ./test/
    cmake -B "${build_dir}/" || exit 1
    cd "${build_dir}/"
    make || exit 1
fi
