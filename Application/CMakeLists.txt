cmake_minimum_required(VERSION 3.5)
project(Application LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 11)

add_library(Application 
    SHARED
    src/Application.cpp
)

target_include_directories(Application 
    PUBLIC
    include
)

target_link_libraries(Application 
    glfw 
    glad
    )