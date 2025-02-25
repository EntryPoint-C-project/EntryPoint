cmake_minimum_required(VERSION 3.10)  # Указываем минимальную версию CMake
project(TelegramBot)  # Указываем имя проекта

# Устанавливаем стандарт C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # Длдя генерации какого-то файлика clang-tidy

# Поиск необходимых библиотек
find_package(Boost REQUIRED COMPONENTS system) # Ищем Boost (модуль system)
find_package(TgBot REQUIRED)                  # Ищем библиотеку TgBot

# Указываем путь к заголовочным файлам
include_directories(include) # Например, папка "inc" для .hpp файлов

# Собираем список исходников
file(GLOB SOURCES source/*.cpp) # Собираем все .cpp файлы в папке src

# Создаём исполняемый файл
add_executable(my_bot ${SOURCES}) # Компилируем все найденные .cpp файлы

# Линкуем с найденными библиотеками
target_link_libraries(my_bot Boost::system TgBot::TgBot)


if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(my_bot PRIVATE
        -g
        -fsanitize=address,undefined
        -fno-omit-frame-pointer
    )
    target_link_options(my_bot PRIVATE
        -fsanitize=address,undefined
        -fno-omit-frame-pointer
    )
endif()