#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "Graph.hpp"
#include "Algorithms.hpp"

using namespace std;
using namespace ariel;

Graph g;

// Passed
TEST_CASE("isDirected") {

	vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(g.directed == false);

    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {1, 1, 0}};
    g.loadGraph(graph1);
    CHECK(g.directed == true);
}

// Passed
TEST_CASE("isWeighted") {

	vector<vector<int>> graph = {
        {0, 2, 0},
        {2, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(g.weighted == true);

    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph1);
    CHECK(g.weighted == false);
}

// Passed
TEST_CASE("Test isConnected") {

    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(isConnected(g) == true);

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(isConnected(g) == false);

	    vector<vector<int>> graph3 = {
        {0, 0, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 0, 1},
        {0, 1, 1, 0, 0},
        {0, 0, 0, 1, 0}};
    g.loadGraph(graph3);
    CHECK(isConnected(g) == true);

    vector<vector<int>> graph4 = {
        {0, 0, 0, 0, 1},
        {0, 0, 1, 0, 0},
        {0, 1, 0, 0, 1},
        {0, 1, 1, 0, 0},
        {0, 0, 0, 1, 0}};
    g.loadGraph(graph4);
    CHECK(isConnected(g) == false);
}

// Passed
TEST_CASE("Test shortestPath") {

    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(shortestPath(g, 0, 2) == "Shortest path: 0->1->2");

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(shortestPath(g, 0, 4) == "-1: No path between vertices");

	vector<vector<int>> graph3 = {
        {0, 2, 0, -2},
        {0, 0, 1, 0},
        {0, 0, 0, 1},
        {0, -3, 0, 0}};
    g.loadGraph(graph3);
    CHECK(shortestPath(g, 0, 2) == "-1: Negative cycle detected");
}

// Passed
TEST_CASE("Test negativeCycle") {

    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(negativeCycle(g) == "-1: No negative cycles were found");

    vector<vector<int>> graph2 = {
        {0, 3, 8, 0, -4},
        {0, 0, 0, 1, 7},
        {0, 3, 0, 0, 0},
        {2, 0, -5, 0, 0},
        {0, 0, 0, 6, 0}};
    g.loadGraph(graph2);
    CHECK(negativeCycle(g) == "Negative cycle found: 1->3->2->1");
}

// Passed
TEST_CASE("Test isBipartite") {

    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(isBipartite(g) == "The graph is bipartite: U = {0 2 }, W = {1 }");

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(isBipartite(g) == "0: The graph is not bipartite");

    vector<vector<int>> graph3 = {
        {0, 1, 0, 2, 0},
        {1, 0, 3, 0, -1},
        {0, 3, 0, 4, 0},
        {2, 0, 4, 0, 5},
        {0, -1, 0, 5, 0}};
    g.loadGraph(graph3);
    CHECK(isBipartite(g) == "The graph is bipartite: U = {0 2 4 }, W = {1 3 }");
}

// !FAILED!
TEST_CASE("Test containsCycle") {

	vector<vector<int>> graph = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 1, 1},
        {1, 1, 0, 0, 0},
        {0, 1, 0, 0, 0},
        {0, 1, 0, 0, 0}};
    g.loadGraph(graph); // Load the graph to the object.
    CHECK(containsCycle(g) == "Cycle detected: 0->1->2");


    vector<vector<int>> graph1 = {
        {0, 1, 1, 0, 0},
        {0, 0, 0, 0, 1},
        {0, 0, 0, 1, 0},
        {0, 1, 0, 0, 4},
        {0, 0, 1, 0, 0}};
    g.loadGraph(graph1); // Load the graph to the object.
    CHECK(containsCycle(g) == "Cycle detected: 1->4->2->3");


    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0},
        {0, 1, 0, 0, 4},
        {0, 0, 1, 0, 0}};
    g.loadGraph(graph2); // Load the graph to the object.
    CHECK(containsCycle(g) == "No cycles detected");


    vector<vector<int>> graph3 = {
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 1, 0, 1},
        {0, 0, 0, 0}};
    g.loadGraph(graph3); // Load the graph to the object.
    CHECK(containsCycle(g) == "Cycle detected: 1->2");
}

// Passed
TEST_CASE("Test invalid graph") {

    vector<vector<int>> graph = {
        {0, 1, 2, 0},
        {1, 0, 3, 0},
        {2, 3, 0, 4},
        {0, 0, 4, 0},
        {0, 0, 0, 5}};
    CHECK_THROWS(g.loadGraph(graph));


	vector<vector<int>> graph1 = {
        {0, 1, 2, 0, 0},
        {1, 0, 3, 0, 1},
        {2, 3, 0, 4, 3},
        {0, 0, 4, 0, 1},
        {0, 0, 0, 5}};
    CHECK_THROWS(g.loadGraph(graph1));
}

