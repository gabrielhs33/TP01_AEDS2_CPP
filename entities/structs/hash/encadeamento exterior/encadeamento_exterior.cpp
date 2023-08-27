#include "encadeamento_exterior.h"

void cria_hash(char *nome_arquivo_hash, int tam)
{
    ListaCompartimentos *lc = cria_compartimentos(0);

    for(int i = 0; i < tam; i++){
        adcn_compartimento(lc, -1);
    }

    salva_compartimentos(nome_arquivo_hash, lc);
    libera_compartimentos(lc);
}

int busca(int cod_aluno, char *nome_arquivo_hash, char *nome_arquivo_dados)
{
/*
	 *	Busca por um registro de chave x:
	 *	Calcular o endereço aplicando a função h(x)
	 *	Percorrer a lista encadeada associada ao endereço
	 *	Comparar a chave de cada nó da lista encadeada com a chave
	 *	x, até encontrar o nó desejado
	 *	Se final da lista for atingido, registro não está lá
	 *
	 * */

    Aluno *al;

    int end = cod_aluno % 7,
            rc = -1,
            seguinte = 0;

    FILE *arq_hash = fopen(nome_arquivo_hash, "rb");

    rc = fseek(arq_hash, (end) * tamanho_compartimento(), SEEK_SET);
    assert(rc == 0 && "Falha no seek\n");

    FILE *arq_alunos = fopen(nome_arquivo_dados, "rb");

    CompartimentoHash *lido = le_compartimento(arq_hash);

    //endereço no arquivo = lido->prox
    seguinte = lido->prox;

    while(seguinte != -1){

        rc = fseek(arq_alunos, seguinte * tamanho(), SEEK_SET);
        assert(rc == 0 && "Falha no seek\n");

        al = le_aluno(arq_alunos);
        if(al->id == cod_aluno){
            if(al->flag == OCUPADO){
                fclose(arq_hash);
                fclose(arq_alunos);
                free(al);
                free(lido);
                return seguinte;
            }
        }
        seguinte = al->prox;
        free(al);
    }

    free(lido);
    fclose(arq_hash);
    fclose(arq_alunos);
    return -1;
}
int insere(int cod_cli, char *nome_cli, char *nome_arquivo_hash, char *nome_arquivo_dados, int num_registros) {
    printf("entrou");
    Aluno *cl = nullptr, *atual = nullptr;

    //	1. Calcular o endereço aplicando a função h(x)
    int end = cod_cli % 7,
            end_escrita = num_registros * tamanho(),
            rc = -1,
            seguinte = 0,
            ultimo = 0;

    FILE *arq_hash = fopen(nome_arquivo_hash, "r+b");
    FILE *arq_clientes = fopen(nome_arquivo_dados, "r+b");

    CompartimentoHash *lido;

    /* 1ª tentativa: Obtenção direta do registro via compartimento hash */

    //cursor na tabela de dispersão posicionado
    rc = fseek(arq_hash, end * tamanho_compartimento(), SEEK_SET);
    assert(rc == 0 && "Falha no seek\n");

    lido = le_compartimento(arq_hash);

    //endereço no arquivo de clientes = lido->prox
    seguinte = lido->prox;

    /*
     *  1ª Iteração: fim da 1ª tentativa
     * 	2ª iteração em diante: 2ª tentativa,
     * 		que é a busca do registro na lista de tratamento das colisões
     *
     * */

    while(seguinte != -1){
        rc = fseek(arq_clientes, seguinte * tamanho(), SEEK_SET);
        assert(rc == 0 && "Falha no seek\n");

        atual = le_aluno(arq_clientes);

        if(atual->id == cod_cli){
            if(atual->flag == OCUPADO){
                fclose(arq_clientes);
                fclose(arq_hash);
                free(atual);
                free(lido);
                //Já existe, erro.
                return -1;
            }
        }

        if(atual->flag == LIBERADO){
            //Se um dos registros com chave congruente % 7 está liberado,
            //esta é a posição para inserir
            end_escrita = seguinte * tamanho();
            seguinte = atual->prox;
            free(atual);
            break;
        }

        ultimo = seguinte;
        seguinte = atual->prox;

        free(atual);
    }

    /* Escrita do registro inserido*/

    if(atual == nullptr){
        /*Atualização do campo próximo no compartimento hash, caso a lista não exista*/
        rc = fseek(arq_clientes, end_escrita, SEEK_SET);
        assert(rc == 0 && "Falha no seek\n");

        cl = aluno(cod_cli, nome_cli,"*****","#####",0.0,OCUPADO, -1 );
        salva_aluno(cl, arq_clientes);

        lido->prox = end_escrita / tamanho();

        rc = fseek(arq_hash, end * tamanho_compartimento(), SEEK_SET);
        assert(rc == 0 && "Falha no seek\n");

        salva_compartimento(lido, arq_hash);
    } else {
        /*Escrita do registro sendo inserido*/
        rc = fseek(arq_clientes, end_escrita, SEEK_SET);
        assert(rc == 0 && "Falha no seek\n");

        cl = aluno(cod_cli, nome_cli,"*****","#####",0.0, OCUPADO,seguinte);
        salva_aluno(cl, arq_clientes);

        /*Escrita do registro anterior, com seu prox atualizado*/
        rc = fseek(arq_clientes, ultimo * tamanho(), SEEK_SET);
        assert(rc == 0 && "Falha no seek\n");

        atual = le_aluno(arq_clientes);
        atual->prox = end_escrita / tamanho();
        atual->flag = OCUPADO;

        rc = fseek(arq_clientes, ultimo * tamanho(), SEEK_SET);
        assert(rc == 0 && "Falha no seek\n");

        salva_aluno(atual, arq_clientes);
        free(atual);
    }

    fclose(arq_hash);
    fclose(arq_clientes);

    free(cl);
    free(lido);

    return end_escrita / tamanho();
}

int exclui(int cod_aluno, char *nome_arquivo_hash, char *nome_arquivo_dados)
{
    printf("entrou");
    int end = busca(cod_aluno, nome_arquivo_hash, nome_arquivo_dados),
            rc = -1;

    FILE *arq_alunos;
    Aluno *al;

    if(end != -1){
        arq_alunos = fopen(nome_arquivo_dados, "r+b");

        rc = fseek(arq_alunos, end * tamanho(), SEEK_SET);
        assert(rc == 0 && "Falha no seek\n");

        al = le_aluno(arq_alunos);
        al->flag = LIBERADO;

        rc = fseek(arq_alunos, end * tamanho(), SEEK_SET);
        assert(rc == 0 && "Falha no seek\n");

        salva_aluno(al, arq_alunos);

        fclose(arq_alunos);
        free(al);
    }

    return end;
}