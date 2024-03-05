# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 3.5)
# Set the project name
project(Render)


add_subdirectory(third_party/glfw)
add_subdirectory(third_party/glad)

add_subdirectory(test)
add_subdirectory(Application)