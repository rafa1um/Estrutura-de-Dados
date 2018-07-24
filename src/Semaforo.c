#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Semaforo.h"

typedef struct _semaforo {
	double x;
	double y;
	char *id;
	char *cfill;
	char *cstrk;
} semaforo;

Semaforo createSemaforo(double x, double y, char *id, char *cfill, char *cstrk) {
	int cont;
	semaforo *sinal;

	sinal = (semaforo *) malloc(sizeof(semaforo));

	sinal->x = x;
	sinal->y = y;
	sinal->id = id;

	cont = strlen(cfill);
	sinal->cfill = (char *) malloc((cont+1)*sizeof(char));
	strcpy(sinal->cfill, cfill);

	cont = strlen(cstrk);
	sinal->cstrk = (char *) malloc((cont+1)*sizeof(char));
	strcpy(sinal->cstrk, cstrk);

	return (Semaforo) sinal;
}

void lerSemaforo(FILE *geo, double *x, double *y, char **id) {
	int cont;
	char *aux;

	aux = (char *) malloc(1000*sizeof(char));

	fscanf(geo, " %lf %lf %s", x, y, aux);

	cont = strlen(aux);
	*id = (char *) malloc((cont+1)*sizeof(char));
	strcpy(*id, aux);

	free(aux);
}

void escreverSemaforo(FILE *saida, Semaforo s) {
	semaforo *sinal;

	sinal = (semaforo *) s;

	fprintf(saida, "\t<circle cx=\"%f\" cy=\"%f\" r=\"%f\" stroke=\"%s\" fill=\"%s\"/>\n", sinal->x, sinal->y, 2.00000, sinal->cstrk, sinal->cfill);
	fprintf(saida, "<text text-anchor=\"middle\" x=\"%lf\" y=\"%lf\" font-size=\"8\">%s</text>", sinal->x, sinal->y, sinal->id);
}

void setSemaforoCfill(Semaforo s, char *cfill) {
	semaforo *sinal;

	sinal = (semaforo *) s;

	sinal->cfill = cfill;
}

void setSemaforoCstrk(Semaforo s, char *cstrk) {
	semaforo *sinal;

	sinal = (semaforo *) s;

	sinal->cstrk = cstrk;
}

double getSemaforoX(Semaforo s) {
	semaforo *sinal;

	sinal = (semaforo *) s;

	return sinal->x;
}

double getSemaforoY(Semaforo s) {
	semaforo *sinal;

	sinal = (semaforo *) s;

	return sinal->y;
}

char *getSemaforoId(Semaforo s) {
	semaforo *sinal;

	sinal = (semaforo *) s;

	return sinal->id;
}

void freeSemaforo(Semaforo s) {
	semaforo *sinal;

	sinal = (semaforo *) s;

	free(sinal->id);
	free(sinal->cfill);
	free(sinal->cstrk);
	free(sinal);
}
