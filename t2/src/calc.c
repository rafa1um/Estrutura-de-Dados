#include "calc.h"

int calc_interno(NODE search, double x, double y) {
  double x1, y1, largura1, altura1;
  if(search->reg.r == -1.0) {
    x1 = search->reg.x;
		y1 = search->reg.y;
		largura1 = search->reg.largura;
		altura1 = search->reg.altura;

		if (x > x1 && x < (x1+largura1) && y > y1 && y < (y1+altura1)) return 1;
		if(x >= x1 && x <= (x1+largura1) && y >= y1 && y <= (y1+altura1)) return 2;
    return -1;
  }
  else {
    x1 = search->reg.x;
    y1 = search->reg.y;

    if((pow(x1-x, 2) + pow(y1-y, 2)) < pow(search->reg.r, 2)) return 1;
    if((pow(x1-x, 2) + pow(y1-y, 2)) == pow(search->reg.r, 2)) return 2;
    return -1;
  }
}

double calc_distance(NODE search01, NODE search02) {
  double x1, y1;

	/* Caso seja 2 Círculos */
	if(search01->reg.r > 0 && search02->reg.r > 0) {
		x1 = pow(search01->reg.x - search02->reg.x, 2);
		y1 = pow(search01->reg.y - search02->reg.y, 2);
	}
	/* Caso seja 2 Retângulos */
	else if (search01->reg.r == -1.0 && search02->reg.r == -1.0) {
		x1 = pow(((search01->reg.x + search01->reg.largura)/2) - ((search02->reg.x + search02->reg.largura)/2), 2);
		y1 = pow(((search01->reg.y + search01->reg.altura)/2) - ((search02->reg.y + search02->reg.altura)/2), 2);
	}
	/* Caso seja 1 Círculo e 1 Retângulo */
	else if(search01->reg.r > 0 && search02->reg.r == -1.0) {
		x1 = pow(((search01->reg.x - search02->reg.x) + (search02->reg.largura)/2), 2);
		y1 = pow(((search01->reg.y - search02->reg.y) + (search02->reg.altura)/2), 2);
	}
	/* Caso seja 1 Retângulo e 1 Círculo */
	else {
		x1 = pow(((search01->reg.x + search01->reg.largura)/2) - search02->reg.x, 2);
		y1 = pow(((search01->reg.y + search01->reg.altura)/2) - search02->reg.y, 2);
	}
  return sqrt(x1 + y1);
}

double calc_mass_rect(NODE search) {
  double xy;
  if(search->reg.r == -1.0) {
    xy = ((search->reg.x + search->reg.y)/2);
  }
  else {
    printf("Nao foi possivel encontrar o centro de massa!!");
  }
  return xy;
}

int calc_sobrepos(FILE* file, NODE search01, NODE search02) {
  double x1, x2, y1, y2, altura1, altura2, altura3, largura1, largura2, largura3, r1, r2, px, py;

}
