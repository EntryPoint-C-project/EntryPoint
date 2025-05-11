cmake_minimum_required(VERSION 3.22)

project(ENTRYPOINT)

find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIR})

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

include_directories(
    ${PROJECT_SOURCE_DIR}/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/json
    /usr/include/nlohmann
    ${CURL_INCLUDE_DIR}
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

enable_testing()

add_executable(runTests
    tests/test_manageSOP.cpp
    src/manageSOP.cpp
)

target_link_libraries(runTests
    GTest::gtest_main
    ${CURL_LIBRARIES}
    pthread
)

include(GoogleTest)
gtest_discover_tests(runTests)