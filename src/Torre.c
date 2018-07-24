#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Torre.h"

typedef struct _torre {
	double x;
	double y;
	char *id;
	char *cfill;
	char *cstrk;
} torre;

Torre createTorre(double x, double y, char *id, char *cfill, char *cstrk) {
	int cont;
	torre *cel;

	cel = (torre *) malloc(sizeof(torre));

	cel->x = x;
	cel->y = y;
	cel->id = id;

	cont = strlen(cfill);
	cel->cfill = (char *) malloc((cont+1)*sizeof(char));
	strcpy(cel->cfill, cfill);

	cont = strlen(cstrk);
	cel->cstrk = (char *) malloc((cont+1)*sizeof(char));
	strcpy(cel->cstrk, cstrk);

	return (Torre) cel;
}

void lerTorre(FILE *geo, double *x, double *y, char **id) {
	int cont;
	char *aux;

	aux = (char *) malloc(1000*sizeof(char));

	fscanf(geo, " %lf %lf %s", x, y, aux);

	cont = strlen(aux);
	*id = (char *) malloc((cont+1)*sizeof(char));
	strcpy(*id, aux);

	free(aux);
}

void escreverTorre(FILE *saida, Torre t) {
	torre *cel;

	cel = (torre *) t;

	fprintf(saida, "\t<circle cx=\"%f\" cy=\"%f\" r=\"%f\" stroke=\"%s\" fill=\"%s\"/>\n", cel->x, cel->y, 2.00000, cel->cstrk, cel->cfill);
	fprintf(saida, "<text text-anchor=\"middle\" x=\"%lf\" y=\"%lf\" font-size=\"8\">%s</text>", cel->x, cel->y, cel->id);
}

void setTorreCfill(Torre t, char *cfill) {
	torre *cel;

	cel = (torre *) t;

	cel->cfill = cfill;
}

void setTorreCstrk(Torre t, char *cstrk) {
	torre *cel;

	cel = (torre *) t;

	cel->cstrk = cstrk;
}

double getTorreX(Torre t) {
	torre *cel;

	cel = (torre *) t;

	return cel->x;
}

double getTorreY(Torre t) {
	torre *cel;

	cel = (torre *) t;

	return cel->y;
}

char *getTorreId(Torre t) {
	torre *cel;

	cel = (torre *) t;

	return cel->id;
}

void freeTorre(Torre t) {
	torre *cel;

	cel = (torre *) t;

	free(cel->id);
	free(cel->cfill);
	free(cel->cstrk);
	free(cel);
}
