// Implemente um programa que, infinitamente, receba, como parâmetro de entrada, um número n e retorne a representação binária de n.
// Por exemplo, se n é igual a 12, a resposta deste programa deve ser “1100”. Seu programa para quando n for menor que zero.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void transf_binario(int n){

    char bin[65];
    itoa(n, bin, 2);
    printf("%d em binario eh %s\n", n, bin);
}

int main (){
    int n = 1;
    int nb;
    while (n != 0){
        printf("Digite um valor para ser convertido:\n");
        scanf("%d", &n);
        if (n <= 0){
            break;
        }
        transf_binario(n);
    }
}