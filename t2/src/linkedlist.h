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
/* Recebe uma lista para ser inicializada. */
int tamanho(LISTA* lista);
/* Recebe uma lista e retorna o seu tamanho. */
void exibirLista(LISTA* lista);
/* Recebe uma lista e exibe para o usuário suas chaves. */
NODE buscaSeq(LISTA* lista, int ch);
/* Recebe uma lista e um inteiro ch, onde o valor chave desse ch será buscado na lista. */
NODE buscaSeqExc(LISTA* lista, int ch, NODE* anterior);
void inserirElemento(LISTA* lista, REGISTRO reg);
/* Recebe uma lista e um registro, onde esse registro será inserido na lista. */
int excluirElemento(LISTA* lista, int ch);
/* Recebe uma lista e um inteiro ch, onde esse ch será o número de chave da lista que será excluído. */
void reinicializarLista(LISTA* lista);
/* Recebe uma lista e reinicializa a mesma, para poder ser reutilizada ou liberada posteriormente */

#endif
