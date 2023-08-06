#include <iostream>
#include "Pilha.h"

void inicializa(TPilha *pilha, int lim, int topo){
    pilha->topo = topo;
    pilha->limite = lim;
}

int pilha_cheia(int lim, int topo) {

    if (topo == lim)
        return 1;
    else
        return 0;
}

int pilha_vazia(int base, int topo) {
    if (topo == 0)
        return 1; //pilha vazia
    else
        return 0; //pilha tem pelo menos 1 elemento
}

void push(TPilha *pilha, int lim, int *topo, Aluno *info, int p){
    if (pilha_cheia(lim, *topo)) {
        std::cout<< "\n\nPilha Cheia\n\n"<<std::endl;
    }
    else {
        //faz a inserção
        *topo = *topo + 1;
        pilha[*topo].info = info;
        pilha[*topo].p = p;
    }
}

Aluno *pop(TPilha *pilha, int base, int *topo) {

    if (pilha_vazia(base, *topo)) {
        return nullptr;
    }
    else {
        //faz a remoção
        Aluno *info = pilha[*topo].info;
        *topo = *topo - 1;
        return info;
    }
}

Aluno *peek_func(TPilha *pilha, int base, const int *topo) {
    if (pilha_vazia(base, *topo))
        return nullptr;
    else {
        //faz consulta
        return pilha[*topo].info;
    }
}

int peek_fp(TPilha *pilha, int base, const int *topo) {

    if (pilha_vazia(base, *topo))
        return 0;
    else {
        //faz consulta
        return pilha[*topo].p;
    }
}

void imprime_pilha(TPilha *pilha, const int *topo) {

    printf("\nEstado atual da Pilha:\n");
    for (int i = *topo; i >= 0; i--) {
        printf("posição [%d]: %d\n", i, pilha[i].info->id);
    }
    printf("\n");
}

void cria_pilha_particao(TPilha *pilha, FILE *arq, int nAluno, int *vetTopo){

    int lim=nAluno-1;

    rewind(arq);
    int i = nAluno-1;
    fseek(arq,  0 * sizeof (Aluno), SEEK_SET);
    if(arq != nullptr) {
        int aux = 1;
        do{
            fseek(arq, (i) * tamanho(), SEEK_SET);
            Aluno *aluno = le_aluno(arq);
            if(aluno){

                push(pilha,lim,vetTopo,aluno, i);
                i--;
            }else aux = 0;
        }while(aux);
    }
    else printf("Erro ao abrir arquivo\n");

    //imprime_pilha(pilha,vetTopo);
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
        aux = pop(&pilha, 0, &pilha.topo);
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
        aux2->info = pop(pilha, 0, &pilha->topo);
        if(aux2->info->id != r.id){
            aux2->info = pop(pilha, 0, &pilha->topo);
            push(pilha2, pilha2->limite, &i, aux2->info, i);
        }else {
            *p = *p + 1;
            aux2->info = pop(pilha, 0, &pilha->topo);
            aux3->info = le_aluno(arq);
            a3 = aux3->info;
            push(pilha2, pilha2->limite, &i, aux3->info, i);
            if(a3->id < r.id){
                array_congelados[a3->id] = 1;
            }
        }
    }
    for(int b = 0; b < 6; b++){
        aux2->info = pop(pilha2, 0, &pilha2->topo);
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