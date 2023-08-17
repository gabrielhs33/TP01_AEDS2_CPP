#include "intercalacao_otima.h"

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