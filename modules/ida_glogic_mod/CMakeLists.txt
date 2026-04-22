cmake_minimum_required(VERSION 3.10)
project(ida_bardak_glogic)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)


add_library(ida.bardak.glogic SHARED
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ida_glogic_mod.cpp
)

target_include_directories(ida.bardak.glogic PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

target_link_libraries(ida.bardak.glogic PUBLIC
    modlib-ifc
    modlib
    binmsg
) 
