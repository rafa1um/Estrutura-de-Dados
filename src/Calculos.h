/*
	Autor: Renan Yuji Koga Ferreira
	Estrutura de Dados 2017
*/

#ifndef CALCULOS_H
#define CALCULOS_H

#include "Lista.h"
#include "Circulo.h"
#include "Retangulo.h"

	double calcularDistancia(double x1, double y1, double x2, double y2);
	/*
		Calcula e retorna a distância entre dois pontos (x1,y1) e (x2, y2).
			-x1: Primeiro ponto X
			-y1: Primeiro ponto Y
			-x2: Segundo ponto X
			-y2: Segundo ponto y
	*/

	int internoCirculo(Lista lc, Posic p, double x, double y);
	/*
		Verifica se o ponto (x,y) é interno ao Circulo de indicador p.
		Retorna 0 em caso negativo.
		Retorna 1 se o ponto for interno.
		Retorna 2 se o ponto tocar na borda (não é interno)
			-lc: Lista
			-p: Posic
			-x: Ponto X
			-y: Ponto Y
	*/

	int internoRetangulo(Lista lr, Posic p, double x, double y);
	/*
		Verifica se o ponto (x,y) é interno ao Retangulo de indicador p.
		Retorna 0 em caso negativo.
		Retorna 1 se o ponto for interno.
		Retorna 2 se o ponto tocar na borda (não é interno)
			-lr: Lista
			-p: Posic
			-x: Ponto X
			-y: Ponto Y
	*/

	int sobreposicaoCirculo(FILE *resultado, Lista sobreposicao, Lista lc, Posic p1, Posic p2);
	/*
		Verifica se dois Circulos indicados pelo Posic p1 e p2 se sobrepõem, em caso afirmativo, adiciona-se na Lista sobreposicao um retângulo de sobreposição e escreve no arquivo txt os identificadores das figuras que se sobrepõem.
		Retorna 0 em caso negativo.
		Retorna 1 se os Circulos se sobrepõem.
			-resultado: arquivo txt para escrita
			-sobreposicao: Lista
			-lc: Lista
			-p1: Posic
			-p2: Posic
	*/

	int sobreposicaoRetangulo(FILE *resultado, Lista sobreposicao, Lista lr, Posic p1, Posic p2);
	/*
		Verifica se dois Retangulos indicados pelo Posic p1 e p2 se sobrepõem, em caso afirmativo, adiciona-se na Lista sobreposicao um retângulo de sobreposição e escreve no arquivo txt os identificadores das figuras que se sobrepõem.
		Retorna 0 em caso negativo.
		Retorna 1 se os Retangulos se sobrepõem.
			-resultado: arquivo txt para escrita
			-sobreposicao: Lista
			-lr: Lista
			-p1: Posic
			-p2: Posic
	*/

	int sobreposicaoCirculoRetangulo(FILE *resultado, Lista sobreposicao, Lista lc, Lista lr, Posic p1, Posic p2);
	/*
		Verifica se duas figuras geométricas (Circulo/Retangulo) indicadas pelo Posic p1 e p2 se sobrepõem, em caso afirmativo, adiciona-se na Lista sobreposicao um retângulo de sobreposição e escreve no arquivo txt os identificadores das figuras que se sobrepõem.
		Retorna 0 em caso negativo.
		Retorna 1 se as figuras se sobrepõem.
			-resultado: arquivo txt para escrita
			-sobreposicao: Lista
			-lc: Lista
			-lr: Lista
			-p1: Posic
			-p2: Posic
	*/

#endif
