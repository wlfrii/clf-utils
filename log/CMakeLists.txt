cmake_minimum_required(VERSION 3.20)

project(tiny_logger)

set(CMAKE_CXX_STANDARD 17)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()
# Manually link pthread to adapt to old linux distribution.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread")

add_executable(${PROJECT_NAME}
    main.cpp
    tiny_logger.cpp
)