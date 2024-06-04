
# 这行代码将MyTinySTL目录添加到包含路径中，使编译器能够找到该目录下的头文件。
include_directories(${PROJECT_SOURCE_DIR}/MyTinySTL)

# 定义一个变量APP_SRC，其值为test.cpp。这个变量包含了生成可执行文件所需的源文件列表。在这个例子中，只包含一个源文件test.cpp。
set(APP_SRC test.cpp)

# 设置生成的可执行文件的输出路径。这里是将可执行文件输出到项目根目录下的bin目录中。通过这行代码，所有生成的可执行文件都会放在${PROJECT_SOURCE_DIR}/bin目录中。
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# 定义一个名为stltest的可执行文件，包含APP_SRC变量中列出的源文件。在这个例子中，`生成的可执行文件名为stltest，其源文件为test.cpp。
add_executable(stltest ${APP_SRC})