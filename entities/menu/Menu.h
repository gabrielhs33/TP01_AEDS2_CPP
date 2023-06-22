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

int contar_registros(FILE *out);

void ordena_id(FILE *arq, int tam);

void cria_base_dados(FILE *out);

#endif //TP01_AEDS2_CPP_MENU_H
