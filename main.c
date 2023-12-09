#include "bmh.c"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define ALPHABET_SIZE 26

void searchBMH(char *txt, char *pat);

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
    char text[1000];
    int shift;
    int option;

    printf("Escolha uma opcao:\n");
    printf("1. Criptografar\n");
    printf("2. Descriptografar\n");
    printf("3. Chave aleatoria e tabela de frequencias\n");
    printf("4. Teste Algoritmo BMH\n");
    scanf("%d", &option);

    switch (option) {
        case 1:
            printf("Digite o texto a ser criptografado: ");
            scanf(" %[^\n]s", text);
            printf("Digite o valor do shift: ");
            scanf("%d", &shift);
            char* encrypted_text = encrypt(text, shift);
            printf("Texto criptografado: %s\n", encrypted_text);
            save_to_file("texto_criptografado.txt", encrypted_text);
            free(encrypted_text);
            break;

        case 2:
            printf("Digite o texto a ser descriptografado: ");
            scanf(" %[^\n]s", text);
            printf("Digite o valor do shift: ");
            scanf("%d", &shift);
            char* decrypted_text = decrypt(text, shift);
            printf("Texto descriptografado: %s\n", decrypted_text);
            save_to_file("texto_descriptografado.txt", decrypted_text);
            free(decrypted_text);
            break;

        case 3:
            printf("Digite o texto para calcular as frequencias: ");
            scanf(" %[^\n]s", text);
            guess_key(text);
            break;
        case 4:
        char *input_text = NULL; // Renomeei text para input_text para evitar sombreamento
        char *pattern = NULL;
        size_t text_size = 0;
        size_t pattern_size = 0;

        printf("Digite o texto: ");
        getline(&input_text, &text_size, stdin);
        input_text[strcspn(input_text, "\n")] = '\0';

        printf("Digite o padrão a ser procurado: ");
        getline(&pattern, &pattern_size, stdin);
        pattern[strcspn(pattern, "\n")] = '\0';

        searchBMH(input_text, pattern); 
        break;
        default:
            printf("Opcao invalida!\n");
            break;
    }
    return 0;
}
