CPPFLAGS = -MMD -MP 
# ^ C Pre Processor options: includes dir, automatic header dependencies
# -I is a preprocessor flag, not a compiler flag

CXXFLAGS = -Wall -Wextra -J3
# ^ C++ compiler options: warnings, 3 jobs

CFLAGS = -Wall -Wextra -J3
# ^ C compiler options: warnings, 3 jobs

LDFLAGS :=
# ^ link Flags:

LDLIBS  :=
# ^ link Libraries:

CXX = g++
CC  = gcc

TARGET_EXEC := noteman

BUILD_DIR := ./build
SRC_DIRS  := ./src

# Find all the C and C++ files we want to compile
SRCS := $(shell find $(SRC_DIRS) -name *.cpp -or -name *.c)

# String substitution for every C/C++ file.
# As an example, hello.cpp turns into ./build/hello.cpp.o
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

# Build step for C++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX)  -c $< -o $@ $(CXXFLAGS) $(CPPFLAGS)

# Build step for C source
$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

# The final build step (Linking?).
$(TARGET_EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDLIBS) $(LDFLAGS)

.PHONY: clean
clean:
	rm -r $(BUILD_DIR)
