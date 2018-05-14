#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "linkedlist.h"

int calc_interno(NODE search, double x, double y);
/* Recebe o nó cabeça da posição da figura na lista, x e y e verifica se o ponto é ou não interno à figura.
  OBS: Bordas não estão incluídas no espaço interno da figura!!
  OBS2: Retorna 1 = interno
                2 = borda
               -1 = não pertence a figura */

double calc_distance(NODE search01, NODE search02);
/* Recebe dois nós cabeça da posição de duas figuras e retorna a distância entre elas. */

double calc_mass_rect(NODE search01);
/* Recebe o nó cabeça da posição de um retângulo na lista e retorna seu centro de massa. */

int calc_sobrepos(FILE* file, NODE search01, NODE search02);
