#include <stdio.h>
#include <stdlib.h>

// Structure to represent a job
struct Job {
    int id; // Job ID
    int deadline; // Deadline of the job
    int profit; // Profit of the job
};

// Comparison function used by qsort to sort jobs in descending order of profit
int compare(const void *a, const void *b) {
    return (((struct Job *)b)->profit - ((struct Job *)a)->profit);
}

// Function to find the maximum profit by scheduling jobs
void jobSequencing(struct Job arr[], int n) {
    // Sort jobs by decreasing order of profit
    qsort(arr, n, sizeof(struct Job), compare);

    int maxDeadline = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i].deadline > maxDeadline) {
            maxDeadline = arr[i].deadline;
        }
    }

    // Initialize array to track slot availability
    int *slot = (int *)malloc(maxDeadline * sizeof(int));
    for (int i = 0; i < maxDeadline; i++) {
        slot[i] = -1; // Initialize all slots as available
    }

    int totalProfit = 0;
    int jobCount = 0;
    for (int i = 0; i < n; i++) {
        for (int j = (arr[i].deadline - 1); j >= 0; j--) {
            if (slot[j] == -1) {
                slot[j] = arr[i].id;
                totalProfit += arr[i].profit;
                jobCount++;
                break;
            }
        }
    }

    printf("Total profit: %d\n", totalProfit);
    printf("Jobs scheduled: ");
    for (int i = 0; i < maxDeadline; i++) {
        if (slot[i] != -1) {
            printf("%d ", slot[i]);
        }
    }
    printf("\n");

    free(slot);
}

int main() {
    struct Job arr[] = {{1, 4, 20}, {2, 1, 10}, {3, 1, 40}, {4, 1, 30}};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Maximizing profit with deadlines:\n");
    jobSequencing(arr, n);

    return 0;
}
