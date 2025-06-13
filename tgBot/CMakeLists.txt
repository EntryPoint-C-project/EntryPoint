# В tgBot/CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(TelegramBot)

include(FetchContent)

FetchContent_Declare(
  libpqxx
  GIT_REPOSITORY https://github.com/jtv/libpqxx.git
  GIT_TAG 7.6.0
)

FetchContent_MakeAvailable(libpqxx)

file(GLOB_RECURSE TGBOT_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp"
)

file(GLOB_RECURSE DATABASE_SOURCES
    "${CMAKE_SOURCE_DIR}/DataBase/source/*.cpp"
)

add_library(tgBotLib STATIC
    ${TGBOT_SOURCES}
    ${DATABASE_SOURCES}
)

target_include_directories(tgBotLib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/DataBase/include
)

target_link_libraries(tgBotLib
    PUBLIC
        pqxx
        fmt::fmt    # Добавить эту строку!
)
