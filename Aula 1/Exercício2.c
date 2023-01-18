#include <stdio.h>
#include <stdlib.h>

typedef struct lista{
    int info;
    struct lista *prox;
}TLista;

typedef struct pilha{
    TLista *topo;
}TPilha;

TPilha *inicializa() {
    TPilha *pilha = (TPilha *)malloc(sizeof(TPilha));
    pilha->topo = NULL;
    return pilha;
}

int *pilha_vazia(TPilha *pilha){
    if (pilha->topo == NULL){
        return 1;}
    else {
        return 0;}
}

void push(TPilha *pilha, int elem){
    TLista *novo = (TLista*)malloc(sizeof(TLista));
    novo->info = elem;
    novo->prox = pilha->topo;
    pilha->topo = novo;
}

int pop(TPilha *pilha){
    if (pilha_vazia(pilha)){
        exit (1);
    }

    else{
        TLista *aux = pilha->topo;
        int info = aux->info;
        pilha->topo = aux->prox;
        free(aux);
        return info;
    }
}

int peek(TPilha *pilha){
    if (pilha_vazia(pilha)){
        return (-1);
    }
    else{
        return pilha->topo->info;
    }
}

void imprime_pilha(TPilha *pilha){
    TPilha *pi;
    TLista *aux;
    while (aux != NULL){
        printf("%d \n", aux->info);
        aux = aux->prox;
    }

}

int main (){
    TPilha *pil =  inicializa();
    push(pil,5);
    push(pil,4);
    push(pil,3);
    imprime_pilha(pil);
}

