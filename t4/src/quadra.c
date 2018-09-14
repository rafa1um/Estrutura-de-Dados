#include "quadra.h"

void quadra_SVG(FILE* output, REGISTRO *reg_quadra) {
  fprintf(output, "\t<rect fill='%s' stroke='%s' stroke-width='%dpx' width='%f' height='%f' y='%f' x='%f' />\n", reg_quadra->cor, reg_quadra->borda, 1, reg_quadra->largura, reg_quadra->altura, reg_quadra->y, reg_quadra->x);
  fprintf(output, "\t<text x='%f' y='%f' font-family='Arial' font-size='10' fill='%s'>%s</text>\n", (reg_quadra->x)+45, (reg_quadra->y)+40, "black", reg_quadra->id);
}

void ini_quadra(GENERIC *head) {
  head = (GENERIC*) calloc(1, sizeof(GENERIC));
  head->next = NULL;
}

void add_quadra(GENERIC **head, char *line, STORE_COLOR *cor_borda) {
  char *token = NULL;
  GENERIC *new_node = NULL;
  QUADRA *new_reg = (QUADRA*) calloc(1, sizeof(QUADRA));
  ini_quadra(new_node);
  token = strtok(line, " ");
  new_reg->id = (char*) calloc(strlen(token) + 1, sizeof(char));
  strcpy(new_reg->id, token);
  token = strtok(NULL, " ");
  new_reg->x = atof(token);
  token = strtok(NULL, " ");
  new_reg->y = atof(token);
  new_reg->cor = (char*) calloc(strlen(cor_borda->cor_quadra)+1, sizeof(char));
  strcpy(new_reg->cor, cor_borda->cor_quadra);
  new_reg->borda = (char*) calloc(strlen(cor_borda->borda_quadra)+1, sizeof(char));
  strcpy(new_reg->borda, cor_borda->borda_quadra);
  new_node->data = new_reg;
  new_node->next = *head;
  *head = new_node;
}

void show_quadra(GENERIC *head) {
  GENERIC *aux = head;
  while(aux != NULL) {
    printf("%s ", ((QUADRA *)aux->data)->id);
    printf("%s ", ((QUADRA *)aux->data)->cor);
    printf("%s ", ((QUADRA *)aux->data)->borda);
    printf("%lf ", ((QUADRA *)aux->data)->x);
    printf("%lf\n", ((QUADRA *)aux->data)->y);

    aux = aux->next;
  }
}

void del_quadra(GENERIC *head) {
  GENERIC *aux = NULL;
  while(head != NULL) {
    aux = head;
    head = head->next;
    free_str(&(((QUADRA *)aux->data)->id));
    free_str(&(((QUADRA *)aux->data)->cor));
    free_str(&(((QUADRA *)aux->data)->borda));
    free(aux->data);
    free(aux);
  }
}

int search_quadra(GENERIC *head, GENERIC **node, char *id) {
  GENERIC *aux = head;
  while(aux != NULL) {
    if(strcmp(id, (((QUADRA *)aux->data)->id)) == 0) {
      *node = aux;
      return 1;
    }
    aux = aux->next;
  }
  return -1;
}
