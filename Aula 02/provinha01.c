#include <stdio.h>
#include <stdlib.h>

typedef struct noA {
    char info;
    struct noA *esq;
    struct noA *dir;
} TNoA;

TNoA *inicializa(void) {
    return NULL;
}

void imprime(TNoA *nodo, int tab) {
    for (int i = 0; i < tab; i++) {
        printf("-");
    }
    if (nodo != NULL) {
        printf("%c\n", nodo->info);
        imprime(nodo->esq, tab + 4);
        printf("\n");
        imprime(nodo->dir, tab + 4);
    } else printf("vazio");
}

TNoA *criaNo(char ch) {
    TNoA *novo;
    novo = (TNoA *) malloc(sizeof(TNoA));
    novo->info = ch;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

void pos_ordem (TNoA *a){
    if(a != NULL){
        pos_ordem(a->esq);
        pos_ordem(a->dir);
        printf("%c \n", a->info);
    }
}

void simetrica (TNoA *a){
    if (a != NULL){
        simetrica(a->esq);
        printf("%c \n", a->info);
        simetrica(a->dir);
    }
}

void profundidade(TNoA *a){
    if (a != NULL){
        printf("%c \n", a->info);
        profundidade(a->esq);
        profundidade(a->dir);
    }
}
int main(void) {
    TNoA *raiz;
    raiz = criaNo('A');
    raiz->esq = criaNo('B');
    raiz->dir = criaNo('C');
    raiz->dir->esq = criaNo('D');
    raiz->dir->dir = criaNo('E');
    pos_ordem(raiz);
    printf("\n");
    simetrica(raiz);

};
