cmake_minimum_required(VERSION 3.16)
project(terminal_3d)

set(SOURCES
    main.cpp
)

set(HEADERS
    atrib.h
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})