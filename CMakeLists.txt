cmake_minimum_required(VERSION 3.15)
project(cs235_labs)

set(CMAKE_CXX_STANDARD 20)


add_executable(cs235_labs lab1/vin/main.cpp lab1/vin/TodoListInterface.h lab1/vin/TodoList.h lab1/vin/TodoList.cpp lab1/vin/TodoItem.cpp lab1/vin/TodoItem.h)

# Add for lab 3 to work
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/lab3/vin/1Nephi.txt
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/lab3/vin/Nephi_Trump.txt
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/lab3/vin/movie_scripts.txt
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

add_executable(cs235_labs_lab3 lab3/vin/main.cpp)

add_executable(cs235_labs_lab4 lab4/vin/main.cpp)
