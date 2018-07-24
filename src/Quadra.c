#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Quadra.h"

typedef struct _quadra {
	double x;
	double y;
	double largura;
	double altura;
	char *cep;
	char *cfill;
	char *cstrk;
} quadra;

Quadra createQuadra(double x, double y, double largura, double altura, char *cep, char *cfill, char *cstrk) {
	int cont;
	quadra *square;

	square = (quadra *) malloc(sizeof(quadra));

	square->x = x;
	square->y = y;
	square->largura = largura;
	square->altura = altura;
	square->cep = cep;

	cont = strlen(cfill);
	square->cfill = (char *) malloc((cont+1)*sizeof(char));
	strcpy(square->cfill, cfill);

	cont = strlen(cstrk);
	square->cstrk = (char *) malloc((cont+1)*sizeof(char));
	strcpy(square->cstrk, cstrk);

	return (Quadra) square;
}

void lerQuadra(FILE *geo, double *x, double *y, double *largura, double *altura, char **cep) {
	int cont;
	char *aux;

	aux = (char *) malloc(1000*sizeof(char));

	fscanf(geo, " %lf %lf %lf %lf %s", x, y, largura, altura, aux);

	cont = strlen(aux);
	*cep = (char *) malloc((cont+1)*sizeof(char));
	strcpy(*cep, aux);

	free(aux);
}

void escreverQuadra(FILE *saida, Quadra q) {
	quadra *square;
	double x, y;

	square = (quadra *) q;


	x = square->largura/2;
	x += square->x;
	y = square->altura/2;
	y += square->y;

	fprintf(saida, "\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" stroke=\"%s\" fill=\"%s\"/>\n", square->x, square->y, square->largura, square->altura, square->cstrk, square->cfill);
	fprintf(saida, "<text text-anchor=\"middle\" x=\"%f\" y=\"%f\">%s</text>", x, y, square->cep);
}

void setQuadraCfill(Quadra q, char *cfill) {
	quadra *square;

	square = (quadra *) q;

	square->cfill = cfill;
}

void setQuadraCstrk(Quadra q, char *cstrk) {
	quadra *square;

	square = (quadra *) q;

	square->cstrk = cstrk;
}

double getQuadraX(Quadra q) {
	quadra *square;

	square = (quadra *) q;

	return square->x;
}

double getQuadraY(Quadra q) {
	quadra *square;

	square = (quadra *) q;

	return square->y;
}

double getQuadraLargura(Quadra q) {
	quadra *square;

	square = (quadra *) q;

	return square->largura;
}

double getQuadraAltura(Quadra q) {
	quadra *square;

	square = (quadra *) q;

	return square->altura;
}

char *getQuadraCep(Quadra q) {
	quadra *square;

	square = (quadra *) q;

	return square->cep;
}

void freeQuadra(Quadra q) {
	quadra *square;

	square = (quadra *) q;

	free(square->cep);
	free(square->cfill);
	free(square->cstrk);
	free(square);
}
