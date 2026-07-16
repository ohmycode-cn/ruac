cmake_minimum_required(VERSION 3.20)
project(ruacdb LANGUAGES C CXX)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(UNIT_TEST "Enable unit test mode" OFF)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/cxx/*.cpp src/cxx/*.c src/cxx/*.cc)

add_executable(${PROJECT_NAME} ${SOURCES}
    src/cxx/src/main.cpp)

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/"
)

target_include_directories(${PROJECT_NAME} PRIVATE src/cxx/include)

if(UNIT_TEST)
    target_compile_definitions(${PROJECT_NAME} PRIVATE UNIT_TEST)
endif()
