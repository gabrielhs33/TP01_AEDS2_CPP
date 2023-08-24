#ifndef TP01_AEDS2_CPP_ALUNO_H
#define TP01_AEDS2_CPP_ALUNO_H
#include <string>

#define LIBERADO 0
#define OCUPADO 1


class Aluno {

    public:
        int id;
        char nome[50];
        char matricula[10];
        char data_nascimento[13];
        //int flag;
        double coeficiente;
        //int prox;
};

//Imprime aluno
void imprime(Aluno *aluno);

//Cria aluno
Aluno *aluno(int id, const char *nome, const char *matricula, const char *data_nascimento, double coeficiente);

//Salva aluno no arquivo
void salva_aluno(Aluno *aluno, FILE *out);

//conta quantos registros foram inseridos no arquivo
int contar_registros(FILE *out);

// Le um aluno do arquivo in na posicao atual do cursor
// Retorna um ponteiro para aluno lido do arquivo
Aluno *le_aluno(FILE *in);

// Retorna tamanho do aluno em bytes
int tamanho();

// Realiza busca binaria no arquivo ordenado
// Retorna um ponteiro para aluno lido do arquivo
Aluno* busca_id(int id, FILE *arq, int tam);

//ordena os alunos no arquivo em ordem crescente pelo id
void ordena_aluno_id(FILE *arq, int tam);

// le todos os alunos do arquivo
void le_alunos(FILE *in);

//ordena os alunos no arquivo em ordem alfabetica pelo nome
Aluno* busca_sequencial(int id, FILE* file);

void insere_no_arquivo( FILE  *out);

#endif
