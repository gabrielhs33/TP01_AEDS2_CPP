#include "arvore_vencedores.h"

ArvoreVencedores *cria_no(Aluno *a, int num_arq){

    auto *tree =(ArvoreVencedores*) malloc(sizeof(ArvoreVencedores));
    tree->aluno = a;
    tree->num_arq = num_arq;
    tree->left = nullptr;
    tree->right = nullptr;
    return tree;
}

ArvoreVencedores *cria_arvore(ArvoreVencedores *r, ArvoreVencedores *l){

    if(r == nullptr || l == nullptr) return nullptr;
    auto *res =(ArvoreVencedores*) malloc(sizeof(ArvoreVencedores));
    ArvoreVencedores *aux = (r->aluno->id < l->aluno->id)? r:l;
    res->aluno = aux->aluno;
    res->num_arq = aux->num_arq;
    res->left = r;
    res->right = l;
    printf("\ntestanto##########################################");
    imprime(res->aluno);
    imprime(res->left->aluno);
    return res;
}

void substituir(Aluno *a, Aluno *a_subst, ArvoreVencedores *tree){

    if(!tree->right && !tree->left){
        tree->aluno = a_subst;
        return;
    }
    if(tree->right->aluno == a) substituir(a, a_subst, tree->right);
    if(tree->left->aluno == a) substituir(a, a_subst, tree->left);
    ArvoreVencedores *aux = (tree->right->aluno->id < tree->left->aluno->id)? tree->right:tree->left;

    tree->aluno = aux->aluno;
    tree->num_arq = aux->num_arq;
}

void intercalacao(int qtd, FILE *out){

    char nomeParticao[100];
    int j, k, space;
    FILE *files[qtd];
    for (j = 0; j < qtd; j++) {
        sprintf(nomeParticao, "../files/particao%d.dat", j);
        files[j] = fopen(nomeParticao, "rb");
    }

    arvore_vencedores *av[qtd];
    for (j = 0; j < qtd; j++) {
        Aluno *a = le_aluno(files[j]);
        av[j] = cria_no(a, j);
    }
    k = 2;
    space = 1;
    while (space < qtd) {
        for (j = 0; j + space < qtd; j += k) {
            av[j] = cria_arvore(av[j], av[j + space]);
        }
        k *= 2;
        space = k >> 1;
    }
    ArvoreVencedores *venc = av[0];
    // intercala partições

    while (venc->aluno->id != INT_MAX ) {
        salva_aluno(venc->aluno, out);
        Aluno *a = le_aluno(files[venc->num_arq]);
        if (a == nullptr){

            break;
        }
        substituir(venc->aluno, a, venc);
    }
    salva_aluno(venc->aluno,out);
    le_alunos(out);
}