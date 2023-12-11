#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>
#include <limits.h>
#include <time.h>

#define ALPHABET_SIZE 26

#if defined(__MINGW32__) || defined(_MSC_VER)
#define limpar_input() fflush(stdin)
#define limpar_tela() system("cls")
#define pausar_tela() system("pause")
#else
#include <stdio_ext.h>
#define limpar_input() __fpurge(stdin)
#define limpar_tela() system("clear")
#define pausar_tela() printf("\nPress any key to continue..."); limpar_input(); getchar();
#endif
