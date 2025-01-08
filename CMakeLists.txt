cmake_minimum_required(VERSION 3.31.2)
project(NSnake CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES 
    src/nSnake.cpp
    src/snake.cpp
)

set(HEADERS
    src/snake.h
)

#requires nCurces to work
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})


add_executable(n_snake ${SOURCES} ${HEADERS})



target_link_libraries(n_snake ${CURSES_LIBRARIES})

include_directories(src)

