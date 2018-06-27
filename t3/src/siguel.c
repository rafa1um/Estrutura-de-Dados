#include "svg.h"
#include "io_name.h"
#include "calc.h"

int main(int argc, char *argv[]) {
      FILE *file, *o_SVG, *o_TXT, *o_suSVG;
      char *base_name = NULL, *token = NULL, *dir = NULL, *path = NULL, *content = NULL, *aux = NULL, *aux_name = NULL;
      char comando[5];
      double x, y, distance;
      int nx = 1000, id1, id2, i_point, sobrepos, open = 0, i, j, len;
      REGISTRO *regCirculo = (REGISTRO*) malloc(sizeof(REGISTRO));
      REGISTRO *regRetangulo = (REGISTRO*) malloc(sizeof(REGISTRO));
      REGISTRO *reg_quadra = (REGISTRO*) malloc(sizeof(REGISTRO));
      REGISTRO *reg_hidrante = (REGISTRO*) malloc(sizeof(REGISTRO));
      REGISTRO *reg_semaforo = (REGISTRO*) malloc(sizeof(REGISTRO));
      REGISTRO *reg_radio = (REGISTRO*) malloc(sizeof(REGISTRO));
      LISTA *lista = (LISTA*) malloc(sizeof(LISTA));
      LISTA *equip = (LISTA*) malloc(sizeof(LISTA));
      LISTA *quadra = (LISTA*) malloc(sizeof(LISTA));

      NODE search01, search02;

      /* ------------- ARGUMENTOS ---------------*/
      for (i = 1; i < argc; i++) {
        if (strcmp("-e", argv[i]) == 0) {
          i++;
          len = strlen(argv[i]);
          path = (char *)calloc(len + 1, sizeof(char));
          strcpy(path, argv[i]);
        }

        if (strcmp("-f", argv[i]) == 0) {
          i++;
          len = strlen(argv[i]);
          base_name = (char *)calloc(len + 1, sizeof(char));
          strcpy(base_name, argv[i]);
        }

        if (strcmp("-o", argv[i]) == 0) {
          i++;
          len = strlen(argv[i]);
          dir = (char *)calloc(len + 1, sizeof(char));
          strcpy(dir, argv[i]);
        }
      }

      /* Lida com casos que tenha "." no -f */
      if (path != NULL) {
        if (base_name[0] == '.') {
          len = strlen(base_name);
          aux = (char *)calloc(len, sizeof(char));

          for (i = 1, j = 0; i < len; i++, j++) {
            aux[j] = base_name[i];
          }
          aux[len - 1] = '\0';
          free(base_name);
          base_name = (char *)calloc(len, sizeof(char));
          strcpy(base_name, aux);
          free(aux);
        }
      }

      /* Lida com casos que tenha / no -f e -e */
      if (path != NULL) {
        len = strlen(path);

        if ((path[len - 1] == '/') && (base_name[0] == '/')) {
          path[len - 1] = '\0';
          aux = (char *)calloc(len, sizeof(char));
          strcpy(aux, path);
          free(path);
          path = (char *)calloc(len + strlen(base_name), sizeof(char));
          sprintf(path, "%s%s", aux, base_name);
          free(aux);
        } else

        if ((path[len - 1] != '/') &&  (base_name[0] != '/')) {
          aux = (char *)calloc(len + 1, sizeof(char));
          strcpy(aux, path);
          free(path);
          path = (char *)calloc(len + 2 + strlen(base_name),
                                               sizeof(char));
          sprintf(path, "%s/%s", aux, base_name);
          free(aux);
        } else {
          aux = (char *)calloc(len + 1, sizeof(char));
          strcpy(aux, path);
          free(path);
          path = (char *)calloc(len + 1 + strlen(base_name),
                                               sizeof(char));
          sprintf(path, "%s%s", aux, base_name);
          free(aux);
        }
      } else {
        path =
          (char *)calloc(strlen(base_name) + 1, sizeof(char));
        strcpy(path, base_name);
      }

      /* Isola o nome da arquivo para usar nas extensões */
      len = strlen(base_name);

      for (i = len-1; i > -1; i--) {
        if (base_name[i] == '/') {
          break;
        }
      }

      /* Caso não tenha -e */
      if (i == -1) {
        aux = (char *)calloc(len + 1, sizeof(char));
        i   = 0;

        for (j = 0; j < len - 4; j++, i++) {
          aux[j] = base_name[i];
        }
        aux[len - 4] = '\0';
        free(base_name);
        base_name = (char *)calloc(len + 1, sizeof(char));
        strcpy(base_name, aux);
        free(aux);
      } else {
        /* Caso tenho -e */
        len = len - i;
        aux = (char *)calloc(len + 1, sizeof(char));
        i++;

        for (j = 0; j < len - 5; j++, i++) {
          aux[j] = base_name[i];
        }
        aux[len - 5] = '\0';
        free(base_name);
        base_name = (char *)calloc(len + 1, sizeof(char));
        strcpy(base_name, aux);
        free(aux);
      }

      /* ----------------------- INICIO ------------------------------ */
      file = fopen(path, "r"); /* Abre o arquivo no modo leitura na variável file; */
      if(file == NULL) { /* Verifica se o arquivo foi aberto; */
        printf("Ocorreu um problema ao tentar abrir o arquivo!\n");
        exit(0); /* Termina o programa; */
      }
      /* ----- INICIALIZAÇÕES ----- */
      inicializarLista(lista);
      inicializarLista(equip);
      inicializarLista(quadra);

      if (dir[strlen(dir)-1] != '/') {
        aux_name = (char*) calloc((strlen(base_name) + (strlen(dir))+6), sizeof(char));
        sprintf(aux_name, "%s/%s.txt", dir, base_name);
  		}
      else {
        aux_name = (char*) calloc((strlen(base_name) + (strlen(dir))+5), sizeof(char));
        sprintf(aux_name, "%s%s.txt", dir, base_name);
      }
      o_TXT = fopen(aux_name, "w"); /* Abre ou cria arquivo .txt em modo escrita */
      free(aux_name);
      if (dir[strlen(dir)-1] != '/') {
        aux_name = (char*) calloc((strlen(base_name) + (strlen(dir))+6), sizeof(char));
         sprintf(aux_name, "%s/%s.svg", dir, base_name);
   	  }
      else {
         aux_name = (char*) calloc((strlen(base_name) + (strlen(dir))+5), sizeof(char));
         sprintf(aux_name, "%s%s.svg", dir, base_name);
      }
      o_SVG = fopen(aux_name, "w"); /* Abre ou cria um arquivo .svg em modo escrita. */
      free(aux_name);
      fprintf(o_SVG, "<svg xmlns='http://www.w3.org/2000/svg' version='1.1' xmlns:xlink='http://www.w3.org/1999/xlink'>\n");
      content = (char*) malloc(1000*sizeof(char));
      /* -------------------------- */

      while (!feof(file)) { /* Loop até o fim do arquivo; */
        fscanf(file, " %s", comando); /* Lê a primeira linha do arquivo (comandos); */
        /*---------- C O M A N D O  -  nx ----------*/
        if(strcmp(comando, "nx") == 0) { /* Altera o número máximo de círculos e retângulos; */
            fscanf(file, " %[^\n]s ", content);
            token = strtok(content, " ");
            nx=atoi(token);
        }
        /*---------- C O M A N D O  -  c ----------*/
        else if(strcmp(comando, "c") == 0) { /* Desenha um círculo; */
          if(nx > 0){
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
            circ(o_SVG, regCirculo);
            inserirElemento(lista, *regCirculo);
            nx--;
          }
          else{
            printf("Nao foi possivel adicionar mais elementos na lista, numero nx excedido!!\n!");
            printf("O programa foi finalizado");
            return 0;
          }
        }
        /*---------- C O M A N D O  -  r ----------*/
        else if(strcmp(comando, "r") == 0) { /* Desenha um retângulo; */
          if(nx > 0) {
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
            rect(o_SVG, regRetangulo);
            inserirElemento(lista, *regRetangulo);
            nx--;
          }
          else {
            printf("Nao foi possivel adicionar mais elementos na lista, numero nx excedido!!\n");
            printf("!!!!O programa foi finalizado!!!!\n");
            return 0;
          }
        }
        /*---------- C O M A N D O  -  q ----------*/
        else if(strcmp(comando, "q") == 0) { /* Insere uma quadra (retângulo e cep) */
          fscanf(file, " %[^\n]s ", content);
          token = strtok(content, " ");
          reg_quadra->id = (char*) malloc((strlen(token)+1)* sizeof(char));
          strcpy(reg_quadra->id, token);
          token = strtok(NULL, " ");
          reg_quadra->x = atof(token);
          token = strtok(NULL, " ");
          reg_quadra->y = atof(token);
          token = strtok(NULL, " ");
          reg_quadra->largura = atof(token);
          token = strtok(NULL, " ");
          reg_quadra->altura = atof(token);
          quadra_SVG(o_SVG, reg_quadra);
          inserirQUAHISERA(quadra, *reg_quadra);
        }
        /*---------- C O M A N D O  -  h ----------*/
        else if(strcmp(comando, "h") == 0) { /* Insere um hidrante */
          fscanf(file, " %[^\n]s ", content);
          token = strtok(content, " ");
          reg_hidrante->id = (char*) malloc((strlen(token)+1)* sizeof(char));
          strcpy(reg_hidrante->id, token);
          token = strtok(NULL, " ");
          reg_hidrante->x = atof(token);
          token = strtok(NULL, " ");
          reg_hidrante->y = atof(token);
          hidrante_SVG(o_SVG, reg_hidrante);
          inserirQUAHISERA(equip, *reg_hidrante);
        }
        /*---------- C O M A N D O  -  s ----------*/
        else if(strcmp(comando, "s") == 0) { /* Insere um semáforo */
          fscanf(file, " %[^\n]s ", content);
          token = strtok(content, " ");
          reg_semaforo->id = (char*) malloc((strlen(token)+1)* sizeof(char));
          strcpy(reg_semaforo->id, token);
          token = strtok(NULL, " ");
          reg_semaforo->x = atof(token);
          token = strtok(NULL, " ");
          reg_semaforo->y = atof(token);
          semaforo_SVG(o_SVG, reg_semaforo);
          inserirQUAHISERA(equip, *reg_semaforo);
        }
        /*---------- C O M A N D O  -  t ----------*/
        else if(strcmp(comando, "t") == 0) { /* Insere uma rádio-base (torre de celular) */
          fscanf(file, " %[^\n]s ", content);
          token = strtok(content, " ");
          reg_radio->id = (char*) malloc((strlen(token)+1)* sizeof(char));
          strcpy(reg_radio->id, token);
          token = strtok(NULL, " ");
          reg_radio->x = atof(token);
          token = strtok(NULL, " ");
          reg_radio->y = atof(token);
          inserirQUAHISERA(equip, *reg_radio);
        }
        /*---------- C O M A N D O  -  cq ----------*/
        else if(strcmp(comando, "cq") == 0) { /* Insere uma rádio-base (torre de celular) */
          fscanf(file, " %[^\n]s ", content);
          token = strtok(content, " ");
          reg_quadra->borda = (char*) malloc((strlen(token)+1)* sizeof(char));
          strcpy(reg_quadra->borda, token);
          token = strtok(NULL, " ");
          reg_quadra->cor = (char*) malloc((strlen(token)+1)* sizeof(char));
          strcpy(reg_quadra->cor, token);
        }
        /*---------- C O M A N D O  -  ch ----------*/
        else if(strcmp(comando, "ch") == 0) { /* Insere uma rádio-base (torre de celular) */
          fscanf(file, " %[^\n]s ", content);
          token = strtok(content, " ");
          reg_hidrante->borda = (char*) malloc((strlen(token)+1)* sizeof(char));
          strcpy(reg_hidrante->borda, token);
          token = strtok(NULL, " ");
          reg_hidrante->cor = (char*) malloc((strlen(token)+1)* sizeof(char));
          strcpy(reg_hidrante->cor, token);
        }
        /*---------- C O M A N D O  -  ct ----------*/
        else if(strcmp(comando, "ct") == 0) { /* Insere uma rádio-base (torre de celular) */
          fscanf(file, " %[^\n]s ", content);
          token = strtok(content, " ");
          reg_radio->borda = (char*) malloc((strlen(token)+1)* sizeof(char));
          strcpy(reg_radio->borda, token);
          token = strtok(NULL, " ");
          reg_radio->cor = (char*) malloc((strlen(token)+1)* sizeof(char));
          strcpy(reg_radio->cor, token);
        }
        /*---------- C O M A N D O  -  cs ----------*/
        else if(strcmp(comando, "cs") == 0) { /* Insere uma rádio-base (torre de celular) */
          fscanf(file, " %[^\n]s ", content);
          token = strtok(content, " ");
          reg_semaforo->borda = (char*) malloc((strlen(token)+1)* sizeof(char));
          strcpy(reg_semaforo->borda, token);
          token = strtok(NULL, " ");
          reg_semaforo->cor = (char*) malloc((strlen(token)+1)* sizeof(char));
          strcpy(reg_semaforo->cor, token);
        }
        /*---------- C O M A N D O  -  o ----------*/
        else if(strcmp(comando, "o") == 0) { /* Verifica a sobreposição das formas; */
            fscanf(file, " %[^\n]s ", content);
            token = strtok(content, " ");
            id1 = atoi(token);
            token = strtok(NULL, " ");
            id2 = atoi(token);
            search01 = buscaSeq(lista, id1);
            search02 = buscaSeq(lista, id2);
            if(search01 != NULL && search02 != NULL) {
              fprintf(o_TXT, "%s ", comando);
              fprintf(o_TXT, "%d ", id1);
              fprintf(o_TXT, "%d\n", id2);
              sobrepos = calc_sobrepos(o_SVG, search01, search02);
              if(sobrepos == 1) {
                fprintf(o_TXT, "SIM\n");
              }
              else fprintf(o_TXT, "NAO\n");;
            }

        }
        /*---------- C O M A N D O  -  i ----------*/
        else if(strcmp(comando, "i") == 0) { /* Verifica se o ponto é interno à figura; */
            fscanf(file, " %[^\n]s ", content);
            token = strtok(content, " ");
            search01 = buscaSeq(lista, atoi(token));
            if(search01 != NULL) {
              fprintf(o_TXT, "%s %i ",comando, atoi(token));
              token = strtok(NULL, " ");
              x = atof(token);
              fprintf(o_TXT, "%f ", x);
              token = strtok(NULL, " ");
              y = atof(token);
              fprintf(o_TXT, "%f\n", y);
              i_point = calc_interno(search01, x, y);
              if(i_point == 1) fprintf(o_TXT, "SIM\n");
              else fprintf(o_TXT, "NAO\n");
            }
        }
        /*---------- C O M A N D O  -  d ----------*/
        else if(strcmp(comando, "d") == 0) { /* Distância do centro de massa das formas geométricas; */
            fscanf(file, " %[^\n]s ", content);
            token = strtok(content, " ");
            id1 = atoi(token);
            token = strtok(NULL, " ");
            id2 = atoi(token);
            search01 = buscaSeq(lista, id1);
            search02 = buscaSeq(lista, id2);
            if(search01 != NULL && search02 != NULL) {
              fprintf(o_TXT, "%s %d ", comando, id1);
              fprintf(o_TXT, "%d\n", id2);
              distance = calc_distance(search01, search02);
              fprintf(o_TXT, "%.2f\n" , distance);
            }
        }
        /*---------- C O M A N D O  -  a ----------*/
        else if(strcmp(comando, "a") == 0) {
            NODE search02 = lista->cabeca;
            fscanf(file, " %[^\n]s ", content);
            token = strtok(content, " ");
            id1 = atoi(token);
            search01 = buscaSeq(lista, id1);
            if(search01->reg.r == -1.0) {
              x = search01->reg.x + (search01->reg.largura/2);
              y = search01->reg.y + (search01->reg.altura/2);
            }
            else {
              x = search01->reg.x;
              y = search01->reg.y;
            }
            if(open == 0) {
              token = strtok(NULL, " ");
              /* Faz as devidas mudanças nas extensões do arquivo base para o comando a */
              if (dir[strlen(dir)-1] != '/') {
                aux_name = (char*) calloc((strlen(base_name) + (strlen(dir))+ (strlen(token))+7), sizeof(char));
                sprintf(aux_name, "%s/%s-%s.svg", dir, base_name, token);
          		}
              else {
                aux_name = (char*) calloc((strlen(base_name) + (strlen(dir))+ (strlen(token))+6), sizeof(char));
                sprintf(aux_name, "%s%s-%s.svg", dir, base_name, token);
              }
              /* ---------------------------------------------------------------------- */
              o_suSVG = fopen(aux_name, "w");
              free(aux_name);
              new_SVG(o_suSVG);
              open = 1;
            }
            while(search02 != NULL) {
              if(search02->reg.r == -1.0) {
                fprintf(o_suSVG, "\t<rect fill='%s' stroke='%s' stroke-width='%dpx' width='%f' height='%f' y='%f' x='%f' />\n", search02->reg.cor, search02->reg.borda, 1, search02->reg.largura, search02->reg.altura, search02->reg.y, search02->reg.x);
              }
              else {
                fprintf(o_suSVG, "\t<circle fill='%s' stroke='%s' r='%f' cx='%f' cy='%f' />\n", search02->reg.cor, search02->reg.borda, search02->reg.r, search02->reg.x, search02->reg.y);
              }
              search02 = search02->prox;
            }
            search02 = lista->cabeca;
            line(o_suSVG, search01, search02, x, y);
            end_SVG(o_suSVG);
            fclose(o_suSVG);
        }
        /*---------- C O M A N D O  -  # ----------*/
        else if(strcmp(comando, "#") == 0) { /* Finaliza arquivo; */
            fscanf(file, " %[^\n]s ", content);
            exibirLista(equip);
            end_SVG(o_SVG); /* Fecha a TAG do SVG */
            fclose(o_SVG);
            fclose(o_TXT);
            /* -- LIBERAÇÃO DO RESTANTE DAS MEMÓRIAS USADAS -- */
            free(base_name);
            free(dir);
            free(path);
            free(content);
            free(regCirculo);
            free(regRetangulo);
            free(reg_quadra->cor);
            free(reg_hidrante->cor);
            free(reg_semaforo->cor);
            free(reg_radio->cor);
            free(reg_quadra->borda);
            free(reg_hidrante->borda);
            free(reg_semaforo->borda);
            free(reg_radio->borda);
            free(reg_quadra);
            free(reg_hidrante);
            free(reg_semaforo);
            free(reg_radio);
            reinicializarListaEquip(quadra);
            free(quadra);
            reinicializarListaEquip(equip);
            free(equip);
            reinicializarLista(lista);
            free(lista);
            /* ------------------------------------------------- */
        }
      }
      /* ---- FINALIZAÇÃO DO CÓDIGO ----- *//**/
      fclose(file);
      printf("Programa executado com sucesso!\n");
      /* -------------------------------- */
  return 0;
}
