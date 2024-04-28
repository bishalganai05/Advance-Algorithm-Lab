#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define V 4 // Number of vertices (cities)

// Function to find the minimum of two integers
int min(int a, int b) {
    return (a < b) ? a : b;
}

// Function to find the shortest tour that visits all cities exactly once and returns to the starting city
int tsp(int graph[][V], int mask, int pos, int dp[][1 << V]) {
    // If all cities have been visited, return the cost of returning to the starting city
    if (mask == (1 << V) - 1)
        return graph[pos][0];

    // If the result is already computed, return it
    if (dp[pos][mask] != -1)
        return dp[pos][mask];

    int minCost = INT_MAX;

    // Try to visit each city that has not been visited yet
    for (int city = 0; city < V; city++) {
        if ((mask & (1 << city)) == 0) { // If city has not been visited
            int newMask = mask | (1 << city);
            int cost = graph[pos][city] + tsp(graph, newMask, city, dp);
            minCost = min(minCost, cost);
        }
    }

    // Save the result in the DP table
    dp[pos][mask] = minCost;

    return minCost;
}

int main() {
    int graph[V][V] = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };

    // DP table to memoize intermediate results
    int dp[V][1 << V];
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < (1 << V); j++) {
            dp[i][j] = -1;
        }
    }

    // Start the TSP from the first city (index 0) and initialize the mask with the first city visited
    int startCity = 0;
    int startMask = 1 << startCity;

    // Find the minimum cost of the TSP using DP
    int minCost = tsp(graph, startMask, startCity, dp);

    printf("Minimum cost of the traveling salesman tour: %d\n", minCost);

    return 0;
}
