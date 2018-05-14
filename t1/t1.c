#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---------- F U N C O E S ---------- */

char *concat(char *str1, char *str2) { // Função para concatenar duas strings;
    char *aux = NULL;
    int tamanho;
    if(str1 == NULL) {
      str1 = "";
    }
    else if(str2 == NULL) {
      str2 = "";
    }
    tamanho = strlen(str1) + strlen(str2) + 1;
    aux = (char*) malloc((tamanho)*sizeof(char));
    sprintf(aux, "%s%s", str1, str2);
    return aux;
}

char *t_aspas(char *str) { // Função para tirar aspas de uma palavra;
    char *aux = NULL;
    int i;
    int tamanho;
    tamanho = strlen(str);

    if(str[0] == '\"' && str[tamanho - 1] != '\"') { // Verifica para o caso de, ex: "abcd
      aux = (char*) malloc((tamanho + 20)*sizeof(char));
      for(i = 1; i < tamanho; i++){
        aux[i - 1] = str[i];
      }
      aux[i - 1] = '\0';
      return aux;
    }
    else if(str[0] != '\"' && str[tamanho - 1] == '\"') { // Verifica para o caso de, ex: abcd"
      aux = (char*) malloc((tamanho + 20)*sizeof(char));
      for(i = 0; i < tamanho; i++){
        aux[i] = str[i];
      }
      aux[i - 1] = '\0';
      return aux;
    }
    else if (str[0] == '\"' && str[tamanho - 1] == '\"') { // Verifica para o caso de, ex: "abcd"
      aux = (char*) malloc((tamanho + 20)*sizeof(char));
      for(i = 1; i < tamanho - 1; i++){
        aux[i - 1] = str[i];
      }
      aux[i - 1] = '\0';
      return aux;
    }
    /*if(str[0] == '\"' || str[tamanho - 1] == '\"') { // + 1 pois tem o \0;
      aux = (char*) malloc((tamanho - 1)*sizeof(char)); // - 1 pois tem o \0;
      for(i = 1; i < tamanho - 1; i++){ // -1 pois tirou as aspas;
        aux[i - 1] = str[i];
      }
    }*/
    else return str;
}

char *slashFix(char *str) { // Função para ajustar a barra (/) quando for necessário;
	int tamanho;

	tamanho = strlen(str);

	if (str[tamanho - 1] != '/' && tamanho > 0)	{
		str = realloc(str, (tamanho + 2)*sizeof(char));
	  str[tamanho] = '/';
		str[tamanho + 1] = '\0';
	}
  return str;
}

char *dotFix(char *str){ // Função para ajustar o ponto final (.) quando for necessário;
  int tamanho, i;

  tamanho = strlen(str);

	if (str[0] != '.') {
		str = realloc(str, (tamanho + 2)*sizeof(char));
		for (i = tamanho; i > 0; i--) {
			str[i] = str[i - 1];
    }
		str[0] = '.';
	}
  str[tamanho + 1] = '\0';
  return str;
}

/* ---------- M A I N ---------- */

int main(int argc, char const *argv[]) {
      FILE *files[10];
      FILE *file;
      char comando[10];
      char *content = NULL, *token = NULL, auxR[1000], *arqName = NULL;
      char *x = NULL, *y = NULL, *z = NULL, *auxZ = NULL;
      char *d = NULL, *a = NULL, *e = NULL, *c = NULL, *l = NULL, *o = NULL, *w = NULL, *f = NULL;
      char *auxFree;
      int id = 0, i, j, k;
      char nOpen = 'F', n_exist = 'F'; // Variaveis para verificacao de erros;
      char *p1 = NULL, *p2 = NULL, *p3 = NULL; // variaveis p1 = @1, p2 = @2, p3 = @3 (argumentos passados pelo terminal);

      /*for(k = 0; k < argc; k++) {
        if(strcmp(argv[k], "-f") == 0) {
          arqName = (char*) malloc((strlen(argv[k+1])+1)*sizeof(char));
          strcpy(arqName, argv[k+1]);
          k++;
        }
        else if(strcmp(argv[k], "-o") == 0) {
          dir = (char*) malloc((strlen(argv[k+1])+1)*sizeof(char));
          strcpy(dir, argv[k+1]);
          k++;
        }
        else if(p1 == NULL) {
          p1 = (char*) malloc((strlen(argv[k])+1)*sizeof(char));
          strcpy(p1, argv[k]);
          printf("%s\n", argv[k]);
        }
        else if(p2 == NULL) {
          p2 = (char*) malloc((strlen(argv[k])+1)*sizeof(char));
          strcpy(p2, argv[k]);
          printf("%s\n", argv[k]);
        }
        else if(p3 == NULL) {
          p3 = (char*) malloc((strlen(argv[k])+1)*sizeof(char));
          strcpy(p3, argv[k]);
          printf("%s\n", argv[k]);
        }
      }*/

      for(k = 0; k < argc; k++){ // Lida com argumentos recebidos do terminal;
        if (strcmp(argv[k],"-f") == 0) {
          arqName = (char *) malloc((strlen(argv[k+1])+1)*sizeof(char *));
          n_exist = 'T';
          strncpy(arqName, argv[k+1], strlen(argv[k+1])+1);
        }
        if (strcmp(argv[k],"-o") == 0) {
          if(k+1 < argc) {
            d = (char*) malloc((strlen(argv[k+1]) + 1)*sizeof(char *));
            strcpy(d,argv[k+1]);
            if (d[strlen(d)-1] != '/') {
              d = (char *) realloc(d,(strlen(d)+2) * sizeof(char));
              strcat(d,"/");
            }
          }
        }
        if (p1 != NULL && p2 != NULL && p3 == NULL) {
          p3 = (char*) malloc((strlen(argv[k])+1)*sizeof(char *));
          strcpy(p3, argv[k]);
        }
        if (p1 != NULL && p2 == NULL) {
          p2 = (char*) malloc((strlen(argv[k])+1)*sizeof(char *));
          strcpy(p2, argv[k]);
        }
        if (k > 1  && strcmp(argv[k],"-o") != 0 && strcmp(argv[k-1],"-f") != 0 && strcmp(argv[k-1],"-o") != 0 && p1 == NULL) {
          p1 = (char*) malloc((strlen(argv[k])+1)*sizeof(char *));
          strcpy(p1, argv[k]);
        }
      }
      if(n_exist == 'F') // Mensagem de erro caso não tenha parametros obrigatorios (-f);
      {
        printf("Houve um erro na leitura dos parametros!\n");
      }
      else{

      content = (char*) malloc(10000*sizeof(char)); // Aloca a variavel content que sera usada durante a leitura dos arquivos;

      file = fopen(arqName, "r"); // Abre o arquivo no modo leitura na variável file;
      if(file == NULL) { // Verifica se o arquivo foi aberto;
        printf("Ocorreu um problema ao tentar abrir o arquivo!\n");
        exit(0); // Termina o programa;
      }

      while (!feof(file)) { // Loop ate o fim do arquivo;
        fscanf(file, " %s", comando); // Le a primeira linha do arquivo (comandos);
        /*---------- C O M A N D O  -  +x ----------*/
        if(strcmp(comando, "+x") == 0) { // Comando +x (concatena a variavel x);
          fscanf(file, " %[^\n]s ", content);
          content = t_aspas(content);
          if(strcmp(content, "@1") == 0) {
            x = (char*) malloc((strlen(p1)+1)*sizeof(char));
            strcpy(x, p1);
          }
          else if(strcmp(content, "@2") == 0) {
            x = (char*) malloc((strlen(p2)+1)*sizeof(char));
            strcpy(x, p2);
          }
          else if(strcmp(content, "@3") == 0) {
            x = (char*) malloc((strlen(p3)+1)*sizeof(char));
            strcpy(x, p3);
          }
          else if(x == NULL) {
            x = (char*) malloc((strlen(content)+1)*sizeof(char));
            strcpy(x, content);
          }
          else {
            auxFree = x;
            x = concat(x, content);
            free(auxFree);
            printf("%s\n", x);
          }
        }
        /*---------- C O M A N D O  -  +y ----------*/
        else if(strcmp(comando, "+y") == 0) { // Comando +y (concatena a variavel y);
          fscanf(file, " %[^\n]s ", content);
          content = t_aspas(content);
          if(strcmp(content, "@1") == 0) {
            y = (char*) malloc((strlen(p1)+1)*sizeof(char));
            strcpy(y, p1);
          }
          else if(strcmp(content, "@2") == 0) {
            y = (char*) malloc((strlen(p2)+1)*sizeof(char));
            strcpy(y, p2);
            printf("%s\n", y);
          }
          else if(strcmp(content, "@3") == 0) {
            y = (char*) malloc((strlen(p3)+1)*sizeof(char));
            strcpy(y, p3);
            printf("%s\n", p1);
            printf("%s\n", p2);
            printf("%s\n", p3);
          }
          else if(y == NULL) {
            y = (char*) malloc((strlen(content)+1)*sizeof(char));
            strcat(y, content);
          }
          else {
            auxFree = y;
            y = concat(y, content);
            free(auxFree);
          }
        }
        /*---------- C O M A N D O  -  +z ----------*/
        else if(strcmp(comando, "+z") == 0) { // Comando +z;
          fscanf(file, " %s", content);
          content = t_aspas(content);
          if(strcmp(content, "**") == 0){ // Para o parametro **;
            auxZ = (char*) malloc((strlen(z)+1)*sizeof(char));
            strcpy(auxZ, z);
            printf("%s", auxZ);
            if(atoi(p1) != 0){
              i = atoi(p1);
              for(j = 0; j < i; j++){
                z = concat(auxZ, z);
              }
            }
          }
          else if(content[0] == '*'){ // Para o parametro *n;
            auxZ = (char*) malloc((strlen(z)+1)*sizeof(char));
            strcpy(auxZ, z);
            content = strtok(content, "*");
            i = atoi(content);
            for(j = 0; j < i; j++) {
              z = concat(auxZ, z);
            }
          }
          else if(z == NULL) {
            z = (char*) malloc((strlen(content)+1)*sizeof(char));
            strcpy(z, content);
          }
          else {
            auxFree = z;
            z = concat(z, content);
            free(auxFree);
          }
        }
        /*---------------------------------*/
        else if(strcmp(comando, "x") == 0) { // Comando x (limpa o conteudo de x);
          if(x != NULL){
            x = "";
          }
        }
        /*---------------------------------*/
        else if(strcmp(comando, "y") == 0) { // Comando y (limpa o conteudo de y);
          if(y != NULL){
            y = "";
          }
        }
        /*---------------------------------*/
        else if(strcmp(comando, "z") == 0) { // Comando z (limpa o conteudo de z);
          if(z != NULL){
            z = "";
          }
        }
        /*---------- C O M A N D O  -  d ----------*/
        else if(strcmp(comando, "d") == 0) { // Define diretorio;
          fscanf(file, " %s ", content);

          if (strcmp(content, "#x") == 0) {
            d = (char*) malloc((strlen(x)+1)*sizeof(char));
            d = "";
    				concat(d, x);
          }
    			else if (strcmp(content, "#y") == 0) {
            d = "";
            d = (char*) malloc((strlen(y)+1)*sizeof(char));
    				concat(d, y);
          }
    			else if (strcmp(content, "#z") == 0) {
            d = "";
            d = (char*) malloc((strlen(z)+1)*sizeof(char));
    				concat(d, z);
          }
          else if(d == NULL) {
            d = "";
            d = (char*) malloc((strlen(content)+1)*sizeof(char));
            strcpy(d, content);
          }
          else {
            auxFree = d;
            d = "";
            d = concat(d, content);
            free(auxFree);
          }
          d = slashFix(d);
        }
        /*---------- C O M A N D O  -  a ----------*/
        else if(strcmp(comando, "a") == 0) { // Define o nome do arquivo;
          fscanf(file, " %s ", content);

          if (strcmp(content, "#x") == 0) {
            a = (char*) malloc((strlen(x)+1)*sizeof(char));
    				strcpy(a, x);
          }
    			else if (strcmp(content, "#y") == 0) {
            a = (char*) malloc((strlen(y)+1)*sizeof(char));
    				strcpy(a, y);
          }
    			else if (strcmp(content, "#z") == 0) {
            a = (char*) malloc((strlen(z)+1)*sizeof(char));
    				strcpy(a, z);
          }
          else if(a == NULL) {
              a = (char*) malloc((strlen(content)+1)*sizeof(char));
              strcpy(a, content);
          }
          else {
            auxFree = a;
            a = "";
            a = concat(a, content);
            free(auxFree);
          }
          a = t_aspas(a);
          printf("%s\n", a);
        }
        /*---------- C O M A N D O  -  e ----------*/
        else if(strcmp(comando, "e") == 0) { // Define a extensão do nome arquivo;
          fscanf(file, " %s ", content);

          if (strcmp(content, "#x") == 0) {
            e = (char*) malloc((strlen(x)+1)*sizeof(char));
    				strcpy(e, x);
          }
    			else if (strcmp(content, "#y") == 0) {
            e = (char*) malloc((strlen(y)+1)*sizeof(char));
    				strcpy(e, y);
          }
    			else if (strcmp(content, "#z") == 0) {
            e = (char*) malloc((strlen(z)+1)*sizeof(char));
    				strcpy(e, z);
          }
          else {
            e = (char*) malloc((strlen(content)+1)*sizeof(char));
            strcpy(e, content);
          }

          e = t_aspas(e);
          e = dotFix(e);
          printf("%s\n", e);
        }
        /*---------- C O M A N D O  -  c ----------*/
        else if(strcmp(comando, "c") == 0) { // Cria o arquivo usando as informacoes de a, e, d;
          fscanf(file, " %d ", &id);
          c = concat(c, d);
          c = concat(c, a);
          c = concat(c, e);
          printf("%s\n", c);
          files[id] = fopen(c, "w");
          c = "";
          if(files[id] == NULL){
            nOpen = 'T';
          }
        }
        /*---------- C O M A N D O  -  o ----------*/
        else if(strcmp(comando, "o") == 0) { // Abre o arquivo em modo append;
          fscanf(file, " %d ", &id);
          o = concat(o, d);
    			o = concat(o, a);
    			o = concat(o, e);
          files[id] = fopen(o, "a+");
          o = "";
        }
        /*---------- C O M A N D O  -  l ----------*/
        else if(strcmp(comando, "l") == 0) { // Abre o arquivo em modo leitura;
          fscanf(file, " %d ", &id);
          l = concat(l, d);
          l = concat(l, a);
          l = concat(l, e);
          printf("%s\n", l);
          files[id] = fopen(l, "r");
          l = "";
        }
        /*---------- C O M A N D O  -  w ----------*/
        else if(strcmp(comando, "w") == 0) { // Escreve uma linha no arquivo aberto;
          fscanf(file, " %d ", &id);
          fscanf(file, "%[^\n]s ", content);
          printf("CONTENT: %s\n", content);

          printf("%d\n", id);
          if (strcmp(content, "#x") == 0) {
            w = (char*) malloc((strlen(x)+1)*sizeof(char));
            strcpy(w, x);
            printf("%s", w);
          }
    			else if (strcmp(content, "#y") == 0) {
            w = (char*) malloc((strlen(y)+1)*sizeof(char));
            strcpy(w, y);
          }
    			else if (strcmp(content, "#z") == 0){
            w = (char*) malloc((strlen(z)+1)*sizeof(char));
            strcpy(w, z);
          }
          else {
            w = (char*) malloc((strlen(content)+1)*sizeof(char));
            strcpy(w, content);
            if (content[strlen(content) - 1] == '$') {
              w[strlen(w)-1] = '\0';
            }
          }
    			if(nOpen == 'T') {
            printf("Não foi possível gravar no arquivo atual!\n");
            exit(0);
          }
          else {
            fprintf(files[id], "%s\n", w);
            printf("%s\n", w);
            printf("Gravado com sucesso!\n");
          }
          w = "";
        }
        /*---------- C O M A N D O  -  r ----------*/
        else if(strcmp(comando, "r") == 0) { // Le o arquivo e armazena na variavel indicada;
          fscanf(file, " %d ", &id);
          fscanf(file, " %s ", content);
          fgets(auxR, 1000, files[id]);
          if (strcmp(content, "#x") == 0) {
            x = (char*) malloc((strlen(auxR) + 1)*sizeof(char));
            strcpy(x, auxR);
            printf("%s", x);
          }
    			else if (strcmp(content, "#y") == 0) {
            y = (char*) malloc((strlen(auxR) + 1)*sizeof(char));
            strcpy(y, auxR);
            printf("%s", y);
          }
    			else if (strcmp(content, "#z") == 0){
            strcpy(z, auxR);
          }
        }
        /*---------- C O M A N D O  -  f ----------*/
        else if(strcmp(comando, "f") == 0) { // Fecha o arquivo;
          fscanf(file, " %d ", &id);
          fclose(files[id]);
        }
      /*---------------------------------*/
      }
      printf("Programa executado com sucesso!\n");
    }
  return 0;
}
