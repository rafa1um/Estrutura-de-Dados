#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Procedimentos.h"

Lista parametroC(FILE *geo, Lista lc, double **lMax, double **hMax) {
	Circulo circulo;
	int id;
	char *cor;
	double x, y, raio;

	/*Leitura dos atributos de um Círculo*/
	lerCirculo(geo, &id, &raio, &x, &y, &cor);

	/*Calcular a Largura máxima e a Altura máxima para escrever no svg*/
	if (raio+x > **lMax)
		**lMax = raio+x;
	if (raio+y > **hMax)
	    **hMax = raio+y;

	/*Cria uma forma geométrica do tipo círculo*/
	if (raio <= 0)
		printf("Atributos inválidos!\nNão será possível criar um círculo!\n");
	else {
	    circulo = createCirculo(id, x, y, raio, cor);
	    insert(lc, circulo);
	}

	return lc;
}

Lista parametroR(FILE *geo, Lista lr, double **lMax, double **hMax) {
	Retangulo retangulo;
	int id;
	char *cor;
	double x, y, largura, altura;

	/*Leitura dos atributos de um Retângulo*/
   	lerRetangulo(geo, &id, &largura, &altura, &x, &y, &cor);

	/*Calcular a Largura máxima e a Altura máxima para escrever no svg*/
	if (largura+x > **lMax)
		**lMax = largura+x;
	if (altura+y > **hMax)
		**hMax = altura+y;

	/*Cria uma forma geométrica do tipo retângulo*/
	if (largura <= 0|| altura <= 0)
		printf("Atributos inválidos!\nNão será possível criar um retângulo!\n");

	else {
	   	retangulo = createRetangulo(id, x, y, altura, largura, cor);
	    insert(lr, retangulo);
	}

	return lr;
}

void parametroO(FILE *geo, FILE *resultado, Lista lc, Lista lr, Lista sobreposicao) {
	int id1, id2, logic=0, logic1=0, logic2=0, logicCirculo=0;
	Posic pc, pr, p1, p2;

	fscanf(geo, " %d %d", &id1, &id2);

	pc = getFirst(lc);
	pr = getFirst(lr);

	while (pc != NULL) {
		if (getCirculoId(get(lc, pc)) == id1) {
			p1 = pc;
			logic1 = 1;
		}
		if (getCirculoId(get(lc, pc)) == id2) {
			p2 = pc;
			logic2 = 1;
			logicCirculo = 1;
		}

		if (logic1 == 1 && logic2 == 1) {
			sobreposicaoCirculo(resultado, sobreposicao, lc, p1, p2);
			logic = 1;
			break;
		}

		pc = getNext(lc, pc);
	}

	if (logic == 0) {
		if (logic1 == 0 || logic2 == 0) {
			while (pr != NULL) {
				if (getRetanguloId(get(lr, pr)) == id1) {
					if (logicCirculo == 1) {
						p1 = p2;
						p2 = pr;
						break;
					}
					p1 = pr;
					logic1 = 1;
				}
				if (getRetanguloId(get(lr, pr)) == id2) {
					p2 = pr;
					logic2 = 1;
				}

				if (logic1 == 1 && logic2 == 1) {
					sobreposicaoRetangulo(resultado, sobreposicao, lr, p1, p2);
					logic = 1;
					break;
				}

				pr = getNext(lr, pr);
			}
		}
	}

	if (logic == 0) {
		sobreposicaoCirculoRetangulo(resultado, sobreposicao, lc, lr, p1, p2);
	}
}

void parametroI(FILE *geo, FILE *resultado, Lista lc, Lista lr) {
	int id, logic=0;
	double x, y;
	Posic pc, pr;

	fscanf(geo, " %d %lf %lf ", &id, &x, &y);

	pc = getFirst(lc);
	while(pc != NULL) {
		if (getCirculoId(get(lc, pc)) == id) {

			if (internoCirculo(lc, pc, x, y) == 1) {
				fprintf(resultado, "O ponto %lf,%lf é interno à figura %d\n", x, y, id);
			}
			else {
				fprintf(resultado, "O ponto %lf,%lf não é interno à figura %d\n", x, y, id);
			}

			logic = 1;
			break;
		}

		pc = getNext(lc, pc);
	}

	if (logic == 0) {
		pr = getFirst(lr);
		while(pr != NULL) {
			if (getRetanguloId(get(lr, pr)) == id) {

				if (internoRetangulo(lr, pr, x, y) == 1) {
					fprintf(resultado, "O ponto %lf %lf é interno à figura %d\n", x, y, id);
				}
				else {
					fprintf(resultado, "O ponto %lf %lf não é interno à figura %d\n", x, y, id);
				}

				logic = 1;
				break;
			}

			pr = getNext(lr, pr);
		}
	}
}

void parametroD(FILE *geo, FILE *resultado, Lista lc, Lista lr) {
	int id1, id2, logic1=0, logic2=0;
	double x1, y1, x2, y2, dist;
	Posic pc, pr;

	fscanf(geo, " %d %d ", &id1, &id2);

	pc = getFirst(lc);
	while(pc != NULL) {
		if (getCirculoId(get(lc, pc)) == id1) {
			x1 = getCirculoX(get(lc, pc));
			y1 = getCirculoY(get(lc, pc));
			logic1 = 1;
		}
		if (getCirculoId(get(lc, pc)) == id2) {
			x2 = getCirculoX(get(lc, pc));
			y2 = getCirculoY(get(lc, pc));
			logic2 = 1;
		}

		pc = getNext(lc, pc);
	}

	pr = getFirst(lr);
	while(pr != NULL) {
		if (getRetanguloId(get(lr, pr)) == id1) {
			x1 = getRetanguloX(get(lr, pr));
			x1 += getRetanguloLargura(get(lr,pr))/2;
			y1 = getRetanguloY(get(lr, pr));
			y1 += getRetanguloAltura(get(lr, pr))/2;

			logic1 = 1;
		}
		if (getRetanguloId(get(lr, pr)) == id2) {
			x2 = getRetanguloX(get(lr, pr));
			x2 += getRetanguloLargura(get(lr,pr))/2;
			y2 = getRetanguloY(get(lr, pr));
			y2 += getRetanguloAltura(get(lr, pr))/2;

			logic2 = 1;
		}

		pr = getNext(lr, pr);
	}

	if (logic1 == 1 && logic2 == 1) {
		dist = calcularDistancia(x1, y1, x2, y2);
		fprintf(resultado, "Distância: %d %d = %f\n", id1, id2, dist);
	}
	else fprintf(resultado, "%d %d %s\n", id1, id2, "Id(s) não encontrado!");
}

void parametroA(FILE *geo, Lista lc, Lista lr, char *nome, char *pathOut, double hMax, double lMax) {
	char *sufixo, *cor, *adicional, *dirAdicional;
	FILE *svgAdicional;

	sufixo = (char *) malloc(100000*sizeof(char));
	cor = (char *) malloc(100000*sizeof(char));

	fscanf(geo, " %s %s ", sufixo, cor);

	adicional = concatenaTraco(nome, sufixo);
	adicional = saidaSvg(adicional);
	dirAdicional = diretorio(pathOut, adicional);

	printf("ADICIONAL: %s\n", dirAdicional);

	svgAdicional = criarArquivo(dirAdicional);

	escreverSvgAdicional(svgAdicional, lc, lr, cor, hMax, lMax);

	fclose(svgAdicional);

	free(sufixo);
	free(cor);
	free(adicional);
	free(dirAdicional);
}

void parametroQ(FILE *geo, Cidade city, double **hMax, double **lMax, int **contInserir, char *Qcfill, char *Qcstrk) {
	double x, y, largura, altura;
	char *cep;
	Quadra square;

	lerQuadra(geo, &x, &y, &largura, &altura, &cep);

	/*Calcular a Largura máxima e a Altura máxima para escrever no svg*/
	if (largura+x > **lMax)
		**lMax = largura+x;
	if (altura+y > **hMax)
		**hMax = altura+y;

	if (largura <= 0 || altura <= 0) {
		printf("Atributos Inválidos!\n");
	}
	else {
		square = createQuadra(x, y, largura, altura, cep, Qcfill, Qcstrk);
		insereQuadra(city, square);
		(**contInserir)++;
	}
}

void parametroH(FILE *geo, Cidade city, char *Hcfill, char *Tcstrk) {
	double x, y;
	char *id;
	Hidrante hidra;

	lerHidrante(geo, &x, &y, &id);

	hidra = createHidrante(x, y, id, Hcfill, Tcstrk);
	insereHidrante(city, hidra);
}

void parametroS(FILE *geo, Cidade city, char *Scfill, char *Scstrk) {
	double x, y;
	char *id;
	Semaforo sinal;

	lerSemaforo(geo, &x, &y, &id);

	sinal = createSemaforo(x, y, id, Scfill, Scstrk);
	insereSemaforo(city, sinal);
}

void parametroT(FILE *geo, Cidade city, char *Tcfill, char *Tcstrk) {
	double x, y;
	char *id;
	Torre cel;

	lerTorre(geo, &x, &y, &id);

	cel = createTorre(x, y, id, Tcfill, Tcstrk);
	insereTorre(city, cel);
}

void parametroCq(FILE *geo, char **Qcfill, char **Qcstrk) {
	char *aux1, *aux2;

	aux1 = (char *) malloc(1000*sizeof(char));
	aux2 = (char *) malloc(1000*sizeof(char));

	fscanf(geo, " %s %s ", aux1, aux2);

	if (*Qcfill != NULL)
		free(*Qcfill);
	*Qcfill = corrigeString(aux1);

	if (*Qcstrk != NULL)
		free(*Qcstrk);
	*Qcstrk = corrigeString(aux2);

	free(aux1);
	free(aux2);
}

void parametroCh(FILE *geo, char **Hcfill, char **Hcstrk) {
	char *aux1, *aux2;

	aux1 = (char *) malloc(1000*sizeof(char));
	aux2 = (char *) malloc(1000*sizeof(char));

	fscanf(geo, " %s %s ", aux1, aux2);

	if (*Hcfill != NULL)
		free(*Hcfill);
	*Hcfill = corrigeString(aux1);

	if (*Hcstrk != NULL)
		free(*Hcstrk);
	*Hcstrk = corrigeString(aux2);

	free(aux1);
	free(aux2);
}

void parametroCs(FILE *geo, char **Scfill, char **Scstrk) {
	char *aux1, *aux2;

	aux1 = (char *) malloc(1000*sizeof(char));
	aux2 = (char *) malloc(1000*sizeof(char));

	fscanf(geo, " %s %s ", aux1, aux2);

	if (*Scfill != NULL)
		free(*Scfill);
	*Scfill = corrigeString(aux1);

	if (*Scstrk != NULL)
		free(*Scstrk);
	*Scstrk = corrigeString(aux2);

	free(aux1);
	free(aux2);
}

void parametroCt(FILE *geo, char **Tcfill, char **Tcstrk) {
	char *aux1, *aux2;

	aux1 = (char *) malloc(1000*sizeof(char));
	aux2 = (char *) malloc(1000*sizeof(char));

	fscanf(geo, " %s %s ", aux1, aux2);

	if (*Tcfill != NULL)
		free(*Tcfill);
	*Tcfill = corrigeString(aux1);

	if (*Tcstrk != NULL)
		free(*Tcstrk);
	*Tcstrk = corrigeString(aux2);

	free(aux1);
	free(aux2);
}

void parametroDq(FILE *qry, FILE *resultado, Cidade city, int **contRemover, int **contRemoverCompar) {
	double pX, pY, pLargura, pAltura, x, y, largura, altura;
	char *cep;
	Retangulo retangulo;
	Lista dq, lq;
	Posic p, pq;

	fscanf(qry, " %lf %lf %lf %lf ", &pX, &pY, &pLargura, &pAltura);

	dq = createLista();
	retangulo = createRetangulo(-1, pX, pY, pAltura, pLargura, "NULL");
	insert(dq, retangulo);
	p = getFirst(dq);

	lq = getListaQuadra(city);
	pq = getFirst(lq);

	while (pq != NULL) {
		(**contRemoverCompar)++;

		x = getQuadraX(get(lq, pq));
		y = getQuadraY(get(lq, pq));
		largura = getQuadraLargura(get(lq, pq));
		altura = getQuadraAltura(get(lq, pq));
		cep = getQuadraCep(get(lq, pq));

		pq = getNext(lq, pq);

		if (internoRetangulo(dq, p, x, y) == 1 && internoRetangulo(dq, p, x+largura, y) == 1 && internoRetangulo(dq, p, x, y+altura) == 1 && internoRetangulo(dq, p, x+largura, y+altura) == 1) {
			fprintf(resultado, "CEP: %s - Quadra removida com sucesso!\n", cep);
			removeQuadra(city, cep);
			(**contRemover)++;
		}
	}

	freeRetangulo(get(dq, p));
	remover(dq, p);
	free(dq);
}

void parametroDh(FILE *qry, FILE *resultado, Cidade city) {
	double pX, pY, pLargura, pAltura, x, y;
	char *id;
	Retangulo retangulo;
	Lista dh, lh;
	Posic p, ph;

	fscanf(qry, " %lf %lf %lf %lf ", &pX, &pY, &pLargura, &pAltura);

	dh = createLista();
	retangulo = createRetangulo(-1, pX, pY, pAltura, pLargura, "NULL");
	insert(dh, retangulo);
	p = getFirst(dh);

	lh = getListaHidrante(city);
	ph = getFirst(lh);

	while (ph != NULL) {
		x = getHidranteX(get(lh, ph));
		y = getHidranteY(get(lh, ph));
		id = getHidranteId(get(lh, ph));


		ph = getNext(lh, ph);

		if (internoRetangulo(dh, p, x, y) == 1) {
			fprintf(resultado, "ID: %s - Hidrante removido com sucesso!\n", id);
			removeHidrante(city, id);
		}
	}

	freeRetangulo(get(dh, p));
	remover(dh, p);
	free(dh);
}

void parametroDs(FILE *qry, FILE *resultado, Cidade city) {
	double pX, pY, pLargura, pAltura, x, y;
	char *id;
	Retangulo retangulo;
	Lista ds, ls;
	Posic p, ps;

	fscanf(qry, " %lf %lf %lf %lf ", &pX, &pY, &pLargura, &pAltura);

	ds = createLista();
	retangulo = createRetangulo(-1, pX, pY, pAltura, pLargura, "NULL");
	insert(ds, retangulo);
	p = getFirst(ds);

	ls = getListaSemaforo(city);
	ps = getFirst(ls);

	while (ps != NULL) {
		x = getSemaforoX(get(ls, ps));
		y = getSemaforoY(get(ls, ps));
		id = getSemaforoId(get(ls, ps));

		ps = getNext(ls, ps);

		if (internoRetangulo(ds, p, x, y) == 1) {
			fprintf(resultado, "ID: %s - Semáforo removido com sucesso!\n", id);
			removeSemaforo(city, id);
		}
	}

	freeRetangulo(get(ds, p));
	remover(ds, p);
	free(ds);
}

void parametroDt(FILE *qry, FILE *resultado, Cidade city) {
	double pX, pY, pLargura, pAltura, x, y;
	char *id;
	Retangulo retangulo;
	Lista dt, lt;
	Posic p, pt;

	fscanf(qry, " %lf %lf %lf %lf ", &pX, &pY, &pLargura, &pAltura);

	dt = createLista();
	retangulo = createRetangulo(-1, pX, pY, pAltura, pLargura, "NULL");
	insert(dt, retangulo);
	p = getFirst(dt);

	lt = getListaTorre(city);
	pt = getFirst(lt);

	while (pt != NULL) {
		x = getTorreX(get(lt, pt));
		y = getTorreY(get(lt, pt));
		id = getTorreId(get(lt, pt));

		pt = getNext(lt, pt);

		if (internoRetangulo(dt, p, x, y) == 1) {
			fprintf(resultado, "ID: %s - Torre removida com sucesso!\n", id);
			removeTorre(city, id);
		}
	}

	freeRetangulo(get(dt, p));
	remover(dt, p);
	free(dt);
}

void parametroDQ(FILE *qry, FILE *resultado, Cidade city, int **contRemover, int **contRemoverCompar) {
	double pX, pY, pLargura, pRaio, x, y, largura, altura;
	char *cep;
	Circulo circulo;
	Lista dq, lq;
	Posic p, pq;

	fscanf(qry, " %lf %lf %lf ", &pX, &pY, &pRaio);

	dq = createLista();
	circulo = createCirculo(-1, pX, pY, pRaio, "NULL");
	insert(dq, circulo);
	p = getFirst(dq);

	lq = getListaQuadra(city);
	pq = getFirst(lq);

	while (pq != NULL) {
		(**contRemoverCompar)++;

		x = getQuadraX(get(lq, pq));
		y = getQuadraY(get(lq, pq));
		largura = getQuadraLargura(get(lq, pq));
		altura = getQuadraAltura(get(lq, pq));
		cep = getQuadraCep(get(lq, pq));

		pq = getNext(lq, pq);


		if (internoCirculo(dq, p, x, y) == 1 && internoCirculo(dq, p, x+largura, y) == 1 && internoCirculo(dq, p, x, y+altura) == 1 && internoCirculo(dq, p, x+largura, y+altura) == 1) {
			fprintf(resultado, "CEP: %s - Quadra removida com sucesso!\n", cep);
			removeQuadra(city, cep);
			(**contRemover)++;
		}
	}

	freeCirculo(get(dq, p));
	remover(dq, p);
	free(dq);
}

void parametroDH(FILE *qry, FILE *resultado, Cidade city) {
	double pX, pY, pRaio, x, y;
	char *id;
	Circulo circulo;
	Lista dh, lh;
	Posic p, ph;

	fscanf(qry, " %lf %lf %lf ", &pX, &pY, &pRaio);

	dh = createLista();
	circulo = createCirculo(-1, pX, pY, pRaio, "NULL");
	insert(dh, circulo);
	p = getFirst(dh);

	lh = getListaHidrante(city);
	ph = getFirst(lh);

	while (ph != NULL) {
		x = getHidranteX(get(lh, ph));
		y = getHidranteY(get(lh, ph));
		id = getHidranteId(get(lh, ph));

		ph = getNext(lh, ph);

		if (internoCirculo(dh, p, x, y) == 1) {
			fprintf(resultado, "ID: %s - Hidrante removido com sucesso!\n", id);
			removeHidrante(city, id);
		}
	}

	freeCirculo(get(dh, p));
	remover(dh, p);
	free(dh);
}

void parametroDS(FILE *qry, FILE *resultado, Cidade city) {
	double pX, pY, pRaio, x, y;
	char *id;
	Circulo circulo;
	Lista ds, ls;
	Posic p, ps;

	fscanf(qry, " %lf %lf %lf ", &pX, &pY, &pRaio);

	ds = createLista();
	circulo = createCirculo(-1, pX, pY, pRaio, "NULL");
	insert(ds, circulo);
	p = getFirst(ds);

	ls = getListaSemaforo(city);
	ps = getFirst(ls);

	while (ps != NULL) {
		x = getSemaforoX(get(ls, ps));
		y = getSemaforoY(get(ls, ps));
		id = getSemaforoId(get(ls, ps));

		ps = getNext(ls, ps);

		if (internoCirculo(ds, p, x, y) == 1) {
			fprintf(resultado, "ID: %s - Semáforo removido com sucesso!\n", id);
			removeSemaforo(city, id);
		}
	}

	freeCirculo(get(ds, p));
	remover(ds, p);
	free(ds);
}

void parametroDT(FILE *qry, FILE *resultado, Cidade city) {
	double pX, pY, pRaio, x, y;
	char *id;
	Circulo circulo;
	Lista dt, lt;
	Posic p, pt;

	fscanf(qry, " %lf %lf %lf ", &pX, &pY, &pRaio);

	dt = createLista();
	circulo = createCirculo(-1, pX, pY, pRaio, "NULL");
	insert(dt, circulo);
	p = getFirst(dt);

	lt = getListaTorre(city);
	pt = getFirst(lt);

	while (pt != NULL) {
		x = getTorreX(get(lt, pt));
		y = getTorreY(get(lt, pt));
		id = getTorreId(get(lt, pt));

		pt = getNext(lt, pt);

		if (internoCirculo(dt, p, x, y) == 1) {
			fprintf(resultado, "ID: %s - Torre removida com sucesso!\n", id);
			removeTorre(city, id);
		}
	}

	freeCirculo(get(dt, p));
	remover(dt, p);
	free(dt);
}

void parametroCrd(FILE *qry, FILE *resultado, Cidade city) {
	char *aux, *identificador, *id;
	int cont=0, logic=0;
	double x, y;
	Lista lista;
	Posic p;

	aux = (char *) malloc(100000*sizeof(char));

	fscanf(qry, " %s ", aux);

	cont = strlen(aux);
	identificador = (char *) malloc((cont+1)*sizeof(char));
	strcpy(identificador, aux);

	lista = getListaQuadra(city);
	p = getFirst(lista);

	while (p != NULL) {
		id = getQuadraCep(get(lista, p));

		if (strcmp(identificador, id) == 0) {
			x = getQuadraX(get(lista, p));
			y = getQuadraY(get(lista, p));

			fprintf(resultado, "Identificação: %s (%f, %f)\t - \tQuadra \n", id, x, y);

			logic = 1;
			break;
		}

		p = getNext(lista, p);
	}

	if (logic == 0) {
		lista = getListaHidrante(city);
		p = getFirst(lista);

		while (p != NULL) {
			id = getHidranteId(get(lista, p));

			if (strcmp(identificador, id) == 0) {
				x = getHidranteX(get(lista, p));
				y = getHidranteY(get(lista, p));

				fprintf(resultado, "Identificação: %s (%f, %f)\t - \tHidrante \n", id, x, y);

				logic = 1;
				break;
			}

			p = getNext(lista, p);
		}
	}

	if (logic == 0) {
		lista = getListaSemaforo(city);
		p = getFirst(lista);

		while (p != NULL) {
			id = getSemaforoId(get(lista, p));

			if (strcmp(identificador, id) == 0) {
				x = getSemaforoX(get(lista, p));
				y = getSemaforoY(get(lista, p));

				fprintf(resultado, "Identificação: %s (%f, %f)\t - \tSemaforo \n", id, x, y);

				logic = 1;
				break;
			}

			p = getNext(lista, p);
		}
	}

	if (logic == 0) {
		lista = getListaTorre(city);
		p = getFirst(lista);

		while (p != NULL) {
			id = getTorreId(get(lista, p));

			if (strcmp(identificador, id) == 0) {
				x = getTorreX(get(lista, p));
				y = getTorreY(get(lista, p));

				fprintf(resultado, "Identificação: %s (%f, %f)\t - \tTorre \n", id, x, y);

				logic = 1;
				break;
			}

			p = getNext(lista, p);
		}
	}

	free(aux);
	free(identificador);
}
