#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compara(const void *p1,const void *p2){
  int *i1 = (int *) p1, *i2 = (int *) p2;
  if((*i1) > (*i2))return 1;
  if((*i1) < (*i2))return -1;
  return 0;
}

int classInterna(char *nome, char *parte){
  int n;
  printf("Digite o tamanho (maior que zero) do vetor: ");
  while(1){
    scanf("%d", &n);
    if(n > 0)break;
  }
  int vet[n];
  int r, i, aux, particoes = 0;
  char aux2[41], num[5];
	printf("%s\n", nome);
  FILE *fp = fopen(nome, "r"), *fp2;
  if(!fp) printf("não abriu o arquivo");
  while(1){
	printf("entrou no loop");
    i = 0;
    while(i < n){
      r = fscanf(fp, "%d", &aux);
	printf("r: %d, aux: %d \n", r, aux);
      if(r != 1) break;
      vet[i++] = aux;
    }   
    if(!i) break;
    //Faz um quick sort no array
    qsort(vet, i, sizeof(int), compara);
    particoes++;
    strcpy(aux2, parte);
    sprintf(num, "%d", particoes);
    strcat(aux2, num);
    strcat(aux2, ".txt");
    fp2 = fopen(aux2, "w");
    if(!fp2) exit(1);
    int j;
    for(j = 0; j < i; j++)fprintf(fp2, "%d\n", vet[j]);
    fclose(fp2);
  }
  fclose(fp);
  return particoes;
}

int main(void){
  char nome[31];
  printf("Digite o nome do arquivo: ");
  scanf("%s",nome);
  
  //lê inteiros positivos até ler um negativo
  FILE *fp = fopen(nome,"w");
  if(!fp)exit(1);
  int aux;
  do{
    printf("Digite o elemento: ");
    scanf("%d",&aux);
    if(aux < 0){
      fclose(fp);
      break;
    }
    fprintf(fp,"%d\n",aux);
  }while(1);
 
  char saida[31];
  printf("Digite o pedaco do nome do arquivo de saida: ");
  scanf("%s",saida);
  int n = classInterna(nome, saida);
  if(n > 0){
    if(n == 1) printf("Foi gerada 1 particao\n");
    else printf("Foram geradas %d particoes\n", n);
  }
  return 0;
}
