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
	@echo 
	@echo           "******* Run Command ***********"
	@echo "./cache_emulator --sets <num_sets> --blocks <num_blocks> --size <block_size> --trace <trace_filename>"

bin:
	mkdir -p bin

bin/%.o: src/%.cpp | bin
	$(CXX) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(TARGET) bin



