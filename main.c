#include "./headers/bm.h"
#include "./headers/shifitAnd.h"
#include "./headers/leitura.h"
#include "./headers/codificar.h"
#include "./headers/random_key.h"

void menu() {
    printf("Escolha uma opcao:\n");
    printf("1. Criptografar\n");
    printf("2. Descriptografar\n");
    printf("3. Chave aleatoria e tabela de frequencias\n");
    printf("4. Ler o texto para testar o casamento\n");
    printf("5. Teste Algoritmo Boyer/Moore\n");
    printf("6. Teste Algoritmo ShiftAnd\n");
    printf("7. Sair\n");
}

int main() {
    char input_text[1000];
    int shift;
    int option;

    char filename[100];

    bool textoCriado = false;

    TTexto* texto = (TTexto*) malloc(sizeof(TTexto));
    TshifitAnd* tabela = NULL;

    do {
        menu();
        char caminhoCasamento[100] = "./casamento/texto";
        char caminhoCriptografia[100] = "./criptografia/texto";
        scanf("%d", &option);
    
        while ((getchar()) != '\n'); // Clear input buffer

        switch (option) {
            case 1:{
                printf("Digite o nome do arquivo com o texto a ser criptografado: ");

                scanf(" %[^\n]s", filename);
                strcat(caminhoCriptografia, filename);
                strcat(caminhoCriptografia, ".txt");

                char* plaintext = leitura_arquivo_TAREFAB(caminhoCriptografia);
                if (plaintext != NULL) {
                    printf("Digite o valor do shift: ");
                    scanf("%d", &shift);
                    char* encrypted_text = encrypt(plaintext, shift);
                    printf("Texto criptografado: %s\n", encrypted_text);
                    save_to_file("./criptografado/texto_criptografado.txt", encrypted_text);
                    free(plaintext);
                    free(encrypted_text);
                }
                break;
            }

            case 2: {
                printf("Digite o nome do arquivo com o texto a ser descriptografado: ");

                scanf(" %[^\n]s", filename);
                strcat(caminhoCriptografia, filename);
                strcat(caminhoCriptografia, ".txt");

                char* encrypted_text = leitura_arquivo_TAREFAB(caminhoCriptografia);
                if (encrypted_text != NULL) {
                    printf("Digite o valor do shift: ");
                    scanf("%d", &shift);
                    char* decrypted_text = decrypt(encrypted_text, shift);
                    printf("Texto descriptografado: %s\n", decrypted_text);
                    save_to_file("./descriptografado/texto_descriptografado.txt", decrypted_text);
                    free(encrypted_text);
                    free(decrypted_text);
                }
                break;
            }

            case 3: 
                printf("Digite o nome do arquivo com o texto para calcular as frequencias: ");

                scanf(" %[^\n]s", filename);
                strcat(caminhoCriptografia, filename);
                strcat(caminhoCriptografia, ".txt");

                char* frequency_text = leitura_arquivo_TAREFAB(caminhoCriptografia);
                
                if (frequency_text != NULL) {
                    guess_key(frequency_text);
                    free(frequency_text);
                }
                break;

            case 4:
                if (textoCriado){
                    freeMemoria(texto);
                }

                printf("Digite o numero do texto a ser lido\n");

                scanf(" %[^\n]s", filename);
                strcat(caminhoCasamento, filename);
                strcat(caminhoCasamento, ".txt");

                lerTextoCasamento(texto, caminhoCasamento);
                textoCriado = true;
                break;

            case 5: {
                
                clock_t start_time = clock();
                int result = boyerMoore(texto->texto, texto->padrao);
                clock_t end_time = clock();

                double elapsed_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
                printf("Tempo de execucao: %.50lf segundos\n", elapsed_time);

                if (result != -1) {
                    printf("Padrao encontrado no indice: %d\n", result);
                } else {
                    printf("Padrao nao encontrado no texto.\n");
                }

                break;
            }

            case 6: {

                clock_t start_time = clock();
                tabela = criarTabelaM(texto->padrao);

                shiftAnd(tabela, texto->texto);
                clock_t end_time = clock();

                double elapsed_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
                printf("Tempo de execucao: %.50lf segundos\n", elapsed_time);
                break;
            }

            case 7:
                printf("Saindo do programa.\n");
                if(textoCriado)
                    freeMemoria(texto); // Free the dynamically allocated text
                exit(0);
                break;

            default:
                printf("Opção invalida!\n");
                break;
        }

    }
     while (option != 7);

    return 0;
}