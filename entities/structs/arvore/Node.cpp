//#include <iostream>
//#include <vector>
//#include <cstdio>
//#include <dirent.h>
//#include "../../aluno/Aluno.h"
//using namespace std;
//
//// Estrutura para representar um nó da árvore binária de perdedores
//struct Node {
//
//    Aluno* aluno;
//    Node* esquerda;
//    Node* direita;
//
//    explicit Node(Aluno* aluno) : aluno(aluno), esquerda(nullptr), direita(nullptr) {}
//};
//
//// Função para criar um novo nó com o registro de um aluno
//Node* criarNo(Aluno* aluno) {
//    return new Node(aluno);
//}
//
//// Função para construir a árvore binária de perdedores a partir de um vetor de registros
//Node* construirArvoreDePerdedores(vector<Node*> registros) {
//    if (registros.size() == 1) {
//        return registros[0];
//    }
//    vector<Node*> novaLista;
//    for (size_t i = 0; i < registros.size(); i += 2) {
//        if (i + 1 < registros.size()) {
//            // Compara os registros dos dois nós e mantém o menor na nova lista
//            if (registros[i]->aluno->id < registros[i + 1]->aluno->id) {
//                novaLista.push_back(registros[i]);
//            } else {
//                novaLista.push_back(registros[i + 1]);
//            }
//
//            // Conecta o nó da esquerda ao nó da direita
//            registros[i]->esquerda = registros[i + 1];
//            registros[i + 1]->esquerda = nullptr;
//        } else {
//            // Se o tamanho for ímpar, o último nó é passado diretamente para a nova lista
//            novaLista.push_back(registros[i]);
//        }
//    }
//    return construirArvoreDePerdedores(novaLista);
//}
//
//// Função para liberar a memória ocupada pela árvore
//void liberarArvore(Node* raiz) {
//    if (raiz) {
//        liberarArvore(raiz->esquerda);
//        liberarArvore(raiz->direita);
//        delete raiz;
//    }
//}
//
//// Função para inserir o registro do nó em um arquivo de saída
//void inserirNoArquivo(FILE* arquivoSaida, Node* no) {
//    salva_aluno(no->aluno,arquivoSaida);
//}
//
//void ordenarRegistros(FILE* arquivoSaida) {
//
//    FILE *out = fopen("alunos-2.dat","wb+");
//    vector<Node*> registros;
//    char nomeParticao[100]; // Tamanho adequado para o array
//
//    int i = 0;
//    sprintf(nomeParticao, "../files/particao%d.dat", i);
//    FILE* iu = fopen(nomeParticao, "rb");
//
//    while (iu != nullptr) {
//        // Lê o primeiro registro de cada arquivo e cria os nós folha da árvore
//        Aluno* aluno = le_aluno(iu);
//        if (aluno != nullptr) { // Verifica se o aluno foi lido corretamente
//            Node* nodo = criarNo(aluno);
//            registros.push_back(nodo);
//            printf("chegou");
//        }
//        fclose(iu);
//
//        i++;
//        sprintf(nomeParticao, "../files/particao%d.dat", i);
//        iu = fopen(nomeParticao, "rb");
//    }
//    Node* raizArvore = construirArvoreDePerdedores(registros);
//    // Ordena os registros e insere os registros no arquivo de saída
//    // Libera a memória ocupada pela árvore
//    inserirNoArquivo(out, raizArvore);
//    le_alunos(out);
//    fclose(out);
//    liberarArvore(raizArvore);
//}
//
//
//void chama_arvore(FILE* in){
//
//    printf("chegou 1");
//    std::string folderPath = "../files";
//    ordenarRegistros(in);
//}
