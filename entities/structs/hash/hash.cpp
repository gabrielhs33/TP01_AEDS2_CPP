#include "hash.h"
#define NOME_ARQUIVO_HASH "tabHash.dat"
#define NOME_ARQUIVO_DADOS "alunosTabHash.dat"

#include "lista compartimentos/lista_compartimentos.h"
#include "compartimento hash/compartimento_hash.h"
#include "encadeamento exterior/encadeamento_exterior.h"
#include "../../aluno/Aluno.h"
#include "../../structs/lista/lista_alunos.h"
#include <cassert>
#include <iostream>

int main(){

    ListaCompartimentos *tab_hash, *tab_hash_saida;
    Tlista_aluno *tab_alunos, *tab_cliente_saida;

    tab_hash = cria_compartimentos(7,
                                   compartimento_hash(0),
                                   compartimento_hash(-1),
                                   compartimento_hash(4),
                                   compartimento_hash(1),
                                   compartimento_hash(-1),
                                   compartimento_hash(2),
                                   compartimento_hash(-1));
    salva_compartimentos(NOME_ARQUIVO_HASH, tab_hash);

    tab_alunos = cria_alunos(6,
                                aluno(49, "Joao","21.2.5000","**/**/****",0.0, OCUPADO,-1),
                                aluno(59, "Maria","21.2.5001","**/**/****",0.0, OCUPADO, 3),
                                aluno(103, "Pedro","21.2.5002","**/**/****",0.0, OCUPADO, -1),
                                aluno(3, "Janio","21.2.5003","**/**/****",0.0, OCUPADO, 5),
                                aluno(51, "Ana","21.2.5004","**/**/****",0.0, OCUPADO, -1),
                                aluno(87, "Mauricio","21.2.5005","**/**/****",0.0, OCUPADO, -1));
    salva_alunos_lista(NOME_ARQUIVO_DADOS, tab_alunos);

    int op=0;
    FILE *out;
    char nome[50];
    int id;
    int end;

    while(op != -1){

        std::cout<<"\ninforme a operacao:"<<std::endl;
        std::cout<<"(1) imprimir todos os registros"<<std::endl;
        std::cout<<"(2) inserir novo registro"<<std::endl;
        std::cout<<"(3) buscar registro"<<std::endl;
        std::cout<<"(4) excluir registro"<<std::endl;

        std::cin>>op;

        switch(op){

            case 1:
                out = fopen(NOME_ARQUIVO_DADOS,"rb");
                le_alunos(out);
                fclose(out);
                break;

            case 2:
                std::cout<<"informe as informações do registro que deseja inserir:"<<std::endl;
                std::cout<<"id:"<<std::endl;
                std::cin>>id;
                std::cout<<"nome: "<<std::endl;
                std::cin>>nome;

                end = insere(id,nome, NOME_ARQUIVO_HASH, NOME_ARQUIVO_DADOS,6 );
                break;
            case 3:
//                std::cout<<"informe o id que deseja buscar: "<<std::endl;
//                std::cin>>id;
                end = busca(59, NOME_ARQUIVO_HASH,NOME_ARQUIVO_DADOS);
                if(end == -1){

                    std::cout<<"registro não encontrado"<<std::endl;
                }else{

                    out = fopen(NOME_ARQUIVO_DADOS,"rb");
                    fseek(out, end*tamanho(), SEEK_SET);
                    imprime(le_aluno(out));
                    fclose(out);
                }
        }

    }


    tab_hash_saida = le_compartimentos(NOME_ARQUIVO_HASH);

    libera_aluno(tab_alunos);
    tab_alunos = cria_alunos(7,
                                aluno(49, "Joao","21.2.5000","**/**/****",0.0, -1, OCUPADO),
                                aluno(59, "Maria","21.2.5000","**/**/****",0.0, 3, OCUPADO),
                                aluno(103, "Pedro","21.2.5000","**/**/****",0.0, -1, OCUPADO),
                                aluno(3, "Janio","21.2.5000","**/**/****",0.0, 5, OCUPADO),
                                aluno(51, "Ana","21.2.5000","**/**/****",0.0, -1, OCUPADO),
                                aluno(87, "Mauricio","21.2.5000","**/**/****",0.0, 6, OCUPADO),
                                aluno(10, "Ana","21.2.5000","**/**/****",0.0, -1, OCUPADO));

    tab_cliente_saida = le_alunos_lista(NOME_ARQUIVO_DADOS);

    libera_compartimentos(tab_hash);
    libera_compartimentos(tab_hash_saida);
    libera_aluno(tab_alunos);
    libera_aluno(tab_cliente_saida);
}