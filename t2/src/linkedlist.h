#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct {
  int chave;
  char *borda;
  char *cor;
  double r;
  double x;
  double y;
  double largura;
  double altura;
} REGISTRO;

/* Estrutura INFO, contem as informacoes relevantes do problema tratado */

typedef struct aux{
  REGISTRO reg;
  struct aux* prox;
} ELEMENTO;

typedef ELEMENTO* NODE;

typedef struct {
  NODE cabeca;
} LISTA;

void inicializarLista(LISTA* lista);
int tamanho(LISTA* lista);
void exibirLista(LISTA* lista);
NODE buscaSeq(LISTA* lista, int ch);
NODE buscaSeqExc(LISTA* lista, int ch, NODE* anterior);
void inserirElemento(LISTA* lista, REGISTRO reg);
int excluirElemento(LISTA* lista, int ch);
void reinicializarLista(LISTA* lista);

#endif
