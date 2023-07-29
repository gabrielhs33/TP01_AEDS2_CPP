#ifndef TP01_AEDS2_CPP_ALUNO_H
#define TP01_AEDS2_CPP_ALUNO_H

#include <string>

class Aluno {

    public:
        int id;
        char nome[50];
        char matricula[10];
        char data_nascimento[13];
        double coeficiente;
};

//Imprime aluno
void imprime(Aluno *aluno);

//Cria aluno
Aluno* aluno(int id, const char *nome, const char *matricula, const char *data_nascimento, double coeficiente );

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
//ordena os alunos no arquivo em ordem alfabetica pelo nome
void ordena_aluno_nome(FILE *arq, int tam);

void ordena_aluno_coeficiente(FILE *arq, int tam);

Aluno* busca_sequencial(int id, FILE* file);

void selecao_por_substituicao(FILE* arq, int memoria);

#endif
