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

void libera_aluno(Tlista_aluno *la)
{
    int i;
    for (i = 0; i < la->tam; i++) {
        free(la->lista[i]);
    }
    free(la->lista);
    free(la);
}


Tlista_aluno * le_alunos_lista(char *nome_arquivo)
{
    int qtd = 0;
    auto *la = (Tlista_aluno *)  malloc(sizeof(Tlista_aluno));
    FILE *in = fopen(nome_arquivo, "rb");
    if (in != nullptr) {
        Aluno* cliente = nullptr;
        while((cliente = le_aluno(in)) != nullptr) {
            qtd += 1;
            free(cliente);
        }
        fseek(in, 0, SEEK_SET);
        la->tam = qtd;
        la->lista = (Aluno **) malloc(sizeof(Aluno *) * (qtd));
        qtd = 0;
        while((cliente = le_aluno(in)) != nullptr) {
            la->lista[qtd++] = cliente;
        }
        fclose(in);
    } else {
        la->tam = 0;
        la->lista = nullptr;
    }
    return la;
}

Tlista_aluno *cria_alunos(int qtd, ...)
{
    va_list ap;
    auto *la = (Tlista_aluno *)  malloc(sizeof(Tlista_aluno));
    la->tam = qtd;
    la->lista = (Aluno **) malloc(sizeof(Aluno *) * (qtd));
    int i;
    va_start(ap, qtd);
    for (i = 0; i < qtd; i++) {
        la->lista[i] = va_arg(ap, Aluno *);
    }
    va_end(ap);
    return la;
}


void salva_alunos_lista(char *nome_arquivo, Tlista_aluno *la)
{
    FILE *out = fopen(nome_arquivo, "wb");
    int i;
    for (i = 0; i < la->tam; i++) {
        salva_aluno(la->lista[i], out);
    }
    fclose(out);
}