cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(MyProject)

# Подключаем сторонние библиотеки через CPM
include(cmake/CPM.cmake)

CPMAddPackage(
  NAME Boost
  VERSION 1.86.0
  URL https://github.com/boostorg/boost/releases/download/boost-1.86.0/boost-1.86.0-cmake.tar.xz
  URL_HASH SHA256=2c5ec5edcdff47ff55e27ed9560b0a0b94b07bd07ed9928b476150e16b0efc57
  OPTIONS "BOOST_ENABLE_CMAKE ON" "BOOST_SKIP_INSTALL_RULES ON"
          "BUILD_SHARED_LIBS OFF" "BOOST_INCLUDE_LIBRARIES system"
)

CPMAddPackage(
  NAME TgBot
  GIT_REPOSITORY https://github.com/reo7sp/tgbot-cpp.git
  GIT_TAG master
)

CPMAddPackage(
  NAME nlohmann_json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.11.2
)

CPMAddPackage(
  NAME libcurl
  GIT_REPOSITORY https://github.com/curl/curl.git
  GIT_TAG curl-8_1_2
  OPTIONS "BUILD_CURL_EXE OFF" "BUILD_TESTING OFF"
)

CPMAddPackage(
  NAME libpqxx
  GIT_REPOSITORY https://github.com/jtv/libpqxx.git
  GIT_TAG 7.6.0
)

CPMAddPackage(
  NAME fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG 10.2.1
)

# Добавляем поддиректорию tgBot
add_subdirectory(tgBot)

# Указываем путь к main.cpp
set(MAIN_SOURCES
    tgBot/source/main.cpp
)

add_executable(main ${MAIN_SOURCES})

target_include_directories(main PRIVATE tgBot/include)

target_link_libraries(main
  Boost::system
  TgBot
  nlohmann_json::nlohmann_json
  curl
  pqxx
  fmt::fmt
  tgBotLib
)
