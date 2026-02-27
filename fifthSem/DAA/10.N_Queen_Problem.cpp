#include <iostream>
using namespace std;
const int N = 4;
int count = 0;

void printSolution(int board[N][N]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (board[i][j] == 1)
				cout << "Q";
			else
				cout << ".";
		}
		cout << endl;
	}
}

bool isSafe(int board[N][N], int row, int col) {
	// Check left side of current row
	for (int i = 0; i < col; i++) {
		if (board[row][i] == 1) {
			count++;
			return false;
		}
		count += 4;
	}

	// Check upper-left diagonal
	for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
		if (board[i][j] == 1) {
			count++;
			return false;
		}
		count += 6;
	}

	// Check lower-left diagonal
	for (int i = row, j = col; i < N && j >= 0; i++, j--) {
		if (board[i][j] == 1) {
			count++;
			return false;
		}
		count += 6;
	}
	return true;
}

bool solveNQUtil(int board[N][N], int col) {
	if (col >= N) {
		count++;
		return true;
	}

	for (int i = 0; i < N; i++) {
		if (isSafe(board, i, col)) {
			board[i][col] = 1;
			count++;
			if (solveNQUtil(board, col + 1)) {
				count++;
				return true;
			}
			board[i][col] = 0; // backtrack
		}
	}

	return false;
}

bool solveNQ() {
	int board[N][N] = {0}; // initialize all to 0

	if (!solveNQUtil(board, 0)) {
		cout << "Solution does not exist" << endl;
		return false;
	}
	printSolution(board);
	return true;
}

int main() {
	solveNQ();
	cout << "No. of required steps: " << count << endl;
	return 0;
}