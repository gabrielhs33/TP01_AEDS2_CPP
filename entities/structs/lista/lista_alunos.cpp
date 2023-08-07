#include "lista_alunos.h"
#include <cstdlib>
#include <cstdarg>


void ler_aluno_lista(FILE *in, Tlista_aluno **list, int tam, int *congelados){

    if(tam < 0 || in == nullptr){
        (*list)->tam = 0;
        (*list)->lista = nullptr;
        return;
    }

    int i = 0;

    if(*list == nullptr){
        *list = (Tlista_aluno *) malloc(sizeof(Tlista_aluno));
        Aluno *aluno = nullptr;
        (*list)->tam = tam;
        (*list)->lista = new class Aluno * [tam];

        for(i = 0; i < tam && (aluno = le_aluno(in)) != nullptr; i++){
            (*list)->lista[i] = aluno;
            congelados[i] = 0;
        }
    } else {
        Aluno *aluno = nullptr;
        int tamAntiga = (*list)->tam;
        (*list)->tam += tam;
        (*list)->lista = new class Aluno* [(*list)->tam];

        for(i = tamAntiga; i < (*list)->tam && (aluno = le_aluno(in)) != nullptr; i++){
            (*list)->lista[i] = aluno;
            congelados[i] = 0;
        }
    }
    for(; i < tam; i++) congelados[i] = 1;
}

void libera_aluno(Tlista_aluno *lc)
{
    int i;
    for (i = 0; i < lc->tam; i++) {
        free(lc->lista[i]);
    }
    free(lc->lista);
    free(lc);
}