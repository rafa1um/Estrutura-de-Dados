#include "svg.h"
#include "io_name.h"
#include "calc.h"


int main(int argc, char *argv[]) {
      FILE *file, *output, *o_result;
      char *base_name = NULL, *token = NULL, *dir = NULL, *path = NULL, *content = NULL;
      char comando[5];
      double x, y, distance;
      int nx = 1000, id_aux, i_point;
      REGISTRO *regCirculo = (REGISTRO*) malloc(sizeof(REGISTRO));
      REGISTRO *regRetangulo = (REGISTRO*) malloc(sizeof(REGISTRO));
      LISTA *lista = (LISTA*) malloc(sizeof(LISTA));
      NODE search01, search02;

      /* ------------- ARGUMENTOS ---------------*/
      args(argc, argv, &dir, &base_name, &path);

      /* ----------------------- INICIO ------------------------------ */
      file = fopen(base_name, "r"); /* Abre o arquivo no modo leitura na variável file; */
      if(file == NULL) { /* Verifica se o arquivo foi aberto; */
        printf("Ocorreu um problema ao tentar abrir o arquivo!\n");
        exit(0); /* Termina o programa; */
      }
      /* ----- INICIALIZAÇÕES ----- */
      inicializarLista(lista);
      t_ext(base_name); /* Tira a extensão .geo do nome base. */
      strcat(base_name, ".txt");
      o_result = fopen(base_name, "w");
      t_ext(base_name);
      strcat(base_name, ".svg"); /* Concatena o nome base com .svg ficando nomebase.svg. */
      printf("%s", base_name);
      output = fopen(base_name, "w"); /* Abre ou cria um arquiov em modo escrita. */
      new_SVG(output);
      content = (char*) malloc(1000*sizeof(char));
      /* -------------------------- */

      while (!feof(file)) { /* Loop até o fim do arquivo; */
        fscanf(file, " %s", comando); /* Lê a primeira linha do arquivo (comandos); */
        /*---------- C O M A N D O  -  nx ----------*/
        if(strcmp(comando, "nx") == 0) { /* Altera o número máximo de círculos e retângulos; */
            fscanf(file, " %[^\n]s ", content);
            nx=nx+1;
        }
        /*---------- C O M A N D O  -  c ----------*/
        else if(strcmp(comando, "c") == 0) { /* Desenha um círculo; */
            fscanf(file, " %[^\n]s ", content);
            token = strtok(content, " ");
            regCirculo->chave = atof(token);
            token = strtok(NULL, " ");
            regCirculo->borda = (char*) malloc((strlen(token)+1)* sizeof(char));
            strcpy(regCirculo->borda, token);
            token = strtok(NULL, " ");
            regCirculo->cor = (char*) malloc((strlen(token)+1)* sizeof(char));
            strcpy(regCirculo->cor, token);
            token = strtok(NULL, " ");
            regCirculo->r = atof(token);
            token = strtok(NULL, " ");
            regCirculo->x = atof(token);
            token = strtok(NULL, " ");
            regCirculo->y = atof(token);
            circ(output, regCirculo);
            inserirElemento(lista, *regCirculo);
            free(regCirculo->borda);
            free(regCirculo->cor);
        }
        /*---------- C O M A N D O  -  r ----------*/
        else if(strcmp(comando, "r") == 0) { /* Desenha um retângulo; */
            fscanf(file, " %[^\n]s ", content);
            token = strtok(content, " ");
            regRetangulo->chave = atof(token);
            token = strtok(NULL, " ");
            regRetangulo->borda = (char*) malloc((strlen(token)+1)* sizeof(char));
            strcpy(regRetangulo->borda, token);
            token = strtok(NULL, " ");
            regRetangulo->cor = (char*) malloc((strlen(token)+1)* sizeof(char));
            strcpy(regRetangulo->cor, token);
            token = strtok(NULL, " ");
            regRetangulo->largura = atof(token);
            token = strtok(NULL, " ");
            regRetangulo->altura = atof(token);
            token = strtok(NULL, " ");
            regRetangulo->x = atof(token);
            token = strtok(NULL, " ");
            regRetangulo->y = atof(token);
            regRetangulo->r = -1;
            rect(output, regRetangulo);
            inserirElemento(lista, *regRetangulo);
            free(regRetangulo->borda);
            free(regRetangulo->cor);
        }
        /*---------- C O M A N D O  -  o ----------*/
        else if(strcmp(comando, "o") == 0) { /* Verifica a sobreposição das formas; */
            fscanf(file, " %[^\n]s ", content);
            token = strtok(content, " ");
            id_aux = atoi(token);
            search01 = buscaSeq(lista, id_aux);
            token = strtok(NULL, " ");
            id_aux = atoi(token);
            search02 = buscaSeq(lista, id_aux);
            if(search01->reg.r == -1.0){
              printf("ok");
            }
            else {
              printf("fuck");
            }
            if(search02->reg.r == -1.0){
              printf("ok");
            }
            else {
              printf("fuck");
            }
        }
        /*---------- C O M A N D O  -  i ----------*/
        else if(strcmp(comando, "i") == 0) { /* Verifica se o ponto é interno à figura; */
            fscanf(file, " %[^\n]s ", content);
            token = strtok(content, " ");
            fprintf(o_result, "%s %i",comando, atoi(token));
            search01 = buscaSeq(lista, atoi(token));
            token = strtok(NULL, " ");
            x = atof(token);
            fprintf(o_result, "%f ", x);
            token = strtok(NULL, " ");
            y = atof(token);
            fprintf(o_result, "%f\n", y);
            i_point = calc_interno(search01, x, y);
            if(i_point == 1) {
              fprintf(o_result, "SIM\n");
            }
            else {
              fprintf(o_result, "NAO\n");
            }
        }
        /*---------- C O M A N D O  -  d ----------*/
        else if(strcmp(comando, "d") == 0) { /* Distância do centro de massa das formas geométricas; */
            fscanf(file, " %[^\n]s ", content);
            token = strtok(content, " ");
            search01 = buscaSeq(lista, atoi(token));
            token = strtok(NULL, " ");
            search02 = buscaSeq(lista, atoi(token));
            distance = calc_distance(search01, search02);
            printf("%.2f\n" ,distance);
        }
        /*---------- C O M A N D O  -  a ----------*/
        else if(strcmp(comando, "a") == 0) {
            fscanf(file, " %[^\n]s ", content);
            token = strtok(content, " ");
            id_aux = atoi(token);
            token = strtok(NULL, " ");
            /* Faz as devidas mudanças nas extensões do arquivo base para o comando a */
            t_ext(base_name);
            strcat(base_name, "-");
            strcat(base_name, token);
            strcat(base_name, ".svg");
            printf("%s", base_name);
            /* ---------------------------------------------------------------------- */
        }
        /*---------- C O M A N D O  -  # ----------*/
        else if(strcmp(comando, "#") == 0) { /* Finaliza arquivo; */
            fscanf(file, " %[^\n]s ", content);
            end_SVG(output); /* Fecha a TAG do SVG */
            fclose(output);
            fclose(o_result);
            exibirLista(lista); /* TIRAR NO FINAL DO CÓDIGO!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

            /* -- LIBERAÇÃO DO RESTANTE DAS MEMÓRIAS  USADAS -- */
            free(base_name);
            free(dir);
            free(path);
            free(content);
            free(regCirculo);
            free(regRetangulo);
            reinicializarLista(lista);
            free(lista);
            /* ------------------------------------------------- */
        }
      }
      /* ---- FINALIZAÇÃO DO CÓDIGO ----- */
      fclose(file);
      printf("Programa executado com sucesso!\n");
      /* -------------------------------- */
  return 0;
}
