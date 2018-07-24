#include "quadra.h"

void quadra_SVG(FILE* output, REGISTRO *reg_quadra) {
  fprintf(output, "\t<rect fill='%s' stroke='%s' stroke-width='%dpx' width='%f' height='%f' y='%f' x='%f' />\n", reg_quadra->cor, reg_quadra->borda, 1, reg_quadra->largura, reg_quadra->altura, reg_quadra->y, reg_quadra->x);
  fprintf(output, "\t<text x='%f' y='%f' font-family='Arial' font-size='10' fill='%s'>%s</text>\n", (reg_quadra->x)+45, (reg_quadra->y)+40, "black", reg_quadra->id);
}
