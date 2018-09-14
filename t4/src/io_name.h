#ifndef IONAME_H
#define IONAME_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void t_ext(char *base_name);
/* Recebe um ponteiro para o conteudo do nome base do arquivo e retira a extensão. */

typedef struct {
  char *cor_hidrante;
  char *cor_quadra;
  char *cor_semaforo;
  char *cor_torre;

  char *borda_hidrante;
  char *borda_quadra;
  char *borda_semaforo;
  char *borda_torre;
} STORE_COLOR;

void change_color(STORE_COLOR *cor_borda, char* comando, char* content);

void free_str(char **slave);

void birth_color(STORE_COLOR *slave);

void kill_color(STORE_COLOR *slave);

#endif
