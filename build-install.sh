#!/bin/bash
clear

function build_vision_usage() {
    echo ">>> BUILD clf-project: usage: $0 [-x][-t]"
    echo "    [-x] denotes that clear the cache and rebuild test project"
    echo "    [-t] denotes that build corresponding test project"
}
build_vision_usage $0

build_dir="build"
need_rebuild=false
need_build_test=false
while getopts "xt" opt; do
    case $opt in
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

if [ $need_rebuild == "true" ]; then
    project_name="$(cat ${build_dir}/project_name.txt)"
    echo "Start to clear and rebuild ${project_name}"
    rm -r "${build_dir}/"

fi

# Build project
cmake -B "${build_dir}/" || exit 1
cd "${build_dir}/"
make -j8 || exit 1
make install
cd ../

# Check whether need to build corresponding test project.
if [ $need_build_test == "true" ]; then
    cd ./test/

    if [ $need_rebuild == "true" ]; then
        rm -r "${build_dir}/"
    fi

    cmake -B "${build_dir}/" || exit 1
    cd "${build_dir}/"
    make || exit 1
fi