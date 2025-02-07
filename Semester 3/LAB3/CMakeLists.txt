cmake_minimum_required(VERSION 3.27)
project(ClionProjects
        VERSION 1.0
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

add_executable(ClionProjects main.cpp
        Menu.h
        Menu.cpp
        StringParser.cpp
        StringParser.h
        BaseTree.cpp
        BaseTree.h
        RBTree.cpp
        RBTree.h)