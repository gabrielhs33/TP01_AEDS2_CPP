//
// Created by Mikael on 21/06/2023.
//

#include <cstring>
#include <iostream>
#include "Gestor.h"


void imprime_gestor(Gestor *gestor){
    std::cout<<"**********************************************"<<std::endl;
    std::cout<<"Gestor de codigo "<< gestor->id<<std::endl;
    std::cout<<"Nome: "<<gestor->nome<<std::endl;
    std::cout<<"Data de Nascimento: "<<gestor->data_nascimento<<std::endl;
    std::cout<<"telefone: "<<gestor->telefone<<std::endl;
    std::cout<<"CPF:"<<gestor->CPF<<std::endl;
    std::cout<<"**********************************************"<<std::endl;
}

//Cria gestor
Gestor *gestor(int id, const char *nome, const char *data_nascimento, int telefone, const char *CPF){
    auto * gestor = new Gestor;
    gestor->id = id;
    std::strcpy(gestor->nome, nome);
    std::strcpy(gestor->data_nascimento, data_nascimento);
    gestor->telefone = telefone;
    std::strcpy(gestor->CPF, CPF);

    return gestor;
}

//Salva informações de gestor
void salva_gestor(Gestor *gestor, FILE *out){
    fwrite(&gestor->id, sizeof(int), 1, out);
    //func->nome ao invés de &func->nome, pois string já é ponteiro
    fwrite(gestor->nome, sizeof(char), sizeof(gestor->nome), out);
    fwrite(&gestor->telefone, sizeof(int), 1, out);
    fwrite(gestor->data_nascimento, sizeof(char), sizeof(gestor->data_nascimento), out);
    fwrite(&gestor->CPF, sizeof(char), sizeof(gestor->CPF), out);
}

// Le um gestor do arquivo in na posicao atual do cursor
// Retorna um ponteiro para gestor lido do arquivo
Gestor *le_gestor(FILE *in){
    auto *gestor = new Gestor;

    if (0 >= fread(&gestor->id, sizeof(int), 1, in)) {

        free(gestor);
        return nullptr;
    }

    std::fread(gestor->nome, sizeof(char), sizeof (gestor->nome), in);
    std::fread(gestor->CPF, sizeof(char), sizeof (gestor->CPF), in);
    std::fread(gestor->data_nascimento, sizeof(char), sizeof(gestor->data_nascimento), in);
    std::fread(&gestor->telefone, sizeof(int), 1, in);

    return gestor;
}

// Retorna tamanho do gestor em bytes
int tamanho_prof(){
    return sizeof(int)  //cod
           + sizeof(char) * 50 //nome
           + sizeof(char) * 15 //CPF
           + sizeof(char) * 11 //data_nascimento
           + sizeof(int); // telefone
}

Gestor* busca_id_gestor(int id, FILE *arq, int tam){
    int left = 0, right = tam - 1;
    while(left <= right)
    {
        int middle = (left + right) / 2;
        fseek(arq, middle * tamanho_prof(), SEEK_SET);
        Gestor* gestor = le_gestor(arq);

        if(gestor == nullptr){

            return nullptr;
        }else{

            if(id == gestor->id) {
                return gestor;
            }
            else if(gestor->id < id) {
                left = middle + 1;
            }
            else {
                right = middle - 1;
            }
        }
    }
    return nullptr;
}