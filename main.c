#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_line 1024

struct Aluno{
    char nome[30];
    char telefone[15];
    char curso[15];
    float nota1;
    float nota2;
}; //Struct Usada para guardar dados dos alunos;

//escopo das funções;

int contagemRegistros(FILE *arquivo);
void lerArquivo(FILE *arquivo, struct Aluno a[], int cont);
void criarArquivo(FILE *arquivo, struct Aluno a[],int cont);


int main(){
    FILE *arquivo;
    int cont = 0;

    arquivo = fopen("DadosEntrada.csv","r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1); 
    }

    // Ignora a primeira linha;
    char linha[MAX_line];
    fgets(linha, MAX_line, arquivo);

    cont = contagemRegistros(arquivo);// função para definir tamanho da struct;

    struct Aluno a[cont];

    lerArquivo(arquivo, a, cont);// leitura de arquivos;

    fclose(arquivo);

    arquivo = fopen("SituacaoFinal.csv","w"); // criação de arquivo final;

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1); 
    }

    criarArquivo(arquivo, a , cont); // função que calcula e imprime a media e situação final;

    fclose(arquivo);

    return 0;
}

//funções

int contagemRegistros(FILE *arquivo){
    int qtdRegistros = 0;
    char linha[MAX_line];
    while (fgets(linha, MAX_line, arquivo) != NULL) {
        qtdRegistros++;
    }
    rewind(arquivo);
    return qtdRegistros;
}



void lerArquivo(FILE *arquivo, struct Aluno a[], int cont){
    char linha[MAX_line];

    // Ignorar a primeira linha
    fgets(linha, MAX_line, arquivo);

    for (int i = 0; i < cont; i++) {
        fscanf(arquivo, "%[^,],%[^,],%[^,],%f,%f", a[i].nome, a[i].telefone, a[i].curso, &a[i].nota1, &a[i].nota2);
    }
}


 
void criarArquivo(FILE *arquivo, struct Aluno a[],int cont){

    for(int i = 0; i < cont; i++){
        fprintf(arquivo, "%s, %.2f,\t ", a[i].nome, ((a[i].nota1 + a[i].nota2) / 2));
        if((a[i].nota1 + a[i].nota2) / 2  >= 7){
            fprintf(arquivo, "APROVADO\n");
        }else{
            fprintf(arquivo,"REPROVADO\n");
        }
    }
}
