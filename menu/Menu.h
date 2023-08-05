#ifndef TP01_AEDS2_CPP_MENU_H
#define TP01_AEDS2_CPP_MENU_H


#include "../entities/aluno/Aluno.h"

class Menu {

public:
    static void application();
};


//adiciona um aluno no final do arquivo
void adiciona_aluno(FILE *in);

//cria uma base de dados aleatoria para exemplificação do programa
void cria_base_dados(FILE *out);

#endif //TP01_AEDS2_CPP_MENU_H
