#ifndef TP01_AEDS2_CPP_NODO_ARVORE_H
#define TP01_AEDS2_CPP_NODO_ARVORE_H
#include "../../aluno/Aluno.h"


struct Nodo_arvore {

    Aluno *aluno;
    Nodo_arvore* left;
    Nodo_arvore* right;

    Nodo_arvore(Aluno* aluno) : aluno(aluno), left(nullptr), right(nullptr) {}
};

#endif //TP01_AEDS2_CPP_NODO_ARVORE_H
