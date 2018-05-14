#include "svg.h"
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

void line(FILE* o_line, NODE search, double x1y1, double x2y2, double distance) {
    fprintf(o_line, "\t<line stroke='%s' stroke-width='%dpx' x1='%f' y1='%f' x2='%f' y2='%f'/>\n", search->reg.cor, 1, x1y1, x1y1, x2y2, x2y2);
    fprintf(o_line, "\t<text x='%f' y='%f' fill='%s'>%f</text>\n", distance/2, distance/2, "black", distance/2);
}

/* FECHA O ARQUIVO SVG */
void end_SVG(FILE* output) {
  fprintf(output, "</svg>");
}
