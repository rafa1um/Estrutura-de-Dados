/*
	Autor: Renan Yuji Koga Ferreira
	Estrutura de Dados 2017
*/

#ifndef HIDRANTE_H
#define HIDRANTE_H

	typedef void *Hidrante;
	/*
		Tipo Abstrato Hidrante

			Hidrante é um equipamento urbano de uma Cidade que tem como atributos: centro (x, y), identificador, cor de preenchimento e cor de borda. A princípio o Hidrante será representado por um círculo de raio 2.
	*/

	Hidrante createHidrante(double x, double y, char *id, char *cfill, char *cstrk);
	/*
		Cria um Hidrante e a retorna.
			-x: O ponto X do ponto âncora de um Hidrante
			-y:	O ponto Y do ponto âncora de um Hidrante
			-id: Identificador de um Hidrante
			-cfill:	Cor de preenchimento
			-cstrk: Cor de borda
	*/

	void lerHidrante(FILE *geo, double *x, double *y, char **id);
	/*
		Obtém os atributos de uma quadra contida no arquivo de leitura geo.
			-geo: Arquivo de leitura
			-x: O ponto X do ponto âncora de um Hidrante
			-y:	O ponto Y do ponto âncora de um Hidrante
			-id: Identificador de um Hidrante
	*/

	void escreverHidrante(FILE *saida, Hidrante h);
	/*
		Escreve um Hidrante em um arquivo SVG saida, com todos os seus atributos.
			-saida: Um arquivo.
			-h: Uma Hidrante.
	*/

	double getHidranteX(Hidrante h);
	/*
		Retorna o ponto X do ponto âncora de um Hidrante h.
			-h: Hidrante
	*/

	double getHidranteY(Hidrante h);
	/*
		Retorna o ponto Y do ponto âncora de um Hidrante h.
			-h: Hidrante
	*/

	char *getHidranteId(Hidrante h);
	/*
		Retorna o identificador de um Hidrante h.
			-h: Hidrante
	*/

	char *getHidranteCfill(Hidrante h);
	/*
		Retorna a cor de preenchimento de um Hidrante h.
			-h: Hidrante
	*/

	char *getHidranteCstrk(Hidrante h);
	/*
		Retorna a cor de borde de um Hidrante h.
			-h: Hidrante
	*/

	void freeHidrante(Hidrante h);
	/*
		Desaloca a memória utilizada por um Hidrante h: identificador, cor de borda e cor de preenchimento.
			-h: Hidrante
	*/

#endif
