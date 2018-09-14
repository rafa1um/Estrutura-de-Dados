#include "io_name.h"


/* ---------- RETIRA EXTENSÃO ---------- */
void t_ext(char *base_name) {
  int i;
  for (i = strlen(base_name) - 1; i >= 0; i--) {
    if (base_name[i] == '.') {
      base_name[i] = 0;
      return;
    }
  }
}

/**/
void change_color(STORE_COLOR *cor_borda, char* comando, char* content) {
  char *token = NULL;
  if(strcmp(comando, "ch") == 0) {
    free_str(&(cor_borda->cor_hidrante));
    free_str(&(cor_borda->borda_hidrante));
    token = strtok(content, " ");
    cor_borda->cor_hidrante = (char*) calloc(strlen(token)+1, sizeof(char));
    strcpy(cor_borda->cor_hidrante, token);
    token = strtok(NULL, " ");
    cor_borda->borda_hidrante = (char*) calloc(strlen(token)+1, sizeof(char));
    strcpy(cor_borda->borda_hidrante, token);
  }
  else if(strcmp(comando, "cq") == 0) {
    free_str(&(cor_borda->cor_quadra));
    free_str(&(cor_borda->borda_quadra));
    token = strtok(content, " ");
    cor_borda->cor_quadra = (char*) calloc(strlen(token)+1, sizeof(char));
    strcpy(cor_borda->cor_quadra, token);
    token = strtok(NULL, " ");
    cor_borda->borda_quadra = (char*) calloc(strlen(token)+1, sizeof(char));
    strcpy(cor_borda->borda_quadra, token);
  }
  else if(strcmp(comando, "cs") == 0) {
    free_str(&(cor_borda->cor_semaforo));
    free_str(&(cor_borda->borda_semaforo));
    token = strtok(content, " ");
    cor_borda->cor_semaforo = (char*) calloc(strlen(token)+1, sizeof(char));
    strcpy(cor_borda->cor_semaforo, token);
    token = strtok(NULL, " ");
    cor_borda->borda_semaforo = (char*) calloc(strlen(token)+1, sizeof(char));
    strcpy(cor_borda->borda_semaforo, token);
  }
  else if(strcmp(comando, "ct") == 0) {
    free_str(&(cor_borda->cor_torre));
    free_str(&(cor_borda->borda_torre));
    token = strtok(content, " ");
    cor_borda->cor_torre = (char*) calloc(strlen(token)+1, sizeof(char));
    strcpy(cor_borda->cor_torre, token);
    token = strtok(NULL, " ");
    cor_borda->borda_torre = (char*) calloc(strlen(token)+1, sizeof(char));
    strcpy(cor_borda->borda_torre, token);
  }
}

void free_str(char **slave) {
  if(*slave != NULL) {
    free(*slave);
    *slave = NULL;
  }
}

/* -- COLOCAR STRINGS DE  */
void birth_color(STORE_COLOR *slave) {
  slave = (STORE_COLOR*) calloc(1, sizeof(STORE_COLOR));
  slave->cor_hidrante = NULL;
  slave->cor_quadra = NULL;
  slave->cor_semaforo = NULL;
  slave->cor_torre = NULL;
  slave->borda_hidrante = NULL;
  slave->borda_quadra = NULL;
  slave->borda_semaforo = NULL;
  slave->borda_torre = NULL;
}

void kill_color(STORE_COLOR *slave) {
  free_str(&(slave->cor_hidrante));
  free_str(&(slave->cor_quadra));
  free_str(&(slave->cor_semaforo));
  free_str(&(slave->cor_torre));
  free_str(&(slave->borda_hidrante));
  free_str(&(slave->borda_quadra));
  free_str(&(slave->borda_semaforo));
  free_str(&(slave->borda_torre));
  free(slave);
}
