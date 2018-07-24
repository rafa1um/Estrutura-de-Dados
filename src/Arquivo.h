/*
	Autor: Renan Yuji Koga Ferreira
	Estrutura de Dados 2017
*/

#ifndef ARQUIVO_H
#define ARQUIVO_H

#include "Cidade.h"
#include "Lista.h"
#include "Circulo.h"
#include "Retangulo.h"
#include "Operacoes_de_String.h"
#include "Processamentos.h"
#include "Procedimentos.h"

	void ArqGeo(FILE *geo, FILE *resultado, Cidade city, Lista lc, Lista lr, Lista sobreposicao, char *nome, char *pathOut, double *lMax, double *hMax, int *contInserir);
	/*
		Processa o arquivo geo, inserindo os equipamentos urbanos em city, círculos em lc e retângulos em lr, dependendo do comando lido no arquivo geo. As variáveis hMax e lMax são para obter a altura e a largura do arquivo SVG que será criado.
			-geo: Arquivo geo de leitura
			-resultado: Arquivo txt para escrita
			-city: Cidade
			-lc: Lista
			-lr: Lista
			-sobreposicao: Lista
			-nome: String
			-pathOut: String
			-hMax: Altura do SVG
			-lMax: Largura do SVG
			-contInserir: Contador para Quadra(s) inserida(s)
	*/

	void ArqQry(FILE *qry, FILE *resultado, Cidade city, int *contRemover, int *contRemoverCompar);
	/*
		Processa o arquivo qry na Cidade city e escreve no arquivo .txt dependendo do comando lido no arquivo qry.
		 	-qry: Arquivo qry de leitura
			-resultado: Arquivo txt para escrita
			-city: Cidade
			-contRemover: Contador para Quadra(s) removida(s)
			-contRemoverCompar: Contador para quantidade de comparações feitas para remover Quadra(s)
	*/

	void escreverSvg(Cidade city, Lista lc, Lista lr, Lista sobreposicao, char *nomeArq, char *pathOut, double hMax, double lMax);
	/*
		Escreve em um arquivo SVG (que é criado dentro desse procedimento, através das strings 'nomeArq' e 'pathOut') de altura hMax e largura lMax, os equipamentos urbanos, Circulos, Retangulos e retângulos de sobreposição.
			-city: Cidade
			-lc: Lista
			-lr: Lista
			-sobreposicao: Lista
			-nomeArq: String
			-pathOut: String
			-hMax: Altura do SVG
			-lMax: Largura do SVG
	*/

	void escreverSvgAdicional(FILE *svgAdicional, Lista lc, Lista lr, char *cor, double hMax, double lMax);
	/*
		Escreve em um arquivo SVG de altura hMax e largura lMax, círculos de cor 'cor', representando os centros dos Circulos e vértices dos Retangulos.
			-svgAdicional: arquivo SVG
			-lc: Lista
			-lr: Lista
			-cor: String
			-hMax: Altura do SVG
			-lMax: Largura do SVG
	*/

	void processaResumo(char *pathOut, char *nome, char *arqQry, int logic, int contInserir, int contRemover, int contRemoverCompar);
	/*
		Cria ou se dá append em um arquivo 'reumo.txt' dependendo do valor do logic, e escreve-se nele o nome do arquivo que foi usado na bateria de teste (com base nas strings 'nome' e 'arqQry') e a quantidade de comparações para inserir e remover uma Quadra, e a quatidade de Quadras inseridas e removidas.
		 	-nome: String
			-arqQry: String
			-logic: variável lógicas
			-contInserir: Quantidade de Quadra(s) inserida(s)
			-contRemover: Quantidade de Quadra(s) removida(s)
			-contRemoverCompar: Quantidade de comparações feitas para remover a(s) Quadra(s)
	*/

	void liberaCirculo(Lista lc);
	/*
		Desaloca a memória utilizada pela Lista lc, liberando todo o seu conteúdo.
			-lc: Lista
	*/

	void liberaRetangulo(Lista lr);
	/*
		Desaloca a memória utilizada pela Lista lr, liberando todo o seu conteúdo.
			-lr: Lista
	*/

	void liberaSobreposicao(Lista sobreposicao);
	/*
		Desaloca a memória utilizada pela Lista sobreposicao, liberando todo o seu conteúdo.
			-sobreposicao: Lista
	*/

	void liberaStrings(char *nome, char *pathIn, char *pathOut, char *nomeArq, char *arqQry, char *dir);
	/*
		Desaloca a memória utilizada pelas strings.
			-nome: String
			-pathIn: String
			-pathOut: String
			-nomeArq: String
			-arqQry: String
			-dir: String
	*/

#endif
