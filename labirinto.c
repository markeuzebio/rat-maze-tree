#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "labirinto.h"
#include "arvore.h"

Labirinto* alocarLabirinto()
{
    Labirinto* labirinto = (Labirinto*) malloc(sizeof(Labirinto));

    return labirinto;
}

void desalocarLabirinto(Labirinto** labirinto)
{
    for(int i = 0 ; i < (*labirinto)->qtde_linhas ; i++)
        free((*labirinto)->desenho[i]);

    free((*labirinto)->desenho);

    free(*labirinto);
}

bool acharSaida(Labirinto* labirinto, int x, int y, No** no)
{
    Posicao proximo;
    labirinto->desenho[x][y] = '.';

    if(labirinto->qtde_linhas - 2 == x && labirinto->qtde_colunas - 1 == y)
    {
        (*no)->caminho = true;
        labirinto->desenho[x][y] = ' ';
        return true;
    }

    // Ha caminho a direita?
    if(labirinto->desenho[x][y + 1] == ' ')
    {
        proximo.x = x;
        proximo.y = y + 1;
        (*no)->dir = noCria(proximo);

        if(acharSaida(labirinto, x, y + 1, &(*no)->dir) == true)
            (*no)->caminho = true;
    }
    // Ha caminho abaixo?
    if(labirinto->desenho[x + 1][y] == ' ')
    {
        proximo.x = x + 1;
        proximo.y = y;
        (*no)->baixo = noCria(proximo);

        if(acharSaida(labirinto, x + 1, y, &(*no)->baixo) == true)
            (*no)->caminho = true;
    }
    // Ha caminho a esquerda?
    if(labirinto->desenho[x][y - 1] == ' ')
    {
        proximo.x = x;
        proximo.y = y - 1;
        (*no)->esq = noCria(proximo);

        if(acharSaida(labirinto, x, y - 1, &(*no)->esq) == true)
            (*no)->caminho = true;
    }
    // Ha caminho a acima?
    if(labirinto->desenho[x - 1][y] == ' ')
    {
        proximo.x = x - 1;
        proximo.y = y;
        (*no)->cima = noCria(proximo);

        if(acharSaida(labirinto, x - 1, y, &(*no)->cima) == true)
            (*no)->caminho = true;
    }

    labirinto->desenho[x][y] = ' ';

    if((*no)->caminho == true)
        return true;
        
    return false;
}

bool leLabirinto(Labirinto **labirinto, char *opcao)
{
    scanf("%d%d", &(*labirinto)->qtde_linhas, &(*labirinto)->qtde_colunas);
    scanf(" %c", opcao);

    (*labirinto)->desenho = (char**) malloc(sizeof(char*) * (*labirinto)->qtde_linhas);

    if((*labirinto)->desenho == NULL)
        return false;

    // Aloca, para cada linha, strings de caracteres que irao
    // compor o labirinto.
    for(int i = 0 ; i < (*labirinto)->qtde_linhas ; i++)
    {
        (*labirinto)->desenho[i] = (char*) malloc(sizeof(char) * (*labirinto)->qtde_colunas);

        if((*labirinto)->desenho[i] == NULL)
        return false;
    }

    for(int i = 0 ; i < (*labirinto)->qtde_linhas ; i++)
    {
        getchar();	// Evita que a leitura do próximo caractere
                    // seja 'bugada' pela captura de um '\n'.

        // Lê o labirinto propriamente dito.
        for(int j = 0 ; j < (*labirinto)->qtde_colunas ; j++)
        {
            scanf("%c", &(*labirinto)->desenho[i][j]);

            // Grava a posicao de onde se sai no TAD labirinto.
            if((*labirinto)->desenho[i][j] == 'M')
            {
                (*labirinto)->posicao_inicio.x = i;
                (*labirinto)->posicao_inicio.y = j;
            }
        }
    }

    return true;
}

void imprimeLabirinto(Labirinto* labirinto)
{
  for(int i = 0 ; i < labirinto->qtde_linhas ; i++)
  {
    for(int j = 0 ; j < labirinto->qtde_colunas ; j++)
    {
      printf("%c", labirinto->desenho[i][j]);
    }

    printf("\n");
  }
}
