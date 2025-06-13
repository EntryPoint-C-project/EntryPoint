include(FetchContent)

# libpqxx
FetchContent_Declare(
  libpqxx
  GIT_REPOSITORY https://github.com/jtv/libpqxx.git
  GIT_TAG 7.6.0
)
FetchContent_MakeAvailable(libpqxx)

# fmt
FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG 10.2.1  # или нужная версия
)
FetchContent_MakeAvailable(fmt)

file(GLOB_RECURSE TGBOT_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp"
)

file(GLOB_RECURSE DATABASE_SOURCES
    "${CMAKE_SOURCE_DIR}/DataBase/source/*.cpp"
)

file(GLOB_RECURSE GOOGLE_API_SOURCES
    "${CMAKE_SOURCE_DIR}/Google API/src/*.cpp"
)

add_library(tgBotLib STATIC
    ${TGBOT_SOURCES}
    ${DATABASE_SOURCES}
    ${GOOGLE_API_SOURCES}
)

target_include_directories(tgBotLib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/DataBase/include
        ${CMAKE_SOURCE_DIR}/Google API/inc
)

target_link_libraries(tgBotLib
    PUBLIC
        pqxx
        fmt::fmt
        TgBot::tgbot   # если используешь API из CPM библиотеки TgBot
)