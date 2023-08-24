#include <cstring>
#include "intercalacao_otima.h"

void intercalacaoOtimaUnificadaFuncionarios(  FILE *out, int qtdParticoes)
{
    FILE *particoes[qtdParticoes + 1];
    Aluno *registros[qtdParticoes + 1];

    clock_t inicio = clock();
    int comparacao = 0;

    // Início da intercalação otimizada
    for (int i = 0; i < qtdParticoes; i++)
    {

        char nomeParticao[20];

        sprintf(nomeParticao, "../files/particao%d.dat", i);
        particoes[i] = fopen(nomeParticao, "rb");

        if (particoes[i] == nullptr)
        {
            printf("Erro ao abrir o arquivo da partição %s\n", nomeParticao);
            exit(1);
        }

        registros[i] = le_aluno(particoes[i]);
    }

    int grupoSize = 4;
    int numGrupos = qtdParticoes / grupoSize;

    for (int grupo = 0; grupo < qtdParticoes; grupo += 4)
    {
        Aluno *grupoRegistros[4 * qtdParticoes];
        int idx = 0;

        for (int i = grupo; i < grupo + 4 && i < qtdParticoes; i++)
        {
            while (registros[i] != nullptr)
            {
                comparacao++;
                grupoRegistros[idx++] = registros[i];
                registros[i] = le_aluno(particoes[i]);

                if (idx >= 4 * qtdParticoes)
                {
                    break;
                }
            }
        }

        for (int i = 0; i < idx - 1; i++)
        {
            for (int j = i + 1; j < idx; j++)
            {
                if (grupoRegistros[i]->id > grupoRegistros[j]->id)
                {
                    comparacao++;
                    Aluno *temp = grupoRegistros[i];
                    grupoRegistros[i] = grupoRegistros[j];
                    grupoRegistros[j] = temp;
                }
            }
        }

        char nomeParticao[100];
        char nomeDaParticao[100];
        char str1[100];
        char str2[100] = ".dat";

        sprintf(nomeDaParticao, "../files/particao%d.dat", grupo);

        int numeroParticao = qtdParticoes + 1 + grupo / 4;
        sprintf(str1, "%d", numeroParticao);
        strcat(strcpy(nomeParticao, nomeDaParticao), str1);
        strcat(strcpy(nomeParticao, nomeParticao), str2);

        FILE *filePartition = fopen(nomeParticao, "wb+");
        if (filePartition == nullptr)
        {
            printf("Erro ao criar a partição %s\n", nomeParticao);
            exit(1);
        }

        for (int i = 0; i < idx; i++)
        {
            salva_aluno(grupoRegistros[i], filePartition);
        }

        fclose(filePartition);


    }
    // Fim da intercalação otimizada

    // Início da união das partições ordenadas

    for (int i = 0; i < qtdParticoes; i++)
    {
        char nomeArqParticao[20];
        char nomeDaParticao[100];
        sprintf(nomeDaParticao, "../files/particao%d.dat", i);

        snprintf(nomeArqParticao, sizeof(nomeArqParticao), "%s%d.dat", nomeDaParticao, i);
        particoes[i] = fopen(nomeArqParticao, "rb");
        if (particoes[i] == nullptr)
        {
            printf("\nAAA: %s\n", nomeDaParticao);
            printf("Erro ao abrir o arquivo da particaoo %s\n", nomeArqParticao);
            exit(1);
        }

        registros[i] = le_aluno(particoes[i]);
    }

    while (true)
    {
        int menorCod = INT_MAX;
        int idxMenor = -1;

        for (int i = 0; i < qtdParticoes; i++)
        {
            if (registros[i] != nullptr && registros[i]->id < menorCod)
            {
                menorCod = registros[i]->id;
                idxMenor = i;
            }
        }

        if (idxMenor == -1)
        {
            break;
        }

        salva_aluno(registros[idxMenor], out);
        registros[idxMenor] = le_aluno(particoes[idxMenor]);
    }

    for (int i = 0; i < qtdParticoes; i++)
    {
        fclose(particoes[i]);
        char nomeArqParticao[20];
        snprintf(nomeArqParticao, sizeof(nomeArqParticao), "%s%d.dat", nomeArqParticao, i);
        remove(nomeArqParticao);
    }

    // Fim da união das partições ordenadas

    // Liberação de memória, finalização do processo e salvando no log
    for (int i = 0; i < qtdParticoes; i++)
    {
        free(registros[i]);
    }

    clock_t fim = clock();
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("\nTempo de execucao do metodo de intercalacao otima: %.2f segundos\n", tempo);
    printf("Numero de comparacoes: %d\n\n\n", comparacao);

}

void intercalacao_otima( FILE* out,int numParticoes) {

    FILE **particoes = (FILE **)malloc(numParticoes * sizeof(FILE *));
    auto **alunoAtual = (Aluno **)malloc(numParticoes * sizeof(Aluno *));
    int *indices = (int *)malloc(numParticoes * sizeof(int));

    FILE *saida= std::fopen("teste.dat", "wb+");

    rewind(out);

    for (int i = 0; i < numParticoes; i++) {
        char nomeParticao[20];

        sprintf(nomeParticao, "../files/particao%d.dat", i);
        particoes[i] = fopen(nomeParticao, "rb");

        if (particoes[i] == nullptr) {
            printf("Erro ao abrir a partição %s.\n", nomeParticao);

            for (int j = 0; j < i; j++) {
                fclose(particoes[j]);
            }

            free(particoes);
            free(alunoAtual);
            free(indices);

            return;
        }

        alunoAtual[i] = le_aluno(particoes[i]);

        if (alunoAtual[i] == nullptr) {
            indices[i] = -1;
        } else {
            indices[i] = i;
        }
    }

    while (true) {
        int menorIndice = -1;
        auto *menoraluno = new Aluno;

        for (int i = 0; i < numParticoes; i++) {
            if (indices[i] != -1 && (menorIndice == -1 || (alunoAtual[i]->id < menoraluno->id))) {
                menorIndice = i;
                menoraluno = alunoAtual[i];
            }
        }

        if (menorIndice == -1) {
            break;
        }

        salva_aluno(menoraluno, saida);

        free(menoraluno);
        alunoAtual[menorIndice] = le_aluno(particoes[menorIndice]);
        if (alunoAtual[menorIndice] == nullptr) {
            indices[menorIndice] = -1;
        }
    }

    for (int i = 0; i < numParticoes; i++) {
        fclose(particoes[i]);
    }
    free(particoes);
    free(alunoAtual);
    free(indices);

    fclose(saida);
}