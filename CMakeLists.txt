cmake_minimum_required(VERSION 3.15)
project(BFCD VERSION 0.0.1)

set(
    BFCD_SOURCES
    ./src/Application.cpp
    ./src/File/File.cpp
    ./src/File/Reader.cpp
)

set(
    BFCD_HEADERS
    ./src/File/File.hpp
    ./src/File/Reader.hpp
)

find_package(Boost REQUIRED)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS}) 
    add_executable(${PROJECT_NAME} ${BFCD_SOURCES} ${BFCD_HEADERS})
    target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
endif()

message(STATUS "Boost_FOUND: ${Boost_FOUND}")

