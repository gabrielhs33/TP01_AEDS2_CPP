cmake_minimum_required(VERSION 3.23)
project(TP01_AEDS2_CPP)

set(CMAKE_CXX_STANDARD 14)

add_executable(TP01_AEDS2_CPP main.cpp entities/aluno/Aluno.cpp entities/aluno/Aluno.h menu/Menu.cpp menu/Menu.h entities/random/Random.cpp entities/random/Random.h
        entities/structs/lista/lista_alunos.cpp entities/structs/lista/lista_alunos.h
        "entities/structs/selecao_substituicao/selecao_substituicao.cpp" "entities/structs/selecao_substituicao/selecao_substituicao.h"
        entities/structs/intercalacao/intercalacao_otima.cpp entities/structs/intercalacao/intercalacao_otima.h "entities/structs/hash/encadeamento exterior/encadeamento_exterior.cpp"
        "entities/structs/hash/lista compartimentos/lista_compartimentos.cpp"
        entities/structs/hash/hash.cpp
        entities/structs/hash/hash.h
        "entities/structs/hash/compartimento hash/compartimento_hash.cpp")
