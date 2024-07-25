#include "Graph.hpp"
#include <stdexcept>
#include <climits>

using namespace std;

namespace ariel {

	Graph::Graph() {
		// Default Constructor
	}

	Graph::Graph(const std::vector<std::vector<int>>& matrix) {
		loadGraph(matrix);
	}

    Graph::~Graph() {
    	// Default Destructor
    }


	void Graph::loadGraph(const vector<vector<int>>& matrix) {
		int numNodes = static_cast<int>(matrix.size());
		for(int i = 0; i < numNodes; i++) {
			if (numNodes != static_cast<int>(matrix[i].size())) {
				throw runtime_error("Invalid input: Matrix is not square");
			}
		}
		graph = matrix;
		size = numNodes;
		for(int i = 0; i < size; i++){
			for (int j = 0; j < size; j++) {
		 		if ((graph[i][j] == 0) && (i != j)) {
		 			graph[i][j] = INT_MAX;
		 		}
		 	}
		}
		size = matrix[0].size();
		weighted = 0;
		for(int i = 0; i < size; i++) {
			for(int j = 0; j < size; j++) {
				if ((graph[i][j] != 0) && (graph[i][j] != INT_MAX) && (graph[i][j] != 1)) {
					weighted = 1;
				}
			}
		}
		directed = 0;
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if (graph[i][j] != graph[j][i]) {
					directed = 1;
				}
			}
		}
	}

	void Graph::printGraph() const {
		int size = graph.size();
		cout << "The graph (as an adjacency matrix):" << endl;
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				cout << graph[i][j] << " ";
			}
			cout << "\n";
		}
	}

	const std::vector<int>& Graph::operator[](size_t index) const {
        return graph[index];
    }
}