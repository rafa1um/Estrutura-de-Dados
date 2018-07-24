#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Calculos.h"

/*
Função que calcula e retorna a distância dos centros de duas figuras
d² = (x1-x2)² + (y1-y2)²
*/
double calcularDistancia(double x1, double y1, double x2, double y2) {
	double dist;

	dist =  pow((x1-x2), 2) + pow((y1-y2), 2);

	return sqrt(dist);
}

/*
Função que verifica se um ponto é interno a tal figura, e retorna um inteiro lógico
0 - Se o ponto não é interno
1 - Se o ponto é interno
2 - Se o ponto fica na borda da figura, porém não é interno
*/


/*Círculo*/
int internoCirculo(Lista lc, Posic p, double x, double y) {
	int logic=0;
	double x1, y1, dist;

	x1 = getCirculoX(get(lc, p));
	y1 = getCirculoY(get(lc, p));

	if (calcularDistancia(x, y, x1, y1) < getCirculoRaio(get(lc, p)))
		logic = 1;
	else if(calcularDistancia(x, y, x1, y1) < getCirculoRaio(get(lc, p)))
		logic = 2;

	return logic;
}

/*Retângulo*/
int internoRetangulo(Lista lr, Posic p, double x, double y) {
	int logic=0;
	double x1, y1, l1, h1;

	x1 = getRetanguloX(get(lr, p));
	y1 = getRetanguloY(get(lr, p));
	l1 = getRetanguloLargura(get(lr, p));
	h1 = getRetanguloAltura(get(lr, p));

	if (x > x1 && x < (x1+l1) && y > y1 && y < (y1+h1))
		logic = 1;
	else if (x >= x1 && x <= (x1+l1) && y >= y1 && y <= (y1+h1))
		logic = 2;

	return logic;
}

/*Função que verifica se duas figuras estão sobrepostas*/
int sobreposicaoCirculo(FILE *resultado, Lista sobreposicao, Lista lc, Posic p1, Posic p2) {
	int logic=0;
	double x1, y1, x2, y2, raio1, raio2, pontoX, pontoY, largura, altura;
	Retangulo retangulo;

	/*Dois Círculos*/

	x1 = getCirculoX(get(lc, p1));
	y1 = getCirculoY(get(lc, p1));
	raio1 = getCirculoRaio(get(lc, p1));

	x2 = getCirculoX(get(lc, p2));
	y2 = getCirculoY(get(lc, p2));
	raio2 = getCirculoRaio(get(lc, p2));

	if (calcularDistancia(x1, y1, x2, y2) < raio1+raio2)
		logic = 1;

	if (x1-raio1 < x2-raio2)
		pontoX = x1-raio1;
	else pontoX = x2-raio2;

	if (y1-raio1 < y2-raio2)
		pontoY = y1-raio1;
	else pontoY = y2-raio2;

	if (x1+raio1 > x2+raio2)
		largura = x1+raio1 - pontoX;
	else largura = x2+raio2 - pontoX;

	if (y1+raio1 > y2+raio2)
		altura = y1+raio1 - pontoY;
	else altura = y2+raio2 - pontoY;

	if (logic == 1){
		retangulo = (-1, pontoX, pontoY, altura, largura, "NULL");
		insert(sobreposicao, retangulo);
		fprintf(resultado, "As figuras %d %d se sobrepõem\n", getCirculoId(get(lc, p1)), getCirculoId(get(lc, p2)));
	}
	else {
		fprintf(resultado, "As figuras %d %d não se sobrepõem\n", getCirculoId(get(lc, p1)), getCirculoId(get(lc, p2)));
	}
}

/*Dois Retângulos*/
int sobreposicaoRetangulo(FILE *resultado, Lista sobreposicao, Lista lr, Posic p1, Posic p2) {
	int logic=0;
	double x1, y1, x2, y2, l1, h1, l2, h2, raio1, raio2, pontoX, pontoY, largura, altura;
	Retangulo retangulo;

	x1 = getRetanguloX(get(lr, p1));
	y1 = getRetanguloY(get(lr, p1));
	l1 = getRetanguloLargura(get(lr, p1));
	h1 = getRetanguloAltura(get(lr, p1));

	x2 = getRetanguloX(get(lr, p2));
	y2 = getRetanguloY(get(lr, p2));
	l2 = getRetanguloLargura(get(lr, p2));
	h2 = getRetanguloAltura(get(lr, p2));

	if (internoRetangulo(lr, p2, x1, y1) > 0 || internoRetangulo(lr, p2, x1+l1, y1) > 0 || internoRetangulo(lr, p2, x1, y1+h1) > 0 || internoRetangulo(lr, p2, x1+l1, y1+h1) > 0)
		logic = 1;

	if (x1 < x2)
		pontoX = x1;
	else pontoX = x2;

	if (y1 < y2)
		pontoY = y1;
	else pontoY = y2;

	if (x1+l1 > x2+l2)
		largura = x1+l1 - pontoX;
	else largura = x2+l2 - pontoX;

	if (y1+h1 > y2+h2)
		altura = y1+h1 - pontoY;
	else altura = y2+h2 - pontoY;

	if (logic == 1) {
		retangulo = (-1, pontoX, pontoY, altura, largura, "NULL");
		insert(sobreposicao, retangulo);
		fprintf(resultado, "As figuras %d %d se sobrepõem\n", getRetanguloId(get(lr, p1)), getRetanguloId(get(lr, p2)));
	}
	else {
		fprintf(resultado, "As figuras %d %d não se sobrepõem\n", getRetanguloId(get(lr, p1)), getRetanguloId(get(lr, p2)));
	}
}

/*Um Círculo e um Retângulo*/
int sobreposicaoCirculoRetangulo(FILE *resultado, Lista sobreposicao, Lista lc, Lista lr, Posic p1, Posic p2) {
	int logic=0;
	double x1, y1, x2, y2, l1, h1, l2, h2, raio1, raio2, pontoX, pontoY, largura, altura;
	Retangulo retangulo;

	x1 = getCirculoX(get(lc, p1));
	y1 = getCirculoY(get(lc, p1));
	raio1 = getCirculoRaio(get(lc, p1));

	x2 = getRetanguloX(get(lr, p2));
	y2 = getRetanguloY(get(lr, p2));
	l2 = getRetanguloLargura(get(lr, p2));
	h2 = getRetanguloAltura(get(lr, p2));

	if ((internoRetangulo(lr, p2, x1, y1) > 0))
		logic = 1;
	if ((internoCirculo(lc, p1, x2, y2) > 0) || (internoCirculo(lc, p1, x2+l2, y2) > 0) || (internoCirculo(lc, p1, x2, y2+h2) > 0) || (internoCirculo(lc, p1, x2+l2, y2+h2) > 0))
		logic = 1;
	if ((internoRetangulo(lr, p2, x1+raio1, y1) > 0) || (internoRetangulo(lr, p2, x1, y1-raio1) > 0) || (internoRetangulo(lr, p2, x1-raio1, y1) > 0) || (internoRetangulo(lr, p2, x1, y1+raio1) > 0))
		logic = 1;

	if (x1-raio1 < x2)
		pontoX = x1-raio1;
	else pontoX = x2;

	if (y1-raio1 < y2)
		pontoY = y1-raio1;
	else pontoY = y2;

	if (x1+raio1 > x2+l2)
		largura = x1+raio1 - pontoX;
	else largura = x2+l2 - pontoX;

	if (y1+raio1 > y2+h2)
		altura = y1+raio1 - pontoY;
	else altura = y2+h2 - pontoY;

	if (logic == 1) {
		retangulo = createRetangulo(-1, pontoX, pontoY, altura, largura, "NULL");
		insert(sobreposicao, retangulo);
		fprintf(resultado, "As figuras %d %d se sobrepõem\n", getCirculoId(get(lc, p1)), getRetanguloId(get(lr, p2)));
	}
	else {
		fprintf(resultado, "As figuras %d %d não se sobrepõem\n", getCirculoId(get(lc, p1)), getRetanguloId(get(lr, p2)));
	}
}
