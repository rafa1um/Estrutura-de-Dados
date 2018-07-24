#include "torre.h"


void torre_SVG(FILE* output, REGISTRO *reg_torre) {
  fprintf(output, "\t<circle fill='%s' stroke='%s' r='8px' cx='%f' cy='%f' />\n", reg_torre->cor, reg_torre->borda, reg_torre->x, reg_torre->y);
  fprintf(output, "\t<text x='%f' y='%f' font-family='Arial' font-size='10' fill='%s'>%c</text>\n", (reg_torre->x)-3.5, (reg_torre->y)+3, "white", 'T');
}
