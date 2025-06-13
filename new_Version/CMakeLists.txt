cmake_minimum_required(VERSION 3.10)
project(EP_dpw VERSION 1.0 LANGUAGES CXX)

# Настройка стандарта C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавляем пути поиска для Homebrew
list(APPEND CMAKE_PREFIX_PATH "/opt/homebrew/opt/libpqxx")
list(APPEND CMAKE_PREFIX_PATH "/opt/homebrew/opt/libpq")
list(APPEND CMAKE_PREFIX_PATH "/opt/homebrew/opt/fmt")
list(APPEND CMAKE_PREFIX_PATH "/opt/homebrew/opt/googletest")

# Поиск зависимостей
find_package(fmt REQUIRED)

# Для libpqxx используем альтернативный подход
find_path(LIBPQXX_INCLUDE_DIR pqxx/pqxx)
find_library(LIBPQXX_LIBRARY NAMES pqxx)

# Для PostgreSQL
find_package(PostgreSQL REQUIRED)

# Исходные файлы
file(GLOB SOURCES "source/*.cpp")
file(GLOB HEADERS "include/*.hpp")

# Исполняемый файл
add_executable(${PROJECT_NAME} 
    main.cpp 
    ${SOURCES} 
    ${HEADERS}
)

# Подключение заголовочных файлов
target_include_directories(${PROJECT_NAME} PRIVATE
    include/
    ${LIBPQXX_INCLUDE_DIR}
    ${PostgreSQL_INCLUDE_DIRS}
    ${FMT_INCLUDE_DIR}
)

# Линковка библиотек
target_link_libraries(${PROJECT_NAME} PRIVATE
    ${LIBPQXX_LIBRARY}
    ${PostgreSQL_LIBRARIES}
    fmt::fmt
)

# Подавление предупреждений
target_compile_options(${PROJECT_NAME} PRIVATE 
    -Wno-unknown-attributes
)