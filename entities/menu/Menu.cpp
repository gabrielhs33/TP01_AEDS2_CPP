//
// Created by Gabriel on 15/06/2023.
//

#include <iostream>
#include <limits>
#include "Menu.h"


void Menu::application() {

    int op = 0;

    FILE *out = std::fopen("aluno.dat", "w+b");

    if (out != nullptr) {

        insere_5_alunos(out);

        while( op != -1 ){

            std::cout << "\nInforme a operacao que deseja realizar" << std::endl;
            std::cout << "(1) Inserir aluno" << std::endl;
            std::cout << "(2) Imprimir todos os alunos" << std::endl;
            std::cout << "(4) Ordenar base de dados" << std::endl;

            std::cin>>op;

            switch (op){

                case 1:

                    adiciona_aluno(out);
                    break;
                case 2:

                    le_alunos(out);
                    break;
            }
        }

        std::fclose(out);

    }else{

        std::cout<<"erro ao abrir o arquivo"<<std::endl;
    }
}

    void le_alunos(FILE *in) {

        std::cout<< "\n\nLendo alunos do arquivo...\n\n"<<std::endl;
        rewind(in);
        Aluno *a;
        while ((a = le(in)) != nullptr) {
            imprime(a);
            free(a);
        }
    }

Aluno* cadastra_aluno(){

    char nome[50];
    char matricula[10];
    char data_nascimento[11];
    double coeficiente;

    std::cout << "Nome: " << std::endl;
    std::cin.getline(nome, 50);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Matricula: " << std::endl;
    std::cin.getline(matricula, 10);
    std::cout << "Data de nascimento: " << std::endl;
    std::cin.getline(data_nascimento, 11);
    std::cout << "Coeficiente: " << std::endl;
    std::cin>>coeficiente;

    return  aluno(6, nome,matricula,data_nascimento,coeficiente);
}

    void adiciona_aluno(FILE *in) {

        //pula 5 registros para posicionar no início do final do arquivo
        fseek(in, tamanho() * 5, SEEK_SET);
        Aluno* a = cadastra_aluno();
        std::cout<<"aqui";
        imprime(a);
        salva(a, in);
        free(a);
        //lê funcionário que acabou de ser gravado
        //posiciona novamente o cursor no início desse registro


        std::cout << "Adicionando aluno no final do arquivo..." << std::endl;
        fseek(in, tamanho() * 5, SEEK_SET);
        Aluno *a6 = le(in);
        if (a6 != nullptr) {

            free(a6);
        }
    }

    void insere_5_alunos(FILE *out) {

        std::cout << "Inserindo 5 alunos no arquivo..." << std::endl;

        Aluno * a1 = aluno(1, "Ana", "000.000.000-00", "01/01/1980", 3000);
        salva(a1, out);
        free(a1);

        Aluno * a2 = aluno(2, "Carlos", "111.111.111-11", "01/01/1990", 500);
        salva(a2, out);
        free(a2);

        Aluno * a3 = aluno(3, "Fatima", "222.222.222-22", "02/02/1980", 1000);
        salva(a3, out);
        free(a3);

        Aluno * a4 = aluno(4, "Marcelo", "333.333.333-33", "03/03/1990", 1500);
        salva(a4, out);
        free(a4);

        Aluno * a5 = aluno(5, "Silvia", "444.444.444-44", "04/04/1980", 900);
        salva(a5, out);
        free(a5);
    }




