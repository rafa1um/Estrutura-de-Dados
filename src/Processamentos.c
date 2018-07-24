#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Processamentos.h"

FILE *criarArquivo(char *nome) {
    FILE *arq;

    arq = fopen(nome, "w");

    if (arq == NULL) {
        printf("Problemas ao criar o arquivo!\n");
    }

    return arq;
}

FILE *abrirArquivo(char *nome) {
    FILE *arq;

    arq = fopen(nome, "r");

    if (arq == NULL) {
        printf("Problemas ao abir o arquivo!\n");
    }

    return arq;
}

FILE *appendArquivo(char *nome) {
    FILE *arq;

    arq = fopen(nome, "a");

    if (arq == NULL) {
        printf("Problemas ao dar append no arquivo!\n");
    }

    return arq;
}

FILE *arquivoTxt(char *nome, char *pathOut) {
    char *txt, *dirTxt;
    FILE *resultado;

    txt = nomeBase(nome);
  	txt = saidaTxt(txt);
  	dirTxt = diretorio(pathOut, txt);
  	printf("TXT: %s\n", dirTxt);
    resultado = criarArquivo(dirTxt);

    free(txt);
    free(dirTxt);

    return resultado;
}

FILE *arquivoQry(char *pathIn, char *arqQry, int logic) {
    char *dirQry;
    FILE *qry;

    if (logic%7 == 0) {
        dirQry = diretorio(pathIn, arqQry);
    }
    else dirQry = arqQry;

    printf("Arquivo Qry: %s\n", dirQry);
    qry = abrirArquivo(dirQry);

    if (logic%7 != 0) {
        dirQry = NULL;
    }
    free(dirQry);

    return qry;
}

FILE *arquivoResumo(int logic, char *nome) {
    FILE *resumo;

    if (logic%3 == 0) {
        resumo = criarArquivo(nome);

        fprintf(resumo, "nome-arq.geo\t\t#ins\t#cpi\t#del\t#cpd\n\n");
    }
    else if (logic%5 == 0) {
        resumo = appendArquivo(nome);
    }

    return resumo;
}
