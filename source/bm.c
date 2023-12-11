#include "../headers/bm.h"

#define ALPHABET_SIZE_BM 256

int maximo(int a, int b) {
    return (a > b) ? a : b;
}

void badCharHeuristic(char *pattern, int patternLength, int badChar[ALPHABET_SIZE_BM]) {
    int i;
    for (i = 0; i < ALPHABET_SIZE_BM; i++)
        badChar[i] = -1;

    for (i = 0; i < patternLength; i++)
        badChar[(int)pattern[i]] = i;
}

int boyerMoore(char *text, char *pattern) {
    int textLength = strlen(text);
    int patternLength = strlen(pattern);

    int badChar[ALPHABET_SIZE_BM];
    badCharHeuristic(pattern, patternLength, badChar);

    int s = 0;
    while (s <= (textLength - patternLength)) {
        int j = patternLength - 1;

        while (j >= 0 && pattern[j] == text[s + j])
            j--;

        if (j < 0)
            return s;
        else
            s += maximo(1, j - badChar[(int)text[s + j]]);
    }
    return -1;
}