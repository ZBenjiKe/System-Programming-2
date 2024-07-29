#include "Algorithms.hpp"
#include <stdexcept>
#include <string>
#include <queue>
#include <vector>
#include <stack>
#include <climits>

using namespace std;

namespace ariel {


	// Check connectivity - Done
	int isConnectedUndirected(const Graph& graph){
		int nodes = graph.size;
		int source = 0;
		vector<int> reached(nodes, 0);
		queue<int> q;
		q.push(source);
		reached[source] = 1;
		while (!q.empty()) {
			int u = q.front();
			q.pop();
			for(int v = 0; v < nodes; v++) {
				if (graph[u][v] != INT_MAX && reached[v] == 0) {
					q.push(v);
					reached[v] = 1;
				}
			}
		}
		for (int i = 0; i < nodes; i++)	{
			if (reached[i] == 0) {
				return 0;
			}
		}
		return 1;
	}

	int isConnectedDirected(const Graph& graph){
		int nodes = graph.size;
		int source = 0;
		vector<int> reached(nodes, 0);
		queue<int> q;
		q.push(source);
		reached[source] = 1;
		while (!q.empty()) {
			int u = q.front();
			q.pop();
			for(int v = 0; v < nodes; v++) {
				if (graph[u][v] != INT_MAX && reached[v] == 0) {
					q.push(v);
					reached[v] = 1;
				}
			}
		}
		for (int i = 0; i < nodes; i++)	{
			if (reached[i] == 0) {
				return 0;
			}
		}
		vector<vector<int>> reverseGraph(nodes, vector<int>(nodes, 0));
		for (int i = 0; i < nodes; i++) {
			for (int j=0; j < nodes; j++) {
				reverseGraph[i][j] = graph[j][i];
			}
		}
		vector<int> reachedReverse(nodes, 0);
		q.push(source);
		reachedReverse[source] = 1;
		while (!q.empty()) {
			int u = q.front();
			q.pop();
			for(int v = 0; v < nodes; v++) {
				if (reverseGraph[u][v] != INT_MAX && reachedReverse[v] == 0) {
					q.push(v);
					reachedReverse[v] = 1;
				}
			}
		}
		for (int i = 0; i < nodes; i++)	{
			if (reachedReverse[i] == 0) {
				return 0;
			}
		}
		return 1;
	}

	int isConnected(const Graph& graph) {
		if(graph.directed == 0) {
			return isConnectedUndirected(graph);
		} else {
			return isConnectedDirected(graph);
		}
	}


	// Find shortest path - Done
	string shortestPath(const Graph& graph, int start, int end) {
		
		// Get graph parameters
		int size = graph.size;
		vector<int> distance(size, INT_MAX);
		vector<int> parent(size, -1);
		distance[start] = 0;


		// Relax edges of graph n-1 times
		for(int n = 0; n < size-1; n++) {
			for (int i = 0; i < size; i++) {
				for (int j = 0; j < size; j++) {
					if ((graph[i][j] != INT_MAX) && (distance[i] != INT_MAX)) {
						if (distance[j] > graph[i][j] + distance[i]) {
							distance[j] = graph[i][j] + distance[i];
							parent[j] = i;
						}
					}
				}
			}
		}

		// Relax n-th time to check for are negative cycles
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if ((graph[i][j] != INT_MAX) && (distance[i] != INT_MAX)) {
					if (distance[j] > graph[i][j] + distance[i]) {
						return "-1: Negative cycle detected";
					}
				}
			}
		}

		// Extract path from start vertex to end vertex 
		if (distance[end] == INT_MAX) {
			return "-1: No path between vertices";
		} else {
			stack<int> path;
			int prev = parent[end];
			while(prev != start){
				path.push(prev);
				prev = parent[prev];
			}
			path.push(start);

			// Print the shortest path
			string sp = "Shortest path: ";
			while(!path.empty()) {
				sp += to_string(path.top()) + "->";
				path.pop();
			}
			sp += to_string(end);
			return sp;
		}
	}


	// Check for cycles - Done
	void dfs(const Graph& graph, int u, vector<int>& color, vector<int>& parent, vector<int>& discovered, vector<int>& finished, int& rtime) {
		color[u] = 1;
		rtime += 1;
		discovered[u] = rtime;

		for(int v = 0; v < graph.size; v++) {
	        if (graph[u][v] != INT_MAX) { // Check if there is an edge
				if(color[v] == 0) {
					parent[v] = u;
					dfs(graph, v, color, parent, discovered, finished, rtime);
				}
			}
		}

		color[u] = 2;
		rtime += 1;
		finished[u] = rtime;
	}

	string containsCycleUndirected(const Graph& graph) {
		
		int size = graph.size;
		vector<int> color(size, 0);
		vector<int> parent(size, -1);
		vector<int> discovered(size, 0);
		vector<int> finished(size, 0);

		int time = 0;
		int& rtime = time;

		for(int u = 0; u < size; u++) {
			if(color[u] == 0) {
				dfs(graph, u, color, parent, discovered, finished, rtime);
			}
		}

		// for(int i = 0; i < size; i ++) {
		// 	cout << "Node " << i << ": " << ", parent=" << parent[i] << ", discovered=" << discovered[i] << ", finished=" << finished[i] << endl;
		// }

		for(int u = 0; u < size; u++) {
			for(int v = 0; v < size; v++) {
				if((graph[u][v] != INT_MAX) && (u != v) && (parent[u] != v)) {
					if(discovered[v] < discovered[u] && finished[u] < finished[v]) {
						// Cycle detected
						stack<int> cycle;
						int prev = u;
						while(prev != v) {
							cycle.push(prev);
							prev = parent[prev];
						}
						string cf = "Cycle detected: " + to_string(v);
						while(!cycle.empty()) {
							cf += "->" + to_string(cycle.top());
							cycle.pop();
						}
						return cf;
					}
				}
			}
		}

		return "No cycles detected";
	}

	string containsCycleDirected(const Graph& graph) {
		
		int size = graph.size;
		vector<int> color(size, 0);
		vector<int> parent(size, -1);
		vector<int> discovered(size, 0);
		vector<int> finished(size, 0);

		int time = 0;
		int& rtime = time;

		for(int u = 0; u < size; u++) {
			if(color[u] == 0) {
				dfs(graph, u, color, parent, discovered, finished, rtime);
			}
		}

		// for(int i = 0; i < size; i ++) {
		// 	cout << "Node " << i << ": " << ", parent=" << parent[i] << ", discovered=" << discovered[i] << ", finished=" << finished[i] << endl;
		// }

		for(int u = 0; u < size; u++) {
			for(int v = 0; v < size; v++) {
				if((graph[u][v] != INT_MAX) && (u != v)) {
					if(discovered[v] < discovered[u] && finished[u] < finished[v]) {
						// Cycle detected
						stack<int> cycle;
						int prev = u;
						while(prev != v) {
							cycle.push(prev);
							prev = parent[prev];
						}
						string cf = "Cycle detected: " + to_string(v);
						while(!cycle.empty()) {
							cf += "->" + to_string(cycle.top());
							cycle.pop();
						}
						return cf;
					}
				}
			}
		}

		return "No cycles detected";
	}

	string containsCycle(const Graph& graph) {
		if(graph.directed == 0) {
			return containsCycleUndirected(graph);
		} else {
			return containsCycleDirected(graph);
		}
	}


	// Check if the graph is bipartite - Done
	string isBipartite(const Graph& graph) {
		int size = graph.size;

		vector<int> color(size, -1);

		for (int i = 0; i < size; i++) {
			if (color[i] == -1) {
				color[i] = 0;
				queue<int> q;
				q.push(i);
				while (!q.empty()) {
					int u = q.front();
					q.pop();
					for(int v = 0; v < size; v++) {
						if ((u != v) && ((graph[u][v] != INT_MAX) || (graph[v][u] != INT_MAX))) {
							if (color[v] == -1) {
								q.push(v);
								color[v] = 1-color[u];
							} else if (color[v] == color[u]) {
								return "0: The graph is not bipartite";
							}
						}
					}
				}				
			}
		}
		string partition = "The graph is bipartite: U = {";
		for(int i = 0; i < size; i++){
			if(color[i] == 0) {
				partition += (to_string(i) + " ");
			}
		}

		partition += "}, W = {";
		for(int i = 0; i < size; i++){
			if(color[i] == 1) {
				partition += (to_string(i) + " ");
			}
		}
		partition += "}";
		return partition;
	}


	// Check if there are negative cycles in the graph - Done
	string negativeCycle(const Graph& graph) {
		int size = graph.size;
		vector<int> distance(size, INT_MAX);
		vector<int> parent(size, -1);

		int source = 0;
		distance[source] = 0;

		// Relax graph n-1 times
		for(int n = 0; n < size-1; n++) {
			for(int i = 0; i < size; i++) {
				for(int j = 0; j < size; j++) {				
					if ((graph[i][j] != INT_MAX) && (distance[i] != INT_MAX)) {
						if (distance[j] > distance[i] + graph[i][j]) {
							distance[j] = distance[i] + graph[i][j];
							parent[j] = i;
						}
					}
				}
			}
		}

		// Relax for n-th time to check for negative cycle
		for(int i = 0; i < size; i++) {
			for(int j = 0; j < size; j++) {
				if ((graph[i][j] != INT_MAX) && (distance[i] != INT_MAX)) {
					if (distance[j] > distance[i] + graph[i][j]) {
						parent[j] = i;
						
						stack <int> nCyclePath;
						nCyclePath.push(j);
						int prev = parent[j];
						while(prev != j) {
							nCyclePath.push(prev);
							prev = parent[prev];
						}

						string nc = "Negative cycle found: ";
						nc += to_string(j);
						while(!nCyclePath.empty()) {
							nc += "->" + to_string(nCyclePath.top());
							nCyclePath.pop();
						}

						return nc;
					}
				}
			}
		}
		return "-1: No negative cycles were found";
	}

}