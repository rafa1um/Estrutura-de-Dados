/*RENAN YUJIJ KOGA FERREIRA*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Cidade.h"
#include "Lista.h"
#include "Operacoes_de_String.h"
#include "Procedimentos.h"
#include "Processamentos.h"
#include "Arquivo.h"

int main(int argc, char *argv[]) {

	int logic, cont, contInserir=0, contRemover=0, contRemoverCompar=0;
	double lMax=0, hMax=0;
	char *nome, *pathIn, *pathOut, *arqQry, *nomeArq, *dir, *nomeQry=NULL, *nomeGeoQry=NULL;

	FILE *geo, *qry, *resultado, *resultadoQry, *resumo;
	Cidade city;
	Lista lc, lr, sobreposicao;

	city = createCidade();
	lc = createLista();
	lr = createLista();
	sobreposicao = createLista();

	nome = (char *) malloc(100000*sizeof(char));
	pathIn = (char *) malloc(100000*sizeof(char));
	pathOut = (char *) malloc(100000*sizeof(char));
	arqQry = (char *) malloc(100000*sizeof(char));

	logic = Argumentos(argc, argv, &pathIn, &pathOut, &nome, &arqQry);

	pathOut = verificaBarra(pathOut);
	printf("NOME: %s\n", nome);
	nomeArq = nomeBase(nome);
	printf("NOMEARQ: %s\n", nomeArq);

	if (logic%7 == 0) {
		pathIn = verificaBarra(pathIn);
		dir = diretorio(pathIn, nome);
	}
	else {
		cont = strlen(nome);
		dir = (char *) malloc((cont+1)*sizeof(char));
		strcpy(dir, nome);
	}
	printf("ARQUIVO DE ENTRADA: %s\n", dir);

	/*Arquivo geo de entrada*/
	geo = abrirArquivo(dir);
	if (geo == NULL) {
		return 0;
	}

	/*Criação do arquivo txt padrão*/
	resultado = arquivoTxt(nome, pathOut);

	ArqGeo(geo, resultado, city, lc, lr, sobreposicao, nomeArq, pathOut, &lMax, &hMax, &contInserir);
	fclose(geo);

	if (logic%2 == 0) {
		qry = arquivoQry(pathIn, arqQry, logic);

		if (qry == NULL) {
			return 0;
		}

		else {
			nomeQry = nomeBase(arqQry);
			nomeGeoQry = concatenaTraco(nomeArq, nomeQry);

			resultadoQry = arquivoTxt(nomeGeoQry, pathOut);

			ArqQry(qry, resultadoQry, city, &contRemover, &contRemoverCompar);
			fclose(qry);


			escreverSvg(city, lc, lr, sobreposicao, nomeGeoQry, pathOut, hMax, lMax);

			fclose(resultadoQry);
		}
	}

	fclose(resultado);

	if (logic%2 != 0) {
		escreverSvg(city, lc, lr, sobreposicao, nomeArq, pathOut, hMax, lMax);
	}

	if (logic%3 == 0 || logic%5 == 0) {
		processaResumo(pathOut, nomeArq, nomeQry, logic, contInserir, contRemover, contRemoverCompar);
	}

	apocalypse(city);
	liberaCirculo(lc);
	liberaRetangulo(lr);
	liberaSobreposicao(sobreposicao);
	liberaStrings(nome, pathIn, pathOut, nomeArq, arqQry, dir);
	if (nomeQry != NULL) {
		free(nomeQry);
	}
	if (nomeGeoQry != NULL)
		free(nomeGeoQry);

	printf("Programa realizado com sucesso!\n");

	return 0;
}

/*RENAN YUJI KOGA FERREIRA*/
