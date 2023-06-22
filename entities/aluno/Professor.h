//
// Created by Mikael on 21/06/2023.
//

#ifndef TP01_AEDS2_CPP_PROFESSOR_H
#define TP01_AEDS2_CPP_PROFESSOR_H

#include <string>
class Professor {
    public:
        int id;
        char nome[50];
        char data_nascimento[11];
        int telefone;
};

//Imprimir os dados do professor
void imprime_professor(Professor *professor);

//Cria professor
Professor cria_professor(int id, const char *nome, const char *data_nascimento, int telefone);

//Salva informações de professor
void salva_professor (Professor *professor, FILE *out);

// Le um professor do arquivo in na posicao atual do cursor
// Retorna um ponteiro para professor lido do arquivo
Professor *le_professor(FILE *in);

// Retorna tamanho do professor em bytes
int tamanho_prof();

Professor* busca_id_professor(int id, FILE *arq, int tam);

#endif //TP01_AEDS2_CPP_PROFESSOR_H
