#include <iostream>
#include <cstring>
#include <chrono>
#include "Aluno.h"
#include "../structs/pilha/Pilha.h"

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



void cria_pilha(TPilha *pilha, FILE *arq, int tam){
    // Achar o menor indice e inserir todos na pilha
    int j = 0;
    while (!feof(arq) && j < tam){
        pilha->info = le_aluno(arq);
        push(pilha, pilha->limite, &j, pilha->info, j);
    }
}

Aluno * menor_da_pilha(TPilha pilha, Aluno *aluno_menor, int *array_congelados){
    int flag = 0;
    for(int nmr = 0; nmr < 6; nmr++){

        Aluno * aluno = pop(&pilha, 0, &pilha.topo);
        if(array_congelados[aluno->id] == 1) {
            flag = 1;
        }
        if (flag == 0 && aluno_menor->id > aluno->id) {
            aluno_menor = aluno;
        }
    }
    return aluno_menor;
}

bool verifica_congelamento(TPilha pilha, int *array_congelados){
    Aluno *aux;
    int flag;
    for(int a =0; a < 6; a++) {
        flag = 1;
        aux = pop(&pilha, 0, pilha.topo);
        if (array_congelados[aux->id] == 0) {
            flag = 0;
        }
        if (flag == 0){
            return false;
        }
    }
    free(aux);
    return true;
}

void substitui(TPilha *pilha, Aluno r, int *p, FILE *arq, int *array_congelados){
    TPilha *pilha2;
    pilha2 = (TPilha*)malloc(sizeof(TPilha));
    TPilha * aux2;
    aux2 = (TPilha*)malloc(sizeof(TPilha));
    TPilha * aux3;
    aux3 = (TPilha*)malloc(sizeof(TPilha));
    Aluno *a3;

    inicializa(pilha2, 6, 0);
    for (int i = 0; i < 6; i++){
        aux2->info = pop(pilha, 0, pilha->topo;
        if(aux2->info != r){
            aux2->info = pop(pilha, 0, pilha->topo);
            push(pilha2, pilha2->limite, &i, aux2->info, i);
        }else {
            *p = *p + 1;
            aux2->info = pop(pilha, 0, pilha->topo);
            aux3->info = le_aluno(arq);
            a3 = aux3->info;
            push(pilha2, pilha2->limite, &i, aux3->info, i);
            if(a3->id < r.id){
                array_congelados[a3->id] = 1;
            }
        }
    }
    for(int b = 0; b < 6; b++){
        aux2->info = pop(pilha2, 0, pilha2->topo);
        push(pilha, pilha->limite, &b, aux2->info, b);
    }
    free(pilha2);
    free(aux2);
    free(aux3);
    free(a3);
}

void ordena_por_substituicao(FILE *arq, int tam){
    int qtdParticoes = 0;
    int qtd_registros = contar_registros(arq);
    int array[tam];
    int i = 0;
    TPilha *pilha;
    pilha = (TPilha*)malloc(sizeof(TPilha));
    inicializa(pilha, 6, 0);
    cria_pilha(pilha, arq, 6);
    Aluno * menor_id;

    char nomeParticao[int(qtd_registros/tam) + 1];
    sprintf(nomeParticao, "TP01_AEDS2_CPP/files/particao%d.dat", qtdParticoes);
    FILE* p;
    if ((p = fopen(nomeParticao, "wb+")) == nullptr) {
        std::cout << "Erro ao criar arquivo de saida\n";
        return;
    }

    while(i < qtd_registros){
        //acha o menor da pilha
        menor_id = menor_da_pilha(*pilha, pilha->info, array);

        // Gravar o registro r com menor chave na partição de saída
        salva_aluno(menor_id, p);

        // Insere menor no arquivo p
        substitui(pilha, *menor_id, &i, arq, &i);

        // Caso 7
        if(verifica_congelamento(*pilha, array)){
            fclose(p);
            qtdParticoes ++;
            sprintf(nomeParticao, "TP01_AEDS2_CPP/files/particao%d.dat", qtdParticoes);
            if ((p = fopen(nomeParticao, "wb+")) == nullptr) {
                std::cout << "Erro ao criar arquivo de saida\n";
            }
            std::fill(array, array + tam, 0);
        }
    }

    FILE* arquivo = fopen("TP01_AEDS2_CPP/files/particao1.dat", "rb"); // Abrir o arquivo no modo de leitura binária
    if (arquivo == nullptr) {
        perror("Erro ao abrir o arquivo");
    }
    int valor;
    while (fread(&valor, sizeof(valor), 1, arquivo) == 1) {
        // Aqui você pode processar os dados conforme necessário
        printf("%d ", valor);
    }
    fclose(arquivo);

    free(menor_id);
    free(pilha);
}





