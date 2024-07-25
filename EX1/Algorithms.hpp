#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include "Graph.hpp"

namespace ariel {


	int isConnected(const Graph& graph);

	std::string shortestPath(const Graph& graph, int start, int end);

	std::string containsCycle(const Graph& graph);

	std::string isBipartite(const Graph& graph);

	std::string negativeCycle(const Graph& graph);

}

#endif