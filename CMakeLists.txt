cmake_minimum_required(VERSION 3.28)

project(FCLI LANGUAGES CXX)
set (CMAKE_CXX_STANDARD 23)

# Warnings
# if (MSVC)
#     # warning level 4
#     add_compile_options(/W4)
# else()
#     # additional warnings
#     add_compile_options(-Wall -Wextra -Wpedantic)
# endif()


# The library(!!!!)
include_directories(PUBLIC "include")
add_library(FCLI STATIC "src/Engine.cpp" "src/HasHelpInfo.cpp" "src/Builtins.cpp"
"src/argument/Argument.cpp" "src/argument/ArgumentType.cpp"  
"src/command/CommandBase.cpp" "src/command/CommandGroup.cpp" "src/command/Command.cpp")

add_executable(example "example/example.cpp")

target_link_libraries(pcApp robadaLib)