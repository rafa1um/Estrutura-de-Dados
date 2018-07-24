#ifndef QUADRA_H
#define QUADRA_H
#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

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












#endif
