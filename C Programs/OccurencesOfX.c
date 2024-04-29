#include <stdio.h>

int countOccurrencesBinary(int arr[], int size, int x) {
    // Find first occurrence
    int first = -1;
    int low = 0, high = size - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == x) {
            first = mid;
            high = mid - 1;
        } else if (arr[mid] < x)
            low = mid + 1;
        else
            high = mid - 1;
    }

    if (first == -1)
        return 0; // If element is not present

    // Find last occurrence
    int last = -1;
    low = 0, high = size - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == x) {
            last = mid;
            low = mid + 1;
        } else if (arr[mid] < x)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return last - first + 1;
}

int main() {
    int arr[] = {1, 2, 2, 3, 3, 3, 4, 4, 5, 5};
    int size = sizeof(arr) / sizeof(arr[0]);
    int x = 3;

    printf("\nUsing O(logn) approach:\n");
    printf("Occurrences of %d: %d\n", x, countOccurrencesBinary(arr, size, x));

    return 0;
}
