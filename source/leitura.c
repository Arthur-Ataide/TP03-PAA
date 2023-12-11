#include "../headers/leitura.h"

void lerTextoCasamento(TTexto* texto, char* nomeArquivo){
    FILE *arquivo = fopen(nomeArquivo, "r");

    if(arquivo == NULL){
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }

    char palavra[100];

    fscanf(arquivo, "%s", palavra);
        

    fscanf(arquivo, " ");

    texto->padrao = (char*)malloc(sizeof(char) * (strlen(palavra) + 1));

    strcpy(texto->padrao, palavra);

    texto->padrao = strlwr(texto->padrao);
    printf("O padrao eh: %s\n", texto->padrao);

    long pos = ftell(arquivo);

    texto->tamanho = texto->tamanho - pos;

    fseek(arquivo, 0, SEEK_END);
    fseek(arquivo, pos, SEEK_SET);

    texto->texto = (char*)malloc(sizeof(char) * (texto->tamanho + 1));

    fread(texto->texto, sizeof(char), texto->tamanho, arquivo);
    
    texto->texto[texto->tamanho] = '\0';

    fclose(arquivo);

    texto->texto = strlwr(texto->texto);
}

char* leitura_arquivo_TAREFAB(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* content = (char*)malloc((file_size + 1) * sizeof(char));
    if (content == NULL) {
        fclose(file);
        printf("Erro de alocacao de memoria.\n");
        return NULL;
    }

    fread(content, sizeof(char), file_size, file);
    content[file_size] = '\0';

    fclose(file);

    return content;
}

void save_to_file(char* filename, char* content) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    fprintf(file, "%s", content);
    fclose(file);
}

void freeMemoria(TTexto* texto) {
    free(texto->padrao);
    free(texto->texto);
}
