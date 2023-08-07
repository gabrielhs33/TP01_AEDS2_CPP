#ifndef ARVORE_VENCEDORES_H
#define ARVORE_VENCEDORES_H

#include "../../aluno/Aluno.h"

typedef struct arvore_vencedores{

    Aluno *aluno;
    int num_arq;
    struct arvore_vencedores *right;
    struct arvore_vencedores *left;
} ArvoreVencedores;

ArvoreVencedores *cria_no(Aluno *a, int num_arq);

ArvoreVencedores *cria_arvore(ArvoreVencedores *a, ArvoreVencedores *b);

void substituir(Aluno *a, Aluno *a_subst, ArvoreVencedores *av);

void intercalacao(int qtd, FILE *out);

#endif /* ARVORE_VENCEDORES_H */