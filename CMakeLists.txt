cmake_minimum_required(VERSION 3.20)
project(EntryPoint LANGUAGES CXX)

# Настройки компилятора
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Используем FetchContent для загрузки зависимостей
include(FetchContent)

# Загрузка fmt
FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git 
  GIT_TAG        master
)
FetchContent_MakeAvailable(fmt)

# Загрузка libpqxx
FetchContent_Declare(
    libpqxx
    GIT_REPOSITORY https://github.com/jtv/libpqxx.git
    GIT_TAG master
    GIT_SHALLOW TRUE
)

# Загрузка nlohmann_json
FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG master
    GIT_SHALLOW TRUE
)

# Загрузка TgBot
FetchContent_Declare(
    TgBot
    GIT_REPOSITORY https://github.com/reo7sp/tgbot-cpp.git
    GIT_TAG master
    GIT_SHALLOW TRUE
)

# Получаем зависимости
FetchContent_MakeAvailable(
    libpqxx
    nlohmann_json
    TgBot
)

# Для Boost используем системную установку
find_package(Boost 1.74 COMPONENTS system REQUIRED)

# Поиск системных библиотек
find_package(CURL REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(PostgreSQL REQUIRED)
find_package(ZLIB REQUIRED)
find_package(Threads REQUIRED)

# Библиотека Database
add_library(DatabaseLib STATIC)
target_include_directories(DatabaseLib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/DataBase/include
)

# Исключаем тестовые файлы
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

# Библиотека Google API
add_library(GoogleAPILib STATIC)

# Копирование JSON-файлов
set(GOOGLE_JSON_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Google API/json")
set(GOOGLE_JSON_DEST "${CMAKE_CURRENT_BINARY_DIR}/GoogleAPI/json")

# Создаем директорию для JSON файлов
file(MAKE_DIRECTORY "${GOOGLE_JSON_DEST}")

# Определение макроса для доступа к JSON-файлам
target_compile_definitions(GoogleAPILib PUBLIC 
    GOOGLE_JSON_PATH="${GOOGLE_JSON_DEST}"
)

target_include_directories(GoogleAPILib PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/Google API/inc"
)

# Исключаем тестовые файлы - ИСПРАВЛЕННЫЙ ПУТЬ
file(GLOB GOOGLE_SOURCES  # Убрали RECURSE так как в src нет поддиректорий
    "${CMAKE_CURRENT_SOURCE_DIR}/Google API/src/*.cpp"
)
message(STATUS "Google sources found: ${GOOGLE_SOURCES}")  # Для отладки

# Убедимся что app.log не попадает в список
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

# Основной исполняемый файл (tgBot)
add_executable(main)
target_include_directories(main PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/tgBot/include"
)

file(GLOB_RECURSE TGBOT_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/tgBot/source/*.cpp"
)
target_sources(main PRIVATE ${TGBOT_SOURCES})

# Линковка
target_link_libraries(main PRIVATE
    TgBot
    GoogleAPILib
    DatabaseLib
    Boost::system
    ${CMAKE_THREAD_LIBS_INIT}
)

# Копирование JSON-файлов при каждой сборке
add_custom_command(TARGET main PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${GOOGLE_JSON_DIR}"
        "${GOOGLE_JSON_DEST}"
    COMMENT "Copying Google API JSON files"
    VERBATIM
)

# Вывод информации о путях
message(STATUS "Google API JSON files located at: ${GOOGLE_JSON_DEST}")