#ifndef __ARVORE__
#define __ARVORE__

#include <stdbool.h>

#include "labirinto.h"

typedef struct no {
    Posicao posicao;
    bool caminho;
    int contador;
    struct no* dir;
    struct no* baixo;
    struct no* esq;
    struct no* cima;
} No;

No* noCria(Posicao posicao);

int marcarPercurso(Labirinto*, No*, char);

void desalocarArvore(No* no);

#endif