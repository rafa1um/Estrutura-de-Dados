#ifndef SEMAFORO_H
#define SEMAFORO_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"
#include "io_name.h"

typedef struct {
  char *id;
  char *borda;
  char *cor;
  double x;
  double y;
  double altura;
  double largura;
} SEMAFORO;

void semaforo_SVG(FILE* output, REGISTRO *reg_semaforo);
void ini_semaforo(GENERIC *head);
void add_semaforo(GENERIC **head, char *line, STORE_COLOR *cor_borda);
void show_semaforo(GENERIC *head);
void del_semaforo(GENERIC *head);
int search_semaforo(GENERIC *head, GENERIC **node, char *id);

#endif
