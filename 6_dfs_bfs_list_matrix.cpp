#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int MAX = 100;
int adjMatrix[MAX][MAX];		 // Adjacency Matrix
vector<int> adjList[MAX];		 // Adjacency List
bool visited[MAX];				 // Visited array

// DFS using adjacency matrix
void DFS_Matrix(int v, int n) {
	visited[v] = true;
	cout << v << " ";
	for (int i = 1; i <= n; i++) {
		if (adjMatrix[v][i] == 1 && !visited[i]) {
			DFS_Matrix(i, n);
		}
	}
}

// BFS using adjacency matrix
void BFS_Matrix(int start, int n) {
	for (int i = 1; i <= n; i++) visited[i] = false;
	queue<int> q;
	visited[start] = true;
	q.push(start);

	while (!q.empty()) {
		int v = q.front();
		q.pop();
		cout << v << " ";
		for (int i = 1; i <= n; i++) {
			if (adjMatrix[v][i] == 1 && !visited[i]) {
				visited[i] = true;
				q.push(i);
			}
		}
	}
}

// DFS using adjacency list
void DFS_List(int v) {
	visited[v] = true;
	cout << v << " ";
	for (int i = 0; i < adjList[v].size(); i++) {
		int u = adjList[v][i];
		if (!visited[u]) {
			DFS_List(u);
		}
	}
}

// BFS using adjacency list
void BFS_List(int start) {
	for (int i = 0; i < MAX; i++) visited[i] = false;
	queue<int> q;
	visited[start] = true;
	q.push(start);

	while (!q.empty()) {
		int v = q.front();
		q.pop();
		cout << v << " ";
		for (int i = 0; i < adjList[v].size(); i++) {
			int u = adjList[v][i];
			if (!visited[u]) {
				visited[u] = true;
				q.push(u);
			}
		}
	}
}

int main() {
	int n, e;
	cout << "Enter number of vertices (1 to n): ";
	cin >> n;
	cout << "Enter number of edges: ";
	cin >> e;

	// Initialize adjacency matrix
	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= n; j++)
			adjMatrix[i][j] = 0;

	// Read edges
	for (int i = 0; i < e; i++) {
		int u, v;
		cout << "Enter edge (u v): ";
		cin >> u >> v;
		adjMatrix[u][v] = 1;
		adjMatrix[v][u] = 1; // Undirected
		adjList[u].push_back(v);
		adjList[v].push_back(u);
	}

	int start;
	cout << "Enter starting vertex for traversal: ";
	cin >> start;

	// DFS using matrix
	for (int i = 0; i < MAX; i++) visited[i] = false;
	cout << "\nDFS using adjacency matrix: ";
	DFS_Matrix(start, n);

	// BFS using matrix
	cout << "\nBFS using adjacency matrix: ";
	BFS_Matrix(start, n);

	// DFS using list
	for (int i = 0; i < MAX; i++) visited[i] = false;
	cout << "\nDFS using adjacency list: ";
	DFS_List(start);

	// BFS using list
	cout << "\nBFS using adjacency list: ";
	BFS_List(start);

	return 0;
}
