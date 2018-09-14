#ifndef QUADRA_H
#define QUADRA_H
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
} QUADRA;

void quadra_SVG(FILE* output, REGISTRO *reg_quadra);
void ini_quadra(GENERIC *head);
void add_quadra(GENERIC **head, char *line, STORE_COLOR *cor_borda);
void show_quadra(GENERIC *head);
void del_quadra(GENERIC *head);
int search_quadra(GENERIC *head, GENERIC **node, char *id);

#endif
