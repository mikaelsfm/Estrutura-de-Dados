 /* Escreva um algoritmo que receba uma expressão matemática em notação pós-fixa
 (composta por operandos compostos por um único algarismo, operações de +, -,
 * e /) representada por um string e retorne uma árvore binária representando
 esta expressão. A expressão pós-fixa é quando os operandos vem primeiro e
 depois o operador. Ex: (1+2)*3 fica 12+3*. */

#include <stdio.h>
#include <stdlib.h>

typedef struct lista{
    int info;
    struct lista *prox;
}TLista;

typedef struct pilha{
    TLista *topo;
}TPilha;

typedef struct TNoAB {
    int operando;
    char operador;
    struct TNoAB *dir;
    struct TNoAB *esq;
}No;

TPilha *inicializa_pilha();
    TPilha *pilha = (TPilha*)malloc(sizeof(TPilha));
    pilha->topo = NULL;
    return pilha;

int *pilha_vazia(TPilha *pilha){
    if (pilha->topo == NULL){
        return 1;}
    else {
        return 0;}

int pop(TPilha *pilha){
    if (pilha_vazia(pilha)){
        exit (1);
    }
    else{
        TLista *aux = pilha->topo;
        int info = aux->info;
        pilha->topo = aux->prox;
        
    }
}

int main (){
    TPilha *pil = inicializa_pilha();

}