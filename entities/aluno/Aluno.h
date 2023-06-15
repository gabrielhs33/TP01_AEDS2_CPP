//
// Created by Gabriel on 15/06/2023.
//

#ifndef TP01_AEDS2_CPP_ALUNO_H
#define TP01_AEDS2_CPP_ALUNO_H


#include <string>

class Aluno {

    public:

        int id;
        std::string nome;
        std::string matricula;
        std::string data_nascimento;
        double coeficiente;
};

//Imprime aluno
void imprime(Aluno *aluno);

//Cria aluno
Aluno* aluno(int id, std::string nome, std::string matricula, std::string data_nascimento, std::string coeficiente );

//Salva aluno no arquivo
void salva (Aluno *aluno, FILE *out);

// Le um aluno do arquivo in na posicao atual do cursor
// Retorna um ponteiro para aluno lido do arquivo
Aluno *le(FILE *in);

//// Retorna tamanho do aluno em bytes
int tamanho();


#endif //TP01_AEDS2_CPP_ALUNO_H
