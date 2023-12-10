#include "shiftAnd.h"

#define MAX_PATTERN_LENGTH 32

void shiftAnd(char *pattern, char *text) {
    int m = strlen(pattern);
    int n = strlen(text);

    // Inicialize a matriz de bits para representar as máscaras
    unsigned int masks[256] = {0};
    for (int i = 0; i < m; i++) {
        masks[(unsigned char)pattern[i]] |= 1 << i;
    }

    // Inicialize a máscara para a posição mais à esquerda
    unsigned int bitMask = 1 << (m - 1);

    // Inicialize o vetor de estados
    unsigned int state = 0;

    // Iterar sobre o texto
    for (int i = 0; i < n; i++) {
        // Atualize o estado com a máscara atual
        state = ((state << 1) | 1) & masks[(unsigned char)text[i]];

        // Verifique se a posição mais à esquerda é 1 (padrão encontrado)
        if (state & bitMask) {
            printf("Oi");
            printf("Padrão encontrado na posição %d\n", i - m + 1);
        }
    }
}