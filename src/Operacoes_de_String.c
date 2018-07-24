#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Operacoes_de_String.h"

/*Recebe os argumentos (parâmetros) lidos no terminal*/
int Argumentos(int argc, char **argv, char **pathIn, char **pathOut, char **nome, char **arqQry) {
	int i=1, cont, logic1=1, logic2=1, logic3=1, logic4=1;

	while(1) {
		if (i >= argc)
			break;

		if (strcmp(argv[i], "-acc0") == 0) {
			logic2 = 3;
			i++;
		}

		else if (strcmp(argv[i], "-acc") == 0) {
			logic3 = 5;
			i++;
		}

		else if (strcmp(argv[i], "-e") == 0) {
			cont = strlen(argv[i+1]);
			*pathIn = (char *) realloc(*pathIn, (cont+1)*sizeof(char));
			strcpy(*pathIn, argv[i+1]);
			logic4 = 7;
			i++;
		}

		/*Compara se tal argumento é "-f", em caso afirmativo, a String 'nome' recebe o nome do arquivo de entrada*/
		else if (strcmp(argv[i], "-f") == 0) {
			cont = strlen(argv[i+1]);
			*nome = (char *) realloc(*nome, (cont+1)*sizeof(char));
			strcpy(*nome, argv[i+1]);
			i++;
		}

		/*Compara se tal argumento é "-o", em caso afirmativo, a String 'dir' recebe o diretório do arquivo de saída*/
		else if (strcmp(argv[i], "-o") == 0) {
			cont = strlen(argv[i+1]);
			*pathOut = (char *) realloc(*pathOut, (cont+1)*sizeof(char));
			strcpy(*pathOut, argv[i+1]);
			i++;
		}

		else if (strcmp(argv[i], "-q") == 0) {
			cont = strlen(argv[i+1]);
			*arqQry = (char *) realloc(*arqQry, (cont+1)*sizeof(char));
			strcpy(*arqQry, argv[i+1]);
			logic1 = 2;
			i++;
		}

		i++;
	}

	return logic1*logic2*logic3*logic4;
}

char *verificaBarra(char *string) {
	char *saida;
	int cont;

	cont = strlen(string);

	if (string[cont-1] != '/') {
		saida = (char *) malloc((cont+1+1)*sizeof(char));
		sprintf(saida, "%s/", string);

		free(string);

		return saida;
	}

	else {
		return string;
	}
}

char *diretorio(char *dir, char *string) {
	char *saida;
	int cont;

	cont = strlen(dir);
	cont += strlen(string);

	saida = (char *) malloc((cont+1)*sizeof(char));
	sprintf(saida, "%s%s", dir, string);

	return saida;
}

char *nomeBase(char *string) {
	char *saida, *aux=NULL, *aux2, aux3;
	int cont=0, i, j=0;

	cont = strlen(string);
	aux = (char *) malloc((cont+1)*sizeof(char));

	for (i=0; i<cont; i++) {
		if (string[i] == '.') {
			if (string[i+1] != '.' && string[i+1] != '/') {
				break;
			}
		}

		aux[i] = string[i];
	}
	aux[i] = '\0';

	cont = strlen(aux);
	aux2 = (char *) malloc((cont+1)*sizeof(char));

	for (i=cont-1; i>=0; i--) {
		if (aux[i] == '/') {
			break;
		}
		aux2[j] = aux[i];
		j++;
	}
	aux2[j] = '\0';
	cont = strlen(aux2);
	j = cont-1;

	for (i=0; i<cont/2; i++) {
		aux3 = aux2[i];
		aux2[i] = aux2[j];
		aux2[j] = aux3;
		j--;
	}

	cont = strlen(aux2);
	saida = (char *) malloc((cont+1)*sizeof(char));
	strcpy(saida, aux2);

	free(aux);
	free(aux2);

	return saida;
}

char *saidaTxt(char *string) {
	char *saida;
	int cont;

	cont = strlen(string);
	saida = (char *) malloc((cont+1+4)*sizeof(char));
	sprintf(saida, "%s.txt", string);

	free(string);

	return saida;
}

char *saidaSvg(char *string) {
	char *saida;
	int cont;

	cont = strlen(string);
	saida = (char *) malloc((cont+1+4)*sizeof(char));
	sprintf(saida, "%s.svg", string);

	free(string);

	return saida;
}

char *concatenaTraco(char *nome, char *sufixo) {
	char *saida;
	int cont;

	cont = strlen(nome);
	cont += strlen(sufixo);
	saida = (char *) malloc((cont+1+1)*sizeof(char));
	sprintf(saida, "%s-%s", nome, sufixo);

	return saida;
}

char *corrigeString(char *string) {
	int cont;
	char *aux;

	cont = strlen(string);
	aux = (char *) malloc((cont+1)*sizeof(char));
	strcpy(aux, string);

	return aux;
}
