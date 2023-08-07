#include "lista_alunos.h"
#include <cstdlib>
#include <cstdarg>

//void imprime_alunos(Tlista_aluno *lc)
//{
//    for (int i = 0; i < lc->tam; i++) {
//        imprime_alunos(lc->lista[i]);
//    }
//}

Tlista_aluno *cria_lista_lunos(int tam, ...)
{
    va_list ap;
    auto *lc = (Tlista_aluno *)  malloc(sizeof(Tlista_aluno));
    lc->tam = tam;
    lc->lista = (Aluno **) malloc(sizeof(Aluno *) * (tam));
    int i;
    va_start(ap, tam);
    for (i = 0; i < tam; i++) {
        lc->lista[i] = va_arg(ap, Aluno *);
    }
    va_end(ap);
    return lc;
}

void salvar_aluno_lista(char* nome_arquivo, Tlista_aluno *lc)
{
    FILE *out = fopen(nome_arquivo, "wb");
    int i;
    for (i = 0; i < lc->tam; i++) {
        if(lc->lista[i] != nullptr) salva_aluno(lc->lista[i], out);
    }
    fclose(out);
}

//bool compara_alunos(Tlista_aluno *c1, Tlista_aluno *c2)
//{
//    if (c1->tam != c2->tam) {
//        return false;
//    }
//    int i;
//    for (i = 0; i < c1->tam; i++) {
//
//        if (!compara_alunos(c1->lista[i], c2->lista[i])){
//            return false;
//        }
//    }
//    return true;
//}

Tlista_aluno * le_Alunos(char *nome_arquivo)
{
    int tam = 0;
    auto *lc = (Tlista_aluno *)  malloc(sizeof(Tlista_aluno));
    FILE *in = fopen(nome_arquivo, "rb");
    if (in != nullptr) {
        Aluno *Aluno = nullptr;
        while((Aluno = le_aluno(in)) != nullptr) {
            tam += 1;
            free(Aluno);
        }
        fseek(in, 0, SEEK_SET);
        lc->tam = tam;
        lc->lista = new class Aluno * [tam];
        tam = 0;
        while((Aluno = le_aluno(in)) != nullptr) {
            lc->lista[tam++] = Aluno;
        }
        fclose(in);
    } else {
        lc->tam = 0;
        lc->lista = nullptr;
    }
    return lc;
}

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