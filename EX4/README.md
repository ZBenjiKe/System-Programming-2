
# Tree Container (k-ary Tree)

## Overview

This project implements a generic k-ary tree container in C++. The tree supports various traversal methods and includes an option to transform a binary tree into a min-heap. The tree is implemented using smart pointers to ensure proper memory management.

## Features

- **Generic k-ary Tree:** Supports any key type and allows to choose the maximum number of children per node. The default number of children is 2 (i.e., a binary tree).
- **Iterators:** Implements Pre-Order, Post-Order, In-Order (for binary trees), BFS, and DFS traversal.
- **Min-Heap Conversion:** Provides a function to convert a binary tree into a min-heap using the STL algorithm.
- **Graphical Representation:** GUI-based visualization of the tree using Qt.
- **Complex Numbers:** Implementation of complex numbers.
- **Testing:** Includes a test file using the `doctest` framework.

## Implementation Details

- **Complex Class (**`Complex.hpp`**)**
  - Represents complex numbers.
  - Contains two double values, representing the real and imaginary values of the complex number.
- **Node Class (**`Node.hpp`**)**
  - Represents individual tree nodes.
  - Contains a value and a vector of child node pointers.
- **Tree Class (**`Tree.hpp`**)**
  - Manages the root node and tree operations.
  - Provides methods for adding nodes and retrieving iterators for traversal.
  - Contains the iterator classes representing the traversal types - pre-order, post-order, in-order, BFS, DFS, min-heap.
- **Tree GUI Class (**`TreeVisualizer.hpp`**)**
  - Provides a framework for graphic representation of a Tree object.
  - Shows a Tree in a seperate window.
- **Test Class (**`Test.cpp`**)**
  - Doctest framework for unit testing of the project's functionality.
- **Demo Class (**`Main.hpp`**)**
  - A short demo of the main project's functions. 

## Compilation and Running
- Ensure you have `Qt` installed for GUI support.
- Ensure you have 'doctest' installed and a copy of the "doctest.h" file in the project folder for testing.
- Use the provided `Makefile`:
  - 'make all' - Target to compile all project files.
  - 'make clean' - Target to delete .o and .exe files compiled.
- './Test' - Runs the test class.
- './Main' - Runs the demo class.



## Authors

- Benji Kehat

