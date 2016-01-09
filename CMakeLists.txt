#multithreaded pong C++



project(mtPong)
cmake_minimum_required(VERSION 2.8)

#compiler
set(CMAKE_CXX_COMPILER "clang++")


#compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -std=c++14 -Wall -Wextra -Winline -Wno-unused-parameter")


#build_types
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0")


elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -g")

endif()




# find SFML
#find_package(SFML REQUIRED)
#INCLUDE_DIRECTORIES(${SFML_INCLUDE_DIR})


#source files
file(GLOB_RECURSE SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/*.cpp)
file(GLOB_RECURSE HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/*.h)




add_executable(${PROJECT_NAME} ${HEADERS} ${SRCS})

# link
TARGET_LINK_LIBRARIES( ${PROJECT_NAME} -lpthread -lX11 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio)
