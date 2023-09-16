#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "arvore.h"
#include "labirinto.h"

typedef struct celula {
  Posicao posicao;
  struct celula* proximo;
} Celula;

typedef struct lista {
    Celula* cabeca;
    Celula* ultimo;
} Lista;

Celula* alocarCelula()
{
  Celula* nova_celula = (Celula*) malloc(sizeof(Celula));

  if(nova_celula == NULL)
    exit(1);

  nova_celula->proximo = NULL;

  return nova_celula;
}

bool buscarPosicao(Lista* lista, Posicao posicao)
{
    Celula* auxiliar = lista->cabeca->proximo;

    while(auxiliar != NULL)
    {
        if(auxiliar->posicao.x == posicao.x && auxiliar->posicao.y == posicao.y)
            return true;

        auxiliar = auxiliar->proximo;
    }

    return false;
}

void inserirPosicaoFim(Lista* lista, Posicao posicao)
{
    Celula* nova_posicao = alocarCelula();
    nova_posicao->posicao = posicao;

    lista->ultimo->proximo = nova_posicao;
    lista->ultimo = nova_posicao;
}

void iniciarLista(Lista* lista)
{
    lista->cabeca = alocarCelula();
    lista->ultimo = lista->cabeca;
}

No* noCria(Posicao posicao)
{
    No* no = (No*) malloc(sizeof(No));

    if(no != NULL)
    {
        no->posicao = posicao;
        no->dir = no->baixo = no->esq = no->cima = NULL;
        no->caminho = false;
        no->contador = 0;
    }

    return no;
}


void marcarLabirinto(Labirinto* labirinto, No* raiz)
{
    No* maior;

    labirinto->desenho[labirinto->posicao_inicio.x][labirinto->posicao_inicio.y] = 'M';

    while(!(labirinto->qtde_linhas - 2 == raiz->posicao.x && labirinto->qtde_colunas - 1 == raiz->posicao.y))
    {
        maior = raiz;

        if(raiz->dir != NULL)
        {
            maior = raiz->dir;

            if(raiz->baixo != NULL && raiz->baixo->contador > maior->contador)
                maior = raiz->baixo;
            if(raiz->esq != NULL && raiz->esq->contador > maior->contador)
                maior = raiz->esq;
            if(raiz->cima != NULL && raiz->cima->contador > maior->contador)
                maior = raiz->cima;
        }
        else if(raiz->baixo != NULL)
        {
            maior = raiz->baixo;

            if(raiz->dir != NULL && raiz->dir->contador > maior->contador)
                maior = raiz->dir;
            if(raiz->esq != NULL && raiz->esq->contador > maior->contador)
                maior = raiz->esq;
            if(raiz->cima != NULL && raiz->cima->contador > maior->contador)
                maior = raiz->cima;
        }
        else if(raiz->esq != NULL)
        {
            maior = raiz->esq;

            if(raiz->dir != NULL && raiz->dir->contador > maior->contador)
                maior = raiz->dir;
            if(raiz->baixo != NULL && raiz->baixo->contador > maior->contador)
                maior = raiz->baixo;
            if(raiz->cima != NULL && raiz->cima->contador > maior->contador)
                maior = raiz->cima;
        }
        else if(raiz->cima != NULL)
        {
            maior = raiz->cima;

            if(raiz->dir != NULL && raiz->dir->contador > maior->contador)
                maior = raiz->dir;
            if(raiz->baixo != NULL && raiz->baixo->contador > maior->contador)
                maior = raiz->baixo;
            if(raiz->esq != NULL && raiz->esq->contador > maior->contador)
                maior = raiz->cima;
        }

        raiz = maior;
        labirinto->desenho[maior->posicao.x][maior->posicao.y] = '.';
    }
}

void desalocarArvore(No* no)
{
    if(no != NULL)
    {
        desalocarArvore(no->dir);
        desalocarArvore(no->baixo);
        desalocarArvore(no->esq);
        desalocarArvore(no->cima);

        free(no);
    }
}

int rastrearMaiorPercurso(Labirinto* labirinto, No* raiz)
{
    if(raiz->posicao.x == labirinto->qtde_linhas - 2 && raiz->posicao.y == labirinto->qtde_colunas - 1)
        return 0;
    else
    {
        int dir, baixo, esq, cima;

        dir = baixo = esq = cima = -1;

        if(raiz->dir != NULL && raiz->dir->caminho == true)
            dir = rastrearMaiorPercurso(labirinto, raiz->dir);
        if(raiz->baixo != NULL && raiz->baixo->caminho == true)
            baixo = rastrearMaiorPercurso(labirinto, raiz->baixo);
        if(raiz->esq != NULL && raiz->esq->caminho == true)
            esq = rastrearMaiorPercurso(labirinto, raiz->esq);
        if(raiz->cima != NULL && raiz->cima->caminho == true)
            cima = rastrearMaiorPercurso(labirinto, raiz->cima);

        if(dir >= baixo && dir >= esq && dir >= cima)
            raiz->contador = dir + 1;
        else if(baixo >= esq && baixo >= cima)
            raiz->contador = baixo + 1;
        else if(esq >= cima)
            raiz->contador = esq + 1;
        else
            raiz->contador = cima + 1;
    }

    return raiz->contador;
}

int rastrearMenorPercurso(Labirinto* labirinto, No* raiz)
{
    int contador = 0;

    while(!(labirinto->qtde_linhas - 2 == raiz->posicao.x && labirinto->qtde_colunas - 1 == raiz->posicao.y))
    {
        if(raiz->dir != NULL && raiz->dir->caminho == true)
        {
            desalocarArvore(raiz->baixo);
            desalocarArvore(raiz->esq);
            desalocarArvore(raiz->cima);

            raiz->baixo = raiz->esq = raiz->cima = NULL;

            raiz = raiz->dir;
        }
        else if(raiz->baixo != NULL && raiz->baixo->caminho == true)
        {
            desalocarArvore(raiz->dir);
            desalocarArvore(raiz->esq);
            desalocarArvore(raiz->cima);

            raiz->dir = raiz->esq = raiz->cima = NULL;

            raiz = raiz->baixo;
        }
        else if(raiz->esq != NULL && raiz->esq->caminho == true)
        {
            desalocarArvore(raiz->dir);
            desalocarArvore(raiz->baixo);
            desalocarArvore(raiz->cima);

            raiz->dir = raiz->baixo = raiz->cima = NULL;

            raiz = raiz->esq;
        }
        else
        {
            desalocarArvore(raiz->dir);
            desalocarArvore(raiz->baixo);
            desalocarArvore(raiz->esq);

            raiz->dir = raiz->baixo = raiz->esq = NULL;

            raiz = raiz->cima;
        }

        contador++;
    }

    return contador;
}

int marcarPercurso(Labirinto* labirinto, No* raiz, char opcao)
{
    int contador;

    if(opcao == 'g')
        contador = rastrearMaiorPercurso(labirinto, raiz);
    else if(opcao == 's')
        contador = rastrearMenorPercurso(labirinto, raiz);

    marcarLabirinto(labirinto, raiz);

    return contador;
}