#ifndef TP01_AEDS2_CPP_NODE_H
#include "../../aluno/Aluno.h"

struct Node {

    Aluno aluno;
    Node* esquerda;
    Node* direita;

};

void chama_arvore(FILE* in);


#endif //TP01_AEDS2_CPP_NODE_H
