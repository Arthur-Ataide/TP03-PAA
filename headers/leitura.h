#include "./include.h"

typedef struct TTexto{
    char* texto;
    char* padrao;
    int tamanho;
} TTexto;

void lerTexto(TTexto* texto, char* nomeArquivo);

void freeMemoria(TTexto* texto);
