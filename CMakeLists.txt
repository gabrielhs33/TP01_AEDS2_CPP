cmake_minimum_required(VERSION 3.23)
project(TP01_AEDS2_CPP)

set(CMAKE_CXX_STANDARD 14)

add_executable(TP01_AEDS2_CPP main.cpp entities/aluno/Aluno.cpp entities/aluno/Aluno.h menu/Menu.cpp menu/Menu.h entities/random/Random.cpp entities/random/Random.h
        entities/structs/arvore/Node.cpp entities/structs/arvore/Node.h
        entities/structs/lista/lista_alunos.cpp entities/structs/lista/lista_alunos.h
        "entities/structs/selecao_substituicao/selecao_substituicao.cpp" "entities/structs/selecao_substituicao/selecao_substituicao.h" entities/structs/arvore_vencedores/arvore_vencedores.cpp entities/structs/arvore_vencedores/arvore_vencedores.h )
