#include "./include.h"

typedef struct TshifitAnd* PshifitAnd;
typedef struct TshifitAnd{
    int* M;
    char* padrao;
    int tamanho;
} TshifitAnd;

PshifitAnd criarTabelaM(char* padrao);

void shiftAnd(PshifitAnd tabela, char* texto);