cmake_minimum_required(VERSION 3.22)

project(ENTRYPOINT)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git 
  GIT_TAG        master
)
FetchContent_MakeAvailable(fmt)

find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIR})

include(FetchContent)
FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git 
  GIT_TAG        master
)
FetchContent_MakeAvailable(fmt)

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
    src/logger.cpp
)

set(HEADERS
    inc/manageSOP.hpp
    inc/logger.hpp
)

add_executable(program ${SOURCES} ${HEADERS})
target_link_libraries(program ${CURL_LIBRARIES} fmt::fmt-header-only)

enable_testing()

set (TEST_SOURCES
    tests/test_manageSOP.cpp
    src/manageSOP.cpp
    src/logger.cpp
)

add_executable(run_test ${TEST_SOURCES} ${HEADERS})
target_link_libraries(run_test PRIVATE ${CURL_LIBRARIES} GTest::gtest_main fmt::fmt-header-only)
include(GoogleTest)
gtest_discover_tests(run_test)
