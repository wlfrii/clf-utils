<<<<<<< HEAD
cmake_minimum_required(VERSION 3.20)
=======
cmake_minimum_required(VERSION 3.18)
>>>>>>> e6fed90 (update with the optim from codex)

project(clf-utils
        VERSION 1.0.0
        DESCRIPTION "Utility library for CLF."
        LANGUAGES CXX)
message("=====================================================================")
message("                        Build ${PROJECT_NAME}")
message("=====================================================================")

set(MODULE_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")
set(REPO_ROOT "${MODULE_ROOT}/..")
include("${REPO_ROOT}/clf-cmake/clf.cmake")
include(GNUInstallDirs)

find_package(Threads REQUIRED)

# Glob all the source files
file(GLOB_RECURSE SRCS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_library(${PROJECT_NAME} STATIC
    ${SRCS}
)

target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# Common set
clf_common_set()

set_target_properties(${PROJECT_NAME} PROPERTIES POSITION_INDEPENDENT_CODE ON)

# Installation instructions
clf_lib_install(TARGET ${PROJECT_NAME})
