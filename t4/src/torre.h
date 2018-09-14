#ifndef TORRE_H
#define TORRE_H
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
} TORRE;

void torre_SVG(FILE* output, REGISTRO *reg_torre);
void ini_torre(GENERIC *head);
void add_torre(GENERIC **head, char *line, STORE_COLOR *cor_borda);
void show_torre(GENERIC *head);
void del_torre(GENERIC *head);
int search_torre(GENERIC *head, GENERIC **node, char *id);

#endif
