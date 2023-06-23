//
// Created by Mikael on 21/06/2023.
//

#include <iostream>
#include <cstring>
#include "Professor.h"

//Imprime Professor
void imprime_professor(Professor *professor){
    std::cout<<"**********************************************"<<std::endl;
    std::cout<<"Professor de codigo "<< professor->id<<std::endl;
    std::cout<<"Nome: "<<professor->nome<<std::endl;
    std::cout<<"Data de Nascimento: "<<professor->data_nascimento<<std::endl;
    std::cout<<"telefone: "<<professor->telefone<<std::endl;
    std::cout<<"CPF:"<<professor->CPF<<std::endl;
    std::cout<<"**********************************************"<<std::endl;
}

//Cria professor
Professor *professor(int id, const char *nome, const char *data_nascimento, int telefone, const char *CPF){
    auto * professor = new Professor;
    professor->id = id;
    std::strcpy(professor->nome, nome);
    std::strcpy(professor->data_nascimento, data_nascimento);
    professor->telefone = telefone;
    std::strcpy(professor->CPF, CPF);

    return professor;
}

//Salva informações de professor
void salva_professor (Professor *professor, FILE *out){
    fwrite(&professor->id, sizeof(int), 1, out);
    //func->nome ao invés de &func->nome, pois string já é ponteiro
    fwrite(professor->nome, sizeof(char), sizeof(professor->nome), out);
    fwrite(&professor->telefone, sizeof(int), 1, out);
    fwrite(professor->data_nascimento, sizeof(char), sizeof(professor->data_nascimento), out);
    fwrite(professor->CPF, sizeof(char), sizeof(professor->CPF), out);
}

// Le um professor do arquivo in na posicao atual do cursor
// Retorna um ponteiro para professor lido do arquivo
Professor *le_professor(FILE *in){
    auto *professor = new Professor;

    if (0 >= fread(&professor->id, sizeof(int), 1, in)) {

        free(professor);
        return nullptr;
    }

    std::fread(professor->nome, sizeof(char), sizeof (professor->nome), in);
    std::fread(professor->CPF, sizeof(char), sizeof (professor->CPF), in);
    std::fread(professor->data_nascimento, sizeof(char), sizeof(professor->data_nascimento), in);
    std::fread(&professor->telefone, sizeof(int), 1, in);

    return professor;
}

// Retorna tamanho do professor em bytes
int tamanho_prof(){
    return sizeof(int)  //cod
           + sizeof(char) * 50 //nome
           + sizeof(char) * 15 //CPF
           + sizeof(char) * 11 //data_nascimento
           + sizeof(int); // telefone
}

Professor* busca_id_professor(int id, FILE *arq, int tam){
    int left = 0, right = tam - 1;
    while(left <= right)
    {
        int middle = (left + right) / 2;
        fseek(arq, middle * tamanho_prof(), SEEK_SET);
        Professor* professor = le_professor(arq);

        if(professor == nullptr){

            return nullptr;
        }else{

            if(id == professor->id) {
                return professor;
            }
            else if(professor->id < id) {
                left = middle + 1;
            }
            else {
                right = middle - 1;
            }
        }
    }
    return nullptr;
}