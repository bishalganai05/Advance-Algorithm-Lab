#include <stdio.h>
#include <string.h>

// Function to compute the LPS (Longest Prefix Suffix) array for the given pattern
void computeLPSArray(char *pat, int M, int *lps) {
    int len = 0;
    lps[0] = 0; // lps[0] is always 0

    int i = 1;
    while (i < M) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// Function to perform string matching using KMP algorithm
void KMPSearch(char *pat, char *txt) {
    int M = strlen(pat); // Length of the pattern
    int N = strlen(txt); // Length of the text

    int lps[M]; // Array to store LPS values for pattern

    computeLPSArray(pat, M, lps); // Compute LPS array

    int i = 0; // Index for text[]
    int j = 0; // Index for pat[]

    while (i < N) {
        if (pat[j] == txt[i]) {
            j++;
            i++;
        }

        if (j == M) {
            printf("Pattern found at index %d\n", i - j);
            j = lps[j - 1];
        } else if (i < N && pat[j] != txt[i]) {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }
}

int main() {
    char txt[] = "AABACAADAABABA";
    char pat[] = "AAB";

    printf("Text: %s\n", txt);
    printf("Pattern: %s\n", pat);

    printf("Occurrences of pattern in text:\n");
    KMPSearch(pat, txt);

    return 0;
}
