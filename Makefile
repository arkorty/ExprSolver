CXX = clang++
CXXFLAGS = -O3 -std=c++17 -Wall -Wextra -pedantic
BUILD_DIR = build
SRC_DIR = src
SOURCE = ast.cxx
EXECUTABLE = ast

all: $(BUILD_DIR) $(BUILD_DIR)/$(EXECUTABLE)

$(BUILD_DIR):
	mkdir -p $@

$(BUILD_DIR)/$(EXECUTABLE): $(SRC_DIR)/$(SOURCE) $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $<

.PHONY: test
test: CXXFLAGS += -DENABLE_TESTS
test: $(BUILD_DIR)/$(EXECUTABLE)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

.PHONY: rebuild
rebuild: clean all
