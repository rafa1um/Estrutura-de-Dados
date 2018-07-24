/*
	Autor: Renan Yuji Koga Ferreira
	Estrutura de Dados 2017
*/

#ifndef QUADRA_H
#define QUADRA_H

	typedef void *Quadra;
	/*
		Tipo Abstrato Quadra

			Semelhante ao Tipo Abstrato Retangulo, a quadra é uma figura geométrica plana de 4 lados (originalmente um retângulo). As características que se diferem do Retângulo (por enquanto), é a presença de um identificador do tipo String, chamado de cep (CEP) e as cores de bordas e preenchimentos, o que não havia em um Retangulo. Utilizaremos uma Quadra como um equipamento urbano de uma Cidade.
	*/

	Quadra createQuadra(double x, double y, double largura, double altura, char *cep, char *cfill, char *cstrk);
	/*
		Cria uma Quadra e a retorna.
			-x: O ponto X do ponto âncora de uma Quadra
			-y:	O ponto Y do ponto âncora de uma Quadra
			-largura: Largura de uma Quadra
			-altura: Altura de uma Quadra
			-cep: Identificador de uma Quadra (um CEP)
			-cfill:	Cor de preenchimento
			-cstrk: Cor de borda
	*/

	void lerQuadra(FILE *geo, double *x, double *y, double *largura, double *altura, char **cep);
	/*
		Obtém os atributos de uma quadra contida no arquivo de leitura geo.
			-geo: Arquivo de leitura
			-x: O ponto X do ponto âncora de uma Quadra
			-y:	O ponto Y do ponto âncora de uma Quadra
			-largura: Largura de uma Quadra
			-altura: Altura de uma Quadra
			-cep: Identificador de uma Quadra (um CEP)
	*/

	void escreverQuadra(FILE *saida, Quadra q);
	/*
		Escreve uma Quadra em um arquivo SVG saida, com todos os seus atributos.
			-saida: Um arquivo.
			-q: Uma Quadra.
	*/

	double getQuadraX(Quadra q);
	/*
		Retorna o ponto X do ponto âncora de uma Quadra q.
			-q: Quadra
	*/

	double getQuadraY(Quadra q);
	/*
		Retorna o ponto Y do ponto âncora de uma Quadra q.
			-q: Quadra
	*/

	double getQuadraLargura(Quadra q);
	/*
		Retorna a largura de uma Quadra q.
			-q: Quadra
	*/

	double getQuadraAltura(Quadra q);
	/*
		Retorna a altura de uma Quadra q.
			-q: Quadra
	*/

	char *getQuadraCep(Quadra q);
	/*
		Retorna o identificador (CEP) de uma Quadra q.
			-q: Quadra
	*/

	char *getQuadraCfill(Quadra q);
	/*
		Retorna a cor de preenchimento de uma Quadra q.
			-q: Quadra
	*/

	char *getQuadraCstrk(Quadra q);
	/*
		Retorna a cor de borde de uma Quadra q.
			-q: Quadra
	*/

	void freeQuadra(Quadra q);
	/*
		Desaloca a memória utilizada por uma Quadra q: identificador, cor de borda e cor de preenchimento.
			-q: Quadra
	*/

#endif
