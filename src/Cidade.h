/*
	Autor: Renan Yuji Koga Ferreira
	Estrutura de Dados 2017
*/

#ifndef CIDADE_H
#define CIDADE_H

/*
	TAD's necessários para o TAD Cidade
*/
#include "Lista.h"
#include "Quadra.h"
#include "Hidrante.h"
#include "Semaforo.h"
#include "Torre.h"

	typedef void *Cidade;
	/*
		Tipo Abstrato Cidade

			Uma cidade é definida pelo conjunto de equipamentos urbanos contidos nela, estes são: quadra(s), hidrante(s), semaforo(s) e torre(s).
	*/

	Cidade createCidade();
	/*
		Cria e retorna uma Cidade contendo uma Lista para cada equipamento urbano (Quadra, Hidrante, Semaforo, Torre).
	*/

	int insereQuadra(Cidade c, Quadra q);
	/*
		Insere uma Quadra na Cidade
			-c: Uma Cidade.
			-q: Uma Quadra.
	*/

	int insereSemaforo(Cidade c, Semaforo s);
	/*
		Insere um Semaforo na Cidade
			-c: Uma Cidade.
			-s: Um Semáforo.
	*/

	int insereTorre(Cidade c, Torre t);
	/*
		Insere uma Torre na Cidade
			-c: Uma Cidade.
			-t: Uma Torre.

	*/

	int insereHidrante(Cidade c, Hidrante h);
	/*
		Insere um Hidrante na Cidade
			-c: Uma Cidade.
			-h: Uma Hidrante.
	*/

	Quadra getQuadra(Cidade c, char *cep);
	/*
		Retorna uma Quadra de uma Cidade de CEP cep
			-c: Uma Cidade.
			-cep: Identificador de uma Quadra.
	*/

	Hidrante getHidrante(Cidade c, char *id);
	/*
	Retorna um Hidrante de uma Cidade de identificador id
	-c: Uma Cidade.
	-id: Identificador de um Hidrante.
	*/

	Semaforo getSemaforo(Cidade c, char *id);
	/*
		Retorna um Semaforo de uma Cidade de identificador id
			-c: Uma Cidade.
			-id: Identificador de um Semaforo.
	*/

	Torre getTorre(Cidade c, char *id);
	/*
		Retorna uma Torre de uma Cidade de identificador id
			-c: Uma Cidade.
			-id: Identificador de uma Torre.
	*/

	void escreverCidade(FILE *saida, Cidade c);
	/*
		Escreve uma Cidade em um arquivo SVG saida, com todos os seus equipamentos urbanos (se houver)
			-saida: Um arquivo.
			-c: Uma Cidade.
	*/

	Lista getListaQuadra(Cidade c);
	/*
		Retorna a Lista de Quadra (o conjunto de quadras) de uma Cidade c
		 	-c: Cidade.
	*/

	Lista getListaHidrante(Cidade c);
	/*
		Retorna a Lista de Hidrante (o conjunto de hidrantes) de uma Cidade c
		 	-c: Cidade.
	*/

	Lista getListaSemaforo(Cidade c);
	/*
		Retorna a Lista de Semaforo (o conjunto de semáforos) de uma Cidade c
		 	-c: Cidade.
	*/

	Lista getListaTorre(Cidade c);
	/*
		Retorna a Lista de Torre (o conjunto de torres) de uma Cidade c
		 	-c: Cidade.
	*/

	void removeQuadra(Cidade c, char *cep);
	/*
		Remove uma Quadra com CEP cep de uma Cidade c
			-c: Cidade.
			-cep: Identificador de uma Quadra.
	*/

	void removeHidrante(Cidade c, char *id);
	/*
		Remove um Hidrante com identificador id de uma Cidade c
			-c: Cidade.
			-id: Identificador de um Hidrante.
	*/

	void removeSemaforo(Cidade c, char *id);
	/*
		Remove um Semaforo com identificador id de uma Cidade c
			-c: Cidade.
			-id: Identificador de um Semaforo.
	*/

	void removeTorre(Cidade c, char *id);
	/*
		Remove uma Torre com identificador id de uma Cidade c
			-c: Cidade.
			-id: Identificador de uma Torre.
	*/

	void apocalypse(Cidade c);
	/*
		Remove todas as Quadra, Hidrantes, Semaforos e Torres existentes na Cidade c
			-c: Cidade.
	*/

#endif
