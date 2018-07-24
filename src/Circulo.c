#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Circulo.h"

typedef struct _circulo{
    int id;
    double x;
    double y;
    double raio;
    char *cor;
} circulo;

/*Função que cria e retorna uma figura do tipo circulo*/
Circulo createCirculo(int id, double x, double y, double raio, char *cor) {
    circulo *novoCirculo;

    novoCirculo = malloc(sizeof(circulo));

    novoCirculo->id = id;
    novoCirculo->x = x;
    novoCirculo->y = y;
    novoCirculo->raio = raio;
    novoCirculo->cor = cor;

    return (Circulo) novoCirculo;
}

void lerCirculo(FILE *geo, int *id, double *raio, double *x, double *y, char **cor) {
    int cont;
    char *pCor;

    pCor = (char *) malloc(1000*sizeof(char));

    fscanf(geo, " %d %lf %lf %lf %s", id, raio, x, y, pCor);

    cont = strlen(pCor);
    *cor = (char *) malloc((cont+1)*sizeof(char));
    strcpy(*cor, pCor);

    free(pCor);
}

void escreverCirculo(Circulo c, FILE *saida, char *cor) {
    circulo *aux = (circulo *) c;

    if (strcmp(cor, "NULL") == 0)
        fprintf(saida, "\n\t<circle cx=\"%f\" cy=\"%f\" r=\"%f\" fill=\"%s\"/>\n", aux->x, aux->y, aux->raio, aux->cor);
    else fprintf(saida, "\n\t<circle cx=\"%f\" cy=\"%f\" r=\"%f\" fill=\"%s\"/>\n", aux->x, aux->y, 5.000, cor);
}

/*Função que retorna o ID de um circulo*/
int getCirculoId(Circulo c) {
    circulo *aux = (circulo *) c;

    return aux->id;
}

/*Função que retorna o ponto X de um circulo*/
double getCirculoX(Circulo c) {
    circulo *aux = (circulo *) c;

    return aux->x;
}

/*Função que retorna o ponto Y de um circulo*/
double getCirculoY(Circulo c) {
    circulo *aux = (circulo *) c;

    return aux->y;
}

/*Função que retorna o Raio de um circulo*/
double getCirculoRaio(Circulo c) {
    circulo *aux = (circulo *) c;

    return aux->raio;
}

/*Função que retorna a Cor de um circulo*/
char *getCirculoCor(Circulo c) {
    circulo *aux = (circulo *) c;

    return aux->cor;
}

/*Procedimento que libera os circulos criados*/
void freeCirculo(Circulo c) {
    circulo *aux = (circulo *) c;
    if (strcmp("NULL", aux->cor) != 0) {
        free(aux->cor);
    }
    free(aux);
}
