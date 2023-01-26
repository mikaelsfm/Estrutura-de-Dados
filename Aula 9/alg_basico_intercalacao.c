#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct part{
	int menor;
	char *nome;
	FILE *fp;
}TPart;


void inicializa(TPart *vet, int P){
	int i;
	for(i = 0; i < P;i++){
		vet[i].menor = INT_MAX;
		vet[i].nome = NULL;
		vet[i].fp = NULL;
	}
}


void algBasInt (char *saida, TPart *vet, int P){
	FILE *fp = fopen(saida, "wt");
	if(!fp) exit(1); 

	int i;
	for(i = 0; i < P; i++){
		vet[i].fp = fopen(vet[i].nome, "rt");
		if(!vet[i].fp){
			int j;
			for(j = 0; j < i; j++){
				free(vet[j].nome);
				fclose(vet[j].fp);
			}
			free(vet[i].nome);
			exit(1);
		}
		int r = fscanf(vet[i].fp, "%d", &vet[i].menor);
		if(r != 1) vet[i].menor = INT_MAX;
	}
	while(1){
		int menor = INT_MAX, ind_menor;
		for(i = 0; i < P; i++){
			if(vet[i].menor < menor){
				menor = vet[i].menor;
				ind_menor = i;
			}
		}
		if(menor == INT_MAX) break;
		fprintf(fp, "%d\n", menor);
		int r = fscanf(vet[ind_menor].fp, "%d", &vet[ind_menor].menor);
		if(r != 1){ 
			fclose(vet[ind_menor].fp);
			free(vet[ind_menor].nome);
			vet[ind_menor].menor = INT_MAX;
		}
	}
	fclose(fp);
}


int main(int argc, char **argv){
	//if(argc != 2) exit(1); 

	//printf("%s\n", argv[1]);

	int P;
	printf("Entrar o número de partições\n");
	scanf("%d", &P);
	if(P <= 0) return 0;
	TPart vet[P];
	inicializa(vet, P);

	printf("Entrar o nome das partições\n");
	int i;
	for(i = 0; i < P; i++){
		vet[i].nome = (char *) malloc(sizeof(char)*31);
		scanf("%s", vet[i].nome);
	}

	algBasInt ("argv[1]", vet, P);
	return 0;
}
