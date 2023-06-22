//
// Created by Gabriel on 15/06/2023.
//

#include <iostream>
#include "Menu.h"
#include "../random/Random.h"
#include <random>
#include <cstring>


void Menu::application() {

    int op = 0;

    FILE *out = std::fopen("aluno.dat", "w+b");

    if (out != nullptr) {

        cria_base_dados(out);

        while( op != -1 ){

            std::cout << "\nInforme a operacao que deseja realizar" << std::endl;
            std::cout << "(1) Inserir aluno" << std::endl;
            std::cout << "(2) Imprimir todos os alunos" << std::endl;
            std::cout << "(3) Buscar aluno por id" << std::endl;
            std::cout << "(4) Ordenar alunos pelo id" << std::endl;

            std::cin>>op;

            switch (op){

                case 1:

                    adiciona_aluno(out);
                    break;
                case 2:

                    le_alunos(out);
                    break;
                case 3:

                    int x;
                    std::cout<<"informe o id o aluno que deseja buscar"<<std::endl;
                    std::cin>>x;
                    imprime(busca_id(x,out, contar_registros(out)));
                    break;

                case 4:

                    ordena_id(out, contar_registros(out));
                    break;

                default:

                    std::cout<<"informe um valor valido"<<std::endl;
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

    Aluno* cadastra_aluno(int cont){

        char nome[50];
        char matricula[10];
        char data_nascimento[11];
        double coeficiente;

        fflush(stdin);
        std::cout << "Nome: " << std::endl;
        std::cin.getline(nome, 50);
        fflush(stdin);

        std::cout << "Matricula: " << std::endl;
        std::cin.getline(matricula, 10);
        std::cout << "Data de nascimento: " << std::endl;
        std::cin.getline(data_nascimento, 11);
        std::cout << "Coeficiente: " << std::endl;
        std::cin>>coeficiente;

        return  aluno(cont+1, nome,matricula,data_nascimento,coeficiente);
    }

    void adiciona_aluno(FILE *in) {

        int tam = contar_registros(in);

        //pula a quantidade de registros cadastrados para posicionar no início do final do arquivo
        fseek(in, tamanho() * tam, SEEK_SET);
        Aluno* a = cadastra_aluno(tam);
        imprime(a);
        salva(a, in);
        free(a);
        //lê funcionário que acabou de ser gravado
        //posiciona novamente o cursor no início desse registro


        std::cout << "Adicionando aluno no final do arquivo..." << std::endl;
        fseek(in, tamanho() * tam, SEEK_SET);
        Aluno *a6 = le(in);
        if (a6 != nullptr) {

            free(a6);
        }
    }

    void cria_base_dados(FILE *out){

        for (int i=1; i<20; i++){

            Aluno * a = aluno(i, Random::cria_nome_aleatorio(), Random::cria_matricula_aleatoria(),
                              Random::cria_data_aleatoria(), Random::cria_coeficiente_aleatorio());
            salva(a, out);
            free(a);
        }
    }

    int contar_registros(FILE* out) {

        if (out == nullptr) {
            std::cerr << "Arquivo inválido." << std::endl;
            return -1;
        }

        std::fseek(out, 0, SEEK_END);
        long tamanho_arquivo = std::ftell(out);
        std::rewind(out);

        int tamanho_registro = tamanho();

        int total_registros = tamanho_arquivo / tamanho_registro;

        return total_registros;
    }


    //selection sort
    void ordena_id(FILE *arq, int tam) {

        rewind(arq);

        for (int i = 1; i < tam; i++) {

            fseek(arq, (i - 1) * tamanho(), SEEK_SET);
            Aluno *ai = le(arq);
            fseek(arq, i * tamanho(), SEEK_SET);
            Aluno *menor = le(arq);
            int posmenor = i + 1;
            for (int j = i + 2; j <= tam; j++) {
                Aluno *aj = le(arq);
                if ((aj->id) < (menor->id)) {
                    menor = aj;
                    posmenor = j;
                }
            }

            if (menor->id < ai->id) {

                fseek(arq, (posmenor - 1) * tamanho(), SEEK_SET);
                salva(ai, arq);
                fseek(arq, (i - 1) * tamanho(), SEEK_SET);
                salva(menor, arq);
            }
        }


        fflush(arq);
    }






