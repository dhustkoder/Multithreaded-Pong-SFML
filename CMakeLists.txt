#multithreaded pong C++ - SFML

project(mtPong)
cmake_minimum_required(VERSION 3.4)

#compiler
set(CMAKE_CXX_COMPILER "g++")

#precompiled header - path
set(PRECOMPILED_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/src/pch.h")

#precompiled header optimization flags 
set(PCH_OPTIMIZATION_FLAGS )


#compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra -Winline -Wno-unused-parameter -include${PRECOMPILED_HEADER}")

#build_types ---
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g")
	set(PCH_OPTIMIZATION_FLAGS "-O0 -g")

elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
	set(PCH_OPTIMIZATION_FLAGS "-O3")
endif()
#end build types ---




#compile precompiled header...
execute_process(COMMAND ${CMAKE_CXX_COMPILER} ${PCH_OPTIMIZATION_FLAGS} -std=c++14 ${PRECOMPILED_HEADER})



#find SFML
#find_package(SFML REQUIRED)
#INCLUDE_DIRECTORIES(${SFML_INCLUDE_DIR})

# other libs to link
set(LIBS -lpthread -lX11 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio)


#source files
file(GLOB_RECURSE SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/*.cpp)
list(REMOVE_ITEM SRCS "src/pch.cpp")

add_executable(${PROJECT_NAME} ${SRCS})

# link
TARGET_LINK_LIBRARIES( ${PROJECT_NAME}  ${LIBS} )
