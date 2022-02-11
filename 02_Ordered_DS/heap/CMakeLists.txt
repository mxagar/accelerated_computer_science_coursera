cmake_minimum_required(VERSION 3.0)
project(heap)

set(SRC_DIR .)
set(LIBS '')

include_directories(${SRC_DIR})

set (   SRC_FILES 
        Heap.hpp
    )

# Compilation -> add_executable / add_library
set (CMAKE_CXX_FLAGS "-std=c++14 -O0 -pedantic -Wall -Wfatal-errors -Wextra")
# Linking -> target_link_libraries
set (LDFLAGS "-std=c++14")

# ./bst
add_executable(heap main.cpp ${SRC_FILES})
#target_link_libraries(bst ${LIBS})
