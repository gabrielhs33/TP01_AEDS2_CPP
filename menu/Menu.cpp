#include <iostream>
#include "Menu.h"
#include "../entities/random/Random.h"
#include <stdexcept>
#include <limits>


void Menu::application() {

    int op = 0;


    FILE *out = std::fopen("aluno.dat", "wb+");

    if (out != nullptr) {

        cria_base_dados(out);

        while( op != -1 ){

            std::cout << "\nInforme a operacao que deseja realizar:" << std::endl;
            std::cout << "(1) Inserir aluno" << std::endl;
            std::cout << "(2) Imprimir todos os registros" << std::endl;
            std::cout << "(3) Buscar aluno por id" << std::endl;
            std::cout << "(4) Ordenar aluno por id" << std::endl;
            std::cout << "(5) Ordenar alunos em ordem alfabetica"<<std::endl;
            std::cout << "(6) Ordenar alunos por coeficiente"<<std::endl;
            std::cout << "(7) Realizar busca sequencial"<<std::endl;
            std::cout << "(-1) Finaliza a aplicacao"<<std::endl;

            try {

                std::cin >> op;

                if (std::cin.fail()) {
                    throw std::invalid_argument("Entrada invalida. Digite apenas numeros inteiros");
                }

                // Verifica se não há caracteres extras após o número inteiro
                char c;
                if (std::cin.get(c) && !std::isspace(c)) {
                    throw std::invalid_argument("Entrada invalida. Digite apenas numeros inteiros");
                }

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

                        Aluno* aluno;
                        aluno = busca_id(x,out, contar_registros(out));
                        if(aluno != nullptr){

                            imprime(aluno);
                        }else{

                            std::cout<<"aluno nao encontrado na base de dados"<<std::endl;
                        }
                        break;

                    case 4:

                        ordena_aluno_id(out, contar_registros(out));
                        std::cout<<"alunos ordenados pelo id"<<std::endl;
                        break;

                    case 5:

                        //ordena_aluno_nome(out, contar_registros(out));
                        std::cout<<"alunos ordenados pelo nome"<<std::endl;
                        break;

                    case 6:

                        //ordena_aluno_coeficiente(out, contar_registros(out));
                        break;

                    case 7:

                        std::cout<<"informe o id o aluno que deseja buscar"<<std::endl;
                        std::cin>>x;

                        Aluno* a2;
                        a2= busca_sequencial(x,out);
                        if(a2!= nullptr){

                            imprime(a2);
                        }else{

                            std::cout<<"aluno nao encontrado na base de dados"<<std::endl;
                        }
                        break;

                    case 8:
                        int qtd;
                         qtd = selecao_com_substituicao(out, 6);
                        intercalacao(qtd, out);
                        break;

                    case -1:

                        break;

                    default:

                        std::cout<<"Informe um valor valido"<<std::endl;
                        break;
                }
            } catch (const std::invalid_argument& e) {

                std::cerr << "\nErro: " << e.what() << std::endl;
                std::cin.clear(); // Limpar o estado de erro
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Descartar entrada inválida
            }
        }
        std::fclose(out);

    }else{

        std::cout<<"erro ao abrir o arquivo"<<std::endl;
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

    fseek(in, tamanho() * tam, SEEK_SET);
    Aluno* a = cadastra_aluno(tam);
    imprime(a);
    salva_aluno(a, in);
    free(a);


    std::cout << "Adicionando aluno no final do arquivo..." << std::endl;
    fseek(in, tamanho() * tam, SEEK_SET);
    Aluno *a6 = le_aluno(in);
    if (a6 != nullptr) {

        free(a6);
    }
}

void cria_base_dados(FILE *out) {

    long int qtd = 10;

    int ids_disponiveis[qtd - 1];
    for (int i = 1; i <= qtd; i++) {
        ids_disponiveis[i - 1] = i;  // Preenche a lista de IDs disponíveis
    }

    for (int i = 0; i < qtd; i++) {

        int index = rand() % (qtd - i);  // Gera um índice aleatório dentro do intervalo disponível
        int id = ids_disponiveis[index];  // Seleciona o ID na posição aleatória
        ids_disponiveis[index] = ids_disponiveis[(qtd - 1) - i];
        Aluno *a = aluno(id, Random::cria_nome_aleatorio(), Random::cria_matricula_aleatoria(),
                         Random::cria_data_aleatoria(), Random::cria_coeficiente_aleatorio());
        salva_aluno(a, out);
        free(a);
    }
}






