#include "./include.h"

typedef struct TTexto{
    char* texto;
    char* padrao;
    int tamanho;
} TTexto;

void lerTextoCasamento(TTexto* texto, char* nomeArquivo);

char* leitura_arquivo_TAREFAB(const char* filename);

void save_to_file(char* filename, char* content);

void freeMemoria(TTexto* texto);
