// Dados dois arquivos texto contendo números dispostos de forma ordenada, gerar um
// arquivo equivalente ao merge dos dois arquivos, contendo todos os números
// presentes nos dois arquivos de entrada, mas sem repetições

// void merge(char* nomeArq1, char* nomeArq2, char* nomeArqMerge)

#include <stdio.h>

void merge(char* nomeArq1, char* nomeArq2, char* nomeArqMerge){
    // inicia os arquivos
    FILE *arq, *arq2, *arqmerge;
    // abre arquivo 1
    arq = fopen(nomeArq1, "r");
    // abre arquivo 2
    arq2 = fopen(nomeArq2, "r");
    // cria arquivo a ser escrito
    arqmerge = fopen(nomeArqMerge, "w+");
    // caso a leitura de arquivo 1 seja bem-sucedida
    if (arq != NULL){
        // variavel que vai receber o conteudo das linhas como inteiro                    
        int n;
        // enquanto não chega no fim do arquivo 1
        while (!feof(arq)){
            // cria variavel para receber a linha
            char linha[256];
            // lê a linha toda
            fgets(linha, sizeof(linha), arq);
            // converte o conteudo para inteiro e armazena em n
            n = atoi(linha);
            // escreve no arquivo o conteudo de n linha a linha
            fprintf(arqmerge, "%d\n", n);
            fclose(arqmerge);
            }
        }
    else {
        printf ("Não foi possivel abrir o arquivo");
    }
    // caso a leitura de arquivo 2 seja bem-sucedida
    if (arq2 != NULL){
        // variavel que vai receber o conteudo das linhas como inteiro
        int n;
        // enquanto não chega no fim do arquivo 1
        while (!feof(arq2)){
            arqmerge = fopen("arqmerge.txt", "a");
            // cria variavel para receber a linha
            char linha2[256];
            // lê a linha toda
            fgets(linha2, sizeof(linha2), arq2);
            // converte o conteudo para inteiro e armazena em n
            n = atoi(linha2);
            // variavel para receber a linha de arqmerge
            int n2;
            fgets(linha2, sizeof(linha2), arqmerge);
            n2 = atoi(linha2);
            if (n != n2){
                fprintf(arqmerge, "\n%d\n", n);
            }
        }
        fclose(arqmerge);
        
    }    
}

int main (){
    merge("Arquivo 1.txt", "Arquivo 2.txt", "Arquivo Merge.txt");

}