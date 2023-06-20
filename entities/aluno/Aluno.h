//
// Created by Gabriel on 15/06/2023.
//

#ifndef TP01_AEDS2_CPP_ALUNO_H
#define TP01_AEDS2_CPP_ALUNO_H


#include <string>

class Aluno {

    public:

        int id;
        char nome[50];
        char matricula[10];
        char data_nascimento[11];
        double coeficiente;
};

//Imprime aluno
void imprime(Aluno *aluno);

//Cria aluno
Aluno* aluno(int id, const char *nome,const  char *matricula, const char *data_nascimento, double coeficiente );

//Salva aluno no arquivo
void salva (Aluno *aluno, FILE *out);

// Le um aluno do arquivo in na posicao atual do cursor
// Retorna um ponteiro para aluno lido do arquivo
Aluno *le(FILE *in);

//// Retorna tamanho do aluno em bytes
int tamanho();

Aluno* busca_id(int id, FILE *arq, int tam);


#endif //TP01_AEDS2_CPP_ALUNO_H
