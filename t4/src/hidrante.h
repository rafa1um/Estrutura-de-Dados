#ifndef HIDRANTE_H
#define HIDRANTE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"
#include "io_name.h"

typedef struct {
  char *id;
  char *borda;
  char *cor;
  double r;
  double x;
  double y;
} HIDRANTE;

void hidrante_SVG(FILE* output, REGISTRO *reg_hidrante);
void ini_hidrante(GENERIC *head);
void add_hidrante(GENERIC **head, char *line, STORE_COLOR *cor_borda);
void show_hidrante(GENERIC *head);
void del_hidrante(GENERIC *head);
int search_hidrante(GENERIC *head, GENERIC **node, char *id);



#endif
