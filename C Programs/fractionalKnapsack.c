#include <stdio.h>
#include <stdlib.h>

// Structure to represent an item
struct Item {
    int value; // Value of the item
    int weight; // Weight of the item
};

// Comparison function used by qsort to sort items in descending order of value per weight
int compare(const void *a, const void *b) {
    double ratio_a = ((double)((struct Item *)a)->value) / ((struct Item *)a)->weight;
    double ratio_b = ((double)((struct Item *)b)->value) / ((struct Item *)b)->weight;
    if (ratio_a < ratio_b)
        return 1;
    else if (ratio_a > ratio_b)
        return -1;
    else
        return 0;
}

// Function to solve the fractional knapsack problem using greedy approach
double fractionalKnapsack(int W, struct Item arr[], int n) {
    // Sort items by decreasing value per weight ratio
    qsort(arr, n, sizeof(struct Item), compare);

    double totalValue = 0.0; // Total value of items selected
    int currentWeight = 0; // Current weight in knapsack

    // Iterate through sorted items and add them to knapsack
    for (int i = 0; i < n; i++) {
        if (currentWeight + arr[i].weight <= W) {
            // If item can be fully added to knapsack
            totalValue += arr[i].value;
            currentWeight += arr[i].weight;
        } else {
            // If item cannot be fully added, calculate fraction of item to add
            int remainingWeight = W - currentWeight;
            totalValue += ((double)arr[i].value / arr[i].weight) * remainingWeight;
            break; // Knapsack is full
        }
    }

    return totalValue;
}

int main() {
    int W = 50; // Knapsack capacity
    struct Item arr[] = {{60, 10}, {100, 20}, {120, 30}}; // Items: {value, weight}
    int n = sizeof(arr) / sizeof(arr[0]);

    double maxValue = fractionalKnapsack(W, arr, n);
    printf("Maximum value that can be obtained = %.2f\n", maxValue);

    return 0;
}
