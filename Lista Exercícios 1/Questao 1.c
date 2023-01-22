//Escreva um programa que, infinitamente, leia um número inteiro n, que representa o tamanho,seguida de uma sequência de n números inteiros,
//e determine o comprimento máximo de umsegmento crescente destes n (números. Exemplos:Na sequência 5, 10, 3,2, 4, 7, 9, 8, 5 o comprimento do
//segmento crescente máximo é 4.Na sequência 10, 8, 7, 5, 2 o comprimento de um segmento crescente máximo é 1.Seu programa para quando n for menor ou igual a zero.


#include <stdio.h>
#include <stdlib.h>

void imprime_vetor(int *v, int n){
    for (int i = 0; i < n-1; i++){
        printf("%d, ", v[i]);
        }
    printf("%d \n", v[n-1]);
}

int analisa_sequencia (int *v, int n){
    int aux = 1000;
    int cont = 1;
    int contmaior;
    int *p;
    p = &cont;

    for (int i = 0; i < n; i++){
        if (v[i] > aux){
            cont++;
            if (cont >= contmaior){
                contmaior = cont;
            }
            aux = v[i];
        }
        else if (v[i] < aux){
            cont = 1;
            aux = v[i];
        }
    }
    return contmaior;
}

int main (){
    int n = 1;
    int qtd;
    while (n > 0) {
        // gera vetor para receber numeros
        int *v;
        v = (int *)malloc(sizeof(int));
        printf("Digite um numero inteiro: \n");
        // recebe o tamanho do vetor
        scanf("%d", &n);
        printf("Digite %d numeros a serem adicionados a sequencia:\n", n);
        // recebe os numeros
        for (int i = 0; i < n; i++){
               scanf("%d", &v[i]);
               }
        printf("\n");
        printf("Sequencia: \n");
        imprime_vetor(v, n);
        qtd = analisa_sequencia (v, n);
        printf("O comprimento do segmento crescente maximo eh %d \n", qtd);
        printf("\n");
    }
}