# Compiler and flags
CXX      := clang++
CXXFLAGS := -std=c++20 -Wall -Wextra -Wpedantic -O2

BUILD_DIR := build
SRCS      := solve.cpp
HDRS      := solve.hpp

.PHONY: all run test clean

all: run

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# ---- Main binary (for running real input) ----

$(BUILD_DIR)/main: main.cpp $(SRCS) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

run: $(BUILD_DIR)/main
	./$(BUILD_DIR)/main

# ---- Test binary ----

$(BUILD_DIR)/tests: tests.cpp $(SRCS) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

test: $(BUILD_DIR)/tests
	./$(BUILD_DIR)/tests

# ---- Cleanup ----

clean:
	rm -rf $(BUILD_DIR)
