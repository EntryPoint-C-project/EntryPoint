cmake_minimum_required(VERSION 3.20)
project(EntryPoint LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git 
  GIT_TAG        master
)
FetchContent_MakeAvailable(fmt)


FetchContent_Declare(
    libpqxx
    GIT_REPOSITORY https://github.com/jtv/libpqxx.git
    GIT_TAG master
    GIT_SHALLOW TRUE
)

FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG master
    GIT_SHALLOW TRUE
)

FetchContent_Declare(
    TgBot
    GIT_REPOSITORY https://github.com/reo7sp/tgbot-cpp.git
    GIT_TAG master
    GIT_SHALLOW TRUE
)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

FetchContent_MakeAvailable(
    libpqxx
    nlohmann_json
    TgBot
)

find_package(Boost 1.74 COMPONENTS system REQUIRED)

find_package(CURL REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(PostgreSQL REQUIRED)
find_package(ZLIB REQUIRED)
find_package(Threads REQUIRED)

add_library(DatabaseLib STATIC)
target_include_directories(DatabaseLib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/DataBase/include
)

file(GLOB_RECURSE DB_SOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/DataBase/source/*.cpp"
)
list(REMOVE_ITEM DB_SOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/DataBase/source/CreateAllTable.sql"
    "${CMAKE_CURRENT_SOURCE_DIR}/DataBase/source/DeleteAllTable.sql"
)

target_sources(DatabaseLib PRIVATE ${DB_SOURCES})
target_link_libraries(DatabaseLib PUBLIC
    pqxx
    fmt::fmt
)

add_library(GoogleAPILib STATIC)

set(GOOGLE_JSON_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Google API/json")
set(GOOGLE_JSON_DEST "${CMAKE_CURRENT_BINARY_DIR}/GoogleAPI/json")

file(MAKE_DIRECTORY "${GOOGLE_JSON_DEST}")

target_compile_definitions(GoogleAPILib PUBLIC 
    GOOGLE_JSON_PATH="${GOOGLE_JSON_DEST}"
)

target_include_directories(GoogleAPILib PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/Google API/inc"
)

file(GLOB GOOGLE_SOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/Google API/src/*.cpp"
)
message(STATUS "Google sources found: ${GOOGLE_SOURCES}")

list(FILTER GOOGLE_SOURCES EXCLUDE REGEX ".*app\\.log$")

list(REMOVE_ITEM GOOGLE_SOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/Google API/src/pre_main.cpp"
)

target_sources(GoogleAPILib PRIVATE ${GOOGLE_SOURCES})

target_link_libraries(GoogleAPILib PUBLIC
    CURL::libcurl
    OpenSSL::SSL
    OpenSSL::Crypto
    fmt::fmt
    nlohmann_json
    DatabaseLib
)

add_executable(main)
target_include_directories(main PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/tgBot/include"
)

file(GLOB_RECURSE TGBOT_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/tgBot/source/*.cpp"
)
target_sources(main PRIVATE ${TGBOT_SOURCES})

target_link_libraries(main PRIVATE
    TgBot
    GoogleAPILib
    DatabaseLib
    Boost::system
    ${CMAKE_THREAD_LIBS_INIT}
)

add_custom_command(TARGET main PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${GOOGLE_JSON_DIR}"
        "${GOOGLE_JSON_DEST}"
    COMMENT "Copying Google API JSON files"
    VERBATIM
)

add_executable(tests)
target_sources(tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/AllTests.cpp
)

target_include_directories(tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/DataBase/include
    ${CMAKE_CURRENT_SOURCE_DIR}/GoogleAPI/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/tgBot/include
)

target_link_libraries(tests PRIVATE
    GTest::gtest_main
    DatabaseLib
    GoogleAPILib
    TgBot
    Boost::system
    ${CMAKE_THREAD_LIBS_INIT}
    pqxx
    fmt::fmt
    nlohmann_json
    CURL::libcurl
    OpenSSL::SSL
    OpenSSL::Crypto
)

add_custom_command(TARGET tests PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${GOOGLE_JSON_DIR}"
        "${GOOGLE_JSON_DEST}"
    COMMENT "Copying Google API JSON files for tests"
    VERBATIM
)


include(GoogleTest)
gtest_discover_tests(tests
    EXTRA_ARGS --gtest_output=xml:${CMAKE_BINARY_DIR}/test-results.xml
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
