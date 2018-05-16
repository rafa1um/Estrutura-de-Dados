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
		x1 = pow((search01->reg.x + search01->reg.largura/2) - (search02->reg.x + search02->reg.largura/2), 2);
		y1 = pow((search01->reg.y + search01->reg.altura/2) - (search02->reg.y + search02->reg.altura/2), 2);
	}
	/* Caso seja 1 Círculo e 1 Retângulo */
	else if(search01->reg.r > 0 && search02->reg.r == -1.0) {
		x1 = pow(search01->reg.x - (search02->reg.x + (search02->reg.largura/2)), 2);
		y1 = pow(search01->reg.y - (search02->reg.y + (search02->reg.altura/2)), 2);
	}
	/* Caso seja 1 Retângulo e 1 Círculo */
	else {
		x1 = pow((search01->reg.x + search01->reg.largura/2) - search02->reg.x, 2);
		y1 = pow((search01->reg.y + search01->reg.altura/2) - search02->reg.y, 2);
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

int calc_sobrepos(FILE* o_SVG, NODE search01, NODE search02) {
  double x1, x2, y1, y2, altura1, altura2, largura1, largura2, r1, r2, px, py;
  int sobrepos = 0;
  /* Para os dois raios > 0, ou seja, dois círculos; */
  if(search01->reg.r > 0 && search02->reg.r > 0) {

		x1 = search01->reg.x;
		y1 = search01->reg.y;
		r1 = search01->reg.r;

    x2 = search02->reg.x;
		y2 = search02->reg.y;
		r2 = search02->reg.r;

		if(calc_distance(search01, search02) < r1 + r2) sobrepos = 1;

		if(x1 - r1 < x2 - r2) px = x1 - r1;
		else px = x2 - r2;

		if(y1 - r1 < y2 - r2) py = y1 - r1;
		else py = y2 - r2;

		if(x1 + r1 > x2 + r2) largura1 = x1 + r1 - px;
		else largura1 = x2 + r2 - px;

		if(y1 + r1 > y2 + r2) altura1 = y1 + r1 - py;
		else altura1 = y2 + r2 - py;


	}
  /* Para um raio > 0 e um raio == -1, ou seja, um Círculo e um Retângulo; */
  else if(search01->reg.r > 0 && search02->reg.r == -1.0) {

    x1 = search01->reg.x;
		y1 = search01->reg.y;
		r1 = search01->reg.r;

    x2 = search02->reg.x;
		y2 = search02->reg.y;
		largura2 = search02->reg.largura;
		altura2 = search02->reg.altura;

		if(calc_interno(search02, x1, y1) > 0) sobrepos = 1;
		if((calc_interno(search01, x2, y2) > 0) || (calc_interno(search01, x2 + largura2, y2) > 0) || (calc_interno(search01, x2, y2 + altura2) > 0) || (calc_interno(search01, x2 + largura2, y2 + altura2) > 0)) sobrepos = 1;
		if((calc_interno(search02, x1 + r1, y1) > 0) || (calc_interno(search02, x1, y1 - r1) > 0) || (calc_interno(search02, x1 - r1, y1) > 0) || (calc_interno(search02, x1, y1 + r1) > 0)) sobrepos = 1;

		if(x1 - r1 < x2) px = x1 - r1;
		else px = x2;

		if(y1 - r1 < y2) py = y1 - r1;
		else py = y2;

		if(x1 + r1 > x2 + largura2)
			largura1 = x1 + r1 - px;
		else largura1 = x2 + largura2 - px;

		if(y1 + r1 > y2 + altura2) altura1 = y1 + r1 - py;
		else altura1 = y2 + altura2 - py;


	}

  /* Para dois raios == -1, ou seja, dois Retângulos; */
  else if(search01->reg.r == -1.0 && search02->reg.r == -1.0) {

    if(search01->reg.x < (search02->reg.x + search02->reg.largura) && (search01->reg.x + search01->reg.largura) > search02->reg.x && search01->reg.y < (search02->reg.y + search02->reg.altura) && (search01->reg.y + search01->reg.altura) > search02->reg.y) sobrepos = 1;


    if(search01->reg.x <= search02->reg.x) px = search01->reg.x - 1;
    else px = search02->reg.x - 1;

    if ((search02->reg.x + search02->reg.largura) > (search01->reg.x + search01->reg.largura)) largura1 = search02->reg.x - px + search02->reg.largura + 1;
    else largura1 = search01->reg.x - px + search01->reg.largura + 1;

    if(search01->reg.y <= search02->reg.y) py = search01->reg.y - 1;
    else py = search02->reg.y - 1;

    if((search02->reg.y + search02->reg.altura) > (search01->reg.y + search01->reg.altura)) altura1 = search02->reg.y - py + search02->reg.altura + 1;
    else altura1 = search01->reg.y - py + search01->reg.altura + 1;

  }
  /* Para um raio == -1 e um raio > 0, ou seja, um Retângulo e um Círculo; */
  else if(search01->reg.r == -1.0 && search02->reg.r > 0) {

    x1 = search01->reg.x;
		y1 = search01->reg.y;
		largura2 = search01->reg.largura;
		altura2 = search01->reg.altura;
    x2 = search02->reg.x;
		y2 = search02->reg.y;
		r2 = search02->reg.r;

		if((calc_interno(search01, x2, y2) > 0))	sobrepos = 1;
		if((calc_interno(search02, x1, y1) > 0) || (calc_interno(search02, x1 + largura2, y1) > 0) || (calc_interno(search02, x1, y1 + altura2) > 0) || (calc_interno(search02, x1 + largura2, y1 + altura2) > 0))	sobrepos = 1;
		if((calc_interno(search01, x2 + r2, y2) > 0) || (calc_interno(search01, x2, y2 - r2) > 0) || (calc_interno(search01, x2-r2, y2) > 0) || (calc_interno(search01, x2, y2 + r2) > 0)) sobrepos = 1;

		if(x1 < x2 - r2) px = x1;
		else px = x2 - r2;

		if(y1 < y2 - r2) py = y1;
		else py = y2 - r2;

		if(x1 + largura2 > x2 + r2) largura1 = x1 + largura2 - px;
		else largura1 = x2 + r2 - px;

		if(y1 + altura2 > y2 + r2)	altura1 = y1 + altura2 - py;
		else altura1 = y2 + r2 - py;
	}

  if(sobrepos == 1) {
    fprintf(o_SVG, "\t<rect x='%f' y='%f' width='%f' height='%f' fill='none'\n", px, py, largura1, altura1);
    fprintf(o_SVG, "\t\tstyle=\"stroke:%s; stroke-width:3; stroke-dasharray:5,5\" />\n", "black");
    fprintf(o_SVG, "\t<text x='%f' y='%f' font-family='Arial' font-size='20' fill='%s'>sobrepõe</text>\n", px, py-8, "black");
  }
  return sobrepos;
}
