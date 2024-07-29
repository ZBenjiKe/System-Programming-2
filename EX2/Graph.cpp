#include "Graph.hpp"
#include <stdexcept>
#include <climits>

using namespace std;

namespace ariel {
	
	Graph::Graph() {
		// Default Constructor
	}

	Graph::Graph(const vector<vector<int>>& matrix) {
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
				if(graph[i][j] == INT_MAX) {
					cout << "INF ";
				} else {
					cout << graph[i][j] << " ";
				}
			}
			cout << "\n";
		}
	}

	const vector<int>& Graph::operator[](size_t index) const {
        return graph[index];
    }


    Graph Graph::operator+(const Graph& other) const {
    	if(this->size != other.size) {
    		throw invalid_argument("The graphs are not the same size");
    	}

    	vector<vector<int>> adjMatrix(size, vector<int>(size, INT_MAX));

    	for(int i = 0; i < size; i++) {
    		for(int j = 0; j < size; j++) {
    			if(this->graph[i][j] == INT_MAX) {
    				if(other[i][j] == INT_MAX) {
    					adjMatrix[i][j] = INT_MAX;
    				} else {
    					adjMatrix[i][j] = other[i][j];
    				}
    			} else if(other[i][j] == INT_MAX) {
    				adjMatrix[i][j] = this->graph[i][j];
    			} else {
    				adjMatrix[i][j] = this->graph[i][j] + other[i][j];
    			}
    		}
    	}

    	Graph result;
    	result.loadGraph(adjMatrix);

    	return result;
    }
    Graph& Graph::operator+=(const Graph& other) {
    	if(this->size != other.size) {
    		throw invalid_argument("The graphs are not the same size");
    	}

    	for(int i = 0; i < size; i++) {
    		for(int j = 0; j < size; j++) {
    			if(other.graph[i][j] != INT_MAX) {
    				if(this->graph[i][j] == INT_MAX) {
    					this->graph[i][j] = other.graph[i][j];
    				} else {
    					this->graph[i][j] += other[i][j];
    				}
    			}
    		}
    	}
    	return *this;
    }
    Graph& Graph::operator+() {
    	return *this;
    }
    Graph& Graph::operator++() {
    	for(int i = 0; i < size; i++) {
    		for(int j = 0; j < size; j++) {
    			if(this->graph[i][j] != INT_MAX && this->graph[i][j] != 0) {
	    			this->graph[i][j]++;
	    		}
    		}
    	}
    	return *this;
    }
    Graph Graph::operator++(int) {
    	Graph result = *this;
    	++(*this);
    	return result;
    }

    Graph Graph::operator-(const Graph& other) const {
    	if(this->size != other.size) {
    		throw invalid_argument("The graphs are not the same size");
    	}

    	vector<vector<int>> adjMatrix(size, vector<int>(size, INT_MAX));

    	for(int i = 0; i < size; i++) {
    		for(int j = 0; j < size; j++) {
    			if(this->graph[i][j] == INT_MAX) {
    				if(other[i][j] == INT_MAX) {
    					adjMatrix[i][j] = INT_MAX;
    				} else {
    					adjMatrix[i][j] = (-1) * other[i][j];
    				}
    			} else if(other[i][j] == INT_MAX) {
    				adjMatrix[i][j] = this->graph[i][j];
    			} else {
    				adjMatrix[i][j] = this->graph[i][j] - other[i][j];
    			}
    		}
    	}

    	Graph result;
    	result.loadGraph(adjMatrix);

    	return result;
    }
    Graph& Graph::operator-=(const Graph& other) {
    	if(this->size != other.size) {
    		throw invalid_argument("The graphs are not the same size");
    	}

    	for(int i = 0; i < size; i++) {
    		for(int j = 0; j < size; j++) {
    			if(other.graph[i][j] != INT_MAX) {
    				if(this->graph[i][j] == INT_MAX) {
    					this->graph[i][j] = (-1)*other.graph[i][j];
    				} else {
    					this->graph[i][j] -= other[i][j];
    				}
    			}
    		}
    	}
    	return *this;
    }
    Graph& Graph::operator-() {
    	for(int i = 0; i < size; i++) {
    		for(int j = 0; j < size; j++) {
    			if(this->graph[i][j] != INT_MAX) {
    				this->graph[i][j] *= (-1);
	    		}
    		}
    	}
    	return *this;
    }
    Graph& Graph::operator--() {
    	for(int i = 0; i < size; i++) {
    		for(int j = 0; j < size; j++) {
    			if(this->graph[i][j] != INT_MAX && this->graph[i][j] != 0) {
    				this->graph[i][j]--;
	    		}
    		}
    	}
    	return *this;
    }
    Graph Graph::operator--(int) {
    	Graph result = *this;
    	--(*this);
    	return result;
    }

    Graph& Graph::operator*(int x) {
    	for(int i = 0; i < size; i++) {
    		for(int j = 0; j < size; j++) {
    			if(this->graph[i][j] != INT_MAX) {
	    			this->graph[i][j] *= x;
	    		}
    		}
    	}
    	return *this;
    }
    Graph Graph::operator*(const Graph& other) const {
    	if(this->size != other.size) {
    		throw invalid_argument("The graphs are not the same size");
    	}

    	vector<vector<int>> adjMatrix(size, vector<int>(size, INT_MAX));

    	for(int i = 0; i < size; i++) {
	    	for(int j = 0; j < size; j++) {
	    		int sum = 0;
	    		for(int k = 0; k < size; k++) {
	    			if((this->graph[i][k] == INT_MAX) || (other.graph[k][j] == INT_MAX)) {
	    				sum += 0;
	    			} else {
			    		sum += this->graph[i][k]*other.graph[k][j];
			    	}
			    }
			adjMatrix[i][j] = sum;
			}
    	}

    	Graph result;
    	result.loadGraph(adjMatrix);

    	return result;
    }


    bool Graph::identicalGraph(const Graph& other) const {
    	if(this->size != other.size) {
    		return false;
    	}
    	for(int i = 0; i < this->size; i++) {
    		for(int j = 0; j < this->size; j++) {
    			if(this->graph[i][j] != other.graph[i][j]) {
    				return false;
    			}
    		}
    	}
    	return true;
    }

    bool Graph::containsGraph(const Graph& other) const {
    	if(this->identicalGraph(other)) {
    		return false;
    	} else if(this->size < other.size) {
    		return false;
    	} else {
    		for(int i = 0; i < other.size; i++) {
    			for(int j = 0; j < other.size; j++) {
    				if(other.graph[i][j] != INT_MAX && this->graph[i][j] != other.graph[i][j]) {
   						return false;
    				}
    			}
    		}
    	}
    	return true;
    }

    bool Graph::operator==(const Graph& other) const {
    	if(this->identicalGraph(other)) {
    		return true;
    	} else if((*this > other) || (other > *this)) {
    		return false;
    	}
    	return true;
    }
    bool Graph::operator!=(const Graph& other) const {
    	if(*this == other) {
    		return false;
    	}
    	return true;
    }

    bool Graph::operator>(const Graph& other) const {
    	if(this->containsGraph(other)) {
    		return true;
    	} else if(other.containsGraph(*this)) {
    		return false;
    	} else {
    		int numEdgesThis = 0;
    		for(int i = 0; i < this->size; i++) {
    			for(int j = 0; j < this->size; j++) {
    				if(this->graph[i][j] != INT_MAX && this->graph[i][j] != 0) {
    					numEdgesThis++;
    				}
    			}
    		}

    		int numEdgesOther = 0;
    		for(int i = 0; i < other.size; i++) {
    			for(int j = 0; j < other.size; j++) {
    				if(other.graph[i][j] != INT_MAX && other.graph[i][j] != 0) {
    					numEdgesOther++;
    				}
    			}
    		}

    		if(numEdgesThis > numEdgesOther) {
    			return true;
    		} else if(numEdgesThis < numEdgesOther) {
    			return false;
    		} else {
    			if(this->size > other.size) {
    				return true;
    			}
    		}
    	}
    	return false;
    }
    bool Graph::operator>=(const Graph& other) const {
    	if(*this > other || *this == other) {
    		return true;
    	}
    	return false;
    }

	bool Graph::operator<(const Graph& other) const {
		if(other.containsGraph(*this)) {
    		return true;
    	} else if(this->containsGraph(other)) {
    		return false;
    	} else {
    		int numEdgesThis = 0;
    		for(int i = 0; i < this->size; i++) {
    			for(int j = 0; j < this->size; j++) {
    				if(this->graph[i][j] != INT_MAX && this->graph[i][j] != 0) {
    					numEdgesThis++;
    				}
    			}
    		}

    		int numEdgesOther = 0;
    		for(int i = 0; i < other.size; i++) {
    			for(int j = 0; j < other.size; j++) {
    				if(other.graph[i][j] != INT_MAX && other.graph[i][j] != 0) {
    					numEdgesOther++;
    				}
    			}
    		}

    		if(numEdgesThis < numEdgesOther) {
    			return true;
    		} else if(numEdgesThis > numEdgesOther) {
    			return false;
    		} else {
    			if(this->size < other.size) {
    				return true;
    			}
    		}
    	}
    	return false;
	}
	bool Graph::operator<=(const Graph& other) const {
		if(*this < other || *this == other) {
    		return true;
    	}
    	return false;
	}

	ostream& operator<<(ostream& os, const Graph& graph) {
		for(int i = 0; i < graph.size; i++) {
			for(int j = 0; j < graph.size; j++) {
				if(graph.graph[i][j] == INT_MAX) {
					os << "INF ";
				} else {
					os << graph.graph[i][j] << " ";
				}
			}
			os << "\n";
		}
		return os;
	}

}