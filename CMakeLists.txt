cmake_minimum_required(VERSION 3.15)
project(cs235_labs)

set(CMAKE_CXX_STANDARD 20)

add_executable(cs235_labs lab1/main.cpp lab1/TodoListInterface.h lab1/TodoList.h lab1/TodoList.cpp lab1/TodoItem.cpp lab1/TodoItem.h)