/*
	Autor: Renan Yuji Koga Ferreira
	Estrutura de Dados 2017
*/

#ifndef TORRE_H
#define TORRE_H

	typedef void *Torre;
	/*
		Tipo Abstrato Torre

			Torre é um equipamento urbano de uma Cidade que tem como atributos: centro (x, y), identificador, cor de preenchimento e cor de borda. A princípio o Torre será representado por um círculo de raio 2.
	*/

	Torre createTorre(double x, double y, char *id, char *cfill, char *cstrk);
	/*
		Cria uma Torre e a retorna.
			-x: O ponto X do ponto âncora de uma Torre
			-y:	O ponto Y do ponto âncora de uma Torre
			-id: Identificador de uma Torre
			-cfill:	Cor de preenchimento
			-cstrk: Cor de borda
	*/

	void lerTorre(FILE *geo, double *x, double *y, char **id);
	/*
		Obtém os atributos de uma quadra contida no arquivo de leitura geo.
			-geo: Arquivo de leitura
			-x: O ponto X do ponto âncora de uma Torre
			-y:	O ponto Y do ponto âncora de uma Torre
			-id: Identificador de uma Torre
	*/

	void escreverTorre(FILE *saida, Torre t);
	/*
		Escreve uma Torre em um arquivo SVG saida, com todos os seus atributos.
			-saida: Um arquivo.
			-t: Uma Torre.
	*/

	double getTorreX(Torre t);
	/*
		Retorna o ponto X do ponto âncora de uma Torre t.
			-t: Torre
	*/

	double getTorreY(Torre t);
	/*
		Retorna o ponto Y do ponto âncora de uma Torre t.
			-t: Torre
	*/

	char *getTorreId(Torre t);
	/*
		Retorna o identificador de uma Torre t.
			-t: Torre
	*/

	char *getTorreCfill(Torre t);
	/*
		Retorna a cor de preenchimento de uma Torre t.
			-t: Torre
	*/

	char *getTorreCstrk(Torre t);
	/*
		Retorna a cor de borde de uma Torre t.
			-t: Torre
	*/

	void freeTorre(Torre t);
	/*
		Desaloca a memória utilizada por uma Torre t: identificador, cor de borda e cor de preenchimento.
			-t: Torre
	*/

#endif
