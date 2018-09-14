#include "semaforo.h"

/* DESENHA UM SEMAFORO NO ARQUIVO SVG */
void semaforo_SVG(FILE* output, REGISTRO *reg_semaforo) {
  fprintf(output, "\t<rect fill='%s' stroke='%s' stroke-width='20' width='15px' height='35px' y='%f' x='%f' />\n", reg_semaforo->cor, reg_semaforo->borda, reg_semaforo->y, reg_semaforo->x);
  fprintf(output, "\t<text x='%f' y='%f' font-family='Arial' font-size='10' fill='%s'>%c</text>\n", (reg_semaforo->x)+4, (reg_semaforo->y)+20, "black", 'S');
}

void ini_semaforo(GENERIC *head) {
  head = (GENERIC*) calloc(1, sizeof(GENERIC));
  head->next = NULL;
}

void add_semaforo(GENERIC **head, char *line, STORE_COLOR *cor_borda) {
  char *token = NULL;
  GENERIC *new_node = NULL;
  SEMAFORO *new_reg = (SEMAFORO*) calloc(1, sizeof(SEMAFORO));
  ini_semaforo(new_node);
  token = strtok(line, " ");
  new_reg->id = (char*) calloc(strlen(token) + 1, sizeof(char));
  strcpy(new_reg->id, token);
  token = strtok(NULL, " ");
  new_reg->x = atof(token);
  token = strtok(NULL, " ");
  new_reg->y = atof(token);
  new_reg->cor = (char*) calloc(strlen(cor_borda->cor_semaforo)+1, sizeof(char));
  strcpy(new_reg->cor, cor_borda->cor_semaforo);
  new_reg->borda = (char*) calloc(strlen(cor_borda->borda_semaforo)+1, sizeof(char));
  strcpy(new_reg->borda, cor_borda->borda_semaforo);
  new_node->data = new_reg;
  new_node->next = *head;
  *head = new_node;
}

void show_semaforo(GENERIC *head) {
  GENERIC *aux = head;
  while(aux != NULL) {
    printf("%s ", ((SEMAFORO *)aux->data)->id);
    printf("%s ", ((SEMAFORO *)aux->data)->cor);
    printf("%s ", ((SEMAFORO *)aux->data)->borda);
    printf("%lf ", ((SEMAFORO *)aux->data)->x);
    printf("%lf\n", ((SEMAFORO *)aux->data)->y);

    aux = aux->next;
  }
}

void del_semaforo(GENERIC *head) {
  GENERIC *aux = NULL;
  while(head != NULL) {
    aux = head;
    head = head->next;
    free_str(&(((SEMAFORO *)aux->data)->id));
    free_str(&(((SEMAFORO *)aux->data)->cor));
    free_str(&(((SEMAFORO *)aux->data)->borda));
    free(aux->data);
    free(aux);
  }
}

int search_semaforo(GENERIC *head, GENERIC **node, char *id) {
  GENERIC *aux = head;
  while(aux != NULL) {
    if(strcmp(id, (((SEMAFORO *)aux->data)->id)) == 0) {
      *node = aux;
      return 1;
    }
    aux = aux->next;
  }
  return -1;
}
