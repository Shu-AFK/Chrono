# Compiler settings - Can change to cc or gcc as required
CC := gcc

# Include directory for Unity and your source headers
UNITY_DIR := ./Unity/src
INCLUDES := -I$(UNITY_DIR) -I../src/

# Automatically include all .c files in the current directory
TEST_SRC_FILES := $(wildcard *.c)

# Unity source file
UNITY_SRC_FILE := $(UNITY_DIR)/unity.c

# All source files needed for the test (Unity + test source files)
SRC_FILES := $(UNITY_SRC_FILE) $(TEST_SRC_FILES)

# Object files
OBJ_FILES := $(SRC_FILES:.c=.o)

# Output executable for tests
TEST_EXEC := tests

.PHONY: all clean

all: $(TEST_EXEC)
	./$(TEST_EXEC)

$(TEST_EXEC): $(OBJ_FILES)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ_FILES) $(TEST_EXEC)