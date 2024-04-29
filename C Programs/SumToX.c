#include <stdio.h>

int findTwoElementsOptimized(int arr[], int size, int X) {
    int left = 0;
    int right = size - 1;
    while (left < right) {
        int sum = arr[left] + arr[right];
        if (sum == X) {
            printf("Pair found: %d + %d = %d\n", arr[left], arr[right], X);
            return 0;
        } else if (sum < X) {
            left++;
        } else {
            right--;
        }
    }
    printf("No such pair found.\n");
    return -1;
}

int main() {
    int arr[] = {2, 3, 4, 5, 7, 8, 9};
    int size = sizeof(arr) / sizeof(arr[0]);
    int X = 12;

    int result2 = findTwoElementsOptimized(arr, size, X);
    if(result2 == -1) printf("Result: -1\n");

    return 0;
}
