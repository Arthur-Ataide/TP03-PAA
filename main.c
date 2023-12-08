#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

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

    printf("Tabela de Frequencias:\n");
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (frequencies[i] > 0) {
            printf("%c: %.2f%%\n", i + 'a', (float)frequencies[i] / total_chars * 100);
        }
    }
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
            frequency_table(text);
            break;

        default:
            printf("Opcao invalida!\n");
            break;
    }

    return 0;
}
