#include <stdio.h>
#include <string.h>

#define N_DE_CHARS 256

int max(int a, int b) {
    return (a > b) ? a : b;
}

void badCharHeuristic(char *str, int size, int badchar[N_DE_CHARS]) {
    int i;
    for (i = 0; i < N_DE_CHARS; i++)
        badchar[i] = -1;
    for (i = 0; i < size; i++)
        badchar[(int)str[i]] = i;
}

void searchBMH(char *txt, char *pat) {
    int m = strlen(pat);
    int n = strlen(txt);
    int badchar[N_DE_CHARS];

    badCharHeuristic(pat, m, badchar);

    int s = 0;
    while (s <= (n - m)) {
        int j = m - 1;

        while (j >= 0 && pat[j] == txt[s + j])
            j--;

        if (j < 0) {
            printf("\nO padrao ocorre no deslocamento = %d", s);
            s += (s + m < n) ? m - badchar[txt[s + m]] : 1;
        } else {
            s += max(1, j - badchar[txt[s + j]]);
        }
    }
}
