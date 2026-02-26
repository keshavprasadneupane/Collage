#include <climits>
#include <iostream>
#include <vector>
using namespace std;

int c = 0;

// Function to print optimal parenthesization
void printOptimalParenthesis(vector<vector<int>> &s, int i, int j) {
	if (i == j) {
		cout << "A" << i;
		return;
	}

	cout << "(";
	printOptimalParenthesis(s, i, s[i][j]);
	printOptimalParenthesis(s, s[i][j] + 1, j);
	cout << ")";
}

int MatrixChainOrder(int p[], int n) {
	vector<vector<int>> m(n, vector<int>(n));
	vector<vector<int>> s(n, vector<int>(n));

	for (int i = 1; i < n; i++) {
		m[i][i] = 0;
		c++;
	}

	for (int L = 2; L < n; L++) {
		for (int i = 1; i < n - L + 1; i++) {
			int j = i + L - 1;
			m[i][j] = INT_MAX;
			c += 4;

			for (int k = i; k <= j - 1; k++) {
				int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
				c += 7;

				if (q < m[i][j]) {
					m[i][j] = q;
					s[i][j] = k;
					c++;
				}

				c += 5;
			}
			c += 6;
		}
		c += 4;
	}

	cout << "\nOptimal Parenthesization: ";
	printOptimalParenthesis(s, 1, n - 1);
	cout << endl;

	return m[1][n - 1];
}

int main() {
	int size;

	cout << "Enter number of matrices: ";
	cin >> size;

	int arr[100];

	cout << "Enter " << size + 1 << " dimensions: ";
	for (int i = 0; i <= size; i++)
		cin >> arr[i];

	int result = MatrixChainOrder(arr, size + 1);

	cout << "\nMinimum number of multiplications: " << result << endl;
	cout << "Number of steps required: " << c << endl;

	return 0;
}