/*
	Autor: Renan Yuji Koga Ferreira
	Estrutura de Dados 2017
*/

#ifndef SEMAFORO_H
#define SEMAFORO_H

	typedef void *Semaforo;
	/*
		Tipo Abstrato Semaforo

			Semaforo é um equipamento urbano de uma Cidade que tem como atributos: centro (x, y), identificador, cor de preenchimento e cor de borda. A princípio o Semaforo será representado por um círculo de raio 2.
	*/

	Semaforo createSemaforo(double x, double y, char *id, char *cfill, char *cstrk);
	/*
		Cria um Semaforo e a retorna.
			-x: O ponto X do ponto âncora de um Semaforo
			-y:	O ponto Y do ponto âncora de um Semaforo
			-id: Identificador de um Semaforo
			-cfill:	Cor de preenchimento
			-cstrk: Cor de borda
	*/

	void lerSemaforo(FILE *geo, double *x, double *y, char **id);
	/*
		Obtém os atributos de uma quadra contida no arquivo de leitura geo.
			-geo: Arquivo de leitura
			-x: O ponto X do ponto âncora de um Semaforo
			-y:	O ponto Y do ponto âncora de um Semaforo
			-id: Identificador de um Semaforo
	*/

	void escreverSemaforo(FILE *saida, Semaforo s);
	/*
		Escreve um Semaforo em um arquivo SVG saida, com todos os seus atributos.
			-saida: Um arquivo.
			-s: Uma Semaforo.
	*/

	double getSemaforoX(Semaforo s);
	/*
		Retorna o ponto X do ponto âncora de um Semaforo s.
			-s: Semaforo
	*/

	double getSemaforoY(Semaforo s);
	/*
		Retorna o ponto Y do ponto âncora de um Semaforo s.
			-s: Semaforo
	*/

	char *getSemaforoId(Semaforo s);
	/*
		Retorna o identificador de um Semaforo s.
			-s: Semaforo
	*/

	char *getSemaforoCfill(Semaforo s);
	/*
		Retorna a cor de preenchimento de um Semaforo s.
			-s: Semaforo
	*/

	char *getSemaforoCstrk(Semaforo s);
	/*
		Retorna a cor de borde de um Semaforo s.
			-s: Semaforo
	*/

	void freeSemaforo(Semaforo s);
	/*
		Desaloca a memória utilizada por um Semaforo s: identificador, cor de borda e cor de preenchimento.
			-s: Semaforo
	*/

#endif
