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
target_link_libraries(tgBotLib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/build/_deps/libpqxx-build/src/libpqxx-7.6.a
)

target_include_directories(tgBotLib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/DataBase/include
)
