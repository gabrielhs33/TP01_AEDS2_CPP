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
                                aluno(49, "Joao","21.2.5000","**/**/****",0.0,-1, OCUPADO),
                                aluno(59, "Maria","21.2.5001","**/**/****",0.0, 3, OCUPADO),
                                aluno(103, "Pedro","21.2.5002","**/**/****",0.0, -1, OCUPADO),
                                aluno(3, "Janio","21.2.5003","**/**/****",0.0, 5, OCUPADO),
                                aluno(51, "Ana","21.2.5004","**/**/****",0.0, -1, OCUPADO),
                                aluno(87, "Mauricio","21.2.5005","**/**/****",0.0, -1, OCUPADO));
    salva_alunos_lista(NOME_ARQUIVO_DADOS, tab_alunos);

    int end = insere(10,"ana", NOME_ARQUIVO_HASH, NOME_ARQUIVO_DADOS,6 );

    int excluido = exclui(10,NOME_ARQUIVO_HASH,NOME_ARQUIVO_DADOS);

    FILE *out = fopen(NOME_ARQUIVO_DADOS,"rb");
    le_alunos(out);
    fclose(out);

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