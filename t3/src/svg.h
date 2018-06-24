#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"

void new_SVG(FILE* output); /* INICIALIZA O ARQUIVO SVG */
/* Recebe um ponteiro para um arquivo e cria a abertura da tag do SVG */

void rect(FILE* output, REGISTRO *regRetangulo); /* DESENHA UM RETANGULO NO ARQUIVO SVG */
/* Recebe um ponteiro para um arquivo e um registro onde está armazenado todas as informações do retangulo,
 tendo as informações, imprime no arquivo as linhas referentes ao retangulo. */

void circ(FILE* output, REGISTRO *regCirculo); /* DESENHA UM CIRCULO NO ARQUIVO SVG */
/* Recebe um ponteiro para um arquivo e um registro onde está armazenado todas as informações do circulo,
 tendo as informações, imprime no arquivo as linhas referentes ao retangulo. */

void line(FILE* o_suSVG, NODE search01, NODE search02, double x, double y); /* DESENHA UMA LINHA ENTRE O CENTRO DE MASSA DAS FIGURAS */
 /* Recebe um ponteiro para um arquivo, um nó para a posição desejada da buscada, a posição do centro de massa da
  primeira figura x1y1, a posição do centro de massa da segunda figura x2y2 e a distãncia entre as duas */

void end_SVG(FILE* output); /* FECHA O ARQUIVO SVG */
/* Recebe um ponteiro para um arquivo e fecha a tag do SVG */
