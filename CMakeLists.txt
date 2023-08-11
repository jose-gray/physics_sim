cmake_minimum_required(VERSION 3.20)

set(This PersonalTraining)
project(${This} C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

if(WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
endif(WIN32)

add_subdirectory(raylib)
add_subdirectory(googletest)

execute_process(
    COMMAND git describe --tags --abbrev=0
    OUTPUT_VARIABLE TAG_VERSION
    OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/included/TagVersion.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/generated/TagVersion.h @ONLY
)
        
include_directories(${CMAKE_BINARY_DIR}/generated)

file(GLOB Sources src/*.h src/*.cpp src/objects/*.h src/objects/*.cpp src/calculators/*.h src/calculators/*.cpp)
get_filename_component(path_to_main ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp ABSOLUTE)
list(REMOVE_ITEM Sources "${path_to_main}")

add_executable(${This} src/main.cpp ${Sources})
target_link_libraries(${This} PUBLIC raylib)
target_compile_options(${This} PRIVATE -Wall)
        
enable_testing()
add_subdirectory(test)