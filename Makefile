# Compiler and flags
CC=gcc
CXX=g++ # Add g++ as the C++ compiler
CFLAGS=-g -Wall -Wextra -pedantic -std=c99 -MMD -MP
CXXFLAGS=-g -Wall -Wextra -pedantic -std=c++11 -MMD -MP # C++ flags

BUILD_DIR=build

# Source and object files for C and C++
SRC_C=$(wildcard src/*.c)
SRC_CPP=$(wildcard src/*.cpp) # Add C++ source files
OBJ_C=$(SRC_C:src/%.c=$(BUILD_DIR)/%.o)
OBJ_CPP=$(SRC_CPP:src/%.cpp=$(BUILD_DIR)/%.o) # Object files for C++
OBJ=$(OBJ_C) $(OBJ_CPP) # Combine C and C++ object files
DEP=$(OBJ:%.o=%.d)

# Target executable
EXE=$(BUILD_DIR)/chrono

# Default target
all: $(EXE)

# Link the target executable
$(EXE): $(OBJ)
	$(CXX) $^ -o $@ $(CXXFLAGS) # Use CXX and CXXFLAGS here

# Compile C source files into object files
$(BUILD_DIR)/%.o: src/%.c | $(BUILD_DIR)
	$(CC) -c $< -o $@ $(CFLAGS)

# Compile C++ source files into object files
$(BUILD_DIR)/%.o: src/%.cpp | $(BUILD_DIR)
	$(CXX) -c $< -o $@ $(CXXFLAGS)

# Create the build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $@

# Include dependency files
-include $(DEP)

# Clean up build artifacts
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean

