/*
	Autor: Renan Yuji Koga Ferreira
	Estrutura de Dados 2017
*/

#ifndef RETANGULO_H
#define RETANGULO_H

	typedef void* Retangulo;
	/*
		Tipo Abstrato Retangulo

			Retângulo é uma figura geométrica plana de quatro lados (quadrilátero). Possui duas retas paralelas que chamamos de altura e outras duas retas paralelas que chamamos de largura. Portanto a forma geométrica Retangulo têm os segintes atributos: id, para a identificação do Retangulo; ponto x e y, o ponto âncora do Retângulo (o vértice superior esquerdo); largura, a distância entre o vértice superior/inferior esquerdo e o vértice superior/inferior direito; altura, a distância entre o vértice superior direito/esquerdo e o vértice inferior direito/esquerdo; e a cor, definifa no padrão SVG (Gráficos Vetoriais Escaláveis), o formato SVG conta com uma variação de 147 cores.
	*/

	Retangulo createRetangulo(int id, double x, double y, double altura, double largura, char *cor);
	/*
		Cria e retorna um Retangulo.
			-id: Identificador numérico
			-largura: Largura de um Retangulo
			-altura: Altura de um Retangulo
			-x: O ponto X do ponto âncora de um Retangulo
			-y:	O ponto Y do ponto âncora de um Retangulo
			-raio: Raio do Retangulo
			-cor: Cor do Retangulo
	*/

	void lerRetangulo(FILE *geo, int *id, double *largura, double *altura, double *x, double *y, char **cor);
	/*
        Obtém os atributos de um Retangulo contidos no arquivo de leitura geo.
            -geo: Arquivo de leitura
            -id: Identificador numérico
			-largura: Largura de um Retangulo
			-altura: Altura de um Retangulo
            -x: O ponto X do ponto âncora de um Retangulo
            -y:	O ponto Y do ponto âncora de um Retangulo
            -raio: Raio do Retangulo
            -cor: Cor do Retangulo

    */

  	void escreverRetangulo(Retangulo r, FILE *saida, char *cor);
    /*
    Escreve um Retangulo em um arquivo SVG saida, com todos os seus atributos. Caso a 'cor' seja "NULL" então será escrito no arquivo SVG o Retangulo comum, caso contrário, será escrito um Circulo de cor 'cor', representando seus vértices.
        -r: Um Retangulo.
        -saida: Um arquivo.
        -cor: Cor do Retangulo
    */

  	int getRetanguloId(Retangulo r);
    /*
        Retorna o identificador de um Retangulo.
            -r: Retangulo
    */

  	double getRetanguloX(Retangulo r);
    /*
        Retorna o ponto X do ponto âncora de um Retangulo r.
            -r: Retangulo
    */

	double getRetanguloY(Retangulo r);
    /*
        Retorna o ponto Y do ponto âncora de um Retangulo r.
            -r: Retangulo
    */

	double getRetanguloAltura(Retangulo r);
	/*
		Retorna a altura de um Retangulo r.
			-r: Retangulo
	*/

	double getRetanguloLargura(Retangulo r);
	/*
		Retorna a largura de um Retangulo r.
			-r: Retangulo
	*/

	char *getRetanguloCor(Retangulo r);
    /*
        Retorna a cor de um Retangulo r.
            -r: Retangulo
    */

	void freeRetangulo(Retangulo r);
    /*
        Desaloca a memória utilizada por um Retangulo r: cor.
            -r: Retangulo
    */

#endif
