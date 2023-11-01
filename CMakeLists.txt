cmake_minimum_required(VERSION 3.15)
set(CMAKE_BUILD_TYPE Debug)
project(BFCD VERSION 0.0.1)

set(
    BFCD_SOURCES
    ./src/Application.cpp
    ./src/File/File.cpp
    ./src/File/FileHandler.cpp
    ./src/File/Compression/Huffman.cpp
    ./src/File/Compression/DataStructure/HuffmanTree/HuffmanTree.cpp
    ./src/File/Compression/DataStructure/HuffmanTree/Node.cpp
)

set(
    BFCD_HEADERS
    ./src/File/File.hpp
    ./src/File/FileHandler.hpp
    ./src/File/Compression/Huffman.hpp
    ./src/File/Compression/DataStructure/HuffmanTree/HuffmanTree.hpp
    ./src/File/Compression/DataStructure/HuffmanTree/Node.hpp
)

# find_package(Boost REQUIRED)
# if(Boost_FOUND)
    # include_directories(${Boost_INCLUDE_DIRS}) 
    # add_executable(${PROJECT_NAME} ${BFCD_SOURCES} ${BFCD_HEADERS})
    # target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
# endif()

add_executable(${PROJECT_NAME} ${BFCD_SOURCES} ${BFCD_HEADERS})

#message(STATUS "Boost_FOUND: ${Boost_FOUND}")
