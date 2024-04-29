#include <stdio.h>
#include <stdlib.h>

// Function to add two matrices
void addMatrix(int n, int A[][n], int B[][n], int C[][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

// Function to subtract two matrices
void subtractMatrix(int n, int A[][n], int B[][n], int C[][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

// Function to multiply two matrices using Strassen's algorithm
void strassenMultiply(int n, int A[][n], int B[][n], int C[][n]) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    // Divide matrices into submatrices
    int newSize = n / 2;
    int A11[newSize][newSize], A12[newSize][newSize], A21[newSize][newSize], A22[newSize][newSize];
    int B11[newSize][newSize], B12[newSize][newSize], B21[newSize][newSize], B22[newSize][newSize];
    int C11[newSize][newSize], C12[newSize][newSize], C21[newSize][newSize], C22[newSize][newSize];
    int M1[newSize][newSize], M2[newSize][newSize], M3[newSize][newSize], M4[newSize][newSize], M5[newSize][newSize], M6[newSize][newSize], M7[newSize][newSize];
    int temp1[newSize][newSize], temp2[newSize][newSize];

    // Divide matrix A into submatrices
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];
        }
    }

    // Divide matrix B into submatrices
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }
    }

    // Calculate M1 = (A11 + A22) * (B11 + B22)
    addMatrix(newSize, A11, A22, temp1);
    addMatrix(newSize, B11, B22, temp2);
    strassenMultiply(newSize, temp1, temp2, M1);

    // Calculate M2 = (A21 + A22) * B11
    addMatrix(newSize, A21, A22, temp1);
    strassenMultiply(newSize, temp1, B11, M2);

    // Calculate M3 = A11 * (B12 - B22)
    subtractMatrix(newSize, B12, B22, temp1);
    strassenMultiply(newSize, A11, temp1, M3);

    // Calculate M4 = A22 * (B21 - B11)
    subtractMatrix(newSize, B21, B11, temp1);
    strassenMultiply(newSize, A22, temp1, M4);

    // Calculate M5 = (A11 + A12) * B22
    addMatrix(newSize, A11, A12, temp1);
    strassenMultiply(newSize, temp1, B22, M5);

    // Calculate M6 = (A21 - A11) * (B11 + B12)
    subtractMatrix(newSize, A21, A11, temp1);
    addMatrix(newSize, B11, B12, temp2);
    strassenMultiply(newSize, temp1, temp2, M6);

    // Calculate M7 = (A12 - A22) * (B21 + B22)
    subtractMatrix(newSize, A12, A22, temp1);
    addMatrix(newSize, B21, B22, temp2);
    strassenMultiply(newSize, temp1, temp2, M7);

    // Calculate C11 = M1 + M4 - M5 + M7
    addMatrix(newSize, M1, M4, temp1);
    subtractMatrix(newSize, temp1, M5, temp2);
    addMatrix(newSize, temp2, M7, C11);

    // Calculate C12 = M3 + M5
    addMatrix(newSize, M3, M5, C12);

    // Calculate C21 = M2 + M4
    addMatrix(newSize, M2, M4, C21);

    // Calculate C22 = M1 - M2 + M3 + M6
    subtractMatrix(newSize, M1, M2, temp1);
    addMatrix(newSize, temp1, M3, temp2);
    addMatrix(newSize, temp2, M6, C22);

    // Combine submatrices to get result matrix C
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            C[i][j] = C11[i][j];
            C[i][j + newSize] = C12[i][j];
            C[i + newSize][j] = C21[i][j];
            C[i + newSize][j + newSize] = C22[i][j];
        }
    }
}

// Function to display a matrix
void displayMatrix(int n, int mat[][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d\t", mat[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int n = 3; // Size of the square matrix (odd dimension)
    int A[n][n], B[n][n], C[n][n];

    printf("Enter elements of matrix A:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &A[i][j]);
        }
    }

    printf("Enter elements of matrix B:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &B[i][j]);
        }
    }

    printf("\nMatrix A:\n");
    displayMatrix(n, A);

    printf("\nMatrix B:\n");
    displayMatrix(n, B);

    // Perform matrix multiplication using Strassen's algorithm
    strassenMultiply(n, A, B, C);

    printf("\nResultant Matrix (A * B) using Strassen's Algorithm:\n");
    displayMatrix(n, C);

    return 0;
}
