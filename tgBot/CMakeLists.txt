include(FetchContent)

# Добавляем библиотеку fmt
FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG 10.2.1  # Укажите актуальную версию 9.x
)

# Добавляем libpqxx
FetchContent_Declare(
    libpqxx
    GIT_REPOSITORY https://github.com/jtv/libpqxx.git
    GIT_TAG 7.6.0
)

# Загружаем зависимости
FetchContent_MakeAvailable(fmt libpqxx)

file(GLOB_RECURSE TGBOT_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp")
file(GLOB_RECURSE DATABASE_SOURCES "${CMAKE_SOURCE_DIR}/DataBase/source/*.cpp")
file(GLOB_RECURSE GOOGLE_API_SOURCES "${CMAKE_SOURCE_DIR}/Google API/src/*.cpp")

add_library(tgBotLib STATIC
    ${TGBOT_SOURCES}
    ${DATABASE_SOURCES}
    ${GOOGLE_API_SOURCES}
)

target_include_directories(tgBotLib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/DataBase/include
    ${CMAKE_SOURCE_DIR}/Google API/inc
)

# Явно указываем зависимости
target_link_libraries(tgBotLib PUBLIC
    pqxx
    pqxx-static  # Для статической линковки
    fmt::fmt
    PostgreSQL::PQ  # Добавляем официальный таргет для libpq
)