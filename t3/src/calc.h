#ifndef CALC_H
#define CALC_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "linkedlist.h"

int calc_interno(NODE search, double x, double y);
/* Recebe o nó da posição da figura na lista, x e y e verifica se o ponto é ou não interno à figura.
  OBS: Bordas não estão incluídas no espaço interno da figura!!
  OBS2: Retorna 1 = interno
                2 = borda
               -1 = não pertence a figura */

double calc_distance(NODE search01, NODE search02);
/* Recebe dois nós da posição de duas figuras e retorna a distância entre elas. */

double calc_mass_rect(NODE search01);
/* Recebe o nó da posição de um retângulo na lista e retorna seu centro de massa. */

int calc_sobrepos(FILE* o_SVG, NODE search01, NODE search02);
/* Recebe um arquivo e dois nós da posição de duas figuras e verifica se uma sobrepôe a outra e vice-versa */

#endif
