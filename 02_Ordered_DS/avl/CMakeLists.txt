cmake_minimum_required(VERSION 3.0)
project(avl)

set(SRC_DIR .)
set(LIBS '')

include_directories(${SRC_DIR})

set (   SRC_FILES 
        AVL.cpp
        AVL.hpp
        AVL-extra.hpp
    )

# Compilation -> add_executable / add_library
set (CMAKE_CXX_FLAGS "-std=c++14 -O0 -pedantic -Wall -Wfatal-errors -Wextra")
# Linking -> target_link_libraries
set (LDFLAGS "-std=c++14")

# ./avl
add_executable(avl main.cpp ${SRC_FILES})
#target_link_libraries(avl ${LIBS})
