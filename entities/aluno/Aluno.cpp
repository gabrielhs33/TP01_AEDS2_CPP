//
// Created by Gabriel on 15/06/2023.
//

#include <iostream>
#include <cstring>
#include "Aluno.h"

//Imprime aluno
void imprime(Aluno *aluno){

    std::cout<<"**********************************************"<<std::endl;
    std::cout<<"aluno de codigo "<< aluno->id<<std::endl;
    std::cout<<"Nome: "<<aluno->nome<<std::endl;
    std::cout<<"Matricula: "<<aluno->matricula<<std::endl;
    std::cout<<"Data de Nascimento: "<<aluno->data_nascimento<<std::endl;
    std::cout<<"Coeficiente:"<<aluno->coeficiente<<std::endl;
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
    char character = '#';
    fwrite(&character, sizeof(char), 1, out);
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

    int chacter = fgetc(in);
    if(chacter == '#') {
        if (0 >= fread(&aluno->id, sizeof(int), 1, in)) {

            free(aluno);
            return nullptr;
        }
        std::fread(aluno->nome, sizeof(char), sizeof(aluno->nome), in);
        std::fread(aluno->matricula, sizeof(char), sizeof(aluno->matricula), in);
        std::fread(aluno->data_nascimento, sizeof(char), sizeof(aluno->data_nascimento), in);
        std::fread(&aluno->coeficiente, sizeof(double), 1, in);
    }
    else{
        return nullptr;
    }
    return aluno;
}

// Retorna tamanho do aluno em bytes
int tamanho() {
    return sizeof(int)  //cod
           + sizeof(char) * 1 // #
           + sizeof(char) * 50 //nome
           + sizeof(char) * 10 //matricula
           + sizeof(char) * 11 //data_nascimento
           + sizeof(double); //coeficiente
}

Aluno* busca_id(int id, FILE *arq,int tam) {

    clock_t inicio, fim;
    int count = 0;
    int left = 0, right = tam - 1;
    inicio = clock();
    while(left <= right)
    {
        int middle = (left + right) / 2;
        fseek(arq, middle * tamanho(), SEEK_SET);

        Aluno* aluno = le(arq);

        if(aluno == nullptr){
            return nullptr;
        }else{

            count++;
            if(id == aluno->id) {
                fim = clock();
                double time = double(fim - inicio)/CLOCKS_PER_SEC;
                std::cout << "Tempo gasto na busca por id: " << time << std::endl;
                std::cout << "Numero total de comparacoes ao buscar por id: " << count << std::endl;
                return aluno;
            }
            else if(aluno->id < id) {
                left = middle + 1;
            }
            else {
                right = middle - 1;

            }
            count++;
        }

    }
    fim = clock();
    double time = double(fim - inicio)/CLOCKS_PER_SEC;
    std::cout << "Erro: aluno nao encontrado na base de dados. " <<  std::endl;
    std::cout << "Tempo gasto na busca por id: " << time << std::endl;
    std::cout << "Numero total de comparacoes ao buscar por id: " << count << std::endl;
    return nullptr;
}

//selection sort
void ordena_aluno_id(FILE *arq, int tam) {

    rewind(arq);
    long int count = 0;
    clock_t start = clock();

    for (int i = 1; i < tam; i++) {

        fseek(arq, (i - 1) * tamanho(), SEEK_SET);
        Aluno *ai = le(arq);
        fseek(arq, i * tamanho(), SEEK_SET);
        Aluno *menor = le(arq);
        int posmenor = i + 1;
        for (int j = i + 2; j <= tam; j++) {
            Aluno *aj = le(arq);
            count++;
            if ((aj->id) < (menor->id)) {
                menor = aj;
                posmenor = j;
            }
        }

        count++;
        if (menor->id < ai->id) {

            fseek(arq, (posmenor - 1) * tamanho(), SEEK_SET);
            salva(ai, arq);
            fseek(arq, (i - 1) * tamanho(), SEEK_SET);
            salva(menor, arq);
        }
    }

    clock_t end = clock();
    double time = double(end - start)/CLOCKS_PER_SEC;
    std::cout << "Tempo gasto para ordenar os arquivos por id: " << time << std::endl;
    std::cout << "Numero total de comparacoes ao ordenar por id: " << count << std::endl;

    fflush(arq);
}

//selection sort
void ordena_aluno_nome(FILE *arq, int tam) {

    rewind(arq);
    long int count = 0;
    clock_t start = clock();
    for (int i = 1; i < tam; i++) {

        fseek(arq, (i - 1) * tamanho(), SEEK_SET);
        Aluno *ai = le(arq);
        fseek(arq, i * tamanho(), SEEK_SET);
        Aluno *menor = le(arq);
        int posmenor = i + 1;
        for (int j = i + 2; j <= tam; j++) {
            Aluno *aj = le(arq);
            count++;
            if (std::strcmp(aj->nome,menor->nome) < 0) {
                menor = aj;
                posmenor = j;
            }

        }
        count++;
        if (std::strcmp(menor->nome,ai->nome) < 0 ) {

            fseek(arq, (posmenor - 1) * tamanho(), SEEK_SET);
            salva(ai, arq);
            fseek(arq, (i - 1) * tamanho(), SEEK_SET);
            salva(menor, arq);
        }
    }

    clock_t end = clock();
    double time = double(end - start)/CLOCKS_PER_SEC;
    std::cout << "Tempo gasto para ordenar os arquivos por nome: " << time << std::endl;
    std::cout << "Numero total de comparacoes ao ordenar por nome: " << count << std::endl;

    fflush(arq);
}


