cmake_minimum_required(VERSION 3.5)
project(test)
set(CMAKE_CXX_STANDARD 11)

include_directories(include)
add_executable(test src/test.c)
target_link_libraries(test 
    glfw 
    glad
    )