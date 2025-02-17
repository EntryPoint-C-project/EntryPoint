cmake_minimum_required(VERSION 3.22)

project(ENTRYPOINT)

find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIR})

include_directories(
    ${PROJECT_SOURCE_DIR}/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/json
    /usr/include/nlohmann
)

set (SOURCES
    src/main.cpp
    src/manageSOP.cpp
)

set(HEADERS
    inc/manageSOP.hpp
)

add_executable(program ${SOURCES} ${HEADERS})

target_link_libraries(program ${CURL_LIBRARIES})