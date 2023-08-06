#ifndef TP01_AEDS2_CPP_PILHA_H
#define TP01_AEDS2_CPP_PILHA_H


#include "../../aluno/Aluno.h"

typedef struct TPilha {
    public:
        int limite;
        int topo;
        Aluno * info;
        int p;

}TPilha;

/*inicializa a pilha*/
void inicializa(TPilha *pilha, int lim, int topo);

/*verifica se a pilha esta cheia a vazia*/
int pilha_cheia(int lim, int topo);
int pilha_vazia(int base, int topo);

/*Insere e remove elemento do topo da pilha, Insere info no topo da pilha, retorna -1 caso não consiga inserir ou remover na pilha, caso contrário retorna o Aluno*/
void push(TPilha *pilha, int lim, int *topo, Aluno* info, int p);
Aluno *pop(TPilha *pilha, int base, int *topo);

/*consulta e retorna um elemento funcionario da pilha e o id "p" referente à partição, retorna -1 caso pilha esteja vazia*/
Aluno *peek_func(TPilha *pilha, int base, const int *topo);
int peek_fp(TPilha *pilha, int base, const int *topo);

/*imprime a pilha*/
void imprime_pilha(TPilha *pilha, const int *topo);

/*cria uma pilha de nFunc alunos lidos de um arquivo*/
void cria_pilha_particao(TPilha *pilha, FILE *arq, int nFunc, const int *vetTopo);

void cria_pilha(TPilha *pilha, FILE *arq, int tam);

Aluno * menor_da_pilha(TPilha pilha, Aluno *aluno_menor, int *array_congelados);

bool verifica_congelamento(TPilha pilha, int *array_congelados);

void substitui(TPilha *pilha, Aluno r, int *p, FILE *arq, int *array_congelados);

void ordena_por_substituicao(FILE *arq, int tam);

#endif //TP01_AEDS2_CPP_PILHA_H
