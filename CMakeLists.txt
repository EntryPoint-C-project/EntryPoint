cmake_minimum_required(VERSION 3.30)  
project(TelegramBot) 
# Устанавливаем стандарт C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) 

# Поиск необходимых библиотек
find_package(Boost REQUIRED COMPONENTS system) 
find_package(TgBot REQUIRED)                


include_directories(include)


file(GLOB SOURCES source/*.cpp) 


add_executable(my_bot ${SOURCES})


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