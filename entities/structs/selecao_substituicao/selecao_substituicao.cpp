#include "selecao_substituicao.h"
#include <cstring>
#include <limits>

//void mostrar_congelados(int congs[]){
//    int i = 0;
//    for(i = 0; i < sizeof(congs)/sizeof(int); i++) printf("%d ", congs[i]);
//    printf("\n");
//}

int existe_nao_congelado(int congelados[], int M){

    for(int i = 0; i < M; i++){
        if(!congelados[i]) return 1;
    }
    return 0;
}

/*int substituirAluno(ListaAlunos *cls, int pos, FILE *fnt){
	Aluno *cl = le_Aluno(fnt);

}*/

void substituirRegistro(Aluno *dest, Aluno *fnt){
    strcpy(dest->nome, fnt->nome);
    dest->id = fnt->id;
}

void selecao_com_substituicao(FILE* in, int M){

    int qtdParticoes = 0;
    int qtd_registros = contar_registros(in);
    char nomeParticao[int(qtd_registros/M) + 1];
    rewind(in);

    int  m = 0, gravado = 0;
    Tlista_aluno *list = nullptr;
    int congelados[M];
    Aluno *menor = nullptr, *lido;
    memset(congelados, 0, sizeof(congelados));

    FILE *out;

    //	1. Ler M registros do arquivo para a memória
    ler_aluno_lista(in, &list, M, congelados);
    sprintf(nomeParticao, "../files/particao%d.dat", qtdParticoes);
    for(int j = 0; j < 10; j++){

        if(existe_nao_congelado(congelados, M)){
            out = fopen(nomeParticao, "wb+");
            printf("Criado arquivo %d", qtdParticoes);
        }
        else continue;
        while(existe_nao_congelado(congelados, M)){

            //	2. Selecionar, no array em memória, o registro r com menor chave
            int menor_val = INT_MAX;
            for(int i = 0; i < M; i++){
                if(congelados[i]) continue;
                if(list->lista[i]->id <= menor_val){
                    menor_val = list->lista[i]->id;
                    menor = list->lista[i];
                    m = i;
                }
            }
            //	3. Gravar o registro r na partição de saída
            printf("\n%d", menor->id);
            salva_aluno(menor, out);
            //	4. Substituir, no array em memória, o registro r pelo próximo registro do arquivo de entrada
            //if(list->lista[m] != NULL){
            gravado = menor->id;
            lido = le_aluno(in);
            if(lido != nullptr){
                substituirRegistro(list->lista[m], lido);
            } else {
                list->lista[m] = nullptr;
            }

            if(lido == nullptr || lido->id < gravado){
                //	5. Caso a chave deste último seja menor do que a chave recém gravada,
                //	considerá-lo congelado e ignorá-lo no restante do processamento
                congelados[m] = 1;
            }
            if(lido != nullptr)
                free(lido);

            //	6. Caso existam em memória registros não congelados, voltar ao passo 2
        }
        /*	7. Caso contrário:
            - fechar a partição de saída*/
//        if(gravado != INT_MAX){
//            salva_aluno(aluno(INT_MAX, "","","",0), out);
//        }
        fclose(out);
        //	- descongelar os registros congelados
        for(int i = 0; i < M; i++)
            if(list->lista[i] != nullptr) congelados[i] = 0;
        //	- abrir nova partição de saída
        qtdParticoes++;
        sprintf(nomeParticao, "../files/particao%d.dat", qtdParticoes);
    }
    int i = 0;
    sprintf(nomeParticao, "../files/particao%d.dat",i);
    FILE* iu = fopen(nomeParticao,"rb");
    le_alunos(iu);

    while(iu){

        i++;
        sprintf(nomeParticao, "../files/particao%d.dat",i);
        FILE* iu = fopen(nomeParticao,"rb");
        le_alunos(iu);
        fclose(iu);
        printf("///");
    }
    fclose(in);
    libera_aluno(list);
}