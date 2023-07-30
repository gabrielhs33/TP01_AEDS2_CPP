#include <iostream>
#include "Pilha.h"

void inicializa(TPilha *pilha, int lim, int topo){
    pilha->topo = topo;
    pilha->limite = lim;
}

int pilha_cheia(int lim, int topo) {

    if (topo == lim)
        return 1;
    else
        return 0;
}

int pilha_vazia(int base, int topo) {
    if (topo == 0)
        return 1; //pilha vazia
    else
        return 0; //pilha tem pelo menos 1 elemento
}

void push(TPilha *pilha, int lim, int *topo, Aluno *info, int p){
    if (pilha_cheia(lim, *topo)) {
        std::cout<< "\n\nPilha Cheia\n\n"<<std::endl;
    }
    else {
        //faz a inserção
        *topo = *topo + 1;
        pilha[*topo].info = info;
        pilha[*topo].p = p;
    }
}

Aluno *pop(TPilha *pilha, int base, int *topo) {

    if (pilha_vazia(base, *topo)) {
        return nullptr;
    }
    else {
        //faz a remoção
        Aluno *info = pilha[*topo].info;
        *topo = *topo - 1;
        return info;
    }
}

Aluno *peek_func(TPilha *pilha, int base, const int *topo) {
    if (pilha_vazia(base, *topo))
        return nullptr;
    else {
        //faz consulta
        return pilha[*topo].info;
    }
}

int peek_fp(TPilha *pilha, int base, const int *topo) {

    if (pilha_vazia(base, *topo))
        return 0;
    else {
        //faz consulta
        return pilha[*topo].p;
    }
}

void imprime_pilha(TPilha *pilha, const int *topo) {

    printf("\nEstado atual da Pilha:\n");
    for (int i = *topo; i >= 0; i--) {
        printf("posição [%d]: %d\n", i, pilha[i].info->id);
    }
    printf("\n");
}

void cria_pilha_particao(TPilha *pilha, FILE *arq, int nAluno, int *vetTopo){

    int lim=nAluno-1;

    rewind(arq);
    int i = nAluno-1;
    fseek(arq,  0 * sizeof (Aluno), SEEK_SET);
    if(arq != nullptr) {
        int aux = 1;
        do{
            fseek(arq, (i) * tamanho(), SEEK_SET);
            Aluno *aluno = le_aluno(arq);
            if(aluno){

                push(pilha,lim,vetTopo,aluno, i);
                i--;
            }else aux = 0;
        }while(aux);
    }
    else printf("Erro ao abrir arquivo\n");

    //imprime_pilha(pilha,vetTopo);
}
