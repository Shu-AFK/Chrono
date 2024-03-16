# Define directories
SRC_DIR := ../src/
OBJ_DIR := ../obj/
UNITY_DIR := ./Unity/src
INCLUDES := -I$(UNITY_DIR) -I$(SRC_DIR)

# Compiler flags
CFLAGS := -g
CXXFLAGS := -g -std=gnu++17

# Use the same source file definitions
C_SOURCES := $(filter-out $(SRC_DIR)chrono.c, $(wildcard $(SRC_DIR)*.c))
CPP_SOURCES := $(wildcard $(SRC_DIR)*.cpp)
UNITY_SRC_FILES := $(UNITY_DIR)/unity.c

# Adjust the object files to be in the OBJ_DIR
C_OBJS := $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(C_SOURCES))
CPP_OBJS := $(patsubst $(SRC_DIR)%.cpp,$(OBJ_DIR)%.o,$(CPP_SOURCES))
UNITY_OBJS := $(patsubst $(UNITY_DIR)%.c,$(OBJ_DIR)%.o,$(UNITY_SRC_FILES))

# Assuming TEST_FILE is set externally, adjust to compile to OBJ_DIR
TEST_OBJS := $(OBJ_DIR)$(notdir $(TEST_FILE:.c=.o))

OBJS := $(C_OBJS) $(CPP_OBJS) $(UNITY_OBJS) $(TEST_OBJS)

TEST_EXEC := $(basename $(notdir $(TEST_FILE)))

.PHONY: all clean test

all: test

test: $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(TEST_EXEC) $^

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)%.o: $(UNITY_DIR)%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Add rule for compiling the test source file to object file
$(OBJ_DIR)%.o: %.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)* $(TEST_EXEC)

