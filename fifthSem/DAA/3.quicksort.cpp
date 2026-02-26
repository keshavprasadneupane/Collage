#include <iostream>
using namespace std;
int count = 0;

int partition(int A[], int l, int r) {
	int x = l;
	int y = r;
	int pivot = A[l];

	count = count + 3;

	while (x < y) {
		while (A[x] <= pivot) {
			x++;
			count = count + 3;
		}

		while (A[y] > pivot) {
			y--;
			count = count + 3;
		}

		if (x < y) {
			int t = A[x];
			A[x] = A[y];
			A[y] = t;
			count = count + 4;
		}
	}
	A[l] = A[y];
	A[y] = pivot;
	count = count + 3;
	return y;
}

void QuickSort(int A[], int l, int r) {
	if (l < r) {
		count++;
		int p = partition(A, l, r);
		QuickSort(A, l, p - 1);
		QuickSort(A, p + 1, r);
	}
}

void PrintArray(int A[], int n) {
	for (int i = 0; i < n; i++) {
		cout << A[i] << "\t";
	}
	cout << endl;
}
void Sort(void (*sort)(int[], int, int), int A[], int n, const char *name) {
	count = 0;
	cout << "\nSorting using Quick Sort , case = " << name << "\n";
	cout << "Before sorting: \n";
	PrintArray(A, n);
	sort(A, 0, n - 1);
	cout << "After sorting: \n";
	PrintArray(A, n);
	cout << "No. of Steps required : " << count << "\n";
}

int main() {

	int a[9] = {100, 22, 12, 45, 809, 130, 170, 10, 200};
	int a1[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9}; // worst case
	int size = sizeof(a) / sizeof(a[0]);
	Sort(QuickSort, a, size, "Average Case");
	Sort(QuickSort, a1, size, "Worst Case");
	return 0;
}