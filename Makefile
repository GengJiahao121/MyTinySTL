# Specify the compiler
CXX = g++

# Compiler flags
CXXFLAGS = -g -O0

# Target executable name
TARGET = executableFile

# Source files
# 文件名有空格：1. 使用转义字符 2. 使用引号
SRCS = unordered_map.cpp

# Default rule to build the target
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(SRCS)
	$(CXX) $(SRCS) -o $(TARGET) $(CXXFLAGS)

# PHONY target to clean up generated files
.PHONY: clean
clean:
	rm -rf $(TARGET)
