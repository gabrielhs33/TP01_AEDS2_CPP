#ifndef TP01_AEDS2_CPP_LISTA_ALUNOS_H
#define TP01_AEDS2_CPP_LISTA_ALUNOS_H
#include "../../aluno/Aluno.h"

typedef struct lista_alunos {

    Aluno **lista;
    int tam;
}Tlista_aluno;

// Desaloca lista de aluno
void libera_aluno(Tlista_aluno *lc);

void ler_aluno_lista(FILE *in, Tlista_aluno **list, int qtd, int *congelados);

#endif //TP01_AEDS2_CPP_LISTA_ALUNOS_H
