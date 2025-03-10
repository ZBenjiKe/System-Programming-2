# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall -Wextra -I. -fpic

# Qt-related flags
QT_FLAGS = `pkg-config --cflags --libs Qt5Widgets Qt5Gui Qt5Core`

# Source files
SRC = Main.cpp Test.cpp

# Header files
HEADERS = Tree.hpp Complex.hpp Node.hpp TreeVisualizer.hpp

# Object files
OBJ = $(SRC:.cpp=.o)

# Executable names
MAIN_EXE = Main
TEST_EXE = Test

# Moc files
MOC_HEADERS = TreeVisualizer.hpp
MOC_SRCS = $(MOC_HEADERS:.hpp=.moc.cpp)
MOC_OBJS = $(MOC_SRCS:.cpp=.o)

# Default target
all: $(MAIN_EXE) $(TEST_EXE)

# Rule to link the main executable with Qt
$(MAIN_EXE): Main.o $(MOC_OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(QT_FLAGS)

# Rule to link the test executable with Qt
$(TEST_EXE): Test.o $(MOC_OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(QT_FLAGS)

# Rule to compile source files into object files
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(QT_FLAGS)

# Rule to compile moc files
%.moc.cpp: %.hpp
	moc $< -o $@

# Clean up build files
clean:
	rm -f $(OBJ) $(MOC_OBJS) $(MOC_SRCS) $(MAIN_EXE) $(TEST_EXE)

.PHONY: all clean
