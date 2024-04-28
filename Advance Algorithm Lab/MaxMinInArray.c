#include <stdio.h>

// Function to find the maximum and minimum in an array using divide and conquer
void findMaxMin(int arr[], int low, int high, int *max, int *min) {
    if (low == high) {
        *max = *min = arr[low]; // Base case: Single element in array
    } else if (high - low == 1) {
        *max = (arr[low] > arr[high]) ? arr[low] : arr[high]; // Compare two elements
        *min = (arr[low] < arr[high]) ? arr[low] : arr[high];
    } else {
        int mid = (low + high) / 2;
        int leftMax, leftMin, rightMax, rightMin;

        // Divide the array into two halves and recursively find max and min
        findMaxMin(arr, low, mid, &leftMax, &leftMin);
        findMaxMin(arr, mid + 1, high, &rightMax, &rightMin);

        // Merge the results
        *max = (leftMax > rightMax) ? leftMax : rightMax;
        *min = (leftMin < rightMin) ? leftMin : rightMin;
    }
}

int main() {
    int arr[] = {12, 45, 67, 8, 90, 6, 23, 78};
    int size = sizeof(arr) / sizeof(arr[0]);
    int max, min;

    findMaxMin(arr, 0, size - 1, &max, &min);

    printf("Maximum element in the array: %d\n", max);
    printf("Minimum element in the array: %d\n", min);

    return 0;
}
