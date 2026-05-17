cmake_minimum_required(VERSION 3.10)

set(LIB_NAME "clf-utils")
project(test-${LIB_NAME})
message("=====================================================================")
message("                        Build ${PROJECT_NAME}")
message("=====================================================================")

set(MODULE_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")
set(REPO_ROOT "${MODULE_ROOT}/../../")
set(CMAKE_PREFIX_PATH "${REPO_ROOT}/install/")

include(${REPO_ROOT}/clf-cmake/clf.cmake)

# Find dependency
find_required_library(${LIB_NAME})

# Glob all the source files
add_executable(${PROJECT_NAME}
    main.cpp
)

target_link_libraries(${PROJECT_NAME} ${LIB_NAME})

# Common set
clf_common_set()

