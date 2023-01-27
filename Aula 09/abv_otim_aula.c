#include <stdio.h>
#include <stdlib.h>

#define INT_MAX 2147483647

typedef struct no{
	int chave;
	char *nome;
	FILE *fp;
} TNo;


void intercala(TNo *heap, int n_heap, int n, char *saida){
	int i, j = 1;

	//abertura de arquivos e preenchimento de chaves
	for(i = n_heap - n; i < n_heap; i++){
		if(j <= n){
			heap[i].fp = fopen(heap[i].nome, "r");
			if(!heap[i].fp) exit(1);
			fscanf(heap[i].fp, "%d", &heap[i].chave);
			j++;
		}
	}

	int n_indice; //Rosseti - 2016/09/29
	if(n % 2) n_indice = n + 1;
	else n_indice = n;

	//preenchimento inicial das chaves dos nos intermediarios
	for(i = n_indice - 1; i > 0; i--){ //Rosseti - 2016/09/29
		int menor, esq = 2 * i, dir = 2 * i + 1;
		if(dir < n_heap){
			if(heap[esq].chave < heap[dir].chave) menor = heap[esq].chave;
			else menor = heap[dir].chave;
		}
		else menor = heap[esq].chave;
		heap[i].chave = menor;
	}

	//abertura do arquivo de saida
	FILE *fp_saida = fopen(saida, "w");
	if(!fp_saida) exit(1);

	while(heap[1].chave != INT_MAX){
		//escrita do menor atual
		fprintf(fp_saida, "%d\n", heap[1].chave);

		//encontro do caminho do menor atual: O(log n)
		i = 1;
		while((2 * i) < n_heap){
			int esq = 2 * i;
			int dir = 2 * i + 1;
			if(heap[i].chave == heap[esq].chave) i = esq;
			else if(dir != n_heap) i = dir;
		}

		//leitura da nova chave para substituicao do menor atual
		int r = fscanf(heap[i].fp, "%d", &heap[i].chave);
		if (r != 1){ //Rosseti - 2016/09/29
			heap[i].chave = INT_MAX;
			fclose(heap[i].fp); //Rosseti - 2016/10/09
			free(heap[i].nome); 
			heap[i].nome = NULL;
		}

		//atualizacao da arvore: O(log n)
		while(i > 1){
			int pai = i / 2;
			int esq = 2 * pai;
			int dir = 2 * pai + 1;
			if(dir < n_heap){
				if(heap[esq].chave < heap[dir].chave) heap[pai].chave = heap[esq].chave;
				else heap[pai].chave = heap[dir].chave;
			}
			else heap[pai].chave = heap[esq].chave;
			i = pai;
		}
	}

	//fechamento do arquivo de saida: Rosseti - 2016/09/29
	fclose(fp_saida);
}

int main(void){
	//while(1){
		printf("Digite n... ");
		int n;
		scanf("%d", &n);
		if(n <= 0) return 0;

		int n_heap, n_indice;
		if(n % 2) n_indice = n + 1;
		else n_indice = n;
		n_heap = n + n_indice;

		TNo heap[n_heap];
		int i;
		for(i = 0; i < n_heap; i++){
			heap[i].fp = NULL;
			heap[i].nome = NULL;
			heap[i].chave = INT_MAX; 
		}

		int j = 1;
		for(i = n_heap - n; i < n_heap; i++){
			if(j <= n){
				printf("Digite o nome do arquivo %d a ser intercalado... ", j++);
				heap[i].nome = (char *) malloc(sizeof(char) * 31);
				scanf("%s", heap[i].nome);
			}
		}

		char saida[31];
		printf("Digite o nome do arquivo de saida... ");
		scanf("%s", saida);
		intercala(heap, n_heap, n, saida);
	//}
}

