/*
	Autor: Renan Yuji Koga Ferreira
	Estrutura de Dados 2017
*/

#ifndef PROCEDIMENTOS_H
#define PROCEDIMENTOS_H

#include "Cidade.h"
#include "Lista.h"
#include "Circulo.h"
#include "Retangulo.h"
#include "Calculos.h"
#include "Operacoes_de_String.h"
#include "Processamentos.h"
#include "Procedimentos.h"

	Lista parametroC(FILE *geo, Lista lc, double **lMax, double **hMax);
	/*
		Recebe os atributos para criar um Circulo. Os atributos precisam ser válidos (raio positivo e centro não negativo).
			-geo: Arquivo geo de leitura
			-lc: Lista
			-hMax: Altura do SVG
			-lMax: Largura do SVG
	*/

	Lista parametroR(FILE *geo, Lista lr, double **lMax, double **hMax);
	/*
		Recebe os atributos para criar um Retangulo. Os atributos precisam ser válidos (largura e altura positivos e ponto âncora não negativos).
			-geo: Arquivo geo de leitura
			-lr: Lista
			-hMax: Altura do SVG
			-lMax: Largura do SVG
	*/

	void parametroD(FILE *geo, FILE *resultado, Lista lc, Lista lr);
	/*
		Recebe dois identificadores obtidos no arquivo geo para calcular a distância entre os centros de massa destes. Os identificadores precisam ser válidos.
			-geo: arquivo geo de leitura
			-resultado: arquivo txt para escrita
			-lc: Lista
			-lr: Lista
	*/

	void parametroI(FILE *geo, FILE *resultado, Lista lc, Lista lr);
	/*
		Recebe um identificador e um ponto (x,y) obtidos no arquivo geo para verificar se o ponto é interno à figura de tal identificador. O identificador precisa ser válido.
			-geo: arquivo geo de leitura
			-resultado: arquivo txt para escrita
			-lc: Lista
			-lr: Lista
	*/

	void parametroO(FILE *geo, FILE *resultado, Lista lc, Lista lr, Lista sobreposicao);
	/*
		Recebe dois identificadores obtidos no arquivo geo para verificar se estes se sobrepõem. Os identificadores precisam ser válidos.
			-geo: arquivo geo de leitura
			-resultado: arquivo txt para escrita
			-lc: Lista
			-lr: Lista
			-sobreposicao: Lista
	*/

	void parametroA(FILE *geo, Lista lc, Lista lr, char *nome, char *pathOut, double hMax, double lMax);
	/*
		Cria um arquivo SVG de altura hMax e largura lMax, círculos representando os centros dos Circulos e vértices dos Retangulos.
			-geo: arquivo geo de leitura
			-lc: Lista
			-lr: Lista
			-nome: String
			-pathOut: String
			-hMax: Altura do SVG
			-lMax: Largura do SVG
	*/

	void parametroQ(FILE *geo, Cidade city, double **hMax, double **lMax, int **contInserir, char *cfill, char *cstrk);
	/*
		Insere uma Quadra na Cidade city, caso os atributos sejam válidos.
			-geo: Arquivo geo de leitura
			-city: Cidade
			-hMax: Altura do arquivo SVG
			-lMax: Largura do arquivo SVG
			-contInserir: Contador de Quadra(s) inserida(s)
			-Qcfill: Cor de preenchimento da Quadra
			-Qcstrk: Cor da borda da Quadra
	*/

	void parametroH(FILE *geo, Cidade city, char *Hcfill, char *Hcstrk);
	/*
		Insere um Semaforo na Cidade city, caso os atributos sejam válidos.
			-geo: Arquivo geo de leitura
			-city: Cidade
			-Hcfill: Cor de preenchimento do Hidrante
			-Hcstrk: Cor da borda do Hidrante
	*/

	void parametroS(FILE *geo, Cidade city, char *Scfill, char *Scstrk);
	/*
		Insere um Semaforo na Cidade city, caso os atributos sejam válidos.
			-geo: Arquivo geo de leitura
			-city: Cidade
			-Scfill: Cor de preenchimento do Semaforo
			-Scstrk: Cor da borda do Semaforo
	*/

	void parametroT(FILE *geo, Cidade city, char *Tcfill, char *Tcstrk);
	/*
		Insere uma Torre na Cidade city, caso os atributos sejam válidos.
			-geo: Arquivo geo de leitura
			-city: Cidade
			-Tcfill: Cor de preenchimento da Torre
			-Tcstrk: Cor da borda da Torre
	*/

	void parametroCq(FILE *geo, char **Qcfill, char **Qcstrk);
	/*
		Recebe a cor de borda e de preenchimento da Quadra. Caso tivesse uma cor definida antes, a string contendo a cor anterior é liberada armazenando a nova na atual string.
			-geo: Arquivo geo de leitura
			-Qcfill: Cor de preenchimento da Quadra
			-Qcstrk: Cor da borda da Quadra
	*/

	void parametroCh(FILE *geo, char **Hcfill, char **Hcstrk);
	/*
		Recebe a cor de borda e de preenchimento do Hidrante. Caso tivesse uma cor definida antes, a string contendo a cor anterior é liberada armazenando a nova na atual string.
			-geo: Arquivo geo de leitura
			-Hcfill: Cor de preenchimento do Hidrante
			-Hcstrk: Cor da borda do Hidrante
	*/

	void parametroCs(FILE *geo, char **Scfill, char **Scstrk);
	/*
		Recebe a cor de borda e de preenchimento do Semaforo. Caso tivesse uma cor definida antes, a string contendo a cor anterior é liberada armazenando a nova na atual string.
			-geo: Arquivo geo de leitura
			-Scfill: Cor de preenchimento do Semaforo
			-Scstrk: Cor da borda do Semaforo
	*/

	void parametroCt(FILE *geo, char **Tcfill, char **Tcstrk);
	/*
		Recebe a cor de borda e de preenchimento da Torre. Caso tivesse uma cor definida antes, a string contendo a cor anterior é liberada armazenando a nova na atual string.
			-geo: Arquivo geo de leitura
			-Tcfill: Cor de preenchimento da Torre
			-Tcstrk: Cor da borda da Torre
	*/

	void parametroDq(FILE *qry, FILE *resultado, Cidade city, int **contRemover, int **contRemoverCompar);
	/*
		Remove Quadra(s) da Cidade city de acordo com a região retangular obtida através do arquivo de leitura, e escreve o Quadra removido no arquivo txt.
			-qry: Arquivo qry de leitura
			-resultado: Arquivo txt para escrita
			-city: Cidade
			-contRemover: Contador para Quadra(s) removida(s)
			-contRemoverCompar: Contador para quantidade de comparações feitas para remover a(s) Quadra(s)
	*/

	void parametroDh(FILE *qry, FILE *resultado, Cidade city);
	/*
		Remove Hidrante(s) da Cidade city de acordo com a região retangular obtida através do arquivo de leitura, e escreve o Hidrante removido no arquivo txt.
			-qry: Arquivo qry de leitura
			-resultado: Arquivo txt para escrita
			-city: Cidade
	*/

	void parametroDs(FILE *qry, FILE *resultado, Cidade city);
	/*
		Remove Semaforo(s) da Cidade city de acordo com a região retangular obtida através do arquivo de leitura, e escreve o Semaforo removido no arquivo txt.
			-qry: Arquivo qry de leitura
			-resultado: Arquivo txt para escrita
			-city: Cidade
	*/

	void parametroDt(FILE *qry, FILE *resultado, Cidade city);
	/*
		Remove Torre(s) da Cidade city de acordo com a região retangular obtida através do arquivo de leitura, e escreve o Torre removido no arquivo txt.
			-qry: Arquivo qry de leitura
			-resultado: Arquivo txt para escrita
			-city: Cidade
	*/

	void parametroDQ(FILE *qry, FILE *resultado, Cidade city, int **contRemover, int **contRemoverCompar);
	/*
		Remove Quadra(s) da Cidade city de acordo com a região circular obtida através do arquivo de leitura, e escreve o Quadra removido no arquivo txt.
			-qry: Arquivo qry de leitura
			-resultado: Arquivo txt para escrita
			-city: Cidade
			-contRemover: Contador para Quadra(s) removida(s)
			-contRemoverCompar: Contador para quantidade de comparações feitas para remover a(s) Quadra(s)
	*/

	void parametroDH(FILE *qry, FILE *resultado, Cidade city);
	/*
		Remove Hidrante(s) da Cidade city de acordo com a região circular obtida através do arquivo de leitura, e escreve o Hidrante removido no arquivo txt.
			-qry: Arquivo qry de leitura
			-resultado: Arquivo txt para escrita
			-city: Cidade
	*/

	void parametroDS(FILE *qry, FILE *resultado, Cidade city);
	/*
		Remove Semaforo(s) da Cidade city de acordo com a região circular obtida através do arquivo de leitura, e escreve o Semaforo removido no arquivo txt.
			-qry: Arquivo qry de leitura
			-resultado: Arquivo txt para escrita
			-city: Cidade
	*/

	void parametroDT(FILE *qry, FILE *resultado, Cidade city);
	/*
		Remove Torre(s) da Cidade city de acordo com a região circular obtida através do arquivo de leitura, e escreve o Torre removido no arquivo txt.
			-qry: Arquivo qry de leitura
			-resultado: Arquivo txt para escrita
			-city: Cidade
	*/

	void parametroCrd(FILE *qry, FILE *resultado, Cidade city);
	/*
		Dado um identificador obtido no arquivo geo, ele escreve no arquivo txt qual é o tipo de equipamento urbano que possui tal identificador na Cidade city.
		 	-qry: Arquivo qry de leitura
			-resultado: Arquivo txt para escrita
			-city: Cidade
	*/

#endif
