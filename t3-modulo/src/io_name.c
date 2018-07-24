#include "io_name.h"


/* ---------- RETIRA EXTENSÃO ---------- */
void t_ext(char *base_name) {
  int i;
  for (i = strlen(base_name) - 1; i >= 0; i--) {
    if (base_name[i] == '.') {
      base_name[i] = 0;
      return;
    }
  }
}
/* ------------------------------------- */
