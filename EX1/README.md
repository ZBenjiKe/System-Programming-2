
# Graph Operators

## Overview

This project is an implementation of graph representations and select algorithms using adjacency matrices.

## Features

- **Graph:** An adjacency matrix representing any type of graph.
- **Algorithms:** Provide algorithm-based functions to verify graph types and find specific properties of the graph (e.g., whether a given graph is cyclic or not).
- **Testing:** Includes a test file using the `catch` framework.

## Implementation Details

- **Graph Class (**`Graph.hpp`, `Graph.cpp`**)**
  - Represents any type of graph.
  - Contains a 2D vector representing the adjacency matrix.
  - Contains 3 int type values representing the graph's size, and whether the graph is weighted and/or directed.
  - Prints a matrix representation of a graph. 
- **Algorithms Class (**`Algorithms.hpp`,`Algorithms.cpp`**)**
  - Provides the set of algorthims for verifying graph properties:
    - Connectivity.
    - Shortest path between two given nodes.
    - Check whether the graph contains a cycle.
    - Check whether the graph is bipartite.
    - Check whether the graph contains a negative cycle.
- **Test Class (**`Test.cpp`**)**
  - Catch framework for unit testing of the project's functionality.
- **Demo Class (**`Main.hpp`**)**
  - A short demo of the main project's functions. 

## Compilation and Running
- Ensure you have 'catch' installed and a copy of the "catch.hpp" file in the project folder for testing.
- Use the provided `Makefile`:
  - 'make all' - Target to compile all project files.
  - 'make clean' - Target to delete .o and .exe files compiled.
- './test' - Runs the test class.
- './main' - Runs the demo class.



## Authors

- Benji Kehat

