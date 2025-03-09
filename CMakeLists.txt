cmake_minimum_required(VERSION 3.10)
project(MyPQXXProject)

# Настройки для Apple Silicon
if(APPLE)
    set(CMAKE_CXX_FLAGS "-L/opt/homebrew/opt/libpqxx/lib -L/opt/homebrew/opt/libpq/lib")
    set(CMAKE_EXE_LINKER_FLAGS "-L/opt/homebrew/opt/libpqxx/lib -L/opt/homebrew/opt/libpq/lib")
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(app main.cpp)

# Пути для заголовочных файлов
target_include_directories(app PRIVATE
    /opt/homebrew/opt/libpqxx/include
    /opt/homebrew/opt/libpq/include
    /opt/homebrew/opt/fmt/include
)

# Пути к библиотекам
target_link_directories(app PRIVATE
    /opt/homebrew/opt/libpqxx/lib
    /opt/homebrew/opt/libpq/lib
)

# Явное указание библиотек
target_link_libraries(app PRIVATE
    /opt/homebrew/opt/libpqxx/lib/libpqxx.dylib
    /opt/homebrew/opt/libpq/lib/libpq.dylib
    /opt/homebrew/opt/fmt/lib/libfmt.dylib
)

# Подавление предупреждений
target_compile_options(app PRIVATE -Wno-unknown-attributes)