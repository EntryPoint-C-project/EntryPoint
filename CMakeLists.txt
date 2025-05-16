cmake_minimum_required(VERSION 3.22)

project(ENTRYPOINT)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIR})

include_directories(
    ${PROJECT_SOURCE_DIR}/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/json
    /usr/include/nlohmann
    ${CURL_INCLUDE_DIR}
)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

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

set (TEST_SOURCES
    tests/test_manageSOP.cpp
    src/manageSOP.cpp
)

add_executable(run_test ${TEST_SOURCES} ${HEADERS})
target_link_libraries(run_test ${CURL_LIBRARIES} GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(run_test)
