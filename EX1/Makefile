# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall -Wextra -I.

# Source files
SRC = Graph.cpp Algorithms.cpp Main.cpp Test.cpp

# Object files
OBJ = $(SRC:.cpp=.o)

# Executable names
MAIN_EXE = main
TEST_EXE = test

# Default target
all: $(MAIN_EXE) $(TEST_EXE)

# Rule to link the main executable
$(MAIN_EXE): Main.o Graph.o Algorithms.o
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to link the test executable
$(TEST_EXE): Test.o Graph.o Algorithms.o
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJ) $(MAIN_EXE) $(TEST_EXE)

.PHONY: all clean

