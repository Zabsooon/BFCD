cmake_minimum_required(VERSION 3.15)
project(BFCD VERSION 0.0.1)

find_package(Boost REQUIRED)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS}) 
    add_executable(${PROJECT_NAME} ./src/Application.cpp)
    target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
endif()

message(STATUS "Boost_FOUND: ${Boost_FOUND}")

