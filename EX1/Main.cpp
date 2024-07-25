#include "Graph.hpp"
#include "Algorithms.hpp"
#include <iostream>

using namespace ariel;
using namespace std;

int main() {

	Graph g;

	vector<vector<int>> graph = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 1, 1},
        {1, 1, 0, 0, 0},
        {0, 1, 0, 0, 0},
        {0, 1, 0, 0, 0}};
    g.loadGraph(graph); // Load the graph to the object.
    cout << containsCycle(g) << endl;
}
