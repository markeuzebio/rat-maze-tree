#ifndef ____LABIRINTO____
#define ____LABIRINTO____

#include <stdbool.h>

struct no;

typedef struct posicao {
  int x;
  int y;
} Posicao;

typedef struct labirinto {
  int qtde_linhas;
  int qtde_colunas;
  char** desenho;
  Posicao posicao_inicio;
} Labirinto;

Labirinto* alocarLabirinto();

void desalocarLabirinto(Labirinto** labirinto);

bool leLabirinto(Labirinto **labirinto, char *opcao);

bool acharSaida(Labirinto*, int, int, struct no**);

void imprimeLabirinto(Labirinto*);

#endif
