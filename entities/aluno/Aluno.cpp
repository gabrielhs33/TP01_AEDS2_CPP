//
// Created by Gabriel on 15/06/2023.
//

#include <iostream>
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
Aluno* aluno(int id, std::string nome, std::string matricula, std::string data_nascimento, double coeficiente){

    auto * aluno = new Aluno;
    aluno->id = id;
    aluno->nome = std::move(nome);
    aluno->matricula = std::move(matricula);
    aluno->data_nascimento = std::move(data_nascimento);
    aluno->coeficiente = coeficiente;

    return aluno;
}

//Salva aluno no arquivo
void salva(Aluno *aluno, FILE *out){

    fwrite(&aluno->id,sizeof(int),1,out );
    fwrite(&aluno->nome,sizeof (std::string),aluno->nome.size(),out);
    fwrite(&aluno->matricula,sizeof (std::string), aluno->matricula.size(),out);
    fwrite(&aluno->data_nascimento,sizeof (std::string), aluno->data_nascimento.size(),out);
    fwrite(&aluno->coeficiente,sizeof (double ), 1,out);
}

// Le um aluno do arquivo in na posicao atual do cursor
// Retorna um ponteiro para aluno lido do arquivo
Aluno *le(FILE *in) {

    auto *aluno = new Aluno;

    if (0 >= fread(&aluno->id, sizeof(int), 1, in)) {

        free(aluno);
        return nullptr;
    }

    fread(&aluno->nome, sizeof(char), aluno->nome.size(), in);
    fread(&aluno->matricula, sizeof(char), aluno->matricula.size(), in);
    fread(&aluno->data_nascimento, sizeof(char), aluno->data_nascimento.size(), in);
    fread(&aluno->coeficiente, sizeof(double), 1, in);

    imprime(aluno);

    return aluno;
}

// Retorna tamanho do funcionario em bytes
int tamanho() {
    return sizeof(int)  //cod
           + sizeof(std::string) //nome
           + sizeof(std::string) //matricula
           + sizeof(std::string) //data_nascimento
           + sizeof(double); //coeficiente
}
