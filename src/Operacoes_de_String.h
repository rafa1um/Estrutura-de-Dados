/*
	Autor: Renan Yuji Koga Ferreira
	Estrutura de Dados 2017
*/

#ifndef OPERACOES_DE_STRING_H
#define OPERACOES_DE_STRING_H

	int Argumentos(int argc, char **argv, char **pathIn, char **pathOut, char **nome, char **arqQry);
	/*
		Recebe os argumentos de entrada e atribui às strings. Há 4 variávies lógicas simbolizando a presença ou ausência de algum(ns) argumentos. Os argumentos associados a variáveis lógicas são: -q, -acc0, -acc, -e. As variáveis lógicas são iniciadas com 1, porém quando houver esses algum desses argumentos os valores serão, respectivamente, 2, 3, 5, 7 (os quatro primeiros números primos).
		Retorna o produto das 4 variáveis lógicas.
			-argc: Quantidade de argumentos
			-argv: Vetor de Strings contendo cada argumento em um índice
			-pathIn: Recebe o diretório de entrada do arquivo (quando houver o argumento -e)
			-pathOut: Recebe o diretório de saída do arquivo (argumento -o)
			-nome: Recebe o nome do arquivo de entrada (argumento -f)
			-arqQry: Recebe o nome do arquivo qry (quando houver o argumento -q)
	*/

	char *verificaBarra(char *string);
	/*
		Verifica se o último caracter da 'string' é uma barra, em caso negativo, acrescenta-se uma barra.
		Retorna a string modificada se houve o acréscimo da barra, se não retorna a string recebida como parâmetro.
		 	-string: String a ser manipulada.
	*/

	char *diretorio(char *dir, char *string);
	/*
		Concatena a string 'dir' com a string 'string' e retorna uma string concatenada.
			-dir: Primeira string
			-string: Segunda string, que será concatenada junto com a primeira
	*/

	char *nomeBase(char *string);
	/*
		Retorna o nome base da 'string', ou seja, caso a 'string' possua alguma extensão, seja txt, svg, geo, etc., ela retornará uma string sem essa extensão.
			-string: String a ser manipulada.
	*/

	char *saidaTxt(char *string);
	/*
		Cria uma string com extensão .txt, libera a string que fora passada como parâmetro, e retorna a nova string.
			-string: String a ser manipulada.
	*/

	char *saidaSvg(char *string);
	/*
		Cria uma string com extensão .svg, libera a string que fora passada como parâmetro, e retorna a nova string.
			-string: String a ser manipulada.
	*/

	char *concatenaTraco(char *nome, char *sufixo);
	/*
		Concatena as strings 'nome' e 'sufixo' com um traço '-' entre elas e retorna a string concatenada.
			-nome: Primeira string
			-sufixo: Segunda string, que será concatenada junto com a primeira separadas por um traço
	*/

	char *corrigeString(char *string);
	/*
		Caso o tamanho da 'string' seja maior do que realmente é necessário, essa função corrigirá isso retornando uma string de tamanho ideal para o conteúdo da mesma.
	*/

#endif
