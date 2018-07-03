#include "svg.h"
#include "calc.h"
/* INICIALIZA O ARQUIVO SVG */
void new_SVG(FILE* output) {
  fprintf(output, "<svg xmlns='http://www.w3.org/2000/svg' version='1.1' xmlns:xlink='http://www.w3.org/1999/xlink'>\n");
}

/* DESENHA UM RETANGULO NO ARQUIVO SVG */
void rect(FILE* output, REGISTRO *regRetangulo) {
  fprintf(output, "\t<rect fill='%s' stroke='%s' stroke-width='%dpx' width='%f' height='%f' y='%f' x='%f' />\n", regRetangulo->cor, regRetangulo->borda, 1, regRetangulo->largura, regRetangulo->altura, regRetangulo->y, regRetangulo->x);
}

/* DESENHA UM CIRCULO NO ARQUIVO SVG */
void circ(FILE* output, REGISTRO *regCirculo) {
  fprintf(output, "\t<circle fill='%s' stroke='%s' r='%f' cx='%f' cy='%f' />\n", regCirculo->cor, regCirculo->borda, regCirculo->r, regCirculo->x, regCirculo->y);
}

void quadra_SVG(FILE* output, REGISTRO *reg_quadra) {
  fprintf(output, "\t<rect fill='%s' stroke='%s' stroke-width='%dpx' width='%f' height='%f' y='%f' x='%f' />\n", reg_quadra->cor, reg_quadra->borda, 1, reg_quadra->largura, reg_quadra->altura, reg_quadra->y, reg_quadra->x);
  fprintf(output, "\t<text x='%f' y='%f' font-family='Arial' font-size='10' fill='%s'>%s</text>\n", (reg_quadra->x)+45, (reg_quadra->y)+40, "black", reg_quadra->id);
}

/* DESENHA UM HIDRANTE NO ARQUIVO SVG */
void hidrante_SVG(FILE* output, REGISTRO *reg_hidrante) {
  fprintf(output, "\t<circle fill='%s' stroke='%s' r='8px' cx='%f' cy='%f' />\n", reg_hidrante->cor, reg_hidrante->borda, reg_hidrante->x, reg_hidrante->y);
  fprintf(output, "\t<text x='%f' y='%f' font-family='Arial' font-size='10' fill='%s'>%c</text>\n", (reg_hidrante->x)-3.5, (reg_hidrante->y)+3, "white", 'H');
}

/* DESENHA UM SEMAFORO NO ARQUIVO SVG */
void semaforo_SVG(FILE* output, REGISTRO *reg_semaforo) {
  fprintf(output, "\t<rect fill='%s' stroke='%s' stroke-width='20' width='15px' height='35px' y='%f' x='%f' />\n", reg_semaforo->cor, reg_semaforo->borda, reg_semaforo->y, reg_semaforo->x);
  fprintf(output, "\t<text x='%f' y='%f' font-family='Arial' font-size='10' fill='%s'>%c</text>\n", (reg_semaforo->x)+4, (reg_semaforo->y)+20, "black", 'S');
}

void torre_SVG(FILE* output, REGISTRO *reg_torre) {
  fprintf(output, "\t<circle fill='%s' stroke='%s' r='8px' cx='%f' cy='%f' />\n", reg_torre->cor, reg_torre->borda, reg_torre->x, reg_torre->y);
  fprintf(output, "\t<text x='%f' y='%f' font-family='Arial' font-size='10' fill='%s'>%c</text>\n", (reg_torre->x)-3.5, (reg_torre->y)+3, "white", 'T');
}

void line(FILE* o_suSVG, NODE search01, NODE search02, double x, double y) {
    while(search02 != NULL) {
      if(search02->reg.r > 0){
        fprintf(o_suSVG, "\t<text x='%f' y='%f' font-family='Arial' font-size='20' fill='%s'>%.2f</text>\n", (search01->reg.x + search02->reg.x)/2, (search01->reg.y + search02->reg.y)/2, search01->reg.borda, calc_distance(search01, search02));
        fprintf(o_suSVG, "\t<line stroke='%s' stroke-width='%dpx' x1='%f' y1='%f' x2='%f' y2='%f'/>\n", search01->reg.borda, 1, x, y, search02->reg.x, search02->reg.y);
      }
      else {
        fprintf(o_suSVG, "\t<text x='%f' y='%f' font-family='Arial' font-size='20' fill='%s'>%.2f</text>\n", (search01->reg.x + search02->reg.x)/2, (search01->reg.y + search02->reg.y)/2, search01->reg.borda, calc_distance(search01, search02));
        fprintf(o_suSVG, "\t<line stroke='%s' stroke-width='%dpx' x1='%f' y1='%f' x2='%f' y2='%f'/>\n", search01->reg.borda, 1, x, y, search02->reg.x + search02->reg.largura/2, search02->reg.y + search02->reg.altura/2);
      }
      search02 = search02->prox;
    }
}

/* FECHA O ARQUIVO SVG */
void end_SVG(FILE* output) {
  fprintf(output, "</svg>");
}
