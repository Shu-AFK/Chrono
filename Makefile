# Compiler and flags
CC=gcc
CFLAGS=-Wall -Wextra -pedantic -std=c99 -MMD -MP
BUILD_DIR=build

# Source and object files
SRC=$(wildcard src/*.c)
OBJ=$(SRC:src/%.c=$(BUILD_DIR)/%.o)
DEP=$(OBJ:%.o=%.d)

# Target executable
EXE=$(BUILD_DIR)/chrono

# Default target
all: $(EXE)

# Link the target executable
$(EXE): $(OBJ)
	$(CC) $^ -o $@ $(CFLAGS)

# Compile source files into object files
$(BUILD_DIR)/%.o: src/%.c | $(BUILD_DIR)
	$(CC) -c $< -o $@ $(CFLAGS)

# Create the build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $@

# Include dependency files
-include $(DEP)

# Clean up build artifacts
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean

