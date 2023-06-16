//
// Created by Gabriel on 15/06/2023.
//

#include <iostream>
#include <cstring>
#include "Aluno.h"

//Imprime aluno
void imprime(Aluno *aluno){

    std::cout<<"**********************************************"<<std::endl;
    std::cout<<"aluno de codigo ";
    std::cout<< aluno->id<<std::endl;
    std::cout<<"Nome: ";
    std::cout<<aluno->nome<<std::endl;
    std::cout<<"Matricula: ";
    std::cout<<aluno->matricula<<std::endl;
    std::cout<<"Data de Nascimento: ";
    std::cout<<aluno->data_nascimento<<std::endl;
    std::cout<<"Coeficiente:";
    std::cout<<aluno->coeficiente<<std::endl;
    std::cout<<"**********************************************"<<std::endl;
}

//Cria aluno
Aluno* aluno(int id, const char *nome, const char *matricula, const char *data_nascimento, double coeficiente){

    auto * aluno = new Aluno;
    aluno->id = id;
    std::strcpy(aluno->nome, nome);
    std::strcpy(aluno->matricula, matricula);
    std::strcpy(aluno->data_nascimento, data_nascimento);
    aluno->coeficiente = coeficiente;

    return aluno;
}

//Salva aluno no arquivo
void salva(Aluno *aluno, FILE *out){

    fwrite(&aluno->id, sizeof(int), 1, out);
    //func->nome ao invés de &func->nome, pois string já é ponteiro
    fwrite(aluno->nome, sizeof(char), sizeof(aluno->nome), out);
    fwrite(aluno->matricula, sizeof(char), sizeof(aluno->matricula), out);
    fwrite(aluno->data_nascimento, sizeof(char), sizeof(aluno->data_nascimento), out);
    fwrite(&aluno->coeficiente, sizeof(double), 1, out);
}

// Le um aluno do arquivo in na posicao atual do cursor
// Retorna um ponteiro para aluno lido do arquivo
Aluno *le(FILE *in) {

    auto *aluno = new Aluno;

    if (0 >= fread(&aluno->id, sizeof(int), 1, in)) {

        free(aluno);
        return nullptr;
    }

    std::fread(aluno->nome, sizeof(char), sizeof (aluno->nome), in);
    std::fread(aluno->matricula, sizeof(char), sizeof (aluno->matricula), in);
    std::fread(aluno->data_nascimento, sizeof(char), sizeof(aluno->data_nascimento), in);
    std::fread(&aluno->coeficiente, sizeof(double), 1, in);

    return aluno;
}

// Retorna tamanho do aluno em bytes
int tamanho() {
    return sizeof(int)  //cod
           + sizeof(char) * 50 //nome
           + sizeof(char) * 10 //matricula
           + sizeof(char) * 11 //data_nascimento
           + sizeof(double); //salario
}
