#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct Funcionario {
	int cod;
	char nome[50];
	double salario;
} TFunc;

// Imprime funcionario
void imprime(TFunc *func) {
	printf("**********************************************");
	printf("\nFuncionario de código ");
	printf("%d", func->cod);
	printf("\nNome: ");
	printf("%s", func->nome);
	printf("\nSalário: ");
	printf("%4.2f", func->salario);
	printf("\n**********************************************");
}

/*
 * Cria funcionario
 */
TFunc *funcionario(int cod, char *nome, double salario) {
	TFunc *func = (TFunc *) malloc(sizeof(TFunc));
	//inicializa espaço de memória com ZEROS
	if (func) memset(func, 0, sizeof(TFunc));
	//copia valores para os campos de func
	func->cod = cod;
	strcpy(func->nome, nome);
	func->salario = salario;
	return func;
}

/*
 * Salva funcionario no arquivo out, na posicao atual do cursor
 */
void salva(TFunc *func, FILE *out) {
	fwrite(&func->cod, sizeof(int), 1, out);
	//func->nome ao invés de &func->nome, pois string já é ponteiro
	fwrite(func->nome, sizeof(char), sizeof(func->nome), out);
	fwrite(&func->salario, sizeof(double), 1, out);
}

TFunc *le_funcionario(FILE *in) {
	TFunc *func = (TFunc *) malloc(sizeof(TFunc));
	if (0 >= fread(&func->cod, sizeof(int), 1, in)) {
		free(func);
		return NULL;
	}
	fread(func->nome, sizeof(char), sizeof(func->nome), in);
	fread(&func->salario, sizeof(double), 1, in);
	return func;
}

/*
 * Le um funcionario do arquivo in na posicao atual do cursor
 * Retorna um ponteiro para funcionario lido do arquivo
 */
TFunc *le(FILE *in) {
	TFunc *func = (TFunc *) malloc(sizeof(TFunc));
	if (0 >= fread(&func->cod, sizeof(int), 1, in)) {
		free(func);
		return NULL;
	}
	fread(func->nome, sizeof(char), sizeof(func->nome), in);
	fread(&func->salario, sizeof(double), 1, in);
	return func;
}

/*
 * Imprime arquivo
 */
void imprime_arquivo(FILE *arq) {
	//le o arquivo e coloca no vetor
	rewind(arq); //posiciona cursor no inicio do arquivo
	TFunc *f = le(arq);
	int i = 0;
	while (!feof(arq)) {
		imprime(f);
		f = le(arq);
	}
}

/*
 * Retorna tamanho do registro de funcionario em bytes
 */
int tamanho_registro() {
	return sizeof(int)  //cod
		   + sizeof(char) * 50 //nome
		   + sizeof(double); //salario
}

int tamanho_arquivo(FILE *arq) {
	fseek(arq, 0, SEEK_END);
	int tam = trunc(ftell(arq) / tamanho_registro());
	return tam;
}

/*
 * Insere funcionários no arquivo e
 */
void insere_funcionarios(FILE *out) {
	TFunc *f;
	f = funcionario(100, "Ana Bueno", 1500);
	salva(f, out);
	f = funcionario(102, "Arnaldo Souza", 4300);
	salva(f, out);
	f = funcionario(130, "Carlos Albuquerque", 1500);
	salva(f, out);
	f = funcionario(133, "Joao Silva", 1000);
	salva(f, out);
	f = funcionario(135, "Guilherme Santos", 2000);
	salva(f, out);
	f = funcionario(142, "Marisa Clara", 5000);
	salva(f, out);
	f = funcionario(502, "Tatiana Andrade", 2500);
	salva(f, out);
	f = funcionario(509, "Caio Gusmão", 4000);
	salva(f, out);
	f = funcionario(567, "Bianca Amarilo", 3000);
	salva(f, out);
	f = funcionario(876, "Bruno Simão", 4500);
	salva(f, out);
	f = funcionario(887, "Catarina Aguiar", 5000);
	salva(f, out);
	f = funcionario(899, "Carlos Silva", 1200);
	salva(f, out);
	f = funcionario(901, "Bruno Lucca", 1800);
	salva(f, out);
	f = funcionario(903, "Ana Maria dos Santos", 2300);
	salva(f, out);
	f = funcionario(923, "Armando Nogueira", 3000);
	salva(f, out);
	f = funcionario(976, "Carolina Dias", 2500);
	salva(f, out);
	f = funcionario(989, "Carina Matos", 4100);
	salva(f, out);
	free(f);
}

TFunc *busca_binaria(int chave, FILE *in, int inicio, int fim) {
	TFunc *f = NULL;
	int cod = -1;
	while (inicio <= fim && cod != chave) {
		int meio = trunc((inicio + fim) / 2);
		printf("Inicio: %d; Fim: %d; Meio: %d\n", inicio, fim, meio);
		fseek(in, (meio - 1) * tamanho_registro(), SEEK_SET);
		f = le_funcionario(in);
		printf("cod: %d\nnome: %s\n salario: %lf\n", f->cod, f->nome, f->salario);
		if (f) {
			cod = f->cod;
			if (cod > chave) {
				fim = meio - 1;
				free(f);
			} else if(cod < chave){
				inicio = meio + 1;
				free(f);
			}
		}
	}
	if (cod == chave) {
		return f;
	}
	else return NULL;
}

int main() {
	//declara ponteiro para arquivo
	FILE *arq;
	int chave;
	TFunc *f;
	//abre arquivo para leitura e escrita
	if ((arq = fopen("funcionario.dat", "wb+")) == NULL) {
		printf("Erro ao abrir arquivo\n");
	} else {
		//insere funcionários
		insere_funcionarios(arq);
		//força flush para salvar funcionários
		fflush(arq);
		imprime_arquivo(arq);
		printf("\n\nDigite a chave a ser buscada: ");
		scanf("%d", &chave);
		printf("****quantidade de registros****: %d", tamanho_arquivo(arq));
		//a busca está sendo feita em disco, não em um vetor, 
		//então tem que ir do primeiro ao ultimo registro.	
		f = busca_binaria(chave, arq, 1, tamanho_arquivo(arq));
		if (f)
			imprime(f);
		else printf("Funcionario não encontrado.\n");
		fclose(arq);
	}
}
