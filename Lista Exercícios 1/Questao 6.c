#include <stdio.h>
#include <stdlib.h>

typedef struct arvd{
    int num;
    char op;//n = num ou + - * /
    struct arvd *esq, *dir;
} TAD;

TAD *cria_num(int num){
    TAD *novo = (TAD*) malloc(sizeof(TAD));
    novo->op = 'n';
    novo->num = num;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

TAD *cria_op(char op){
    TAD *novo = (TAD*) malloc(sizeof(TAD));
    novo->op = op;
    novo->num = 0; //1 se usa parenteses
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

void bota_parenteses(TAD *arv){
    if(arv && (arv->op == '+' || arv->op == '-'))
        arv->num = 1;
}

void verifica_parenteses(TAD *arv){
    if (!arv) return;
    verifica_parenteses(arv->esq);
    if (arv->op == '*' || arv->op == '/'){
        bota_parenteses(arv->esq);
        bota_parenteses(arv->dir);
    }
    verifica_parenteses(arv->dir);
}

void escreve_num_ou_op(TAD *arv){
    if(arv->op == 'n')
        printf("%d", arv->num);
    else printf("%c", arv->op);
}

void imprime(TAD *arv){
    if(!arv) return;
    if(arv->op != 'n' && arv->num) printf("(");
    imprime(arv->esq);
    escreve_num_ou_op(arv);
    imprime(arv->dir);
    if(arv->op != 'n' && arv->num) printf(")");
}

int main() {
    TAD *lista;
    /*
    lista = cria_op('+');
    lista->esq = cria_num(3);
    lista->dir = cria_op('*');
    lista->dir->esq = cria_num(5);
    lista->dir->dir = cria_num(8);
     */

    lista = cria_op('*');
    lista->esq = cria_op('+');
    lista->esq->esq = cria_num(3);
    lista->esq->dir = cria_num(5);
    lista->dir = cria_num(8);

    verifica_parenteses(lista);
    imprime(lista);

    return 0;
}
