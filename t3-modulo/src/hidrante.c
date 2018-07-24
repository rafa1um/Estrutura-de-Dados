#include "hidrante.h"
#include "io_name.h"

/* DESENHA UM HIDRANTE NO ARQUIVO SVG */
void hidrante_SVG(FILE* output, REGISTRO *reg_hidrante) {
  fprintf(output, "\t<circle fill='%s' stroke='%s' r='8px' cx='%f' cy='%f' />\n", reg_hidrante->cor, reg_hidrante->borda, reg_hidrante->x, reg_hidrante->y);
  fprintf(output, "\t<text x='%f' y='%f' font-family='Arial' font-size='10' fill='%s'>%c</text>\n", (reg_hidrante->x)-3.5, (reg_hidrante->y)+3, "white", 'H');
}

void ini_hidrante(GENERIC *head) {
  head = (GENERIC*) calloc(1, sizeof(GENERIC));
  head->next = NULL;
}

void add_hidrante(GENERIC **head, char *line, STORE_COLOR *cor_borda) {
  char *token = NULL;
  GENERIC *new_node = NULL;
  HIDRANTE *new_reg = (HIDRANTE*) calloc(1, sizeof(HIDRANTE));
  inicializar_hidrante(new_node);
  token = strtok(line, " ");
  new_reg->id = (char*) calloc(strlen(token) + 1, sizeof(char));
  strcpy(new_reg->id, token);
  token = strtok(NULL, " ");
  new_reg->x = atof(token);
  token = strtok(NULL, " ");
  new_reg->y = atof(token);
  new_reg->cor = (char*) calloc(strlen(cor_borda->cor_hidrante)+1, sizeof(char));
  strcpy(new_reg->cor, cor_borda->cor_hidrante);
  new_reg->borda = (char*) calloc(strlen(cor_borda->borda_hidrante)+1, sizeof(char));
  strcpy(new_reg->borda, cor_borda->borda_hidrante);
  new_node->data = new_reg;
  new_node->next = *head;
  *head = new_node;
}

void show_hidrante(GENERIC *head) {
  GENERIC *aux = head;
  while(aux != NULL) {
    printf("%s ", ((HIDRANTE *)aux->data)->id);
    printf("%s ", ((HIDRANTE *)aux->data)->cor);
    printf("%s ", ((HIDRANTE *)aux->data)->borda);
    printf("%lf ", ((HIDRANTE *)aux->data)->x);
    printf("%lf\n", ((HIDRANTE *)aux->data)->y);

    aux = aux->next;
  }
}

void del_hidrante(GENERIC *head) {
  GENERIC *aux = NULL;
  while(head != NULL) {
    aux = head;
    head = head->next;
    free_str(&(((HIDRANTE *)aux->data)->id));
    free_str(&(((HIDRANTE *)aux->data)->cor));
    free_str(&(((HIDRANTE *)aux->data)->borda));
    free(aux->data);
    free(aux);
  }
}
