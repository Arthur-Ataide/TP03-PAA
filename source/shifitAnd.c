#include "../headers/shifitAnd.h"

void print_binary(unsigned int number) {
    if (number) {
        print_binary(number >> 1);
        putc((number & 1) ? '1' : '0', stdout);
    }
}

PshifitAnd criarTabelaM(char* padrao){

    PshifitAnd tabela = (PshifitAnd) malloc(sizeof(TshifitAnd));
    padrao = strlwr(padrao);

    tabela->padrao = padrao;
    tabela->tamanho = strlen(padrao);

    unsigned int masks[256] = {0};

    for (int i = 0; i < tabela->tamanho; i++) {

        masks[(unsigned char)padrao[i]] |= 1 << i;
        
    }

    tabela->M = masks;

    return tabela;
}

void shiftAnd(PshifitAnd tabela, char* texto) {
    int n = strlen(texto);

    // Inicialize a máscara para a posição mais à esquerda
    unsigned int bitMask = 1 << (tabela->tamanho - 1);

    // Inicialize o vetor de estados
    unsigned int state = 0;
    bool encontrado = false;

    // Iterar sobre o texto
    for (int i = 0; i < n; i++) {
        // Atualize o estado com a máscara atual
        state = ((state << 1) | 1) & tabela->M[(unsigned char)texto[i]];

        // Verifique se a posição mais à esquerda é 1 (padrão encontrado)
        if (state & bitMask) {
            printf("Padrao encontrado na posicao %d\n", i - tabela->tamanho + 1);
            encontrado = true;
        }
    }

    if (!encontrado) {
        printf("\n\nPadrao nao encontrado\n\n");
    }
}