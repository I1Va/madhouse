cmake_minimum_required(VERSION 3.10)

project(MadHouse)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(SANITIZE "Enable compiler sanitizers" ON)
if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(
        -Wall
        -Wextra
         $<$<BOOL:${SANITIZE}>:-fsanitize=address,undefined>
    )
    add_link_options(
         $<$<BOOL:${SANITIZE}>:-fsanitize=address,undefined>
    )
endif()

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/server)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/client)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/bardak)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/modules/ida_glogic_mod)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/modules/ida_map_mod)
# add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/modules/ida_tank_mod)


add_executable(${PROJECT_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

target_link_libraries(${PROJECT_NAME} 
    PRIVATE server
    PRIVATE client
    # PRIVATE IAMapPlugin
    # PRIVATE IAGeneralLogicPlugin
    # PRIVATE TankLogicPlugin

    PRIVATE modlib
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
)


