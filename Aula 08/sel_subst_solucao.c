#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VALOR_MIN -2000000000

//Struct pra representar o dado
typedef struct dado{
  int info; //numero
	int cong; //se esta congelado
}TDado;

//inicializa tudo com menos inf e congelado
void inicializaMP(TDado *mp, int n){
  int i;
  for(i = 0; i < n; i++){
	mp[i].info = VALOR_MIN;
	mp[i].cong = 1;
  }
}

//Monta o nome da particao de saida
//inicio eh o nome e parte eh o numero da particao 
void geraNomePart(char *saida, char *inicio, int parte){
  char aux[5];
  strcpy(saida, inicio);
  sprintf(aux, "%d", parte);
  strcat(saida, aux);
  strcat(saida, ".txt");
}

//Retorna zero se existe algum elemento descongelado.
//Senão, retorna o número de elementos congelados.
int existeElemCongDifMenosInf(TDado *mp, int n){
  int achou = 0, i;
  for(i = 0; i < n; i++){
	if(!mp[i].cong) return 0;
	if(mp[i].info != VALOR_MIN) achou++;
  }
  return achou;
}

//Funcao que retorna o menor elemento descongelado (mp) e seu indice (menor_ind). 
//Senao, ela retorna o indice igual a MAX_MP (que eh o tamanho da particao).
void descobreMenor(TDado *mp, int MAX_MP, int *menor, int *menor_ind){
  int i, j = 0;
  (*menor) = VALOR_MIN;
  (*menor_ind) = MAX_MP;
  while(j < MAX_MP){
	if(!mp[j].cong){
	  (*menor) = mp[j].info;
	  (*menor_ind) = j;
	  break;
	}
	else j++;
  }  
  for(i = j + 1; i < MAX_MP; i++) 
	if((mp[i].info < (*menor)) && (!mp[i].cong) && (mp[i].info != VALOR_MIN)){
	  (*menor) = mp[i].info;
	  (*menor_ind) = i;
	}
}

//!!!Selecao com substituicao!!!
//in - nome do arquivo de entrada
//out nome dos arquivos de particao
//MAX_MP - tamanho da memoria a ser usada
//Retorna a quantidade de particoes criadas.
int selSubst(char *in, char *out, int MAX_MP){
  TDado mp[MAX_MP];
  inicializaMP(mp, MAX_MP);
  int part = 0;
  char nome_part[51];

  geraNomePart(nome_part, out, ++part);

  FILE *fp = fopen(in, "rt"), *fpart;
  if(!fp) exit(1);

  //preenche a MP.
  int i, r, aux;
  for(i = 0; i < MAX_MP; i++){
	//lê o elemento do arquivo
	r = fscanf(fp, "%d", &aux);
	if(r != 1)break; //deu erro na leitura
	mp[i].info = aux;
	mp[i].cong = 0;
  }

  //se o arquivo de entrada nao esta vazio.
  int menor, menor_ind;
  if(i){
	fpart = fopen(nome_part,"w");
	if(!fpart)exit(1);
	//se o arquivo de entrada é menor que a memoria
	//ja salva na particao ordenado
	if(i < MAX_MP){
	  fclose(fp);
	  while(1){
		descobreMenor(mp, MAX_MP, &menor, &menor_ind);
		if(menor_ind == MAX_MP){
		  fclose(fpart);
		  break;
		}
		fprintf(fpart,"%d\n", menor);
		mp[menor_ind].info = VALOR_MIN;
		mp[menor_ind].cong = 1;
	  }
	  return part;
	}
  }

  //Roda ate o final do arquivo
  while(r == 1){
	//se a memoria esta toda congelada
	if(existeElemCongDifMenosInf(mp, MAX_MP)){
	  //fecha a particao.
	  fclose(fpart);
	  //descongela a memoria.
	  for(i = 0; i < MAX_MP; i++) if(mp[i].info != VALOR_MIN) mp[i].cong = 0;
	  //gera a nova particao.
	  geraNomePart(nome_part, out, ++part);
	  fpart = fopen(nome_part,"wt");
	  if(!fpart) exit(1);
	}

	//SELECAO COM SUBSTITUICAO!!!
	//descobre o menor
	descobreMenor(mp, MAX_MP, &menor, &menor_ind);
	//escreve na particao
	fprintf(fpart, "%d\n", menor);
	//le o proximo elemento do arquivo de entrada
	r = fscanf(fp, "%d", &aux); 
	if(r == 1){ //sucesso na leitura
	//salva na memoria
	  mp[menor_ind].info = aux;
	  //se o elemento que entrou na particao era maior que o ultimo lido,
	  //congela a particao.
	  if(aux < menor) mp[menor_ind].cong = 1;
	}
	else{//nao tem mais elementos no arquivo
	//zera o espaco que ficou vazio
	  mp[menor_ind].info = VALOR_MIN;
	  mp[menor_ind].cong = 1;
	  //copia todos os elementos que devem estar na particao atual e nao foram 
	  //incluidos ainda.
	  do{
		descobreMenor(mp, MAX_MP, &menor, &menor_ind);
		if(menor_ind == MAX_MP){ //nao tem mais elementos na memoria
		  fclose(fpart);
		  break;
		}
		//copia o menor pra particao
		fprintf(fpart, "%d\n", menor);
		//zera a posicao de memoria que foi copiada 
		mp[menor_ind].info = VALOR_MIN;
		mp[menor_ind].cong = 1;
	  }while(1);
	}
  }
  fclose(fp);

  //se existem elementos congelados e preciso abrir uma nova particao e 
  //inseri-los nela.
  for(i = 0; i < MAX_MP; i++) if(mp[i].info != VALOR_MIN) break;
  if(i != MAX_MP){
	int j;
	for(j = i; j < MAX_MP; j++) if(mp[j].info != VALOR_MIN) mp[j].cong = 0;
	geraNomePart(nome_part, out, ++part);
	fpart = fopen(nome_part, "wt");
	if(!fpart) exit(1);
	while(1){
	  descobreMenor(mp, MAX_MP, &menor, &menor_ind);
	  if(menor_ind == MAX_MP){
		fclose(fpart);
		break;
	  }
	  fprintf(fpart, "%d\n", menor);
	  mp[menor_ind].info = VALOR_MIN;
	  mp[menor_ind].cong = 1;
	}
  }
  return part;
}

int main(void){ //Rosseti: 2016/09/20
  char nome[31];
  printf("Digite o nome do arquivo: ");
  scanf("%s", nome);
  /*
  FILE *fp = fopen(nome, "wt");
  if(!fp) exit(1);
  int nvet, i = 0, aux;
  printf("Digite o numero de elementos distintos do arquivo: ");
  scanf("%d", &nvet);
  while (i < nvet){
	scanf("%d", &aux);
	if(aux >= 0){ 
	  fprintf(fp,"%d\n",aux);
	  i++;
	}
  }
  fclose(fp);
  */
  char saida[31];
  printf("Digite o pedaco do nome do arquivo de particao: ");
  scanf("%s",saida);

  printf("Digite o tamanho (maior que zero) da memoria principal: ");
  int tam;
  while(1){
	scanf("%d",&tam);
	if(tam > 0)break;
  }

  int n = selSubst(nome, saida, tam);
  if(n == 1)printf("Selecao com substituicao gerou %d particao\n",n);
  else if(n > 1)printf("Selecao com substituicao gerou %d particoes\n",n);

  return 0;
}
