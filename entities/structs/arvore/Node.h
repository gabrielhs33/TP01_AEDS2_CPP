//
// Created by Gabriel on 05/08/2023.
//

#ifndef TP01_AEDS2_CPP_NODE_H
#define TP01_AEDS2_CPP_NODE_H


#include "../../aluno/Aluno.h"

struct Node {

    Aluno aluno;
    Node* esquerda;
    Node* direita;

    Node(Aluno aluno) : aluno(aluno), esquerda(nullptr), direita(nullptr) {}
};


#endif //TP01_AEDS2_CPP_NODE_H
