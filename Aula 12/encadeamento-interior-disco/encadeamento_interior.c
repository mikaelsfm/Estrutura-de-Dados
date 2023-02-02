#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <limits.h>

#include "encadeamento_interior.h"

int hash(int cod_cli, int tam) {
    return cod_cli % tam;
}

void cria_hash(char *nome_arquivo_hash, int tam)
{
	//TODO: criar a tabela hash
}

int busca(int cod_cli, char *nome_arquivo_hash, int m, int *encontrou)
{
	//TODO: Inserir aqui o codigo do algoritmo
    return INT_MAX;
}

int insere(int cod_cli, char *nome_cli, char *nome_arquivo_hash, int m)
{
	//TODO: Inserir aqui o codigo do algoritmo de insercao
    return INT_MAX;
}

int exclui(int cod_cli, char *nome_arquivo_hash, int m)
{
	//TODO: Inserir aqui o codigo do algoritmo de remocao
    return INT_MAX;
}
