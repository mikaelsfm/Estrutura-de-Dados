// Dados dois arquivos texto contendo números dispostos de forma ordenada, gerar um
// arquivo equivalente ao merge dos dois arquivos, contendo todos os números
// presentes nos dois arquivos de entrada, mas sem repetições

// void merge(char* nomeArq1, char* nomeArq2, char* nomeArqMerge)

#include <stdio.h>

void merge(char* nomeArq1, char* nomeArq2, char* nomeArqMerge){
    FILE *arq1, *arq2, *arq_merge;
    //abre os 2 arquivos numeros em modo leitura
    arq1 = fopen(nomeArq1, "r");
    arq2 = fopen(nomeArq2, "r");
    //abrir o arquivo de merge em modo escrita
    arq_merge = fopen(nomeArqMerge, "w");

    // numeros de cada arquivo
    int n1, n2;
    
    //caso consiga ler todos os arquivos
    if (arq1 != NULL && arq2 != NULL && arq_merge){
        n1 = fscanf(arq1,"%d", &n1);
        n2 = fscanf(arq2,"%d", &n2);

        while (!feof(arq1) && !feof(arq2)){
            if (n1 < n2){
                fprintf(arq_merge,"%d\n", n1);
                fscanf(arq1, "%d", &n1);
            }
            else{
                if (n1 > n2){
                    fprintf(arq_merge,"%d\n", n2);
                    fscanf(arq2, "%d", &n2);
                }
                else{
                    fprintf(arq_merge,"%d\n", n1);
                    fscanf(arq1, "%d", &n1);
                    fscanf(arq2, "%d", &n2);
                }
            }
        }
        while (!feof(arq1)) {
			fprintf(arq_merge, "%d\n", n1);
			fscanf(arq1, "%d", &n1);
		}
		//grava arq 2 até terminar
		while (!feof(arq2)) {
			fprintf(arq_merge, "%d\n", n2);
			fscanf(arq2, "%d", &n2);
        }
    }
    else{
        printf("Não foi possível ler arquivo");
    }
    fclose(arq1);
    fclose(arq2);
    fclose(arq_merge);
}

int main (){
    merge("Arquivo 1.txt", "Arquivo 2.txt", "Arquivo Merge.txt");

}