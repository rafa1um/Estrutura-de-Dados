/*
	Autor: Renan Yuji Koga Ferreira
	Estrutura de Dados 2017
*/

#ifndef PROCESSAMENTOS_H
#define PROCESSAMENTOS_H

#include "Operacoes_de_String.h"

    FILE *criarArquivo(char *nome);
    /*
        Cria um arquivo do tipo FILE com o nome 'nome' e retorna o arquivo do tipo FILE. Caso não seja possível criar um arquivo, retornará NULL.
            -nome: Nome do arquivo
    */

    FILE *abrirArquivo(char *nome);
    /*
        Abre um arquivo do tipo FILE com o nome 'nome' e retorna o arquivo do tipo FILE. Caso não seja possível abrir um arquivo, retornará NULL.
            -nome: Nome do arquivo
    */

    FILE *appendArquivo(char *nome);
    /*
        Dá um append em um arquivo do tipo FILE com o nome 'nome' e retorna o arquivo do tipo FILE. Caso não seja possível dar o append no arquivo, retornará NULL.
            -nome: Nome do arquivo
    */

    FILE *arquivoTxt(char *nome, char *pathOut);
    /*
        Retorna um FILE de um arquivo .txt criado a partir das strings 'nome' e 'pathOut'.
            -nome: String
            -pathOut: String
    */

    FILE *arquivoQry(char *pathIn, char *arqQry, int logic);
    /*
        Retorna um FILE de um arquivo .qry que foi aberto a partir das strings 'nome' e 'pathOut'.
            -nome: String
            -pathOut: String
            -logic: int
    */

    FILE *arquivoResumo(int logic, char *nome);
    /*
        Retorna um FILE de um arquivo resumo.txt.
            -logic: int
    */

#endif
