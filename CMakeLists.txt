cmake_minimum_required(VERSION 3.15)
project(cs235_labs)

set(CMAKE_CXX_STANDARD 20)


add_executable(cs235_labs_lab1 lab1/vin/main.cpp lab1/vin/TodoListInterface.h lab1/vin/TodoList.h lab1/vin/TodoList.cpp lab1/vin/TodoItem.cpp lab1/vin/TodoItem.h)

# Add for lab 3 to work
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/lab3/vin/1Nephi.txt
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/lab3/vin/Nephi_Trump.txt
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/lab3/vin/movie_scripts.txt
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

add_executable(cs235_labs_lab3 lab3/vin/main.cpp)

file(GLOB lab4_text ${CMAKE_CURRENT_SOURCE_DIR}/lab4/vin/*.txt)
file(COPY ${lab4_text} DESTINATION
        ${CMAKE_CURRENT_BINARY_DIR})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/lab4/vin/Mazes DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(cs235_labs_lab4 lab4/vin/main.cpp lab4/vin/PathfinderInterface.h lab4/vin/Pathfinder.h lab4/vin/Pathfinder.cpp)

file(GLOB lab5_text ${CMAKE_CURRENT_SOURCE_DIR}/lab5/vin/*.txt)
file(COPY ${lab5_text} DESTINATION
        ${CMAKE_CURRENT_BINARY_DIR})

add_executable(cs235_labs_lab5 lab5/vin/main.cpp lab5/vin/QSInterface.h lab5/vin/QS.h lab5/vin/QS.cpp)

# Pretty sure that this copy operation overwrites all of the past operations
file(GLOB lab6_text ${CMAKE_CURRENT_SOURCE_DIR}/lab6/vin/*.txt)
file(COPY ${lab6_text} DESTINATION
        ${CMAKE_CURRENT_BINARY_DIR})

add_executable(cs235_labs_lab6 lab6/vin/main.cpp lab6/vin/LinkedListInterface.h lab6/vin/LinkedList.h)

# Pretty sure that this copy operation overwrites all of the past operations
file(GLOB lab7_text ${CMAKE_CURRENT_SOURCE_DIR}/lab7/vin/*.txt)
file(COPY ${lab7_text} DESTINATION
        ${CMAKE_CURRENT_BINARY_DIR})

add_executable(cs235_labs_lab7 lab7/vin/main.cpp lab7/vin/NodeInterface.h lab7/vin/Node.h lab7/vin/Node.cpp lab7/vin/BSTInterface.h lab7/vin/BST.h lab7/vin/BST.cpp)
