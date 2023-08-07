#ifndef TP01_AEDS2_CPP_MENU_H
#define TP01_AEDS2_CPP_MENU_H

#include "../entities/structs/arvore/Node.h"
#include "../entities/aluno/Aluno.h"
#include "../entities/structs/selecao_substituicao/selecao_substituicao.h"


class Menu {

public:
    static void application();
};


//adiciona um aluno no final do arquivo
void adiciona_aluno(FILE *in);

//cria uma base de dados aleatoria para exemplificação do programa
void cria_base_dados(FILE *out);

#endif //TP01_AEDS2_CPP_MENU_H
