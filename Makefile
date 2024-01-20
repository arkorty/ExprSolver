CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra
SOURCE = main.cxx
EXECUTABLE = ast.out

# Build target
all: $(EXECUTABLE)

# Rule to build the executable
$(EXECUTABLE): $(SOURCE)
	@$(CXX) $(CXXFLAGS) -o $@ $<

run: $(EXECUTABLE)
	@./$(EXECUTABLE)

# Clean up generated files
clean:
	@rm -f $(EXECUTABLE)
