#include <iostream>
using namespace std;

const int MAX = 100;
const int INF = 999999;

int cost[MAX][MAX]; // Cost matrix to store edge weights between offices
bool visited[MAX];	// Array to keep track of visited offices

// Function to apply Prim's Algorithm
int prim(int n)
{
	int totalCost = 0; // Total cost of the Minimum Spanning Tree
	int minCost;

	visited[0] = true; // Start from office 0 (can be any office)

	// Repeat until we include (n - 1) edges in MST
	for (int edges = 1; edges < n; edges++) {
		minCost = INF;
		int a = -1, b = -1;

		// Find the minimum cost edge connecting visited and unvisited vertices
		for (int i = 0; i < n; i++) {
			if (visited[i]) {
				for (int j = 0; j < n; j++) {
					if (!visited[j] && cost[i][j] < minCost) {
						minCost = cost[i][j];
						a = i;
						b = j;
					}
				}
			}
		}

		// Add the selected edge to MST
		if (a != -1 && b != -1) {
			visited[b] = true;					// Mark the new vertex as visited
			totalCost += cost[a][b];			// Add cost to total
			cout << "Edge selected: " << a << " - " << b 
				 << " (Cost: " << cost[a][b] << ")\n";	// Display the edge
		}
	}

	return totalCost; // Return total cost of the MST
}

int main()
{
	int n;
	cout << "Enter number of offices: ";
	cin >> n;

	// Input the cost of connecting each pair of offices
	cout << "Enter cost matrix (0 for no direct connection):\n";
	for (int i = 0; i < n; i++) {
		visited[i] = false; // Initialize all offices as unvisited
		for (int j = 0; j < n; j++) {
			cin >> cost[i][j];
			// If no connection, set to INF so it is not chosen
			if (cost[i][j] == 0)
				cost[i][j] = INF;
		}
	}

	// Run Prim's Algorithm and display minimum total cost
	int minTotal = prim(n);
	cout << "\nMinimum cost to connect all offices: " << minTotal << endl;

	return 0;
}
