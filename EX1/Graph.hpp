#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <iostream>

namespace ariel {

	class Graph {
	private:
		std::vector<std::vector<int>> graph;
	public:
		int size;
		int weighted;
		int directed;

	public:
		Graph();
		Graph(const std::vector<std::vector<int>>& matrix);
        ~Graph();
		void loadGraph(const std::vector<std::vector<int>>& matrix);
		void printGraph() const;

        // Operator[] to access the graph's nodes
        const std::vector<int>& operator[](size_t index) const;

	};
}

#endif