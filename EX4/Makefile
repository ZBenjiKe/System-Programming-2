# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall -Wextra -I.

# Source files
SRC = Main.cpp Test.cpp

# Header files
HEADERS = Tree.hpp Complex.hpp

# Object files
OBJ = $(SRC:.cpp=.o)

# Executable names
MAIN_EXE = Main
TEST_EXE = Test

# Default target
all: $(MAIN_EXE) $(TEST_EXE)

# Rule to link the main executable
$(MAIN_EXE): Main.o Graph.o Algorithms.o
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to link the test executable
$(TEST_EXE): Test.o Graph.o Algorithms.o
	$(CXX) $(CXXFLAGS) -o $@ $^

$(MAIN_EXE): $(OBJ)
	$(CXX) $(OBJ) -o $(MAIN_EXE)

# Rule to compile source files into object files
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJ) $(MAIN_EXE) $(TEST_EXE)

.PHONY: all clean
