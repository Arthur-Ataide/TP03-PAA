#include "./headers/bm.h"
#include "./headers/shifitAnd.h"
#include "./headers/leitura.h"

//struct timespec begin;
//struct timespec end;

#define ALPHABET_SIZE 26

char* encrypt(char* text, int shift) {
    int length = strlen(text);
    char* encrypted_text = (char*)malloc((length + 1) * sizeof(char));

    for (int i = 0; i < length; i++) {
        if (isalpha(text[i])) {
            char base = islower(text[i]) ? 'a' : 'A';
            encrypted_text[i] = (((text[i] - base) + shift) % ALPHABET_SIZE) + base;
        } else {
            encrypted_text[i] = text[i];
        }
    }

    encrypted_text[length] = '\0';
    return encrypted_text;
}

char* decrypt(char* text, int shift) {
    return encrypt(text, ALPHABET_SIZE - shift);
}

void frequency_table(char* text) {
    int frequencies[ALPHABET_SIZE] = {0};
    int total_chars = 0;
    int length = strlen(text);

    for (int i = 0; i < length; i++) {
        if (isalpha(text[i])) {
            char base = islower(text[i]) ? 'a' : 'A';
            frequencies[text[i] - base]++;
            total_chars++;
        }
    }
}

float frequencies_expected[ALPHABET_SIZE] = {
    14.63, 1.04, 3.88, 4.99, 12.57, 1.02, 1.30, 1.28, 6.18, 0.40, 0.02, 2.78, 4.74,
    5.05, 10.73, 2.52, 1.20, 6.53, 7.81, 4.34, 4.63, 1.67, 0.01, 0.21, 0.01, 0.47
};

float calculate_score(float observed[], float expected[]) {
    float score = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        score = score + pow((observed[i] - expected[i]), 2);
    }
    return score;
}

void guess_key(char* text) {
    int frequencies[ALPHABET_SIZE] = {0};
    int total_chars = 0;
    int length = strlen(text);

    for (int i = 0; i < length; i++) {
        if (isalpha(text[i])) {
            char base = islower(text[i]) ? 'a' : 'A';
            frequencies[text[i] - base]++;
            total_chars++;
        }
    }

    float observed_frequencies[ALPHABET_SIZE];
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        observed_frequencies[i] = (float)frequencies[i] / total_chars * 100;
    }

    printf("Tabela de Frequencias:\n");
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        printf("%c: %.2f%%\n", i + 'a', observed_frequencies[i]);
    }

    float min_score = INFINITY;
    int best_shift = 0;

    for (int shift = 0; shift < ALPHABET_SIZE; shift++) {
        float shifted_observed_frequencies[ALPHABET_SIZE];
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            int index = (i + shift) % ALPHABET_SIZE;
            shifted_observed_frequencies[i] = observed_frequencies[index];
        }
        float score = calculate_score(shifted_observed_frequencies, frequencies_expected);
        if (score < min_score) {
            min_score = score;
            best_shift = shift;
        }
    }

    printf("Chave mais provável: %d\n", best_shift);
    printf("Chave real: %d\n", best_shift);
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


int main() {
    char input_text[1000];
    int shift;
    int option;

    TTexto* texto = (TTexto*) malloc(sizeof(TTexto));

    char *text = NULL;
    char *pattern = NULL;

    TshifitAnd* tabela = NULL;

    printf("Escolha uma opcao:\n");
    printf("1. Criptografar\n");
    printf("2. Descriptografar\n");
    printf("3. Chave aleatoria e tabela de frequencias\n");
    printf("4. Ler o texto para testar o casamento\n");
    printf("5. Teste Algoritmo Boyer/Moore\n");
    printf("6. Teste Algoritmo ShiftAnd\n");
    scanf("%d", &option);

    while ((getchar()) != '\n'); // Clear input buffer

    switch (option) {
        case 1:
            printf("Digite o texto a ser criptografado: ");
            scanf(" %[^\n]s", input_text);
            text = strdup(input_text); // Duplicate the string
            printf("Digite o valor do shift: ");
            scanf("%d", &shift);
            char *encrypted_text = encrypt(text, shift);
            printf("Texto criptografado: %s\n", encrypted_text);
            save_to_file("texto_criptografado.txt", encrypted_text);
            free(encrypted_text);
            free(text); // Free the dynamically allocated text
            break;

        case 2:
            printf("Digite o texto a ser descriptografado: ");
            scanf(" %[^\n]s", input_text);
            text = strdup(input_text); // Duplicate the string
            printf("Digite o valor do shift: ");
            scanf("%d", &shift);
            char *decrypted_text = decrypt(text, shift);
            printf("Texto descriptografado: %s\n", decrypted_text);
            save_to_file("texto_descriptografado.txt", decrypted_text);
            free(decrypted_text);
            free(text); // Free the dynamically allocated text
            break;

        case 3:
            printf("Digite o texto para calcular as frequencias: ");
            scanf(" %[^\n]s", input_text);
            text = strdup(input_text); // Duplicate the string
            guess_key(text);
            free(text); // Free the dynamically allocated text
            break;

        case 4:
            char 
            printf("Digite o numero do texto a ser lido\n");

            strcat(texto->nomeArquivo, "./casamento/texto");

            lerTexto(texto, "./casamento/texto1.txt");
            printf("Texto: %s\n", texto->texto);
            printf("Padrao: %s\n", texto->padrao);
            freeMemoria(texto);
            break;

        case 5:
            printf("Entre com o texto: ");
            text = (char *)malloc(sizeof(char) * 1000); // Allocate memory for text
            if (text == NULL) {
                printf("Alocacao de memoria falhou :( .\n");
                return -1;
            }
            fgets(text, 1000, stdin);
            text[strcspn(text, "\n")] = '\0'; // Remove newline character

            printf("Entre com o padrao a ser procurado: ");
            pattern = (char *)malloc(sizeof(char) * 100); // Allocate memory for pattern
            if (pattern == NULL) {
                printf("Alocacao de memoria falhou para o padrao :( .\n");
                free(text); // Free memory allocated for text
                return -1;
            }
            fgets(pattern, 100, stdin);
            pattern[strcspn(pattern, "\n")] = '\0'; // Remove newline character

            clock_t start_time = clock();
            //timespec_get(&begin, TIME_UTC); 
            int result = boyerMoore(text, pattern);
            //timespec_get(&end, TIME_UTC);
            clock_t end_time = clock();
            double elapsed_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
            printf("Tempo de execucao: %lf segundos\n", elapsed_time);

            if (result != -1) {
                printf("Padrao encontrado no indice: %d\n", result);
            } else {
                printf("Padrao nao encontrado no texto.\n");
            }

            free(text); // Free memory allocated for text
            free(pattern);
            break;
        case 6:
            tabela = criarTabelaM("teste");
            clock_t start_time = clock();
            shiftAnd(tabela, "foram feitos em todos os testes posiveis mais nao encontramos");
            clock_t end_time = clock();

            double elapsed_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
            printf("Tempo de execucao: %lf segundos\n", elapsed_time);
        break;
        default:
            printf("Opcao invalida!\n");
            break;
    }
    return 0;
}
