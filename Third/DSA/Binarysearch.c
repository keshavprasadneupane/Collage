#include <stdio.h>
#define ERROR (-9999999)

int binarySearch(int arr[], int size, int target) {
    int left = 0;
    int right = size - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target) {
            return mid;
        } 
        else if (arr[mid] < target) {
            left = mid + 1;
        } 
        else {
            right = mid - 1; 
        }
    }

    return ERROR;
}

int main() {
    int arr[] = {2,4,7,11,16,23,32};
    int size = sizeof(arr) / sizeof(arr[0]);
    int target = 16;

    int result = binarySearch(arr, size, target);

    if (result != ERROR) {
        printf("Element found at index %d\n", result);
    } else {
        printf("Element not found\n");
    }

    return 0;
}
