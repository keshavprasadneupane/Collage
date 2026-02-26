#include <iostream>
using namespace std;
int COUNT = 0;

void BubbleSort(int A[], int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n - 1; j++) {
			if (A[j] > A[j + 1]) {
				int t = A[j];
				A[j] = A[j + 1];
				A[j + 1] = t;
			}
			COUNT = COUNT + 8;
		}
		COUNT = COUNT + 4;
	}
}
void SelectionSort(int A[], int n) {
	for (int i = 0; i < n; i++) {
		int least = A[i];
		int l_index = i;

		for (int j = i + 1; j < n; j++) {
			if (A[j] < least) {
				least = A[j];
				l_index = j;
			}
			COUNT = COUNT + 6;
		}
		A[l_index] = A[i];
		A[i] = least;
		COUNT = COUNT + 8;
	}
}
void InsertionSort(int A[], int n) {
	int key;
	int j;
	for (int i = 1; i <= n - 1; i++) {
		key = A[i];

		for (j = i - 1; A[j] > key && j >= 0; j--) {
			A[j + 1] = A[j];
			COUNT += 7;
		}
		A[j + 1] = key;
		COUNT += 7;
	}
}
void Sort(void (*sort)(int[], int), int A[], int n, const char *name) {
	COUNT = 0;
	cout << "\nSorting using " << name << "\n";
	cout << "Before sorting: \n";
	for (int i = 0; i < n; i++) {
		cout << A[i] << "\t";
	}
	cout << "\n";
	sort(A, n);
	cout << "After sorting: \n";
	for (int i = 0; i < n; i++) {
		cout << A[i] << "\t";
	}
	cout << "\n";
	cout << "No. of Steps required : " << COUNT << "\n";
}
int main() {

	int arr[9] = {100, 22, 12, 45, 809, 130, 170, 10, 200};

	int size = sizeof(arr) / sizeof(arr[0]);
	Sort(BubbleSort, arr, size, "Bubble Sort");
	Sort(SelectionSort, arr, size, "Selection Sort");
	Sort(InsertionSort, arr, size, "Insertion Sort");
	return 0;
}