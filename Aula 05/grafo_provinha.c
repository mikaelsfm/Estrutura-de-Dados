#include <stdlib.h>
#include <stdio.h>

/*
 * Esse código assume que o grafo é íntegro (não existem arestas para nós que não existem
 */

typedef struct vizinho {
    int id_vizinho;
    struct vizinho *prox;
}TVizinho;

typedef struct grafo{
    int id_vertice;
    TVizinho *prim_vizinho;
    struct grafo *prox;
}TGrafo;

TGrafo *inicializa(){
    return NULL;
}

void imprime(TGrafo *g){
    while(g != NULL){
        printf("Vertice %d\n", g->id_vertice);
        printf("Vizinhos: ");
        TVizinho *v = g->prim_vizinho;
        while(v != NULL){
            printf("%d ", v->id_vizinho);
            v = v->prox;
        }
        printf("\n\n");
        g = g->prox;
    }
}

void libera_vizinho(TVizinho *v){
    if(v != NULL) {
        libera_vizinho(v->prox);
        free(v);
    }
}

void libera(TGrafo *g){
    if(g != NULL){
        libera_vizinho(g->prim_vizinho);
        libera(g ->prox);
        free(g);
    }
}

TGrafo* busca_vertice(TGrafo* g, int x){
    while((g != NULL) && (g->id_vertice != x)) {
        g = g->prox;
    }
    return g;
}

TVizinho* busca_aresta(TGrafo *g, int v1, int v2){
    TGrafo *pv1 = busca_vertice(g,v1);
    TGrafo *pv2 = busca_vertice(g,v2);
    TVizinho *resp = NULL;
    //checa se ambos os vértices existem
    if((pv1 != NULL) && (pv2 != NULL)) {
        //percorre a lista de vizinhos de v1 procurando por v2
        resp = pv1->prim_vizinho;
        while ((resp != NULL) && (resp->id_vizinho != v2)) {
            resp = resp->prox;
        }
    }
    return resp;
}

TGrafo *insere_vertice(TGrafo *g, int x){
    TGrafo *p = busca_vertice(g, x);
    if(p == NULL){
        p = (TGrafo*) malloc(sizeof(TGrafo));
        p->id_vertice = x;
        p->prox = g;
        p->prim_vizinho = NULL;
        g = p;
    }
    return g;
}

void insere_um_sentido(TGrafo *g, int v1, int v2){
    TGrafo *p = busca_vertice(g, v1);
    TVizinho *nova = (TVizinho *) malloc(sizeof(TVizinho));
    nova->id_vizinho = v2;
    nova->prox = p->prim_vizinho;
    p->prim_vizinho = nova;
}

void insere_aresta(TGrafo *g, int v1, int v2){
    TVizinho *v = busca_aresta(g, v1, v2);
    if(v == NULL) {
        insere_um_sentido(g, v1, v2);
        insere_um_sentido(g, v2, v1);
    }
}

void retira_um_sentido(TGrafo *g, int v1, int v2){
    TGrafo *p = busca_vertice(g, v1);
    if(p != NULL) {
        TVizinho *ant = NULL;
        TVizinho *atual = p->prim_vizinho;
        while ((atual) && (atual->id_vizinho != v2)) {
            ant = atual;
            atual = atual->prox;
        }
        if (ant == NULL) //v2 era o primeiro nó da lista de vizinhos
            p->prim_vizinho = atual->prox;
        else
            ant->prox = atual->prox;
        free(atual);
    }
}

void retira_aresta(TGrafo *g ,int v1, int v2){
    TVizinho* v = busca_aresta(g,v1,v2);
    if(v != NULL) {
        retira_um_sentido(g, v1, v2);
        retira_um_sentido(g, v2, v1);
    }
}

/*Recebe um ponteiro para o primeiro vértice da lista e o valor do vértice a ser removido*/
TGrafo *retira_vertice(TGrafo *g, int v){
   TGrafo *pv = NULL; //ponteiro pro vertice
   TGrafo *va = NULL; //vertice anterior
   TVizinho *aux = NULL; //proximo vizinho
   int v2;

	pv = g;
	//buscar o vértice
	while((pv != NULL) && (pv->id_vertice != v)) {
    		/*FAZER CODIGO AQUI*/
            va = pv;
            pv = pv->prox;
	}

	//percorrer a lista de vizinhos retirando as arestas
	//apontar o ponteiro pro próximo antes de mandar remover a aresta
	aux = pv->prim_vizinho;
	while(aux != NULL){
		/*FAZER CODIGO AQUI*/
        retira_um_sentido(g, aux->id_vizinho, pv->id_vertice);
        aux = aux->prox;
	}	

	//Depois que removeu todos os vizinhos
	//Remover o vértice
	if(va == NULL){//Eh o primeiro da lista
		/*FAZER CODIGO AQUI*/
        libera_vizinho(g->prim_vizinho);
	}
	else{//Nao eh o primeiro da lista
		/*FAZER CODIGO AQUI*/
        va->prox = pv->prox;
        libera_vizinho(g->prim_vizinho);
	}
	free(pv);

	//Retornar o ponteiro pro começo da lista de vertices
	return g;
}

/*A main cria um grafo não direcionado*/
int main(){
    TGrafo *g = inicializa();
    g = insere_vertice(g, 1);
    g = insere_vertice(g, 2);
    g = insere_vertice(g, 3);
    g = insere_vertice(g, 4);
	g = insere_vertice(g, 5);
	/*insere a aresta não direcionada*/
    insere_aresta(g, 1, 2);
    insere_aresta(g, 1, 3);
    insere_aresta(g, 2, 3);
	insere_aresta(g, 4, 2);
	insere_aresta(g, 5, 2);
    imprime(g);
    //retira_aresta(g, 3, 2);
    //printf("Grafo após exclusão da aresta (3,2): \n\n");
    //imprime(g);
    retira_vertice(g,2);
    printf("Grafo apos exclusao do vertice 2: \n\n");
    imprime(g);
    libera(g);

}
