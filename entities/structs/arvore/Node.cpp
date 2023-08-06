#include <iostream>
#include <vector>
#include <cstdio>
#include "../../aluno/Aluno.h"
using namespace std;

// Estrutura para representar um nó da árvore binária de perdedores
struct Node {
    Aluno* aluno; // Alteração aqui
    Node* esquerda;
    Node* direita;

    explicit Node(Aluno* aluno) : aluno(aluno), esquerda(nullptr), direita(nullptr) {}
};

// Função para criar um novo nó com o registro de um aluno
Node* criarNo(Aluno* aluno) {
    return new Node(aluno);
}

// Função para construir a árvore binária de perdedores a partir de um vetor de registros
Node* construirArvoreDePerdedores(vector<Node*>& registros) {
    if (registros.size() == 1) {
        return registros[0];
    }

    vector<Node*> novaLista;
    for (size_t i = 0; i < registros.size(); i += 2) {
        if (i + 1 < registros.size()) {
            // Compara os registros dos dois nós e mantém o menor na nova lista
            if (registros[i]->aluno->id < registros[i + 1]->aluno->id) {
                novaLista.push_back(registros[i]);
            } else {
                novaLista.push_back(registros[i + 1]);
            }

            // Conecta o nó da esquerda ao nó da direita
            registros[i]->esquerda = registros[i + 1];
            registros[i + 1]->esquerda = nullptr;
        } else {
            // Se o tamanho for ímpar, o último nó é passado diretamente para a nova lista
            novaLista.push_back(registros[i]);
        }
    }

    return construirArvoreDePerdedores(novaLista);
}

// Função para liberar a memória ocupada pela árvore
void liberarArvore(Node* raiz) {
    if (raiz) {
        liberarArvore(raiz->esquerda);
        liberarArvore(raiz->direita);
        delete raiz;
    }
}

// Função para inserir o registro do nó em um arquivo de saída
void inserirNoArquivo(FILE* arquivoSaida, Node* no) {
    fprintf(arquivoSaida, "%d\n", no->aluno->id);
}

// Função que realiza a ordenação dos registros em um único arquivo de saída
void ordenarRegistros(vector<FILE*>& arquivos, FILE* arquivoSaida) {
    vector<Node*> registros;

    // Lê o primeiro registro de cada arquivo e cria os nós folha da árvore
    for (size_t i = 0; i < arquivos.size(); i++) {
        Aluno *aluno;
        if (fscanf(arquivos[i], "%d", &aluno->id) != 1) {
            cerr << "Erro ao ler registro do arquivo_" << i << ".dat" << endl;
            continue;
        }
        registros.push_back(criarNo(aluno));
    }

    // Ordena os registros e insere os registros no arquivo de saída
    Node* raizArvore = construirArvoreDePerdedores(registros);
    inserirNoArquivo(arquivoSaida, raizArvore);

    // Libera a memória ocupada pela árvore
    liberarArvore(raizArvore);
}
