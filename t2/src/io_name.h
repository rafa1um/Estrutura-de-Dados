#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void args(int argc, char **argv, char **dir, char **base_name, char **path);
/* Recebe os argumentos recebidos na main através do terminal, a seguir, faz as operações
   necessárias de leitura dos argumentos passados.*/

void t_ext(char *base_name);
/* Recebe um ponteiro para o conteudo do nome base do arquivo e retira a extensão. */
