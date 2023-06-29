#include <iostream>
#include <cstring>
#include "Professor.h"

//Imprime Professor
void imprime_professor(Professor *professor){
    std::cout<<"**********************************************"<<std::endl;
    std::cout<<"Professor de codigo "<< professor->id<<std::endl;
    std::cout<<"Nome: "<<professor->nome<<std::endl;
    std::cout<<"telefone: "<<professor->telefone<<std::endl;
    std::cout<<"CPF:"<<professor->cpf<<std::endl;
    std::cout<<"**********************************************"<<std::endl;
}

//Cria professor
Professor *professor(int id, const char *nome, const char *telefone, const char *CPF, double salario){
    auto * professor = new Professor;
    professor->id = id;
    std::strcpy(professor->nome, nome);
    std::strcpy(professor->telefone, telefone);
    std::strcpy(professor->cpf, CPF);
    professor -> salario = salario;

    return professor;
}

//Salva informações de professor
void salva_professor (Professor *professor, FILE *out){

    char character = '$';
    fwrite(&character, sizeof(char), 1, out);
    fwrite(&professor->id, sizeof(int), 1, out);
    fwrite(professor->nome, sizeof(char), sizeof(professor->nome), out);
    fwrite(professor->telefone, sizeof(char), sizeof(professor->telefone), out);
    fwrite(professor->cpf, sizeof(char), sizeof(professor->cpf), out);
    fwrite(&professor->salario,sizeof(double ),1,out);
}

// Le um professor do arquivo in na posicao atual do cursor
// Retorna um ponteiro para professor lido do arquivo
Professor *le_professor(FILE *in){
    auto *professor = new Professor;

    int chacter = fgetc(in);

    if(chacter == '$'){

        if (0 >= fread(&professor->id, sizeof(int), 1, in)) {

            free(professor);
            return nullptr;
        }

        std::fread(professor->nome, sizeof(char), sizeof (professor->nome), in);
        std::fread(professor->telefone, sizeof(char), sizeof (professor->telefone), in);
        std::fread(professor->cpf, sizeof(char), sizeof (professor->cpf), in);
        std::fread(&professor->salario,sizeof (double),1,in);

        return professor;
    }else{

        return nullptr;
    }
}

// Retorna tamanho do professor em bytes
int tamanho_prof(){
    return sizeof(int)  //cod
           + sizeof(char) * 50 //nome
           + sizeof(char) * 15 //CPF
           + sizeof(char) * 8 //telefone
           + sizeof(double)// salario
           +sizeof (char); //"$"
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