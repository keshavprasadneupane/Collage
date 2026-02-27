#include <iostream>
using namespace std;
const int SIZE = 9;
int B[SIZE];
int count = 0;

void Merge(int A[], int l, int m, int r) {
	int x = l;
	int y = m;
	int k = l;
	count += 3;

	while (x < m && y <= r) {
		if (A[x] < A[y]) {
			B[k] = A[x];
			k++;
			x++;
			count += 6;
		} else {
			B[k] = A[y];
			k++;
			y++;
			count += 6;
		}
	}

	while (x < m) {
		B[k] = A[x];
		k++;
		x++;
		count += 6;
	}

	while (y <= r) {
		B[k] = A[y];
		k++;
		y++;
		count += 6;
	}

	for (int i = l; i <= r; i++) {
		A[i] = B[i];
		count += 5;
	}
}

void MergeSort(int A[], int l, int r) {
	if (l < r) {
		count += 3;
		int m = (l + r) / 2;
		MergeSort(A, l, m);
		MergeSort(A, m + 1, r);
		Merge(A, l, m + 1, r);
	}
}

int main() {
	int a[SIZE] = {100, 22, 12, 45, 809, 130, 170, 10, 200};
	cout << "\nBefore sorting: \n";
	for (int i = 0; i < SIZE; i++) {
		cout << a[i] << "\t";
	}
	cout << endl;
	MergeSort(a, 0, SIZE - 1);
	cout << "After sorting: \n";
	for (int i = 0; i < SIZE; i++) {
		cout << a[i] << "\t";
	}
	cout << endl;
	cout << "No. of Steps required : " << count;

	return 0;
}