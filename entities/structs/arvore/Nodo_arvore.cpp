#include "Nodo_arvore.h"
#include <vector>
#include <algorithm>
#include <cstdio>
#include <climits>

using namespace std;

vector<Nodo_arvore*> cria_folhas(FILE* file) {
    vector<Nodo_arvore*> leafNodo_arvores;
    int id;
    char nome[100];

    while (fscanf(file, "%d %s", &id, nome) == 2) {
        //leafNodo_arvores.push_back(new Nodo_arvore(Aluno(id, nome)));
    }

    return leafNodo_arvores;
}

Nodo_arvore* cria_nodo_vencedor(Nodo_arvore* leftNode, Nodo_arvore* rightNode) {

    Aluno *minAluno = (leftNode->aluno->id < rightNode->aluno->id) ? leftNode->aluno : rightNode->aluno;
    auto* winnerNode = new Nodo_arvore(minAluno);
    winnerNode->left = leftNode;
    winnerNode->right = rightNode;
    return winnerNode;
}

Nodo_arvore* faz_arvore_vencedores(FILE* file) {

    vector<Nodo_arvore*> leafNodo_arvores = cria_folhas(file);

    while (leafNodo_arvores.size() > 1) {
        vector<Nodo_arvore*> winnerNodo_arvores;
        for (int i = 0; i < leafNodo_arvores.size(); i += 2) {
            Nodo_arvore* leftNodo_arvore = leafNodo_arvores[i];
            Nodo_arvore* rightNodo_arvore = (i + 1 < leafNodo_arvores.size()) ? leafNodo_arvores[i + 1] : nullptr;
            winnerNodo_arvores.push_back(cria_nodo_vencedor(leftNodo_arvore, rightNodo_arvore));
        }
        leafNodo_arvores = winnerNodo_arvores;
    }

    return leafNodo_arvores[0];
}

// Função para extrair o valor mínimo da raiz e inserir o próximo registro correspondente no arquivo de saída
Aluno* retira_min(Nodo_arvore*& root, FILE* file) {

    Aluno *minValue = root->aluno;
    int id;
    char nome[50];

    if (le_aluno(file)) {
        root->aluno->id = id;
        root->aluno->nome = nome;
    } else {
        root->aluno->id = INT_MAX; // Define um ID máximo para o nó vazio
    }

    return minValue;
}