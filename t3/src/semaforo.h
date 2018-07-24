#ifndef SEMAFORO_H
#define SEMAFORO_H
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
} SEMAFORO;

void semaforo_SVG(FILE* output, REGISTRO *reg_semaforo);







#endif
