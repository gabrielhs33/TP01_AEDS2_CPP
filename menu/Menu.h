#ifndef TP01_AEDS2_CPP_MENU_H
#define TP01_AEDS2_CPP_MENU_H


#include "../entities/aluno/Aluno.h"

class Menu {

public:
    static void application();
};

// le todos os alunos do arquivo
void le_alunos(FILE *in);
//adiciona um aluno no final do arquivo
void adiciona_aluno(FILE *in);
//conta quantos registros foram inseridos no arquivo
int contar_registros(FILE *out);
//cria uma base de dados aleatoria para exemplificação do programa
void cria_base_dados(FILE *out);


#endif //TP01_AEDS2_CPP_MENU_H
