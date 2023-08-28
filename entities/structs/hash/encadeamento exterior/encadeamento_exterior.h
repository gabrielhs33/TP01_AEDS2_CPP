#ifndef TP01_AEDS2_CPP_ENCADEAMENTO_EXTERIOR_H
#define TP01_AEDS2_CPP_ENCADEAMENTO_EXTERIOR_H
#include <cassert>
#include "../lista compartimentos/lista_compartimentos.h"
#include "../compartimento hash/compartimento_hash.h"
#include "../../../aluno/Aluno.h"
#include <climits>
#include <cstdlib>

// Cria uma tabela hash vazia de tamanho tam, e salva no arquivo nome_arquivo_hash
// Compartimento que nao tem lista encadeada associada deve ter valor igual a -1
// nome_arquivo_hash: nome do arquivo hash a ser criado
// m: tamanho da tabela hash a ser criada
void cria_hash(char *nome_arquivo_hash, int m);

// Executa busca em Arquivos por Encadeamento Exterior (Hash)
// Assumir que ponteiro para proximo noh eh igual a -1 quando nao houver proximo noh
// cod_aluno: chave do aluno que esta sendo buscado
// nome_arquivo_hash: nome do arquivo que contem a tabela hash
// nome_arquivo_dados: nome do arquivo onde os dados estao armazenados
// m: tamanho da tabela hash (a função de hash é h(x) = x mod m
// Retorna o endereco onde o cliente foi encontrado, ou -1 se nao for encontrado
int busca(int cod_aluno, char *nome_arquivo_hash, char *nome_arquivo_dados);

// Executa insercao em Arquivos por Encadeamento Exterior (Hash)
// cod_aluno: chave do aluno que esta sendo inserido
// nome_aluno: nome do aluno a ser inserido
// nome_arquivo_hash: nome do arquivo que contem a tabela hash
// nome_arquivo_dados: nome do arquivo onde os dados estao armazenados
// num_registros: numero de registros que ja existem gravados no arquivo
// Retorna o endereco onde o aluno foi inserido, ou -1 se nao conseguiu inserir
int insere(int cod_aluno, char *nome_aluno, char *nome_arquivo_hash, char *nome_arquivo_dados);

// Executa exclusao em Arquivos por Encadeamento Exterior (Hash)
// cod_aluno: chave do alunoa ser excluido
// nome_arquivo_hash: nome do arquivo que contem a tabela hash
// nome_arquivo_dados: nome do arquivo onde os dados estao armazenados
// Retorna o endereco do aluno que foi excluido, ou -1 se cliente nao existe
int exclui(int cod_aluno, char *nome_arquivo_hash, char *nome_arquivo_dados);


#endif //TP01_AEDS2_CPP_ENCADEAMENTO_EXTERIOR_H
