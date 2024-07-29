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


        // Arithmetic Operators
        Graph operator+(const Graph& other) const;
        Graph& operator+=(const Graph& other);
        Graph& operator+();
        Graph& operator++();
        Graph operator++(int);

        Graph operator-(const Graph& other) const;
        Graph& operator-=(const Graph& other);
        Graph& operator-();
        Graph& operator--();
        Graph operator--(int);

	    Graph operator*(const Graph& other) const;
        Graph& operator*(int x);


	    bool identicalGraph(const Graph& other) const; 
	    bool containsGraph(const Graph& other) const;

	    bool operator==(const Graph& other) const;
   	    bool operator!=(const Graph& other) const;
	    bool operator>(const Graph& other) const;
	    bool operator>=(const Graph& other) const;
		bool operator<(const Graph& other) const;
		bool operator<=(const Graph& other) const;

		friend std::ostream& operator<<(std::ostream& os, const Graph& graph);

	};
}

#endif