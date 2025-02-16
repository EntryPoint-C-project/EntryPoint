cmake_minimum_required(VERSION 3.10)

# Название проекта (можете изменить)
project(CreateAllTables)

# Указываем стандарт C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Пути к заголовочным файлам (если у вас есть собственные .hpp в других папках, добавьте их)
include_directories(
    /opt/homebrew/opt/libpqxx/include
    /opt/homebrew/opt/libpq/include
)

# Пути к библиотекам
link_directories(
    /opt/homebrew/opt/libpqxx/lib
    /opt/homebrew/opt/libpq/lib
)

# Собираем проект из нескольких файлов
# Добавьте/удалите .cpp-файлы по необходимости
add_executable(app
    main.cpp
    FunctionsForCreateAllTables.cpp
    FunctionsForTable_all_people.cpp
)

# Линкуем библиотеки libpqxx и libpq
target_link_libraries(app PRIVATE pqxx pq)

# Отключаем предупреждения об атрибуте [[assume]] (libpqxx)
target_compile_options(app PRIVATE -Wno-unknown-attributes)
