#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Retangulo.h"

typedef struct _retangulo {
    int id;
    double x;
    double y;
    double altura;
    double largura;
    char *cor;
} retangulo;

/*Função que cria e retorna uma figura do tipo retangulo*/
Retangulo createRetangulo(int id, double x, double y, double altura, double largura, char *cor) {
    retangulo *novoRetangulo;

    novoRetangulo = malloc(sizeof(retangulo));
    novoRetangulo->id = id;
    novoRetangulo->x = x;
    novoRetangulo->y = y;
    novoRetangulo->altura = altura;
    novoRetangulo->largura = largura;
    novoRetangulo->cor = cor;

    return novoRetangulo;
}

/*Procedimento para ler os atributos da figura retangulo*/
void lerRetangulo(FILE *geo, int *id, double *largura, double *altura, double *x, double *y, char **cor) {
    int cont;
    char *pCor;

    pCor = (char *) malloc(1000*sizeof(char));

    fscanf(geo, " %d %lf %lf %lf %lf %s", id, largura, altura, x, y, pCor);

    cont = strlen(pCor);
    *cor = (char *) malloc((cont+1)*sizeof(char));
    strcpy(*cor, pCor);

    free(pCor);
}

/*Procedimento para escrever um retangulo no arquivo svg*/
void escreverRetangulo(Retangulo rect, FILE *saida, char *cor) {
    retangulo *aux = (retangulo *) rect;

    if (strcmp(cor, "NULL") == 0)
        fprintf(saida, "\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" fill=\"%s\"/>\n", aux->x, aux->y, aux->largura, aux->altura, aux->cor);
    else {
        fprintf(saida, "\t<circle cx=\"%f\" cy=\"%f\" r=\"%f\" fill=\"%s\"/>\n", aux->x, aux->y, 5.000, cor);
        fprintf(saida, "\t<circle cx=\"%f\" cy=\"%f\" r=\"%f\" fill=\"%s\"/>\n", aux->x + aux->largura, aux->y, 5.000, cor);
        fprintf(saida, "\t<circle cx=\"%f\" cy=\"%f\" r=\"%f\" fill=\"%s\"/>\n", aux->x, aux->y + aux->altura, 5.000, cor);
        fprintf(saida, "\t<circle cx=\"%f\" cy=\"%f\" r=\"%f\" fill=\"%s\"/>\n", aux->x + aux->largura, aux->y + aux->altura, 5.000 , cor);
    }
}

/*Função que retorna o ID de um retangulo*/
int getRetanguloId(Retangulo rect) {
    retangulo *aux = (retangulo *) rect;

    return aux->id;
}

/*Função que retorna o ponto X de um retangulo*/
double getRetanguloX(Retangulo rect) {
    retangulo *aux = (retangulo *) rect;

    return aux->x;
}

/*Função que retorna o ponto Y de um retangulo*/
double getRetanguloY(Retangulo rect) {
    retangulo *aux = (retangulo *) rect;

    return aux->y;
}

/*Função que retorna a Altura de um retangulo*/
double getRetanguloAltura(Retangulo rect) {
    retangulo *aux = (retangulo *) rect;

    return aux->altura;
}

/*Função que retorna a Largura de um retangulo*/
double getRetanguloLargura(Retangulo rect) {
    retangulo *aux = (retangulo *) rect;

    return aux->largura;
}

/*Função que retorna a Cor de um retangulo*/
char *getRetanguloCor(Retangulo rect) {
    retangulo *aux = (retangulo *) rect;

    return aux->cor;
}

/*Procedimento que libera os retangulos criados*/
void freeRetangulo(Retangulo rect) {
    retangulo *aux = (retangulo *) rect;
    if (strcmp("NULL", aux->cor) != 0) {
        free(aux->cor);
    }
    free(aux);
}
