#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "linkedlist.h"


/* Inicializa a Lista */
void inicializarLista(LISTA* lista) {
 lista->cabeca = NULL;
}

/* Retorna o tamanho da Lista; */
int tamanho(LISTA* lista) {
  NODE endereco = lista->cabeca;
  int tamanho = 0;
  while(endereco != NULL) {
    tamanho++;
    endereco = endereco->prox;
  }
  return tamanho;
}

/* Exibe os elemento da Lista; */
void exibirLista(LISTA* lista) {
  NODE endereco = lista->cabeca;
  printf("\nLista: \n");
  while(endereco != NULL) {
    printf("%s\n", endereco->reg.id);
    endereco = endereco->prox;
  }
  printf("\n");
}

/* Busca um elemento na Lista; */
NODE buscaSeq(LISTA* lista, int ch) {
  NODE pos = lista->cabeca->prox;
  lista->cabeca->reg.chave = ch;
  while(pos->reg.chave != ch) pos = pos->prox;
  if(pos !=lista->cabeca) return pos;
  return NULL;
}

/* Busca auxiliar; */
NODE buscaSeqExc(LISTA* lista, int ch, NODE* anterior) {
  NODE atual = lista->cabeca;
  *anterior = NULL;
  while((atual != NULL) && (atual->reg.chave < ch)) { /*(strcmp(atual->reg.id, ch) != 0)*/
    *anterior = atual;
    atual = atual->prox;
  }
  if (atual != NULL && atual->reg.chave == ch) return atual;
  return NULL;
}

NODE buscaSeqExc2(LISTA* lista, char* ch, NODE* anterior) {
  NODE atual = lista->cabeca;
  *anterior = NULL;
  while((atual != NULL) && (strcmp(atual->reg.id, ch) != 0)) { /*(strcmp(atual->reg.id, ch) != 0)*/
    *anterior = atual;
    atual = atual->prox;
  }
  if (atual != NULL && (strcmp(atual->reg.id, ch) == 0)) return atual;
  return NULL;
}

/* Insere um elemento na Lista */
void inserirElemento(LISTA* lista, REGISTRO reg) {
  NODE anterior, i;
  i = buscaSeqExc(lista, reg.chave, &anterior);
  if(i != NULL) printf("Elemento ja existe!!\n");
  i  = (NODE) malloc(sizeof(ELEMENTO));
  i->reg = reg;
  if(anterior == NULL) {
    i->prox = lista->cabeca;
    lista->cabeca = i;
  }
  else {
    i->prox = anterior->prox;
    anterior->prox = i;
  }
}
/* Insere um elemento na Lista cidade */
void inserirQUAHISERA(LISTA* cidade, REGISTRO reg) {
  NODE anterior, i;
  i = buscaSeqExc2(cidade, reg.id, &anterior);
  if(i != NULL) printf("Elemento ja existe!!\n");
  i = (NODE) malloc(sizeof(ELEMENTO));
  i->reg = reg;
  if(anterior == NULL) {
    i->prox = cidade->cabeca;
    cidade->cabeca = i;
  }
  else {
    i->prox = anterior->prox;
    anterior->prox = i;
  }

}

/* Exclui um elemento da Lista */
void excluirElemento(LISTA* lista, int ch) {
  NODE anterior, i;
  i = buscaSeqExc(lista, ch, &anterior);
  if(i == NULL) printf("Elemento nao encontrado!\n");
  if(anterior == NULL) lista->cabeca = i->prox;
  else anterior->prox = i->prox;
  free(i);
}

void excluirElemento2(LISTA* lista, char* ch) {
  NODE anterior, i;
  i = buscaSeqExc2(lista, ch, &anterior);
  if(i == NULL) printf("Elemento nao encontrado!\n");
  if(anterior == NULL) lista->cabeca = i->prox;
  else anterior->prox = i->prox;
  free(i->reg.id);
  free(i);
}

/* Reinicializa a Lista */
void reinicializarLista(LISTA* lista) {
  NODE endereco = lista->cabeca;
  while (endereco != NULL) {
    NODE apagar = endereco;
    endereco = endereco->prox;
    free(apagar);
  }
  lista->cabeca = NULL;
}

void reinicializarListaEquip(LISTA* lista) {
  NODE endereco = lista->cabeca;
  while (endereco != NULL) {
    NODE apagar = endereco;
    endereco = endereco->prox;
    free(apagar->reg.id);
    free(apagar);
  }
  lista->cabeca = NULL;
}
