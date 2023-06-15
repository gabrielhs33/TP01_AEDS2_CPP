//
// Created by Gabriel on 15/06/2023.
//

#include <iostream>
#include "Menu.h"

void Menu::application() {

    std::cout << "Aplicação finalizada" << std::endl;

    int op;

    while( true ){

        std::cout << "Informe a operação que deseja realizar" << std::endl;
        std::cout << "(1) Inserir aluno" << std::endl;
        std::cout << "(2) Buscar Aluno" << std::endl;
        std::cout << "(3) Imprimir todos os alunos" << std::endl;
        std::cout << "(4) Ordenar base de dados" << std::endl;
        std::cout << "Aplicação finalizada" << std::endl;

        std::cin>>op;

        switch (op){

            case 1:


                break;

        }

        break;
    }
}
