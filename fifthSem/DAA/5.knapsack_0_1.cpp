#include <iostream>
using namespace std;

int c[100][100];

void Knapsack(int W, int n, int wt[], int v[]) {
	// Initialize first column to 0
	for (int i = 0; i <= n; i++)
		c[i][0] = 0;

	// Initialize first row to 0
	for (int w = 0; w <= W; w++)
		c[0][w] = 0;

	// Build DP table
	for (int i = 1; i <= n; i++) {
		for (int w = 1; w <= W; w++) {
			if (wt[i - 1] > w) {
				c[i][w] = c[i - 1][w];
			} else {
				c[i][w] = max(v[i - 1] + c[i - 1][w - wt[i - 1]], c[i - 1][w]);
			}
		}
	}
}

int main() {
	int w[100];
	int v[100];
	int W, n;

	cout << "Enter the capacity and number of items: ";
	cin >> W >> n;

	for (int i = 0; i < n; i++) {
		cout << "Enter weight and value of item [" << (i + 1) << "]: ";
		cin >> w[i] >> v[i];
	}

	Knapsack(W, n, w, v);

	cout << "\nKnapsack DP Table:\n";
	for (int i = 0; i <= n; i++) {
		for (int wt = 0; wt <= W; wt++) {
			cout << c[i][wt] << "\t";
		}
		cout << endl;
	}

	return 0;
}