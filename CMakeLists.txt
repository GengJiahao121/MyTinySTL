# #指定cmake的版本号
cmake_minimum_required(VERSION 2.8)

# 工程名称
project(MyTinySTL)

# version
set(MyTinySTL_VERSION_MAJOR 1)
set(MyTinySTL_VERSION_MINOR 0)
set(MyTinySTL_VERSION_PATCH 0)
set(MyTinySTL_VERSION "${MyTinySTL_VERSION_MAJOR}.${MyTinySTL_VERSION_MINOR}.${MyTinySTL_VERSION_PATCH}")
message(STATUS "The version of this project is: ${MyTinySTL_VERSION}")

# build type 
# set(CMAKE_BUILD_TYPE release)
set(CMAKE_BUILD_TYPE debug)
message(STATUS "CMake build mode is : ${CMAKE_BUILD_TYPE}")


if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

	# 检查GCC的版本是否小于5.0.0。
	if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS "5.0.0")
		message(FATAL_ERROR "required GCC 5.0 or later")
	else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
	endif()
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS "3.5.0")
		message(FATAL_ERROR "required Clang 3.5 or later")
	else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
	endif()
endif()

message(STATUS "The cmake_cxx_flags is: ${CMAKE_CXX_FLAGS}")

add_subdirectory(${PROJECT_SOURCE_DIR}/Test)


