file(GLOB_RECURSE BD_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp"
)

add_library(DataBaseLib STATIC ${BD_SOURCES})

target_include_directories(DataBaseLib
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)