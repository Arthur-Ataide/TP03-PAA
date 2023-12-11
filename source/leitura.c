#include "../headers/leitura.h"

void lerTexto(TTexto* texto, char* nomeArquivo){
    FILE *arquivo = fopen(nomeArquivo, "r");

    if(arquivo == NULL){
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }

    char palavra[100];

    if (fscanf(arquivo, "%s", palavra) == 1) {
        printf("O padrao eh: %s\n", palavra);
    }

    fscanf(arquivo, " ");

    texto->padrao = (char*)malloc(sizeof(char) * (strlen(palavra) + 1));

    strcpy(texto->padrao, palavra);

    long pos = ftell(arquivo);

    texto->tamanho = texto->tamanho - pos;

    fseek(arquivo, 0, SEEK_END);
    fseek(arquivo, pos, SEEK_SET);

    texto->texto = (char*)malloc(sizeof(char) * (texto->tamanho + 1));

    fread(texto->texto, sizeof(char), texto->tamanho, arquivo);
    
    texto->texto[texto->tamanho] = '\0';

    fclose(arquivo);
}

void freeMemoria(TTexto* texto) {
    free(texto->padrao);
    free(texto->texto);
    free(texto);
}
