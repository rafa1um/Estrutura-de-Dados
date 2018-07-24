#include "semaforo.h"

/* DESENHA UM SEMAFORO NO ARQUIVO SVG */
void semaforo_SVG(FILE* output, REGISTRO *reg_semaforo) {
  fprintf(output, "\t<rect fill='%s' stroke='%s' stroke-width='20' width='15px' height='35px' y='%f' x='%f' />\n", reg_semaforo->cor, reg_semaforo->borda, reg_semaforo->y, reg_semaforo->x);
  fprintf(output, "\t<text x='%f' y='%f' font-family='Arial' font-size='10' fill='%s'>%c</text>\n", (reg_semaforo->x)+4, (reg_semaforo->y)+20, "black", 'S');
}
