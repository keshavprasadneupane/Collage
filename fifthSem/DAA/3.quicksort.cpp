#include <iostream>
using namespace std;
int count = 0;
void Swap(int &a, int &b) {
	int t = a;
	a = b;
	b = t;
	count += 4;
}

int partition(int A[], int l, int r) {
	int x = l;
	int y = r;
	int pivot = A[l];

	count += 3;

	while (x < y) {
		while (A[x] <= pivot) {
			x++;
			count += 3;
		}

		while (A[y] > pivot) {
			y--;
			count += 3;
		}

		if (x < y)
			Swap(A[x], A[y]);
	}
	Swap(A[l], A[y]);
	count += 3;
	return y;
}

void RandQuickSort(int A[], int l, int r) {
	if (l < r) {
		count++;
		int p = partition(A, l, r);
		RandQuickSort(A, l, p - 1);
		RandQuickSort(A, p + 1, r);
	}
}

void PrintArray(int A[], int n) {
	for (int i = 0; i < n; i++) {
		cout << A[i] << "\t";
	}
	cout << "\n";
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
	int size = 9;
	Sort(RandQuickSort, a, size, "Average Case");
	Sort(RandQuickSort, a1, size, "Worst Case");
	return 0;
}