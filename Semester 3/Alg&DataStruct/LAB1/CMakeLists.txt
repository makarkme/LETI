cmake_minimum_required(VERSION 3.27)
project(ClionProjects
        VERSION 1.0
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

add_executable(ClionProjects main.cpp
        DoubleLinkedList.h
        DoubleLinkedList.cpp
        DynamicArray.cpp
        DynamicArray.h
        Stack.cpp
        Stack.h
        ReversePolishNotation.h
        ReversePolishNotation.cpp

)