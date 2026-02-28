# Compiler
CXX = g++

# Compiler flags
CFLAGS = -std=c++17 -Wall -g 

TARGET = cache_emulator

# Source files
SRCS := $(wildcard src/*.cpp)

OBJS := $(SRCS:src/%.cpp=bin/%.o)

$(TARGET): $(OBJS)
	$(CXX) $(CFLAGS) $(OBJS) -o $(TARGET) 

bin:
	mkdir -p bin

bin/%.o: src/%.cpp | bin
	$(CXX) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(TARGET) bin



