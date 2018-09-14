#include "torre.h"


void torre_SVG(FILE* output, REGISTRO *reg_torre) {
  fprintf(output, "\t<circle fill='%s' stroke='%s' r='8px' cx='%f' cy='%f' />\n", reg_torre->cor, reg_torre->borda, reg_torre->x, reg_torre->y);
  fprintf(output, "\t<text x='%f' y='%f' font-family='Arial' font-size='10' fill='%s'>%c</text>\n", (reg_torre->x)-3.5, (reg_torre->y)+3, "white", 'T');
}

void ini_torre(GENERIC *head) {
  head = (GENERIC*) calloc(1, sizeof(GENERIC));
  head->next = NULL;
}

void add_torre(GENERIC **head, char *line, STORE_COLOR *cor_borda) {
  char *token = NULL;
  GENERIC *new_node = NULL;
  TORRE *new_reg = (TORRE*) calloc(1, sizeof(TORRE));
  ini_torre(new_node);
  token = strtok(line, " ");
  new_reg->id = (char*) calloc(strlen(token) + 1, sizeof(char));
  strcpy(new_reg->id, token);
  token = strtok(NULL, " ");
  new_reg->x = atof(token);
  token = strtok(NULL, " ");
  new_reg->y = atof(token);
  new_reg->cor = (char*) calloc(strlen(cor_borda->cor_torre)+1, sizeof(char));
  strcpy(new_reg->cor, cor_borda->cor_torre);
  new_reg->borda = (char*) calloc(strlen(cor_borda->borda_torre)+1, sizeof(char));
  strcpy(new_reg->borda, cor_borda->borda_torre);
  new_node->data = new_reg;
  new_node->next = *head;
  *head = new_node;
}

void show_torre(GENERIC *head) {
  GENERIC *aux = head;
  while(aux != NULL) {
    printf("%s ", ((TORRE *)aux->data)->id);
    printf("%s ", ((TORRE *)aux->data)->cor);
    printf("%s ", ((TORRE *)aux->data)->borda);
    printf("%lf ", ((TORRE *)aux->data)->x);
    printf("%lf\n", ((TORRE *)aux->data)->y);

    aux = aux->next;
  }
}

void del_torre(GENERIC *head) {
  GENERIC *aux = NULL;
  while(head != NULL) {
    aux = head;
    head = head->next;
    free_str(&(((TORRE *)aux->data)->id));
    free_str(&(((TORRE *)aux->data)->cor));
    free_str(&(((TORRE *)aux->data)->borda));
    free(aux->data);
    free(aux);
  }
}

int search_torre(GENERIC *head, GENERIC **node, char *id) {
  GENERIC *aux = head;
  while(aux != NULL) {
    if(strcmp(id, (((TORRE *)aux->data)->id)) == 0) {
      *node = aux;
      return 1;
    }
    aux = aux->next;
  }
  return -1;
}
