include(FetchContent)

# libpqxx
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

file(GLOB_RECURSE GOOGLE_API_SOURCES
    "${CMAKE_SOURCE_DIR}/Google API/src/*.cpp"
)

add_library(tgBotLib STATIC
    ${TGBOT_SOURCES}
    ${DATABASE_SOURCES}
    ${GOOGLE_API_SOURCES}        # Добавили исходники Google API
)

target_include_directories(tgBotLib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/DataBase/include
        ${CMAKE_SOURCE_DIR}/Google API/inc      # Добавили include Google API
)

target_link_libraries(tgBotLib
    PUBLIC
        pqxx
        fmt::fmt    # Добавлено
)