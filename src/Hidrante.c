#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Hidrante.h"

typedef struct _hidrante {
	double x;
	double y;
	char *id;
	char *cfill;
	char *cstrk;
} hidrante;

Hidrante createHidrante(double x, double y, char *id, char *cfill, char *cstrk) {
	int cont;
	hidrante *hidra;

	hidra = (hidrante *) malloc(sizeof(hidrante));

	hidra->x = x;
	hidra->y = y;
	hidra->id = id;

	cont = strlen(cfill);
	hidra->cfill = (char *) malloc((cont+1)*sizeof(char));
	strcpy(hidra->cfill, cfill);

	cont = strlen(cstrk);
	hidra->cstrk = (char *) malloc((cont+1)*sizeof(char));
	strcpy(hidra->cstrk, cstrk);

	return (Hidrante) hidra;
}

void lerHidrante(FILE *geo, double *x, double *y, char **id) {
	int cont;
	char *aux;

	aux = (char *) malloc(1000*sizeof(char));

	fscanf(geo, " %lf %lf %s", x, y, aux);

	cont = strlen(aux);
	*id = (char *) malloc((cont+1)*sizeof(char));
	strcpy(*id, aux);

	free(aux);
}

void escreverHidrante(FILE *saida, Hidrante h) {
	hidrante *hidra;

	hidra = (hidrante *) h;

	fprintf(saida, "\t<circle cx=\"%f\" cy=\"%f\" r=\"%f\" stroke=\"%s\" stroke-width=\"1\" fill=\"%s\"/>\n", hidra->x, hidra->y, 2.00000, hidra->cstrk, hidra->cfill);
	fprintf(saida, "<text text-anchor=\"middle\" x=\"%lf\" y=\"%lf\" font-size=\"8\">%s</text>", hidra->x, hidra->y, hidra->id);
}

void setHidranteCfill(Hidrante h, char *cfill) {
	hidrante *hidra;

	hidra = (hidrante *) h;

	hidra->cfill = cfill;
}

void setHidranteCstrk(Hidrante h, char *cstrk) {
	hidrante *hidra;

	hidra = (hidrante *) h;

	hidra->cstrk = cstrk;
}

double getHidranteX(Hidrante h) {
	hidrante *hidra;

	hidra = (hidrante *) h;

	return hidra->x;
}

double getHidranteY(Hidrante h) {
	hidrante *hidra;

	hidra = (hidrante *) h;

	return hidra->y;
}

char *getHidranteId(Hidrante h) {
	hidrante *hidra;

	hidra = (hidrante *) h;

	return hidra->id;
}

void freeHidrante(Hidrante h) {
	hidrante *hidra;

	hidra = (hidrante *) h;

	free(hidra->id);
	free(hidra->cfill);
	free(hidra->cstrk);
	free(hidra);
}
