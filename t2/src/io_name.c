#include "io_name.h"

/* -------------------- ARGUMENTOS --------------------*/

void args(int argc, char **argv, char **dir, char **base_name, char **path) {
	int k;
	for(k = 0; k < argc; k++){ /* Lida com argumentos recebidos pelo terminal; */
		if(strcmp(argv[k], "-f") == 0) {
			*base_name = (char *) malloc((strlen(argv[k+1])+1)*sizeof(char *));
			strcpy(*base_name, argv[k+1]);
		}
		if(strcmp(argv[k], "-o") == 0) {
			if(k+1 < argc) {
				*dir = (char*) malloc((strlen(argv[k+1]) + 1)*sizeof(char *));
				strcpy(*dir,argv[k+1]);
				if (*dir[strlen(*dir)-1] != '/') {
					*dir = (char *) realloc(*dir,(strlen(*dir)+2) * sizeof(char));
					*dir[strlen(*dir)] = '/';
					*dir[strlen(*dir)+1] = '\0';
				}
			}
		}
		if(strcmp(argv[k], "-e") == 0) {
			*path = (char *) malloc((strlen(argv[k+1]) + 1) * sizeof(char));
			strcpy(*path, argv[k+1]);
			if((strlen(*path)-1) != '/') {
				*path = (char *) realloc(*path,((strlen(*path))+2) * sizeof(char));
				*path[strlen(*path)] = '/';
				*path[strlen(*path)+1] = '\0';
			}
		}
	}
}
/* -------------------------------------------------- */

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
