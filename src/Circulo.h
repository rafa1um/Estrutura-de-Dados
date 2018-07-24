/*
	Autor: Renan Yuji Koga Ferreira
	Estrutura de Dados 2017
*/

#ifndef CIRCULO_H
#define CIRCULO_H

  	typedef void *Circulo;
    /*
        Tipo Abstrato Circulo

            Um círculo é uma forma geométrica plana resultante da união de uma circunferência e de seus pontos internos. Uma circunferência é um conjunto de pontos equidistantes a um ponto fixo no plano, ou seja, qualquer ponto que possuir uma distância r a partir do ponto fixo pertence a circunferência. Esse ponto fixo é conhecido o centro de um círculo ou de uma circunferência, dependendo da figura analisada, e a distância r é também conhecida como raio. Resumindo, um círculo é uma área delimitada pela circunferência.
            A forma geométrica círculo tem os seguintes atributos (características): id, usado a identificação do Circulo; ponto x e y, que marca o centro da circunferência/círculo; raio, que é a distância entre o centro e a cirunferência; e a cor, definida no padrão SVG (Gráficos Vetoriais Escaláveis), o formato SVG conta com uma variação de 147 cores.
    */

  	Circulo createCirculo(int id, double x, double y, double raio, char *cor);
    /*
        Cria e retorna um Circulo.
            -id: Identificador numérico
            -x: O ponto X do centro de um Circulo
            -y:	O ponto Y do centro de um Circulo
            -raio: Raio do Circulo
            -cor: Cor do Circulo
    */

  	void lerCirculo(FILE *geo, int *id, double *raio, double *x, double *y, char **cor);
    /*
        Obtém os atributos de um Circulo contidos no arquivo de leitura geo.
            -geo: Arquivo de leitura
            -id: Identificador numérico
            -raio: Raio do Circulo
            -x: O ponto X do centro de um Circulo
            -y:	O ponto Y do centro de um Circulo
            -cor: Cor do Circulo

    */

  	void escreverCirculo(Circulo c, FILE *saida, char *cor);
    /*
    Escreve um Circulo em um arquivo SVG saida, com todos os seus atributos. Caso a 'cor' seja "NULL" então será escrito no arquivo SVG o Circulo comum, caso contrário, será escrito um Circulo de cor 'cor', representando seu ponto âncora.
        -c: Um Circulo.
        -saida: Um arquivo.
        -cor: Cor do Circulo
    */

  	int getCirculoId(Circulo c);
    /*
        Retorna o identificador de um Circulo.
            -c: Circulo
    */

  	double getCirculoX(Circulo c);
    /*
        Retorna o ponto X do centro de um Circulo c.
            -c: Circulo
    */

	double getCirculoY(Circulo c);
    /*
        Retorna o ponto Y do centro de um Circulo c.
            -c: Circulo
    */

	double getCirculoRaio(Circulo c);
    /*
        Retorna o raio de um Circulo c.
            -c: Circulo
    */

	char *getCirculoCor(Circulo c);
    /*
        Retorna a cor de um Circulo c.
            -c: Circulo
    */

	void freeCirculo(Circulo c);
    /*
        Desaloca a memória utilizada por um Circulo c: cor.
            -c: Circulo
    */

#endif
