#include <iostream>
#include <climits>
using namespace std;

const int MAX = 100;

int main()
{
	int n, i, j, r, l;

	cout << "Enter number of keys: ";
	cin >> n;

	int keys[MAX];
	float p[MAX];		  // Probabilities of searching for each key
	float cost[MAX][MAX]; // DP table to store minimum cost
	int root[MAX][MAX];   // Table to store root of subtree from i to j

	cout << "Enter keys in sorted order:\n";
	for (i = 0; i < n; i++) {
		cin >> keys[i];
	}

	cout << "Enter corresponding search probabilities:\n";
	for (i = 0; i < n; i++) {
		cin >> p[i];
	}

	// Initialize the diagonal elements (cost[i][i]) with the probability of that key
	for (i = 0; i < n; i++) {
		cost[i][i] = p[i];
		root[i][i] = i;
	}

	// l is the chain length (number of keys in the subproblem)
	for (l = 2; l <= n; l++) {
		for (i = 0; i <= n - l; i++) {
			j = i + l - 1;	// Ending index of subarray
			cost[i][j] = INT_MAX;
			float sum = 0;

			// Calculate sum of probabilities from i to j
			for (r = i; r <= j; r++) {
				sum += p[r];
			}

			// Try making each key from i to j the root, and calculate cost
			for (r = i; r <= j; r++) {
				float c = 0;

				// Cost of left subtree
				if (r > i)
					c += cost[i][r - 1];

				// Cost of right subtree
				if (r < j)
					c += cost[r + 1][j];

				// Total cost = left + right + sum of all probabilities
				c += sum;

				// Update minimum cost and corresponding root
				if (c < cost[i][j]) {
					cost[i][j] = c;
					root[i][j] = r;
				}
			}
		}
	}

	cout << "\nMinimum cost of optimal BST: " << cost[0][n - 1] << endl;

	// Display root matrix for understanding how tree can be reconstructed
	cout << "\nRoot Matrix:\n";
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (j >= i)
				cout << root[i][j] << " ";
			else
				cout << "- ";
		}
		cout << endl;
	}

	return 0;
}
