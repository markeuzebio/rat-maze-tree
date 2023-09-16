#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "labirinto.h"
#include "arvore.h"

int main(int argc, char** argv)
{
    int contador;
    char opcao;
    Labirinto* labirinto;
    No* raiz;
    Posicao posicao;

    labirinto = alocarLabirinto();

    if(labirinto == NULL)
        return 0;

    if(!leLabirinto(&labirinto, &opcao))
        return 0;

    posicao.x = labirinto->posicao_inicio.x;
    posicao.y = labirinto->posicao_inicio.y;
    
    raiz = noCria(posicao);

    if(raiz == NULL)
        exit(1);

    if(acharSaida(labirinto, labirinto->posicao_inicio.x, labirinto->posicao_inicio.y, &raiz) != false)
    {
        contador = marcarPercurso(labirinto, raiz, opcao);
        printf("%d\n", contador);
        imprimeLabirinto(labirinto);
    }
    else
        printf("EPIC FAIL!\n");

    desalocarArvore(raiz);
    desalocarLabirinto(&labirinto);
}
