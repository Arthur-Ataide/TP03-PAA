# include <limits.h>
# include <string.h>
# include <stdio.h>

int maximo(int a, int b);

void badCharHeuristic(char *pattern, int patternLength, int badChar[]);

int boyerMoore(char *text, char *pattern);