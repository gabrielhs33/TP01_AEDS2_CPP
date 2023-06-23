//
// Created by Mikael on 21/06/2023.
//

#include <cstdio>

#ifndef TP01_AEDS2_CPP_GESTOR_H
#define TP01_AEDS2_CPP_GESTOR_H

class Gestor {
        public:
            int id;
            char nome[50];
            char data_nascimento[11];
            int telefone;
            char CPF[15];
};

//Imprimir os dados do gestor
void imprime_gestor(Gestor *professor);

//Cria gestor
Gestor *gestor(int id, const char *nome, const char *data_nascimento, int telefone, const char *CPF);

//Salva informações de gestor
void salva_gestor(Gestor *gestor, FILE *out);

// Le um gestor do arquivo in na posicao atual do cursor
// Retorna um ponteiro para gestor lido do arquivo
Gestor *le_gestor(FILE *in);

// Retorna tamanho do gestor em bytes
int tamanho_prof();

Gestor* busca_id_gestor(int id, FILE *arq, int tam);

#endif //TP01_AEDS2_CPP_GESTOR_H
