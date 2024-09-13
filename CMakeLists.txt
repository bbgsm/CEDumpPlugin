cmake_minimum_required(VERSION 3.28)
project(CEDumpPlugin)
include_directories(./)
include_directories(Memory)
include_directories(Hooks)
include_directories(CheatEngine)
include_directories(memoryTools)

file(GLOB_RECURSE CE_PLUGIN_SOURCES "main.cpp" "Hooks/*.*" "./*.h" "./*.hpp" "./*.def")
file(GLOB_RECURSE MEMORY_TOOLS_SOURCES "memoryTools/*.cpp" "memoryTools/*.h" "memoryTools/*.hpp")

set(CMAKE_CXX_STANDARD 20)

add_library(CEDumpPlugin SHARED ${CE_PLUGIN_SOURCES} ${MEMORY_TOOLS_SOURCES})
add_executable(test ${CE_PLUGIN_SOURCES} ${MEMORY_TOOLS_SOURCES})
