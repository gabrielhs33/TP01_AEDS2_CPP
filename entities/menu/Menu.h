//
// Created by Gabriel on 15/06/2023.
//

#ifndef TP01_AEDS2_CPP_MENU_H
#define TP01_AEDS2_CPP_MENU_H


#include "../aluno/Aluno.h"

class Menu {

public:
    static void application();
};

void le_alunos(FILE *in);

void adiciona_aluno(FILE *in);

void insere_5_alunos(FILE *out);

int contar_registros(FILE *out);


#endif //TP01_AEDS2_CPP_MENU_H
