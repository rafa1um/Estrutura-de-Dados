#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Processamentos.h"
#include "Arquivo.h"

void ArqGeo(FILE *geo, FILE *resultado, Cidade city, Lista lc, Lista lr, Lista sobreposicao, char *nome, char *pathOut, double *lMax, double *hMax, int *contInserir) {

	char *Qcfill=NULL, *Qcstrk=NULL, *Hcfill=NULL, *Hcstrk=NULL, *Scfill=NULL, *Scstrk=NULL, *Tcfill=NULL, *Tcstrk=NULL;
	char comando;

	while (!feof(geo)) {
		/*Obtém o comando*/
		fscanf(geo, "%c", &comando);

		switch (comando) {
			case 'c':

				fscanf(geo, "%c", &comando);

				switch (comando) {
					case ' ':
						parametroC(geo, lc, &lMax, &hMax);
						break;

					case 'q':
						parametroCq(geo, &Qcfill, &Qcstrk);
						break;

					case 'h':
						parametroCh(geo, &Hcfill, &Hcstrk);
						break;

					case 's':
						parametroCs(geo, &Scfill, &Scstrk);
						break;

					case 't':
						parametroCt(geo, &Tcfill, &Tcstrk);
						break;
				}

				break;

			case 'r':
				parametroR(geo, lr, &lMax, &hMax);
				break;

			case 'o':
				parametroO(geo, resultado, lc, lr, sobreposicao);
				break;

			case 'i':
				parametroI(geo, resultado, lc, lr);
				break;

			case 'd':
				parametroD(geo, resultado, lc, lr);
				break;

			case 'a':
				parametroA(geo, lc, lr, nome, pathOut, *hMax, *lMax);
				break;

			case 'q':
				parametroQ(geo, city, &hMax, &lMax, &contInserir, Qcfill, Qcstrk);
				break;

			case 'h':
				parametroH(geo, city, Hcfill, Hcstrk);
				break;

			case 's':
				parametroS(geo, city, Scfill, Scstrk);
				break;

			case 't':
				parametroT(geo, city, Tcfill, Tcstrk);
				break;

			case '#':
				break;

			default:
				break;
		}
	}

	free(Qcfill);
	free(Qcstrk);
	free(Hcfill);
	free(Hcstrk);
	free(Scfill);
	free(Scstrk);
	free(Tcfill);
	free(Tcstrk);
}

void ArqQry(FILE *qry, FILE *resultado, Cidade city, int *contRemover, int *contRemoverCompar) {
	char *comando;

	comando = (char *) calloc(5, sizeof(char));

	while (!feof(qry)) {
		fscanf(qry, " %s ", comando);

		if (strcmp(comando, "dq") == 0) {
			parametroDq(qry, resultado, city, &contRemover, &contRemoverCompar);
		}
		else if (strcmp(comando, "dh") == 0) {
			parametroDh(qry, resultado, city);
		}
		else if (strcmp(comando, "ds") == 0) {
			parametroDs(qry, resultado, city);
		}
		else if (strcmp(comando, "dt") == 0) {
			parametroDt(qry, resultado, city);
		}
		else if (strcmp(comando, "Dq") == 0) {
			parametroDQ(qry, resultado, city, &contRemover, &contRemoverCompar);
		}
		else if (strcmp(comando, "Dh") == 0) {
			parametroDH(qry, resultado, city);
		}
		else if (strcmp(comando, "Ds") == 0) {
			parametroDS(qry, resultado, city);
		}
		else if (strcmp(comando, "Dt") == 0) {
			parametroDT(qry, resultado, city);
		}
		else if (strcmp(comando, "crd?") == 0) {
			parametroCrd(qry, resultado, city);
		}
		else {
			printf("Comando Inválido!\n");
		}
	}

	free(comando);
}

void circuloSvg(FILE *saida, Lista lc) {
	int i, tamanho;
	Posic pc;

	pc = getFirst(lc);
	tamanho = length(lc);
	for (i=0; i<tamanho; i++) {
		escreverCirculo(get(lc, pc), saida, "NULL");
		pc = getNext(lc, pc);
	}
}

void retanguloSvg(FILE *saida, Lista lr) {
	int i, tamanho;
	Posic pr;

	pr = getFirst(lr);
	tamanho = length(lr);
	for (i=0; i<tamanho; i++) {
		escreverRetangulo(get(lr, pr), saida, "NULL");
		pr = getNext(lr, pr);
	}
}

void sobreposicaoSvg(FILE *saida, Lista sobreposicao) {
	double x, y, altura, largura;
	Posic p;

	p = getFirst(sobreposicao);

	while (p != NULL) {
		x = getRetanguloX(get(sobreposicao, p));
		y = getRetanguloY(get(sobreposicao, p));
		altura = getRetanguloAltura(get(sobreposicao, p));
		largura = getRetanguloLargura(get(sobreposicao, p));

		fprintf(saida, "\t<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" fill=\"none\"\n", x-3.0, y-3.0, largura+6.0, altura+6.0);
		fprintf(saida, "\t\tstyle=\"stroke:%s;stroke-width:3;stroke-dasharray:5,5\" />\n", "gray");
		fprintf(saida, "\t<text x=\"%lf\" y=\"%lf\" fill=\"%s\">sobrepõem</text>\n", x, y+10.5, "black");

		p = getNext(sobreposicao, p);
	}
}

void escreverSvg(Cidade city, Lista lc, Lista lr, Lista sobreposicao, char *nomeArq, char *pathOut, double hMax, double lMax) {
	int cont;
	char *svg, *nome;
	FILE *arqSvg;

	/*Criação do arquivo svg padrão*/
	cont = strlen(nomeArq);
	nome = (char *) malloc((cont+1)*sizeof(char));
	strcpy(nome, nomeArq);

	nome = saidaSvg(nome);
	svg = diretorio(pathOut, nome);
	printf("SVG: %s\n", svg);
	arqSvg = criarArquivo(svg);

	/*Inicia o arquivo svg com altura 0 e largura 0 para ser alterado depois que obtver a maior altura e largura*/
	fprintf(arqSvg, "<svg height=\"%lf\" width=\"%lf\">", hMax, lMax);

	circuloSvg(arqSvg, lc);
	retanguloSvg(arqSvg, lr);
	escreverCidade(arqSvg, city);
	sobreposicaoSvg(arqSvg, sobreposicao);
	fprintf(arqSvg, "\n</svg>\n");

	fclose(arqSvg);

	free(nome);
	free(svg);
}

void escreverSvgAdicional(FILE *svgAdicional, Lista lc, Lista lr, char *cor, double hMax, double lMax) {
	Posic pc, pr;

	fprintf(svgAdicional, "<svg height=\"%lf\" width=\"%lf\">", hMax, lMax);

	pc = getFirst(lc);
	while (pc != NULL) {
		escreverCirculo(get(lc, pc), svgAdicional, cor);

		pc = getNext(lc, pc);
	}

	pr = getFirst(lr);
	while (pr != NULL) {
		escreverRetangulo(get(lr, pr), svgAdicional, cor);

		pr = getNext(lr, pr);
	}

	fprintf(svgAdicional, "</svg>\n");

}

void processaResumo(char *pathOut, char *nome, char *arqQry, int logic, int contInserir, int contRemover, int contRemoverCompar) {
  char *nomeResumo, *arqResumo;
	int cont;
  FILE *resumo;

	arqResumo = diretorio(pathOut, "resumo.txt");

	printf("RESUMO: %s\n", arqResumo);

  resumo = arquivoResumo(logic, arqResumo);

	if (arqQry != NULL) {
		fprintf(resumo, "%s.geo - %s.qry\t\t%d\t\t0\t\t%d\t\t%d\n", nome, arqQry, contInserir, contRemover, contRemoverCompar);
 	}
	else {
		fprintf(resumo, "%s.geo\t\t%d\t\t0\t\t%d\t\t%d\n", nome, contInserir, contRemover, contRemoverCompar);
	}
  fclose(resumo);

	free(arqResumo);
}

void liberaCirculo(Lista lc) {
	Posic pc, pAux;

	pc = getFirst(lc);

	while(pc != NULL) {
		freeCirculo(get(lc, pc));
		pAux = getNext(lc, pc);
		remover(lc, pc);

		pc = pAux;
	}

	free(lc);
}

void liberaRetangulo(Lista lr) {
	Posic pr, pAux;

	pr = getFirst(lr);

 	while(pr != NULL) {
		freeRetangulo(get(lr, pr));
		pAux = getNext(lr, pr);
		remover(lr, pr);

		pr = pAux;
	}

	free(lr);
}

void liberaSobreposicao(Lista sobreposicao) {
	Posic ps;

	ps = getFirst(sobreposicao);

	while(ps != NULL) {
		freeRetangulo(get(sobreposicao, ps));
		remover(sobreposicao, ps);

		ps = getNext(sobreposicao, ps);
	}

	free(sobreposicao);
}

void liberaStrings(char *nome, char *pathIn, char *pathOut, char *nomeArq, char *arqQry, char *dir) {
	free(nome);
	free(pathIn);
	free(pathOut);
	free(nomeArq);
	free(dir);
	free(arqQry);
}
