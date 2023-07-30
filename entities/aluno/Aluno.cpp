#include <iostream>
#include <cstring>
#include <chrono>
#include "Aluno.h"
#include "../pilha/Pilha.h"

//Imprime aluno
void imprime(Aluno *aluno){

    std::cout<<"**********************************************"<<std::endl;
    std::cout<<"aluno de codigo "<< aluno->id<<std::endl;
    std::cout<<"Nome: "<<aluno->nome<<std::endl;
    std::cout<<"Matricula: "<<aluno->matricula<<std::endl;
    std::cout<<"Data de Nascimento: "<<aluno->data_nascimento<<std::endl;
    std::cout<<"Coeficiente:"<<aluno->coeficiente<<std::endl;
    std::cout<<"**********************************************"<<std::endl;
}

//Cria aluno
Aluno* aluno(int id, const char *nome, const char *matricula, const char *data_nascimento, double coeficiente){

    auto * aluno = new Aluno;
    aluno->id = id;
    std::strcpy(aluno->nome, nome);
    std::strcpy(aluno->matricula, matricula);
    std::strcpy(aluno->data_nascimento, data_nascimento);
    aluno->coeficiente = coeficiente;

    return aluno;
}

//Salva aluno no arquivo
void salva_aluno(Aluno *aluno, FILE *out){

    fwrite(&aluno->id, sizeof(int), 1, out);
    //func->nome ao invés de &func->nome, pois string já é ponteiro
    fwrite(aluno->nome, sizeof(char), sizeof(aluno->nome), out);
    fwrite(aluno->matricula, sizeof(char), sizeof(aluno->matricula), out);
    fwrite(aluno->data_nascimento, sizeof(char), sizeof(aluno->data_nascimento), out);
    fwrite(&aluno->coeficiente, sizeof(double), 1, out);
}

// Le um aluno do arquivo in na posicao atual do cursor
// Retorna um ponteiro para aluno lido do arquivo
Aluno *le_aluno(FILE *in) {

    auto *aluno = new Aluno;
    if (0 >= fread(&aluno->id, sizeof(int), 1, in)) {

        free(aluno);
        return nullptr;
    }
    std::fread(aluno->nome, sizeof(char), sizeof(aluno->nome), in);
    std::fread(aluno->matricula, sizeof(char), sizeof(aluno->matricula), in);
    std::fread(aluno->data_nascimento, sizeof(char), sizeof(aluno->data_nascimento), in);
    std::fread(&aluno->coeficiente, sizeof(double), 1, in);

    return aluno;
}

// Retorna tamanho do aluno em bytes
int tamanho() {
    return sizeof(int)  //cod
           + sizeof(char) * 50 //nome
           + sizeof(char) * 10 //matricula
           + sizeof(char) * 13 //data_nascimento
           + sizeof(double); //coeficiente
}

Aluno* busca_id(int id, FILE *arq,int tam) {

    int count = 0;
    int left = 0, right = tam - 1;

    clock_t start = clock();
    while(left <= right)
    {

        int middle = (left + right) / 2;
        fseek(arq, middle * tamanho(), SEEK_SET);

        Aluno* aluno = le_aluno(arq);

        if(aluno == nullptr){
            return nullptr;
        }else{

            count++;
            if(id == aluno->id) {

                clock_t end = clock();
                long double time = (double(end - start))/CLOCKS_PER_SEC;
                std::cout << "Tempo gasto na busca por id: " << time << std::endl;
                std::cout << "Numero total de comparacoes ao buscar por id: " << count << std::endl;
                return aluno;
            }
            else if(aluno->id < id) {
                left = middle + 1;
            }
            else {

                right = middle - 1;
            }
            count++;
        }
    }

    clock_t end = clock();
    long double time = (double(end - start))/CLOCKS_PER_SEC;
    std::cout << "Tempo gasto para realizat busca por id: " << time << std::endl;
    std::cout << "Numero total de comparacoes ao buscar por id: " << count << std::endl;
    return nullptr;
}

//selection sort
void ordena_aluno_id(FILE *arq, int tam) {

    long int count = 0;
    clock_t start = clock();

    for (int i = 1; i < tam; i++) {

        fseek(arq, (i - 1) * tamanho(), SEEK_SET);
        Aluno *ai = le_aluno(arq);
        fseek(arq, i * tamanho(), SEEK_SET);
        Aluno *menor = le_aluno(arq);
        int posmenor = i + 1;
        for (int j = i + 2; j <= tam; j++) {
            Aluno *aj = le_aluno(arq);
            count++;
            if ((aj->id) < (menor->id)) {
                menor = aj;
                posmenor = j;
            }
        }

        count++;
        if (menor->id < ai->id) {

            fseek(arq, (posmenor - 1) * tamanho(), SEEK_SET);
            salva_aluno(ai, arq);
            fseek(arq, (i - 1) * tamanho(), SEEK_SET);
            salva_aluno(menor, arq);
        }
    }

    clock_t end = clock();
    double time = double(end - start)/CLOCKS_PER_SEC;
    std::cout << "Tempo gasto para ordenar os arquivos por id: " << time << std::endl;
    std::cout << "Numero total de comparacoes ao ordenar por id: " << count << std::endl;

    fflush(arq);
}

//selection sort
void ordena_aluno_nome(FILE *arq, int tam) {

    rewind(arq);
    long int count = 0;
    clock_t start = clock();
    for (int i = 1; i < tam; i++) {

        fseek(arq, (i - 1) * tamanho(), SEEK_SET);
        Aluno *ai = le_aluno(arq);
        fseek(arq, i * tamanho(), SEEK_SET);
        Aluno *menor = le_aluno(arq);
        int posmenor = i + 1;
        for (int j = i + 2; j <= tam; j++) {
            Aluno *aj = le_aluno(arq);
            count++;
            if (std::strcmp(aj->nome,menor->nome) < 0) {
                menor = aj;
                posmenor = j;
            }
        }
        count++;
        if (std::strcmp(menor->nome,ai->nome) < 0 ) {

            fseek(arq, (posmenor - 1) * tamanho(), SEEK_SET);
            salva_aluno(ai, arq);
            fseek(arq, (i - 1) * tamanho(), SEEK_SET);
            salva_aluno(menor, arq);
        }
    }

    clock_t end = clock();
    double time = double(end - start)/CLOCKS_PER_SEC;
    std::cout << "Tempo gasto para ordenar os arquivos por nome: " << time << std::endl;
    std::cout << "Numero total de comparacoes ao ordenar por nome do aluno: " << count << std::endl;

    fflush(arq);
}

void ordena_aluno_coeficiente(FILE *arq, int tam) {

    long int count = 0;
    clock_t start = clock();

    for (int i = 1; i < tam; i++) {

        fseek(arq, (i - 1) * tamanho(), SEEK_SET);
        Aluno *ai = le_aluno(arq);
        fseek(arq, i * tamanho(), SEEK_SET);
        Aluno *menor = le_aluno(arq);
        int posmenor = i + 1;
        for (int j = i + 2; j <= tam; j++) {
            Aluno *aj = le_aluno(arq);
            count++;
            if ((aj->coeficiente) < (menor->coeficiente)) {
                menor = aj;
                posmenor = j;
            }
        }

        count++;
        if (menor->coeficiente < ai->coeficiente) {

            fseek(arq, (posmenor - 1) * tamanho(), SEEK_SET);
            salva_aluno(ai, arq);
            fseek(arq, (i - 1) * tamanho(), SEEK_SET);
            salva_aluno(menor, arq);
        }
    }

    clock_t end = clock();
    double time = double(end - start)/CLOCKS_PER_SEC;
    std::cout << "Tempo gasto para ordenar os arquivos por coeficiente: " << time << std::endl;
    std::cout << "Numero total de comparacoes ao ordenar por coeficientedo aluno: " << count << std::endl;

    fflush(arq);
}

int contar_registros(FILE* out) {

    if (out == nullptr) {
        std::cerr << "Arquivo inválido." << std::endl;
        return -1;
    }

    std::fseek(out, 0, SEEK_END);
    //conta o tamanho total do arquivo
    long tamanho_arquivo = std::ftell(out);
    //reposiciona o cursor no inicio do arquivo
    std::rewind(out);

    int tamanho_registro = tamanho();

    int total_registros = tamanho_arquivo / tamanho_registro;

    return total_registros;
}

Aluno* busca_sequencial(int id, FILE* file) {

    rewind(file);

    auto* aluno = new Aluno();
    int count = 0;

    clock_t start = clock();
    while (fread(aluno, tamanho(), 1, file) == 1) {
        count++;
        if (aluno->id == id) {

            clock_t end = clock();
            double time = double(end - start)/CLOCKS_PER_SEC;
            std::cout << "Tempo gasto para ordenar os arquivos por busca sequencial: " << time << std::endl;
            std::cout << "Numero total de comparacoes: " << count << std::endl;
            return aluno;
        }
    }
    delete aluno;
    fflush(file);

    clock_t end = clock();
    double time = double(end - start)/CLOCKS_PER_SEC;
    std::cout << "Tempo gasto para ordenar os arquivos por busca sequencial: " << time << std::endl;
    std::cout << "Numero total de comparacoes: " << count << std::endl;

    return nullptr;
}


void selecao_por_substituicao(FILE* arq, int memoria) {
    rewind(arq); // Posiciona cursor no início do arquivo

    int nFunc = contar_registros(arq);
    int qtdParticoes = 0;

    auto** v = new Aluno*[memoria];
    bool* congelado = new bool[nFunc];
    int i = 0;

    while (i < nFunc) {
        // Leitura dos registros do arquivo original para a memória (limitado pelo tamanho da memória)
        int j = 0;
        while (!feof(arq) && j < memoria) {
            v[j] = le_aluno(arq);
            congelado[i + j] = false; // inicializa todos os registros como não congelados
            j++;
        }

        // Encontrar o registro com a menor chave no array em memória
        int min_idx = i;
        for (int k = i + 1; k < i + j; k++) {
            if (!congelado[k] && v[k - i]->id < v[min_idx - i]->id) {
                min_idx = k;
            }
        }

        // Gravar o registro r com menor chave na partição de saída
        char nomeParticao[20];
        sprintf(nomeParticao, "particao%d.dat", qtdParticoes);
        FILE* p;
        if ((p = fopen(nomeParticao, "wb+")) == nullptr) {
            std::cout << "Erro ao criar arquivo de saida\n";
            break;
        } else {
            // Grava os registros ordenados no arquivo de saída
            for (int k = i; k < i + j; k++) {
                salva_aluno(v[k - i], p);
                congelado[k] = true; // Congela o registro gravado na partição de saída
            }
            fclose(p);
            qtdParticoes++;
        }

        // Libera a memória dos registros gravados na partição de saída
        for (int k = i; k < i + j; k++) {
            delete v[k - i];
        }

        // Procurar por mais registros não congelados em memória
        while (i < nFunc && congelado[i]) {
            i++;
        }
    }

    // Libera a memória alocada para o array de ponteiros e o array de congelados
    delete[] v;
    delete[] congelado;
}

void cria_pilha(TPilha *pilha, FILE *arq, int tam){
    // Achar o menor indice e inserir todos na pilha
    int j = 0;
    while (!feof(arq) && j < tam){
        Aluno *aluno2 = le_aluno(arq);
        push(pilha, 6, &j, aluno2, j);
    }
}

Aluno menor_da_pilha(TPilha pilha, Aluno *aluno_menor, int *array_congelados){
    int flag = 0;
    for(int nmr = 0; nmr < 6; nmr++){
        Aluno * aluno = pop(&pilha, 0, 5);
    }
    return *aluno_menor;
}

void ordena_itens(FILE *arq, int tam){
    int qtdParticoes = 0;
    int array[tam - 1];
    int qtd_registros = contar_registros(arq);

    TPilha *pilha;
    pilha = (TPilha*)malloc(sizeof(TPilha));
    inicializa(pilha, 6, 0);

    while(int i= 0 <qtd_registros){
        Aluno *menor;
        menor = le_aluno(arq);

        // Gravar o registro r com menor chave na partição de saída
        char nomeParticao[int(qtd_registros/tam) + 1];
        sprintf(nomeParticao, "particao%d.dat", qtdParticoes);
        FILE* p;
        if ((p = fopen(nomeParticao, "wb+")) == nullptr) {
            std::cout << "Erro ao criar arquivo de saida\n";
            break;
        }
        else{
            // Insere menor no arquivo p
            salva_aluno(menor, p);

        }
    }
}





