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
  NODE pos = lista->cabeca;
  while(pos != NULL) {
    if(pos->reg.chave == ch) return pos;
    pos = pos->prox;
  }
  return NULL;
}

/* Busca auxiliar; */
NODE buscaSeqExc(LISTA* lista, char* ch, NODE* anterior) {
  NODE atual = lista->cabeca;
  *anterior = NULL;
  while(atual != NULL && (strcmp(atual->reg.id, ch) != 0)) {
    *anterior = atual;
    atual = atual->prox;
  }
  if(atual != NULL && (strcmp(atual->reg.id, ch) == 0)) return atual;
  return NULL;
}

/* Insere um elemento na Lista */
void inserirElemento(LISTA* lista, REGISTRO reg) {
  NODE i;
  i = (NODE) malloc(sizeof(ELEMENTO));
  i->reg = reg;
  i->prox = lista->cabeca;
  lista->cabeca = i;
}
/* Insere um elemento na Lista cidade */
void inserirQUAHISERA(LISTA* cidade, REGISTRO reg) {
  NODE i;
  i = (NODE) malloc(sizeof(ELEMENTO));
  i->reg = reg;
  i->prox = cidade->cabeca;
  cidade->cabeca = i;
}

/* Exclui um elemento da Lista */
int excluirElemento(LISTA* lista, char* ch) {
  NODE anterior, i;
  i = buscaSeqExc(lista, ch, &anterior);
  if(i == NULL) {
    printf("Elemento nao encontrado!");
    return -1;
  }
  anterior->prox = i->prox;
  free(i);
  printf("Elemento excluido com sucesso!");
  return 1;
}

/* Reinicializa a Lista */
void reinicializarLista(LISTA* lista) {
  NODE endereco = lista->cabeca;
  while (endereco != NULL) {
    NODE apagar = endereco;
    free(endereco->reg.cor);
    free(endereco->reg.borda);
    endereco = endereco->prox;
    free(apagar);
  }
  lista->cabeca = NULL;
}

void reinicializarListaEquip(LISTA* lista) {
  NODE endereco = lista->cabeca;
  while (endereco != NULL) {
    NODE apagar = endereco;
    free(endereco->reg.id);
    endereco = endereco->prox;
    free(apagar);
  }
  lista->cabeca = NULL;
}
