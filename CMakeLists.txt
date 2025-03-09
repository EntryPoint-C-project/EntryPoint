cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(MyProject)

include_directories(include)

file(GLOB SOURCES source/*.cpp) 

add_executable(main ${SOURCES})

include(cmake/CPM.cmake)

CPMAddPackage(
  NAME Boost
  VERSION 1.86.0
  URL https://github.com/boostorg/boost/releases/download/boost-1.86.0/boost-1.86.0-cmake.tar.xz
  URL_HASH SHA256=2c5ec5edcdff47ff55e27ed9560b0a0b94b07bd07ed9928b476150e16b0efc57
  OPTIONS "BOOST_ENABLE_CMAKE ON" "BOOST_SKIP_INSTALL_RULES ON"
          "BUILD_SHARED_LIBS OFF" "BOOST_INCLUDE_LIBRARIES system"
)

CPMAddPackage(
  NAME TgBot
  GIT_REPOSITORY https://github.com/reo7sp/tgbot-cpp.git
  GIT_TAG master  
)

target_link_libraries(main 
  Boost::system 
  TgBot 
)
