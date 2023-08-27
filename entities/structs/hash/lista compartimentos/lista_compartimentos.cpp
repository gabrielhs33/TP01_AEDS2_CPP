
#include <cstdio>
#include "lista_compartimentos.h"
#include <cstdarg>
#include <cassert>

void imprime_compartimentos(ListaCompartimentos *lc)
{
    int i;
    for (i = 0; i < lc->qtd; i++) {
        imprime_compartimento(lc->lista[i]);
    }
}

ListaCompartimentos *cria_compartimentos(int qtd, ...)
{
    va_list ap;
    auto *lc = (ListaCompartimentos *)  malloc(sizeof(ListaCompartimentos));
    lc->qtd = qtd;
    lc->lista = (TCompartimento **) malloc(sizeof(TCompartimento *) * (qtd));
    int i;
    va_start(ap, qtd);
    for (i = 0; i < qtd; i++) {
        lc->lista[i] = va_arg(ap, TCompartimento *);
    }
    va_end(ap);
    return lc;
}

void salva_compartimentos(char *nome_arquivo, ListaCompartimentos *lc)
{
    FILE *out = fopen(nome_arquivo, "wb");
    int i;
    for (i = 0; i < lc->qtd; i++) {
        salva_compartimento(lc->lista[i], out);
    }
    fclose(out);
}

ListaCompartimentos * le_compartimentos(char *nome_arquivo)
{
    int qtd = 0;
    auto *lc = (ListaCompartimentos *)  malloc(sizeof(ListaCompartimentos));
    FILE *in = fopen(nome_arquivo, "rb");
    if (in != nullptr) {
        TCompartimento *compartimento = nullptr;
        while((compartimento = le_compartimento(in)) != nullptr) {
            qtd += 1;
            free(compartimento);
        }
        fseek(in, 0, SEEK_SET);
        lc->qtd = qtd;
        lc->lista = (TCompartimento **) malloc(sizeof(TCompartimento *) * (qtd));
        qtd = 0;
        while((compartimento = le_compartimento(in)) != nullptr) {
            lc->lista[qtd++] = compartimento;
        }
        fclose(in);
    } else {
        lc->qtd = 0;
        lc->lista = nullptr;
    }
    return lc;
}

int cmp_compartimentos(ListaCompartimentos *c1, ListaCompartimentos *c2)
{
    if (c1->qtd != c2->qtd) {
        return 0;
    }
    int i;
    for (i = 0; i < c1->qtd; i++) {
        if (!cmp_compartimento(c1->lista[i], c2->lista[i])) {
            return 0;
        }
    }
    return 1;
}

void libera_compartimentos(ListaCompartimentos *lc)
{
    int i;
    for (i = 0; i < lc->qtd; i++) {
        free(lc->lista[i]);
    }
    free(lc->lista);
    free(lc);
}

void adcn_compartimento(ListaCompartimentos *lc, int prox){
    assert(lc != nullptr && "Lista Inválida");

    auto **novo_lc = (CompartimentoHash **) calloc((lc->qtd + 1), sizeof(CompartimentoHash *));
    assert(novo_lc != nullptr && "Falha na criação");
    int i = 0;

    for(i = 0; i < lc->qtd; i++){
        novo_lc[i] = lc->lista[i];
        lc->lista[i] = nullptr;
    }

    novo_lc[lc->qtd] = (CompartimentoHash *) malloc(sizeof(CompartimentoHash *));
    novo_lc[lc->qtd]->prox = prox;

    free(lc->lista);
    lc->lista = novo_lc;
    lc->qtd++;
}