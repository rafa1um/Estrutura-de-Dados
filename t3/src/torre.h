#ifndef TORRE_H
#define TORRE_H
#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

typedef struct {
  char *id;
  char *borda;
  char *cor;
  double r;
  double x;
  double y;
} TORRE;

void hidrante_SVG(FILE* output, REGISTRO *reg_torre);












#endif
