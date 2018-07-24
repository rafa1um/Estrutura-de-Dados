#include "svg.h"
#include "io_name.h"
#include "calc.h"
#include "hidrante.h"
#include "quadra.h"
#include "semaforo.h"
#include "torre.h"

int main(int argc, char *argv[]) {
      FILE *file, *o_SVG, *o_TXT, *o_suSVG, *qry, *o_qrySVG;
      char *base_name = NULL, *token = NULL, *dir = NULL, *path = NULL, *content = NULL, *aux = NULL, *aux_name = NULL, *base_qry = NULL;
      char comando[5];
      double x, y, altura, largura, raio, distance;
      int nx = 1000, id1, id2, i_point, sobrepos, open = 0, open2 = 0, i, j, len;

      /*EQUIPAMENTOS URBANOS */
      STORE_COLOR *cor_borda;

      /* ------------------- */
      REGISTRO *regCirculo = (REGISTRO*) malloc(sizeof(REGISTRO));
      REGISTRO *regRetangulo = (REGISTRO*) malloc(sizeof(REGISTRO));
      REGISTRO *reg_quadra = (REGISTRO*) malloc(sizeof(REGISTRO));
      REGISTRO *reg_hidrante = (REGISTRO*) malloc(sizeof(REGISTRO));
      REGISTRO *reg_semaforo = (REGISTRO*) malloc(sizeof(REGISTRO));
      REGISTRO *reg_torre = (REGISTRO*) malloc(sizeof(REGISTRO));
      LISTA *lista = (LISTA*) malloc(sizeof(LISTA));
      LISTA *quadra = (LISTA*) malloc(sizeof(LISTA));
      LISTA *hidrante = (LISTA*) malloc(sizeof(LISTA));
      LISTA *semaforo = (LISTA*) malloc(sizeof(LISTA));
      LISTA *torre = (LISTA*) malloc(sizeof(LISTA));
      /*GENERIC *hidrante1 = NULL;
      hidrante1->data = reg_hidrante
      printf("%lf", ((REGISTRO *)hidrante1->data)->x);*/
      NODE search01, search02;

      /* ------------- ARGUMENTOS ---------------*/
      for(i = 1; i < argc; i++) {
        if(strcmp("-e", argv[i]) == 0) {
          i++;
          len = strlen(argv[i]);
          path = (char *)calloc(len + 1, sizeof(char));
          strcpy(path, argv[i]);
        }
        if(strcmp("-f", argv[i]) == 0) {
          i++;
          len = strlen(argv[i]);
          base_name = (char *)calloc(len + 1, sizeof(char));
          strcpy(base_name, argv[i]);
        }
        if(strcmp("-o", argv[i]) == 0) {
          i++;
          len = strlen(argv[i]);
          dir = (char *)calloc(len + 1, sizeof(char));
          strcpy(dir, argv[i]);
        }
        if(strcmp("-q", argv[i]) == 0) {
          i++;
          len = strlen(argv[i]);
          base_qry = (char *)calloc(len + 1, sizeof(char));
          strcpy(base_qry, argv[i]);
          qry = fopen(base_qry, "r");
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
          path = (char *)calloc(len + 2 + strlen(base_name), sizeof(char));
          sprintf(path, "%s/%s", aux, base_name);
          free(aux);
        } else {
          aux = (char *)calloc(len + 1, sizeof(char));
          strcpy(aux, path);
          free(path);
          path = (char *)calloc(len + 1 + strlen(base_name), sizeof(char));
          sprintf(path, "%s%s", aux, base_name);
          free(aux);
        }
      } else {
        path = (char *)calloc(strlen(base_name) + 1, sizeof(char));
        strcpy(path, base_name);
      }

      /* Isola o nome do arquivo para usar nas extensões */
      len = strlen(base_name);

      for (i = len-1; i > -1; i--) {
        if (base_name[i] == '/') {
          break;
        }
      }

      /* Caso não tenha -e */
      if (i == -1) {
        aux = (char *)calloc(len + 1, sizeof(char));
        i = 0;

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

      if(base_qry != NULL) { /* Verifica se o arquivo qry foi aberto com exito */
        printf("Arquivo qry executado com sucesso!\n");
        printf("%s", base_qry);
        len = strlen(base_qry);
        for (i = len-1; i > -1; i--) {
          if (base_qry[i] == '/') {
            break;
          }
        }
        /* Caso não tenha -e */
        if (i == -1) {
          aux = (char *)calloc(len + 1, sizeof(char));
          i   = 0;

          for (j = 0; j < len - 4; j++, i++) {
            aux[j] = base_qry[i];
          }
          aux[len - 4] = '\0';
          free(base_qry);
          base_qry = (char *)calloc(len + 1, sizeof(char));
          strcpy(base_qry, aux);
          free(aux);
        } else {
          /* Caso tenho -e */
          len = len - i;
          aux = (char *)calloc(len + 1, sizeof(char));
          i++;

          for (j = 0; j < len - 5; j++, i++) {
            aux[j] = base_qry[i];
          }
          aux[len - 5] = '\0';
          free(base_qry);
          base_qry = (char *)calloc(len + 1, sizeof(char));
          strcpy(base_qry, aux);
          free(aux);
        }
      } else {
        printf("Ocorreu um erro ao abrir o arquivo .qry!!");
      }


      /* ----------------------- INICIO ------------------------------ */
      file = fopen(path, "r"); /* Abre o arquivo no modo leitura na variável file; */
      if(file == NULL) { /* Verifica se o arquivo foi aberto; */
        printf("Ocorreu um problema ao tentar abrir o arquivo geo!\n");
        exit(0); /* Termina o programa; */
      }
      /* ----- INICIALIZAÇÕES ----- */
      inicializarLista(lista);
      inicializarLista(quadra);
      inicializarLista(hidrante);
      inicializarLista(semaforo);
      inicializarLista(torre);

      if (dir[strlen(dir)-1] != '/') {
        aux_name = (char*) calloc((strlen(base_name) + (strlen(dir))+6), sizeof(char));
        sprintf(aux_name, "%s/%s.txt", dir, base_name);
  		}
      else {
        aux_name = (char*) calloc((strlen(base_name) + (strlen(dir))+5), sizeof(char));
        sprintf(aux_name, "%s%s.txt", dir, base_name);
      }
      o_TXT = fopen(aux_name, "a"); /* Abre ou cria arquivo .txt em modo escrita */
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
        printf("%s\n", comando);
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
            free(regCirculo->cor);
            free(regCirculo->borda);
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
            free(regRetangulo->cor);
            free(regRetangulo->borda);
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
          inserirQUAHISERA(hidrante, *reg_hidrante);
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
          inserirQUAHISERA(semaforo, *reg_semaforo);
        }
        /*---------- C O M A N D O  -  t ----------*/
        else if(strcmp(comando, "t") == 0) { /* Insere uma rádio-base (torre de celular) */
          fscanf(file, " %[^\n]s ", content);
          token = strtok(content, " ");
          reg_torre->id = (char*) malloc((strlen(token)+1)* sizeof(char));
          strcpy(reg_torre->id, token);
          token = strtok(NULL, " ");
          reg_torre->x = atof(token);
          token = strtok(NULL, " ");
          reg_torre->y = atof(token);
          torre_SVG(o_SVG, reg_torre);
          inserirQUAHISERA(torre, *reg_torre);
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
          reg_torre->borda = (char*) malloc((strlen(token)+1)* sizeof(char));
          strcpy(reg_torre->borda, token);
          token = strtok(NULL, " ");
          reg_torre->cor = (char*) malloc((strlen(token)+1)* sizeof(char));
          strcpy(reg_torre->cor, token);
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
            if(base_qry != NULL) {
              /*------- LEITURA DO ARQUIVO QRY ---------*/
              while (!feof(qry)) { /* Loop até o fim do arquivo; */
                fscanf(qry, " %s", comando); /* Lê a primeira linha do arquivo (comandos); */
                if(feof(qry)){
                  break;
                }
                if(open2 == 0) {
                  if (dir[strlen(dir)-1] != '/') {
                    aux_name = (char*) calloc((strlen(base_name) + (strlen(dir))+ (strlen(token))+7), sizeof(char));
                    sprintf(aux_name, "%s/%s-%s.svg", dir, base_name, base_qry);
              		}
                  else {
                    aux_name = (char*) calloc((strlen(base_name) + (strlen(dir))+ (strlen(token))+6), sizeof(char));
                    sprintf(aux_name, "%s%s-%s.svg", dir, base_name, base_qry);
                  }
                  /* ---------------------------------------------------------------------- */
                  o_qrySVG = fopen(aux_name, "w");
                  free(aux_name);
                  new_SVG(o_qrySVG);
                  open = 1;
                }
                /*---------- C O M A N D O  -  q? ----------*/
                if(strcmp(comando, "q?") == 0) {
                  fscanf(qry, " %[^\n]s ", content);
                  REGISTRO *regRetanguloTemp = (REGISTRO*) malloc(sizeof(REGISTRO));
                  token = strtok(content, " ");
                  regRetanguloTemp->x = atof(token);
                  token = strtok(NULL, " ");
                  regRetanguloTemp->y = atof(token);
                  token = strtok(NULL, " ");
                  regRetanguloTemp->largura = atof(token);
                  token = strtok(NULL, " ");
                  regRetanguloTemp->altura = atof(token);
                  regRetanguloTemp->r = -1.0;
                  fprintf(o_qrySVG, "\t<rect x='%f' y='%f' width='%f' height='%f' fill='none'\n", regRetanguloTemp->x, regRetanguloTemp->y, regRetanguloTemp->largura, regRetanguloTemp->altura);
                  fprintf(o_qrySVG, "\t\tstyle=\"stroke:%s; stroke-width:3; stroke-dasharray:5,5\" />\n", "black");
                  /* VERIFICAR SE A QUADRA ESTÁ DENTRO DO RETANGULO TRACEJADO */
                  NODE quadra_node = quadra->cabeca;
                  while(quadra_node != NULL) {
                    x = quadra_node->reg.x;
                    y = quadra_node->reg.y;
                    largura = quadra_node->reg.largura;
                    altura = quadra_node->reg.altura;
                    if((calc_interno_2(regRetanguloTemp, x, y) == 1) && (calc_interno_2(regRetanguloTemp, x+largura, y) == 1) && (calc_interno_2(regRetanguloTemp, x, y+altura) == 1) && (calc_interno_2(regRetanguloTemp,x+largura, y+altura)) == 1){
                      fprintf(o_TXT, "QUADRA - CEP: %s - X: %lf - Y: %lf - H: %lf - W: %lf\n", quadra_node->reg.id, quadra_node->reg.x, quadra_node->reg.y, quadra_node->reg.largura, quadra_node->reg.altura);
                    }
                    quadra_node = quadra_node->prox;
                  }
                  /* VERIFICAR SE O HIDRANTE ESTÁ DENTRO DO RETANGULO TRACEJADO */
                  NODE hidrante_node = hidrante->cabeca;
                  while(hidrante_node != NULL) {
                    x = hidrante_node->reg.x;
                    y = hidrante_node->reg.y;
                    raio = 8;
                    if((calc_interno_2(regRetanguloTemp, x, y+raio) == 1) && (calc_interno_2(regRetanguloTemp, x, y-raio) == 1) && (calc_interno_2(regRetanguloTemp, x+raio, y) == 1) && (calc_interno_2(regRetanguloTemp,x-raio, y)) == 1){
                      fprintf(o_TXT, "HIDRANTE - ID: %s - X: %lf - Y: %lf\n", hidrante_node->reg.id, hidrante_node->reg.x, hidrante_node->reg.y);
                    }
                    hidrante_node = hidrante_node->prox;
                  }
                  /* VERIFICAR SE A TORRE ESTÁ DENTRO DO RETANGULO TRACEJADO */
                  NODE torre_node = torre->cabeca;
                  while(torre_node != NULL) {
                    x = torre_node->reg.x;
                    y = torre_node->reg.y;
                    raio = 8;
                    if((calc_interno_2(regRetanguloTemp, x, y+raio) == 1) && (calc_interno_2(regRetanguloTemp, x, y-raio) == 1) && (calc_interno_2(regRetanguloTemp, x+raio, y) == 1) && (calc_interno_2(regRetanguloTemp,x-raio, y)) == 1){
                      fprintf(o_TXT, "TORRE - ID: %s - X: %lf - Y: %lf\n", torre_node->reg.id, torre_node->reg.x, torre_node->reg.y);
                    }
                    torre_node = torre_node->prox;
                  }
                  /* VERIFICAR SE O SEMAFORO ESTÁ DENTRO DO RETANGULO TRACEJADO */
                  NODE semaforo_node = semaforo->cabeca;
                  while(semaforo_node != NULL) {
                    x = semaforo_node->reg.x;
                    y = semaforo_node->reg.y;
                    if((calc_interno_2(regRetanguloTemp, x, y) == 1) && (calc_interno_2(regRetanguloTemp, x+largura, y) == 1) && (calc_interno_2(regRetanguloTemp, x, y+altura) == 1) && (calc_interno_2(regRetanguloTemp,x+largura, y+altura)) == 1){
                      fprintf(o_TXT, "SEMAFORO - ID: %s - X: %lf - Y: %lf\n", semaforo_node->reg.id, semaforo_node->reg.x, semaforo_node->reg.y);
                    }
                    semaforo_node = semaforo_node->prox;
                  }
                  free(regRetanguloTemp);
                }

                /*---------- C O M A N D O  -  Q? ----------*/
                else if(strcmp(comando, "Q?") == 0) {
                  fscanf(qry, " %[^\n]s ", content);
                  REGISTRO *regCirculoTemp = (REGISTRO*) malloc(sizeof(REGISTRO));
                  token = strtok(content, " ");
                  regCirculoTemp->r = atof(token);
                  token = strtok(NULL, " ");
                  regCirculoTemp->x = atof(token);
                  token = strtok(NULL, " ");
                  regCirculoTemp->y = atof(token);
                  /* VERIFICAR SE A QUADRA ESTÁ DENTRO DO CIRCULO TRACEJADO */
                  NODE quadra_node = quadra->cabeca;
                  while(quadra_node != NULL) {
                    x = quadra_node->reg.x;
                    y = quadra_node->reg.y;
                    largura = quadra_node->reg.largura;
                    altura = quadra_node->reg.altura;
                    if((calc_interno_2(regCirculoTemp, x, y) == 1) && (calc_interno_2(regCirculoTemp, x+largura, y) == 1) && (calc_interno_2(regCirculoTemp, x, y+altura) == 1) && (calc_interno_2(regCirculoTemp,x+largura, y+altura)) == 1){
                      fprintf(o_TXT, "QUADRA - CEP: %s - X: %lf - Y: %lf - H: %lf - W: %lf\n", quadra_node->reg.id, quadra_node->reg.x, quadra_node->reg.y, quadra_node->reg.largura, quadra_node->reg.altura);
                    }
                    quadra_node = quadra_node->prox;
                  }
                  /* VERIFICAR SE O HIDRANTE ESTÁ DENTRO DO RETANGULO TRACEJADO */
                  NODE hidrante_node = hidrante->cabeca;
                  while(hidrante_node != NULL) {
                    x = hidrante_node->reg.x;
                    y = hidrante_node->reg.y;
                    raio = 8;
                    if((calc_interno_2(regCirculoTemp, x, y+raio) == 1) && (calc_interno_2(regCirculoTemp, x, y-raio) == 1) && (calc_interno_2(regCirculoTemp, x+raio, y) == 1) && (calc_interno_2(regCirculoTemp,x-raio, y)) == 1){
                      fprintf(o_TXT, "HIDRANTE - ID: %s - X: %lf - Y: %lf\n", hidrante_node->reg.id, hidrante_node->reg.x, hidrante_node->reg.y);
                    }
                    hidrante_node = hidrante_node->prox;
                  }
                  /* VERIFICAR SE A TORRE ESTÁ DENTRO DO RETANGULO TRACEJADO */
                  NODE torre_node = torre->cabeca;
                  while(torre_node != NULL) {
                    x = torre_node->reg.x;
                    y = torre_node->reg.y;
                    raio = 8;
                    if((calc_interno_2(regCirculoTemp, x, y+raio) == 1) && (calc_interno_2(regCirculoTemp, x, y-raio) == 1) && (calc_interno_2(regCirculoTemp, x+raio, y) == 1) && (calc_interno_2(regCirculoTemp, x-raio, y)) == 1){
                      fprintf(o_TXT, "TORRE - ID: %s - X: %lf - Y: %lf\n", torre_node->reg.id, torre_node->reg.x, torre_node->reg.y);
                    }
                    torre_node = torre_node->prox;
                  }
                  /* VERIFICAR SE O SEMAFORO ESTÁ DENTRO DO RETANGULO TRACEJADO */
                  NODE semaforo_node = semaforo->cabeca;
                  while(semaforo_node != NULL) {
                    x = semaforo_node->reg.x;
                    y = semaforo_node->reg.y;
                    largura = 15;
                    altura = 35;
                    if((calc_interno_2(regCirculoTemp, x, y) == 1) && (calc_interno_2(regCirculoTemp, x+largura, y) == 1) && (calc_interno_2(regCirculoTemp, x, y+altura) == 1) && (calc_interno_2(regCirculoTemp,x+largura, y+altura)) == 1){
                      fprintf(o_TXT, "SEMAFORO: ID: %s - X: %lf - Y: %lf\n", semaforo_node->reg.id, semaforo_node->reg.x, semaforo_node->reg.y);
                    }
                    semaforo_node = semaforo_node->prox;
                  }
                  printf("%lf %lf %lf",regCirculoTemp->r,regCirculoTemp->x,regCirculoTemp->y);
                  fprintf(o_qrySVG, "\t<circle r ='%f' cx='%f' cy='%f' fill='none'", regCirculoTemp->r, regCirculoTemp->x, regCirculoTemp->y);
                  fprintf(o_qrySVG, "style=\"stroke:%s; stroke-width:3; stroke-dasharray:5,5\" />\n", "black");
                  free(regCirculoTemp);
                }
                /*---------- C O M A N D O  -  dq ----------*/
                else if(strcmp(comando, "dq") == 0) {
                  fscanf(qry, " %[^\n]s ", content);
                  REGISTRO *regRetanguloTemp = (REGISTRO*) malloc(sizeof(REGISTRO));
                  token = strtok(content, " ");
                  regRetanguloTemp->x = atof(token);
                  token = strtok(NULL, " ");
                  regRetanguloTemp->y = atof(token);
                  token = strtok(NULL, " ");
                  regRetanguloTemp->largura = atof(token);
                  token = strtok(NULL, " ");
                  regRetanguloTemp->altura = atof(token);
                  regRetanguloTemp->r = -1.0;
                  NODE quadra_node = quadra->cabeca;
                  while(quadra_node != NULL) {
                    x = quadra_node->reg.x;
                    y = quadra_node->reg.y;
                    largura = quadra_node->reg.largura;
                    altura = quadra_node->reg.altura;
                    if((calc_interno_2(regRetanguloTemp, x, y) == 1) && (calc_interno_2(regRetanguloTemp, x+largura, y) == 1) && (calc_interno_2(regRetanguloTemp, x, y+altura) == 1) && (calc_interno_2(regRetanguloTemp,x+largura, y+altura)) == 1){
                      fprintf(o_TXT, "QUADRA REMOVIDA - CEP: %s\n", quadra_node->reg.id);
                      excluirElemento2(quadra, quadra_node->reg.id);
                    }
                    quadra_node = quadra_node->prox;
                  }
                  free(regRetanguloTemp);
                }
                /*---------- C O M A N D O  -  dle ----------*/
                else if(strcmp(comando, "dle") == 0) {
                  fscanf(qry, " %[^\n]s ", content);
                  token = strtok(content, " ");
                  /* -----  APENAS h ----- */
                  if(strcmp(token, "h") == 0) {
                    fscanf(qry, " %[^\n]s ", content);
                    REGISTRO *regRetanguloTemp = (REGISTRO*) malloc(sizeof(REGISTRO));
                    token = strtok(NULL, " ");
                    regRetanguloTemp->x = atof(token);
                    token = strtok(NULL, " ");
                    regRetanguloTemp->y = atof(token);
                    token = strtok(NULL, " ");
                    regRetanguloTemp->largura = atof(token);
                    token = strtok(NULL, " ");
                    regRetanguloTemp->altura = atof(token);
                    regRetanguloTemp->r = -1.0;
                    NODE hidrante_node = hidrante->cabeca;
                    while(hidrante_node != NULL) {
                      x = hidrante_node->reg.x;
                      y = hidrante_node->reg.y;
                      raio = 8;
                      if((calc_interno_2(regRetanguloTemp, x+raio, y) == 1) && (calc_interno_2(regRetanguloTemp, x-raio, y) == 1) && (calc_interno_2(regRetanguloTemp, x, y+raio) == 1) && (calc_interno_2(regRetanguloTemp,x, y-raio)) == 1){
                        fprintf(o_TXT, "HIDRANTE REMOVIDO - ID: %s\n", hidrante_node->reg.id);
                        excluirElemento2(hidrante, hidrante_node->reg.id);
                      }
                      hidrante_node = hidrante_node->prox;
                    }
                    free(regRetanguloTemp);
                  }
                  /* -----  APENAS r ----- *//*---------- C O M A N D O  -  dle ----------*/
                  else if(strcmp(token, "r") == 0) {
                    fscanf(qry, " %[^\n]s ", content);
                    REGISTRO *regRetanguloTemp = (REGISTRO*) malloc(sizeof(REGISTRO));
                    token = strtok(NULL, " ");
                    regRetanguloTemp->x = atof(token);
                    token = strtok(NULL, " ");
                    regRetanguloTemp->y = atof(token);
                    token = strtok(NULL, " ");
                    regRetanguloTemp->largura = atof(token);
                    token = strtok(NULL, " ");
                    regRetanguloTemp->altura = atof(token);
                    regRetanguloTemp->r = -1.0;
                    NODE torre_node = torre->cabeca;
                    while(torre_node != NULL) {
                      x = torre_node->reg.x;
                      y = torre_node->reg.y;
                      raio = 8;
                      if((calc_interno_2(regRetanguloTemp, x+raio, y) == 1) && (calc_interno_2(regRetanguloTemp, x-raio, y) == 1) && (calc_interno_2(regRetanguloTemp, x, y+raio) == 1) && (calc_interno_2(regRetanguloTemp,x, y-raio)) == 1){
                        fprintf(o_TXT, "TORRE REMOVIDO - ID: %s\n", torre_node->reg.id);
                        excluirElemento2(torre, torre_node->reg.id);
                      }
                      torre_node = torre_node->prox;
                    }
                    free(regRetanguloTemp);
                  }
                  /* -----  APENAS s ----- */
                  else if(strcmp(token, "s") == 0) {
                    fscanf(qry, " %[^\n]s ", content);
                    REGISTRO *regRetanguloTemp = (REGISTRO*) malloc(sizeof(REGISTRO));
                    token = strtok(NULL, " ");
                    regRetanguloTemp->x = atof(token);
                    token = strtok(NULL, " ");
                    regRetanguloTemp->y = atof(token);
                    token = strtok(NULL, " ");
                    regRetanguloTemp->largura = atof(token);
                    token = strtok(NULL, " ");
                    regRetanguloTemp->altura = atof(token);
                    regRetanguloTemp->r = -1.0;
                    NODE semaforo_node = semaforo->cabeca;
                    while(semaforo_node != NULL) {
                      x = semaforo_node->reg.x;
                      y = semaforo_node->reg.y;
                      raio = 8;
                      if((calc_interno_2(regRetanguloTemp, x+raio, y) == 1) && (calc_interno_2(regRetanguloTemp, x-raio, y) == 1) && (calc_interno_2(regRetanguloTemp, x, y+raio) == 1) && (calc_interno_2(regRetanguloTemp,x, y-raio)) == 1){
                        fprintf(o_TXT, "TORRE REMOVIDO - ID: %s\n", semaforo_node->reg.id);
                        excluirElemento2(semaforo, semaforo_node->reg.id);
                      }
                      semaforo_node = semaforo_node->prox;
                    }
                    free(regRetanguloTemp);
                  }
                  /* -----  PARA hr ou rh ----- */
                  else if((strcmp(token, "hr") == 0) || (strcmp(token, "rh") == 0)) {
                    fscanf(qry, " %[^\n]s ", content);
                    REGISTRO *regRetanguloTemp = (REGISTRO*) malloc(sizeof(REGISTRO));
                    token = strtok(NULL, " ");
                    regRetanguloTemp->x = atof(token);
                    token = strtok(NULL, " ");
                    regRetanguloTemp->y = atof(token);
                    token = strtok(NULL, " ");
                    regRetanguloTemp->largura = atof(token);
                    token = strtok(NULL, " ");
                    regRetanguloTemp->altura = atof(token);
                    regRetanguloTemp->r = -1.0;
                    NODE hidrante_node = hidrante->cabeca;
                    while(hidrante_node != NULL) {
                      x = hidrante_node->reg.x;
                      y = hidrante_node->reg.y;
                      raio = 8;
                      if((calc_interno_2(regRetanguloTemp, x+raio, y) == 1) && (calc_interno_2(regRetanguloTemp, x-raio, y) == 1) && (calc_interno_2(regRetanguloTemp, x, y+raio) == 1) && (calc_interno_2(regRetanguloTemp,x, y-raio)) == 1){
                        fprintf(o_TXT, "HIDRANTE REMOVIDO - ID: %s\n", hidrante_node->reg.id);
                        excluirElemento2(hidrante, hidrante_node->reg.id);
                      }
                      hidrante_node = hidrante_node->prox;
                    }
                    NODE torre_node = torre->cabeca;
                    while(torre_node != NULL) {
                      x = torre_node->reg.x;
                      y = torre_node->reg.y;
                      raio = 8;
                      if((calc_interno_2(regRetanguloTemp, x+raio, y) == 1) && (calc_interno_2(regRetanguloTemp, x-raio, y) == 1) && (calc_interno_2(regRetanguloTemp, x, y+raio) == 1) && (calc_interno_2(regRetanguloTemp,x, y-raio)) == 1){
                        fprintf(o_TXT, "TORRE REMOVIDO - ID: %s\n", torre_node->reg.id);
                        excluirElemento2(torre, torre_node->reg.id);
                      }
                      torre_node = torre_node->prox;
                    }
                    free(regRetanguloTemp);
                  }
                  /* -----  PARA hs ou sh ----- */
                  else if((strcmp(token, "hs") == 0) || (strcmp(token, "sh") == 0)) {
                    fscanf(qry, " %[^\n]s ", content);
                    REGISTRO *regRetanguloTemp = (REGISTRO*) malloc(sizeof(REGISTRO));
                    token = strtok(NULL, " ");
                    regRetanguloTemp->x = atof(token);
                    token = strtok(NULL, " ");
                    regRetanguloTemp->y = atof(token);
                    token = strtok(NULL, " ");
                    regRetanguloTemp->largura = atof(token);
                    token = strtok(NULL, " ");
                    regRetanguloTemp->altura = atof(token);
                    regRetanguloTemp->r = -1.0;
                    NODE hidrante_node = hidrante->cabeca;
                    while(hidrante_node != NULL) {
                      x = hidrante_node->reg.x;
                      y = hidrante_node->reg.y;
                      raio = 8;
                      if((calc_interno_2(regRetanguloTemp, x+raio, y) == 1) && (calc_interno_2(regRetanguloTemp, x-raio, y) == 1) && (calc_interno_2(regRetanguloTemp, x, y+raio) == 1) && (calc_interno_2(regRetanguloTemp,x, y-raio)) == 1){
                        fprintf(o_TXT, "HIDRANTE REMOVIDO - ID: %s\n", hidrante_node->reg.id);
                        excluirElemento2(hidrante, hidrante_node->reg.id);
                      }
                      hidrante_node = hidrante_node->prox;
                    }
                    NODE semaforo_node = semaforo->cabeca;
                    while(semaforo_node != NULL) {
                      x = semaforo_node->reg.x;
                      y = semaforo_node->reg.y;
                      raio = 8;
                      if((calc_interno_2(regRetanguloTemp, x+raio, y) == 1) && (calc_interno_2(regRetanguloTemp, x-raio, y) == 1) && (calc_interno_2(regRetanguloTemp, x, y+raio) == 1) && (calc_interno_2(regRetanguloTemp,x, y-raio)) == 1){
                        fprintf(o_TXT, "TORRE REMOVIDO - ID: %s\n", semaforo_node->reg.id);
                        excluirElemento2(semaforo, semaforo_node->reg.id);
                      }
                      semaforo_node = semaforo_node->prox;
                    }
                    free(regRetanguloTemp);
                  }
                  /* -----  PARA sr ou rs ----- */
                  else if((strcmp(token, "sr") == 0) || (strcmp(token, "rs") == 0)) {
                    fscanf(qry, " %[^\n]s ", content);
                    REGISTRO *regRetanguloTemp = (REGISTRO*) malloc(sizeof(REGISTRO));
                    token = strtok(NULL, " ");
                    regRetanguloTemp->x = atof(token);
                    token = strtok(NULL, " ");
                    regRetanguloTemp->y = atof(token);
                    token = strtok(NULL, " ");
                    regRetanguloTemp->largura = atof(token);
                    token = strtok(NULL, " ");
                    regRetanguloTemp->altura = atof(token);
                    regRetanguloTemp->r = -1.0;
                    NODE torre_node = torre->cabeca;
                    while(torre_node != NULL) {
                      x = torre_node->reg.x;
                      y = torre_node->reg.y;
                      raio = 8;
                      if((calc_interno_2(regRetanguloTemp, x+raio, y) == 1) && (calc_interno_2(regRetanguloTemp, x-raio, y) == 1) && (calc_interno_2(regRetanguloTemp, x, y+raio) == 1) && (calc_interno_2(regRetanguloTemp,x, y-raio)) == 1){
                        fprintf(o_TXT, "TORRE REMOVIDO - ID: %s\n", torre_node->reg.id);
                        excluirElemento2(torre, torre_node->reg.id);
                      }
                      torre_node = torre_node->prox;
                    }
                    NODE semaforo_node = semaforo->cabeca;
                    while(semaforo_node != NULL) {
                      x = semaforo_node->reg.x;
                      y = semaforo_node->reg.y;
                      raio = 8;
                      if((calc_interno_2(regRetanguloTemp, x+raio, y) == 1) && (calc_interno_2(regRetanguloTemp, x-raio, y) == 1) && (calc_interno_2(regRetanguloTemp, x, y+raio) == 1) && (calc_interno_2(regRetanguloTemp,x, y-raio)) == 1){
                        fprintf(o_TXT, "TORRE REMOVIDO - ID: %s\n", semaforo_node->reg.id);
                        excluirElemento2(semaforo, semaforo_node->reg.id);
                      }
                      semaforo_node = semaforo_node->prox;
                    }
                    free(regRetanguloTemp);
                  }
                  /* -----  PARA  todas as 6 possibilidades com 3 letras ----- */
                  else if((strcmp(token, "srh") == 0) || (strcmp(token, "shr") == 0) || (strcmp(token, "rsh") == 0) || (strcmp(token, "rhs") == 0) || (strcmp(token, "hsr") == 0) || (strcmp(token, "hrs") == 0)) {
                    fscanf(qry, " %[^\n]s ", content);
                    REGISTRO *regRetanguloTemp = (REGISTRO*) malloc(sizeof(REGISTRO));
                    token = strtok(NULL, " ");
                    regRetanguloTemp->x = atof(token);
                    token = strtok(NULL, " ");
                    regRetanguloTemp->y = atof(token);
                    token = strtok(NULL, " ");
                    regRetanguloTemp->largura = atof(token);
                    token = strtok(NULL, " ");
                    regRetanguloTemp->altura = atof(token);
                    regRetanguloTemp->r = -1.0;
                    NODE torre_node = torre->cabeca;
                    while(torre_node != NULL) {
                      x = torre_node->reg.x;
                      y = torre_node->reg.y;
                      raio = 8;
                      if((calc_interno_2(regRetanguloTemp, x+raio, y) == 1) && (calc_interno_2(regRetanguloTemp, x-raio, y) == 1) && (calc_interno_2(regRetanguloTemp, x, y+raio) == 1) && (calc_interno_2(regRetanguloTemp,x, y-raio)) == 1){
                        fprintf(o_TXT, "TORRE REMOVIDO - ID: %s\n", torre_node->reg.id);
                        excluirElemento2(torre, torre_node->reg.id);
                      }
                      torre_node = torre_node->prox;
                    }
                    NODE semaforo_node = semaforo->cabeca;
                    while(semaforo_node != NULL) {
                      x = semaforo_node->reg.x;
                      y = semaforo_node->reg.y;
                      raio = 8;
                      if((calc_interno_2(regRetanguloTemp, x+raio, y) == 1) && (calc_interno_2(regRetanguloTemp, x-raio, y) == 1) && (calc_interno_2(regRetanguloTemp, x, y+raio) == 1) && (calc_interno_2(regRetanguloTemp,x, y-raio)) == 1){
                        fprintf(o_TXT, "TORRE REMOVIDO - ID: %s\n", semaforo_node->reg.id);
                        excluirElemento2(semaforo, semaforo_node->reg.id);
                      }
                      semaforo_node = semaforo_node->prox;
                    }
                    NODE hidrante_node = hidrante->cabeca;
                    while(hidrante_node != NULL) {
                      x = hidrante_node->reg.x;
                      y = hidrante_node->reg.y;
                      raio = 8;
                      if((calc_interno_2(regRetanguloTemp, x+raio, y) == 1) && (calc_interno_2(regRetanguloTemp, x-raio, y) == 1) && (calc_interno_2(regRetanguloTemp, x, y+raio) == 1) && (calc_interno_2(regRetanguloTemp,x, y-raio)) == 1){
                        fprintf(o_TXT, "HIDRANTE REMOVIDO - ID: %s\n", hidrante_node->reg.id);
                        excluirElemento2(hidrante, hidrante_node->reg.id);
                      }
                      hidrante_node = hidrante_node->prox;
                    }
                    free(regRetanguloTemp);
                  }
                }
                /*---------- C O M A N D O  -  Dq ----------*/
                else if(strcmp(comando, "Dq") == 0) {
                  fscanf(qry, " %[^\n]s ", content);
                  REGISTRO *regCirculoTemp = (REGISTRO*) malloc(sizeof(REGISTRO));
                  token = strtok(content, " ");
                  regCirculoTemp->r = atof(token);
                  token = strtok(NULL, " ");
                  regCirculoTemp->x = atof(token);
                  token = strtok(NULL, " ");
                  regCirculoTemp->y = atof(token);
                  NODE quadra_node = quadra->cabeca;
                  while(quadra_node != NULL) {
                    x = quadra_node->reg.x;
                    y = quadra_node->reg.y;
                    largura = quadra_node->reg.largura;
                    altura = quadra_node->reg.altura;
                    if((calc_interno_2(regCirculoTemp, x, y) == 1) && (calc_interno_2(regCirculoTemp, x+largura, y) == 1) && (calc_interno_2(regCirculoTemp, x, y+altura) == 1) && (calc_interno_2(regCirculoTemp,x+largura, y+altura)) == 1){
                      fprintf(o_TXT, "QUADRA REMOVIDA - CEP: %s\n", quadra_node->reg.id);
                      excluirElemento2(quadra, quadra_node->reg.id);
                    }
                    quadra_node = quadra_node->prox;
                  }
                  free(regCirculoTemp);
                  exibirLista(quadra);
                }
                /*---------- C O M A N D O  -  Dle ----------*/
                else if(strcmp(comando, "Dle") == 0) {
                  fscanf(qry, " %[^\n]s ", content);
                  token = strtok(content, " ");
                  /* -----  APENAS h ----- */
                  if(strcmp(token, "h") == 0) {
                    fscanf(qry, " %[^\n]s ", content);
                    REGISTRO *regCirculoTemp = (REGISTRO*) malloc(sizeof(REGISTRO));
                    token = strtok(content, " ");
                    regCirculoTemp->r = atof(token);
                    token = strtok(NULL, " ");
                    regCirculoTemp->x = atof(token);
                    token = strtok(NULL, " ");
                    regCirculoTemp->y = atof(token);
                    NODE hidrante_node = hidrante->cabeca;
                    while(hidrante_node != NULL) {
                      x = hidrante_node->reg.x;
                      y = hidrante_node->reg.y;
                      raio = 8;
                      if((calc_interno_2(regCirculoTemp, x+raio, y) == 1) && (calc_interno_2(regCirculoTemp, x-raio, y) == 1) && (calc_interno_2(regCirculoTemp, x, y+raio) == 1) && (calc_interno_2(regCirculoTemp,x, y-raio)) == 1){
                        fprintf(o_TXT, "HIDRANTE REMOVIDO - ID: %s\n", hidrante_node->reg.id);
                        excluirElemento2(hidrante, hidrante_node->reg.id);
                      }
                      hidrante_node = hidrante_node->prox;
                    }
                    free(regCirculoTemp);
                  }
                  /* -----  APENAS r ----- *//*---------- C O M A N D O  -  dle ----------*/
                  else if(strcmp(token, "r") == 0) {
                    fscanf(qry, " %[^\n]s ", content);
                    REGISTRO *regCirculoTemp = (REGISTRO*) malloc(sizeof(REGISTRO));
                    token = strtok(content, " ");
                    regCirculoTemp->r = atof(token);
                    token = strtok(NULL, " ");
                    regCirculoTemp->x = atof(token);
                    token = strtok(NULL, " ");
                    regCirculoTemp->y = atof(token);
                    NODE torre_node = torre->cabeca;
                    while(torre_node != NULL) {
                      x = torre_node->reg.x;
                      y = torre_node->reg.y;
                      raio = 8;
                      if((calc_interno_2(regCirculoTemp, x+raio, y) == 1) && (calc_interno_2(regCirculoTemp, x-raio, y) == 1) && (calc_interno_2(regCirculoTemp, x, y+raio) == 1) && (calc_interno_2(regCirculoTemp,x, y-raio)) == 1){
                        fprintf(o_TXT, "TORRE REMOVIDO - ID: %s\n", torre_node->reg.id);
                        excluirElemento2(torre, torre_node->reg.id);
                      }
                      torre_node = torre_node->prox;
                    }
                    free(regCirculoTemp);
                  }
                  /* -----  APENAS s ----- */
                  else if(strcmp(token, "s") == 0) {
                    fscanf(qry, " %[^\n]s ", content);
                    REGISTRO *regCirculoTemp = (REGISTRO*) malloc(sizeof(REGISTRO));
                    token = strtok(content, " ");
                    regCirculoTemp->r = atof(token);
                    token = strtok(NULL, " ");
                    regCirculoTemp->x = atof(token);
                    token = strtok(NULL, " ");
                    regCirculoTemp->y = atof(token);
                    NODE semaforo_node = semaforo->cabeca;
                    while(semaforo_node != NULL) {
                      x = semaforo_node->reg.x;
                      y = semaforo_node->reg.y;
                      raio = 8;
                      if((calc_interno_2(regCirculoTemp, x+raio, y) == 1) && (calc_interno_2(regCirculoTemp, x-raio, y) == 1) && (calc_interno_2(regCirculoTemp, x, y+raio) == 1) && (calc_interno_2(regCirculoTemp,x, y-raio)) == 1){
                        fprintf(o_TXT, "TORRE REMOVIDO - ID: %s\n", semaforo_node->reg.id);
                        excluirElemento2(semaforo, semaforo_node->reg.id);
                      }
                      semaforo_node = semaforo_node->prox;
                    }
                    free(regCirculoTemp);
                  }
                  /* -----  PARA hr ou rh ----- */
                  else if((strcmp(token, "hr") == 0) || (strcmp(token, "rh") == 0)) {
                    fscanf(qry, " %[^\n]s ", content);
                    REGISTRO *regCirculoTemp = (REGISTRO*) malloc(sizeof(REGISTRO));
                    token = strtok(content, " ");
                    regCirculoTemp->r = atof(token);
                    token = strtok(NULL, " ");
                    regCirculoTemp->x = atof(token);
                    token = strtok(NULL, " ");
                    regCirculoTemp->y = atof(token);
                    NODE hidrante_node = hidrante->cabeca;
                    while(hidrante_node != NULL) {
                      x = hidrante_node->reg.x;
                      y = hidrante_node->reg.y;
                      raio = 8;
                      if((calc_interno_2(regCirculoTemp, x+raio, y) == 1) && (calc_interno_2(regCirculoTemp, x-raio, y) == 1) && (calc_interno_2(regCirculoTemp, x, y+raio) == 1) && (calc_interno_2(regCirculoTemp,x, y-raio)) == 1){
                        fprintf(o_TXT, "HIDRANTE REMOVIDO - ID: %s\n", hidrante_node->reg.id);
                        excluirElemento2(hidrante, hidrante_node->reg.id);
                      }
                      hidrante_node = hidrante_node->prox;
                    }
                    NODE torre_node = torre->cabeca;
                    while(torre_node != NULL) {
                      x = torre_node->reg.x;
                      y = torre_node->reg.y;
                      raio = 8;
                      if((calc_interno_2(regCirculoTemp, x+raio, y) == 1) && (calc_interno_2(regCirculoTemp, x-raio, y) == 1) && (calc_interno_2(regCirculoTemp, x, y+raio) == 1) && (calc_interno_2(regCirculoTemp,x, y-raio)) == 1){
                        fprintf(o_TXT, "TORRE REMOVIDO - ID: %s\n", torre_node->reg.id);
                        excluirElemento2(torre, torre_node->reg.id);
                      }
                      torre_node = torre_node->prox;
                    }
                    free(regCirculoTemp);
                  }
                  /* -----  PARA hs ou sh ----- */
                  else if((strcmp(token, "hs") == 0) || (strcmp(token, "sh") == 0)) {
                    fscanf(qry, " %[^\n]s ", content);
                    REGISTRO *regCirculoTemp = (REGISTRO*) malloc(sizeof(REGISTRO));
                    token = strtok(content, " ");
                    regCirculoTemp->r = atof(token);
                    token = strtok(NULL, " ");
                    regCirculoTemp->x = atof(token);
                    token = strtok(NULL, " ");
                    regCirculoTemp->y = atof(token);
                    NODE hidrante_node = hidrante->cabeca;
                    while(hidrante_node != NULL) {
                      x = hidrante_node->reg.x;
                      y = hidrante_node->reg.y;
                      raio = 8;
                      if((calc_interno_2(regCirculoTemp, x+raio, y) == 1) && (calc_interno_2(regCirculoTemp, x-raio, y) == 1) && (calc_interno_2(regCirculoTemp, x, y+raio) == 1) && (calc_interno_2(regCirculoTemp,x, y-raio)) == 1){
                        fprintf(o_TXT, "HIDRANTE REMOVIDO - ID: %s\n", hidrante_node->reg.id);
                        excluirElemento2(hidrante, hidrante_node->reg.id);
                      }
                      hidrante_node = hidrante_node->prox;
                    }
                    NODE semaforo_node = semaforo->cabeca;
                    while(semaforo_node != NULL) {
                      x = semaforo_node->reg.x;
                      y = semaforo_node->reg.y;
                      raio = 8;
                      if((calc_interno_2(regCirculoTemp, x+raio, y) == 1) && (calc_interno_2(regCirculoTemp, x-raio, y) == 1) && (calc_interno_2(regCirculoTemp, x, y+raio) == 1) && (calc_interno_2(regCirculoTemp,x, y-raio)) == 1){
                        fprintf(o_TXT, "TORRE REMOVIDO - ID: %s\n", semaforo_node->reg.id);
                        excluirElemento2(semaforo, semaforo_node->reg.id);
                      }
                      semaforo_node = semaforo_node->prox;
                    }
                    free(regCirculoTemp);
                  }
                  /* -----  PARA sr ou rs ----- */
                  else if((strcmp(token, "sr") == 0) || (strcmp(token, "rs") == 0)) {
                    fscanf(qry, " %[^\n]s ", content);
                    fscanf(qry, " %[^\n]s ", content);
                    REGISTRO *regCirculoTemp = (REGISTRO*) malloc(sizeof(REGISTRO));
                    token = strtok(content, " ");
                    regCirculoTemp->r = atof(token);
                    token = strtok(NULL, " ");
                    regCirculoTemp->x = atof(token);
                    token = strtok(NULL, " ");
                    regCirculoTemp->y = atof(token);
                    NODE torre_node = torre->cabeca;
                    while(torre_node != NULL) {
                      x = torre_node->reg.x;
                      y = torre_node->reg.y;
                      raio = 8;
                      if((calc_interno_2(regCirculoTemp, x+raio, y) == 1) && (calc_interno_2(regCirculoTemp, x-raio, y) == 1) && (calc_interno_2(regCirculoTemp, x, y+raio) == 1) && (calc_interno_2(regCirculoTemp,x, y-raio)) == 1){
                        fprintf(o_TXT, "TORRE REMOVIDO - ID: %s\n", torre_node->reg.id);
                        excluirElemento2(torre, torre_node->reg.id);
                      }
                      torre_node = torre_node->prox;
                    }
                    NODE semaforo_node = semaforo->cabeca;
                    while(semaforo_node != NULL) {
                      x = semaforo_node->reg.x;
                      y = semaforo_node->reg.y;
                      raio = 8;
                      if((calc_interno_2(regCirculoTemp, x+raio, y) == 1) && (calc_interno_2(regCirculoTemp, x-raio, y) == 1) && (calc_interno_2(regCirculoTemp, x, y+raio) == 1) && (calc_interno_2(regCirculoTemp,x, y-raio)) == 1){
                        fprintf(o_TXT, "TORRE REMOVIDO - ID: %s\n", semaforo_node->reg.id);
                        excluirElemento2(semaforo, semaforo_node->reg.id);
                      }
                      semaforo_node = semaforo_node->prox;
                    }
                    free(regCirculoTemp);
                  }
                  /* -----  PARA  todas as 6 possibilidades com 3 letras ----- */
                  else if((strcmp(token, "srh") == 0) || (strcmp(token, "shr") == 0) || (strcmp(token, "rsh") == 0) || (strcmp(token, "rhs") == 0) || (strcmp(token, "hsr") == 0) || (strcmp(token, "hrs") == 0)) {
                    fscanf(qry, " %[^\n]s ", content);
                    REGISTRO *regCirculoTemp = (REGISTRO*) malloc(sizeof(REGISTRO));
                    token = strtok(content, " ");
                    regCirculoTemp->r = atof(token);
                    token = strtok(NULL, " ");
                    regCirculoTemp->x = atof(token);
                    token = strtok(NULL, " ");
                    regCirculoTemp->y = atof(token);
                    NODE torre_node = torre->cabeca;
                    while(torre_node != NULL) {
                      x = torre_node->reg.x;
                      y = torre_node->reg.y;
                      raio = 8;
                      if((calc_interno_2(regCirculoTemp, x+raio, y) == 1) && (calc_interno_2(regCirculoTemp, x-raio, y) == 1) && (calc_interno_2(regCirculoTemp, x, y+raio) == 1) && (calc_interno_2(regCirculoTemp,x, y-raio)) == 1){
                        fprintf(o_TXT, "TORRE REMOVIDO - ID: %s\n", torre_node->reg.id);
                        excluirElemento2(torre, torre_node->reg.id);
                      }
                      torre_node = torre_node->prox;
                    }
                    NODE semaforo_node = semaforo->cabeca;
                    while(semaforo_node != NULL) {
                      x = semaforo_node->reg.x;
                      y = semaforo_node->reg.y;
                      raio = 8;
                      if((calc_interno_2(regCirculoTemp, x+raio, y) == 1) && (calc_interno_2(regCirculoTemp, x-raio, y) == 1) && (calc_interno_2(regCirculoTemp, x, y+raio) == 1) && (calc_interno_2(regCirculoTemp,x, y-raio)) == 1){
                        fprintf(o_TXT, "TORRE REMOVIDO - ID: %s\n", semaforo_node->reg.id);
                        excluirElemento2(semaforo, semaforo_node->reg.id);
                      }
                      semaforo_node = semaforo_node->prox;
                    }
                    NODE hidrante_node = hidrante->cabeca;
                    while(hidrante_node != NULL) {
                      x = hidrante_node->reg.x;
                      y = hidrante_node->reg.y;
                      raio = 8;
                      if((calc_interno_2(regCirculoTemp, x+raio, y) == 1) && (calc_interno_2(regCirculoTemp, x-raio, y) == 1) && (calc_interno_2(regCirculoTemp, x, y+raio) == 1) && (calc_interno_2(regCirculoTemp,x, y-raio)) == 1){
                        fprintf(o_TXT, "HIDRANTE REMOVIDO - ID: %s\n", hidrante_node->reg.id);
                        excluirElemento2(hidrante, hidrante_node->reg.id);
                      }
                      hidrante_node = hidrante_node->prox;
                    }
                    free(regCirculoTemp);
                  }
                }
              }
              fclose(qry);
              NODE quadra_node = quadra->cabeca;
              while(quadra_node != NULL) {
                fprintf(o_qrySVG, "\t<rect fill='%s' stroke='%s' stroke-width='%dpx' width='%f' height='%f' y='%f' x='%f' />\n", quadra_node->reg.cor, quadra_node->reg.borda, 1, quadra_node->reg.largura, quadra_node->reg.altura, quadra_node->reg.y, quadra_node->reg.x);
                quadra_node = quadra_node->prox;
              }
              NODE hidrante_node = hidrante->cabeca;
              while(hidrante_node != NULL) {
                fprintf(o_qrySVG, "\t<circle fill='%s' stroke='%s' r='%f' cx='%f' cy='%f' />\n", hidrante_node->reg.cor, hidrante_node->reg.borda, 8.0, hidrante_node->reg.x, hidrante_node->reg.y);
                hidrante_node = hidrante_node->prox;
              }
              NODE torre_node = torre->cabeca;
              while(torre_node != NULL) {
                fprintf(o_qrySVG, "\t<circle fill='%s' stroke='%s' r='%f' cx='%f' cy='%f' />\n", torre_node->reg.cor, torre_node->reg.borda, 8.0, torre_node->reg.x, torre_node->reg.y);
                torre_node = torre_node->prox;
              }
              NODE semaforo_node = semaforo->cabeca;
              while(semaforo_node != NULL) {
                fprintf(o_qrySVG, "\t<rect fill='%s' stroke='%s' stroke-width='%dpx' width='%f' height='%f' y='%f' x='%f' />\n", semaforo_node->reg.cor, semaforo_node->reg.borda, 1, 15.0, 35.0, semaforo_node->reg.y, semaforo_node->reg.x);
                semaforo_node = semaforo_node->prox;
              }
              end_SVG(o_qrySVG);
              fclose(o_qrySVG);
            }

            end_SVG(o_SVG); /* Fecha a TAG do SVG */
            fclose(o_SVG);
            fclose(o_TXT);
            /* -- LIBERAÇÃO DO RESTANTE DAS MEMÓRIAS USADAS -- */
            free(base_qry);
            free(base_name);
            free(dir);
            free(path);
            free(content);
            free(regCirculo);
            free(regRetangulo);
            free(reg_quadra->cor);
            free(reg_hidrante->cor);
            free(reg_semaforo->cor);
            free(reg_torre->cor);
            free(reg_quadra->borda);
            free(reg_hidrante->borda);
            free(reg_semaforo->borda);
            free(reg_torre->borda);
            free(reg_quadra);
            free(reg_hidrante);
            free(reg_semaforo);
            free(reg_torre);
            reinicializarListaEquip(quadra);
            free(quadra);
            reinicializarListaEquip(hidrante);
            free(hidrante);
            reinicializarListaEquip(semaforo);
            free(semaforo);
            reinicializarListaEquip(torre);
            free(torre);
            reinicializarLista(lista);
            free(lista);
            /* ------------------------------------------------- */
        }/* Altera o número máximo de círculos e retângulos; */
      }
      /* ---- FINALIZAÇÃO DO CÓDIGO ----- *//**/
      fclose(file);
      printf("Programa executado com sucesso!\n");
      /* -------------------------------- */
  return 0;
}
