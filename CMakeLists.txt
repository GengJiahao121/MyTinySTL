# #指定cmake的版本号
cmake_minimum_required(VERSION 2.8)

# 工程名称
project(STL)

# version
# 设置项目的主版本号为2。
set(MyTinySTL_VERSION_MAJOR 2)
# 设置项目的次版本号为0
set(MyTinySTL_VERSION_MINOR 0)
# 设置项目的补丁版本号为0
set(MyTinySTL_VERSION_PATCH 0)
# 将主版本号、次版本号和补丁版本号组合成一个完整的版本字符串，并存储在变量MyTinySTL_VERSION中
set(MyTinySTL_VERSION "${MyTinySTL_VERSION_MAJOR}.${MyTinySTL_VERSION_MINOR}.${MyTinySTL_VERSION_PATCH}")
# 输出项目的版本信息
message(STATUS "The version of this project is: ${MyTinySTL_VERSION}")

# build type 设置构建类型为"release"模式
set(CMAKE_BUILD_TYPE release)


# 检查当前使用的C++编译器是否是GNU编译器（如GCC）。
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	# 为GNU编译器设置一些编译选项标志：-O2用于优化，-Wall和-Wextra用于启用额外的警告，-Wno-sign-compare、-Wno-unused-but-set-variable、-Wno-array-bounds用于禁用特定的警告。
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g -Wall -Wextra -Wno-sign-compare -Wno-unused-but-set-variable -Wno-array-bounds")
	
	# 注释掉的代码行，包含一些额外的编译选项，可以启用这些选项来进行更严格的代码检查。
	# set(EXTRA_CXX_FLAGS -Weffc++ -Wswitch-default -Wfloat-equal -Wconversion -Wsign-conversion)

	# 检查GCC的版本是否小于5.0.0。
	if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS "5.0.0")
		# 如果GCC版本小于5.0.0，则输出致命错误信息并停止配置过程。
		message(FATAL_ERROR "required GCC 5.0 or later")
	else()
		# 为GNU编译器设置C++11标准。
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
	endif()
# 如果当前使用的编译器是Clang，则执行以下代码。
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g -Wall -Wextra -Wno-sign-compare")
	# set(EXTRA_CXX_FLAGS -Weffc++ -Wswitch-default -Wfloat-equal -Wconversion -Wimplicit-fallthrough)
	if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS "3.5.0")
		message(FATAL_ERROR "required Clang 3.5 or later")
	else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
	endif()
endif()

# 输出当前设置的C++编译器选项标志。
message(STATUS "The cmake_cxx_flags is: ${CMAKE_CXX_FLAGS}")

# 添加子目录“Test”，使其参与构建过程。这通常是包含单元测试或其他子项目的目录。
add_subdirectory(${PROJECT_SOURCE_DIR}/Test)