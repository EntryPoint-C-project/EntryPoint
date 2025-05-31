# tgBot/CMakeLists.txt

file(GLOB_RECURSE TGBOT_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp"
)

add_library(tgBotLib STATIC ${TGBOT_SOURCES})

target_include_directories(tgBotLib
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)