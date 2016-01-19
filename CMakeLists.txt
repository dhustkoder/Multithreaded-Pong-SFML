#multithreaded pong C++



project(mtPong)
cmake_minimum_required(VERSION 2.8)

#compiler
set(CMAKE_CXX_COMPILER "g++")
set(PRECOMPILED_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/src/pch.h")
set(PCH_OPTIMIZATION_FLAGS "")


#compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra -Winline -Wno-unused-parameter -include${PRECOMPILED_HEADER} ")

#build_types
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g")
	set(PCH_OPTIMIZATION_FLAGS "-O0 -g")

elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
	set(PCH_OPTIMIZATION_FLAGS "-O3")
	
endif()

#compile precompiled header...
execute_process(COMMAND ${CMAKE_CXX_COMPILER} -std=c++14  ${PCH_OPTIMIZATION_FLAGS}  ${PRECOMPILED_HEADER})



#find SFML
#find_package(SFML REQUIRED)
#INCLUDE_DIRECTORIES(${SFML_INCLUDE_DIR})


#source files
file(GLOB_RECURSE SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/*.cpp)



add_executable(${PROJECT_NAME} ${SRCS})

# link
TARGET_LINK_LIBRARIES( ${PROJECT_NAME} -lpthread -lX11 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio)
