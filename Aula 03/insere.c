#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct sNoA {
    int chave;
    struct sNoA *esq;
    struct sNoA *dir;
} TNoA;

void imprime(TNoA *nodo, int tab) {
    for (int i = 0; i < tab; i++) {
        printf("-");
    }
    if (nodo != NULL) {
        printf("%d\n", nodo->chave);
        imprime(nodo->esq, tab + 2);
        printf("\n");
        imprime(nodo->dir, tab + 2);
    } else printf("vazio");
}

TNoA *insere(TNoA *no, int chave) {          //recebe raiz e chave
    if (no == NULL) {                        
        no = (TNoA *) malloc(sizeof(TNoA));  //separa espaço para inserir a chave
        no->chave = chave;
        no->esq = NULL;
        no->dir = NULL;
    }
    else if (chave < (no->chave)) {        // se for menor do que a raiz, manda pro filho esquerdo
        no->esq = insere(no->esq, chave);
    }
    else if (chave > (no->chave)) {         // se for maior do que a raiz, manda pro filho direito
        no->dir = insere(no->dir, chave);
    }
    else {
        printf("Inserção inválida! ");
        exit(1);
    }
    return no;
}

int main(void) {
    TNoA *raiz, *no; 
    raiz = NULL; 
    raiz = insere(raiz, 500); 
    insere(raiz, 600); 
    insere(raiz, 550); 
    insere(raiz, 400); 

    imprime(raiz, 0); 

}



