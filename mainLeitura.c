#include "./headers/leitura.h"

int main(){
    TTexto* texto = (TTexto*) malloc(sizeof(TTexto));
    ler_texto(texto, "./casamento/texto1.txt");
    return 0;
}
