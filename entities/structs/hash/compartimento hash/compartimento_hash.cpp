#include "compartimento_hash.h"
#include <cstdlib>
#include <cstdio>


void imprime_compartimento(TCompartimento *compartimento)
{
    printf("%d\n", compartimento->prox);
}

TCompartimento *compartimento_hash(int prox)
{
    auto *compartimento = (TCompartimento *) malloc(sizeof(TCompartimento));
    compartimento->prox = prox;
    return compartimento;
}


void salva_compartimento(TCompartimento *compartimento, FILE *out)
{
    fwrite(&compartimento->prox, sizeof(int), 1, out);
}

TCompartimento *le_compartimento(FILE *in)
{
    auto *compartimento = (TCompartimento *) malloc(sizeof(TCompartimento));
    if (0 >= fread(&compartimento->prox, sizeof(int), 1, in)) {
        free(compartimento);
        return nullptr;
    }
    return compartimento;
}

int cmp_compartimento(TCompartimento *c1, TCompartimento *c2)
{
    if (c1 == nullptr) {
        return (c2 == nullptr);
    }
    if (c1->prox != c2->prox) {
        return 0;
    }
    return 1;
}

int tamanho_compartimento()
{
    return sizeof(int); // prox
}