#ifndef ENCADEAMENTO_EXTERIOR_H
#define ENCADEAMENTO_EXTERIOR_H

/*
 * Função hash implementa método da divisão
 */
int hash(int cod_cli, int tam);

/*
 * Função cria_hash
 * Cria uma tabela hash vazia de tamanho tam, e salva no arquivo nome_arquivo_hash
 * Compartimento que nao tem lista encadeada associada deve ter valor igual a -1
 * Quando o ponteiro para proximo for null, ele deve ser igual a -1
 * nome_arquivo_hash: nome do arquivo hash a ser criado
 * m: tamanho da tabela hash a ser criada
 */
void cria_hash(char *nome_arquivo_hash, int m);


/*
 * Função Busca
 * Executa busca em Arquivos por Encadeamento Interior (Hash)
 * Assumir que ponteiro para NULL é -1
 * cod_cli: chave do cliente que esta sendo buscado
 * nome_arquivo_hash: nome do arquivo que contem a tabela hash
 * m: tamanho da tabela hash (função de hash é h(x) = x mod m
 * encontrou: 1 se registro foi encontrado ou 0, caso contrario
 * Retorna o endereco onde o cliente foi encontrado, ou o primeiro endereco livre, ou -1 se nao ha endereco livre
 */
int busca(int cod_cli, char *nome_arquivo_hash, int m, int *encontrou);

/*
 * Função insere
 * Executa insercao em Arquivos por Encadeamento Interior (Hash)
 * cod_cli: chave do cliente que esta sendo inserido
 * nome_cli: nome do cliente a ser inserido
 * nome_arquivo_hash: nome do arquivo que contem a tabela hash
 * m: tamanho da tabela hash
 * Retorna o endereco onde o cliente foi inserido, ou -1 se nao conseguiu inserir (inclusive em caso de overflow)
 */
int insere(int cod_cli, char *nome_cli, char *nome_arquivo_hash, int m);

/*
 * Função exclui
 * Executa exclusao em Arquivos por Encadeamento Interior (Hash)
 * cod_cli: chave do cliente a ser excluido
 * nome_arquivo_hash: nome do arquivo que contem a tabela hash
 * m: tamanho da tabela hash
 * Retorna o endereco do cliente que foi excluido, ou -1 se cliente nao existe
 */
int exclui(int cod_cli, char *nome_arquivo_hash, int m);

#endif