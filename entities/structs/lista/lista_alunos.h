#ifndef TP01_AEDS2_CPP_LISTA_ALUNOS_H
#define TP01_AEDS2_CPP_LISTA_ALUNOS_H


#include "../../aluno/Aluno.h"

typedef struct lista_alunos {

    Aluno **lista;
    int tam;
}Tlista_aluno;

// Imprime aluno
void imprime_aluno(Tlista_aluno *lc);

// Cria lista de aluno. Lembrar de usar libera_aluno(lista_aluno)
Tlista_aluno *cria_aluno(int qtd, ...);

// Salva lista de aluno no arquivo nome_arquivo
void salva_aluno(char *nome_arquivo, Tlista_aluno *lc);

// Le lista de aluno do arquivo nome_arquivo
Tlista_aluno *le_aluno(char *nome_arquivo);

// Compara duas listas de aluno
// Retorna 1 se os aluno das duas listas forem iguais
// e 0 caso contrario
int cmp_aluno(Tlista_aluno *c1, Tlista_aluno *c2);

// Desaloca lista de aluno
void libera_aluno(Tlista_aluno *lc);
void ler_aluno(FILE *in, Tlista_aluno **list, int qtd, int *congelados);


#endif //TP01_AEDS2_CPP_LISTA_ALUNOS_H
