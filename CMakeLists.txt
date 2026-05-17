cmake_minimum_required(VERSION 3.10)

project(clf-utils
        VERSION 1.0.0
        DESCRIPTION "Utility library for CLF."
        LANGUAGES CXX)
message("=====================================================================")
message("                        Build ${PROJECT_NAME}")
message("=====================================================================")

set(MODULE_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")
set(REPO_ROOT "${MODULE_ROOT}/..")
set(CMAKE_INSTALL_PREFIX "${REPO_ROOT}/install")

include(${REPO_ROOT}/clf-cmake/clf.cmake)

# Glob all the source files
file(GLOB_RECURSE SRCS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
add_library(${PROJECT_NAME} STATIC
    ${SRCS}
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/>
        $<INSTALL_INTERFACE:include/>
    PRIVATE
)

# Common set
clf_common_set()

target_compile_options(${PROJECT_NAME} PUBLIC -fPIC)
target_compile_options(${PROJECT_NAME} PRIVATE -DNDEBUG -O3 -Wall -Werror)

# Installation instructions
clf_lib_install()