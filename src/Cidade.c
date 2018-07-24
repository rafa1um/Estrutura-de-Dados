#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Cidade.h"

typedef struct _cidade{
	Lista quadra;
	Lista semaforo;
	Lista torre;
	Lista hidrante;
} cidade;

Cidade createCidade() {
	cidade *city;

	city = (cidade *) malloc(sizeof(cidade));

	city->quadra = createLista();
	city->semaforo = createLista();
	city->torre = createLista();
	city->hidrante = createLista();

	return (Cidade) city;
}

int insereQuadra(Cidade c, Quadra q) {
	cidade *city;
	Item square;

	city = (cidade *) c;
	square = (Item) q;

	insert(city->quadra, q);

	return 1;
}

int insereSemaforo(Cidade c, Semaforo s) {
	cidade *city;
	Posic p;
	Item sema;

	city = (cidade *) c;
	sema = (Item) s;

	p = insert(city->semaforo, sema);

	return 1;
}

int insereTorre(Cidade c, Torre t) {
	cidade *city;
	Posic p;
	Item cel;

	city = (cidade *) c;
	cel = (Item) t;

	p = insert(city->torre, cel);

	return 1;
}

int insereHidrante(Cidade c, Hidrante h) {
	cidade *city;
	Posic p;
	Item hidra;

	city = (cidade *) c;
	hidra = (Item) h;

	p = insert(city->hidrante, hidra);

	return 1;
}

Quadra getQuadra(Cidade c, char *cep) {
	cidade *city;
	Quadra square;
	Posic p;

	city = (cidade *) c;
	p = getFirst(city->quadra);

	while (strcmp(cep, getQuadraCep(get(city->quadra, p))) != 0) {
		p = getNext(city->quadra, p);
	}

	square = get(city->quadra, p);

	return square;
}

Semaforo getSemaforo(Cidade c, char *id) {
	cidade *city;
	Semaforo sema;
	Posic p;

	city = (cidade *) c;
	p = getFirst(city->semaforo);

	while (strcmp(id, getSemaforoId(get(city->semaforo, p))) != 0) {
		p = getNext(city->semaforo, p);
	}

	sema = get(city->semaforo, p);

	return sema;
}

Torre getTorre(Cidade c, char *id) {
	cidade *city;
	Torre cel;
	Posic p;

	city = (cidade *) c;
	p = getFirst(city->torre);

	while (strcmp(id, getTorreId(get(city->torre, p))) != 0) {
		p = getNext(city->torre, p);
	}

	cel = get(city->torre, p);

	return cel;
}

Hidrante getHidrante(Cidade c, char *id) {
	cidade *city;
	Hidrante hidra;
	Posic p;

	city = (cidade *) c;
	p = getFirst(city->hidrante);

	while (strcmp(id, getHidranteId(get(city->hidrante, p))) != 0) {
		p = getNext(city->hidrante, p);
	}

	hidra = get(city->hidrante, p);

	return hidra;
}

void escreverCidade(FILE *saida, Cidade c) {
	cidade *city;
	Posic p;

	city = (cidade *) c;

	p = getFirst(city->quadra);

	while(p != NULL) {
		escreverQuadra(saida, get(city->quadra, p));

		p = getNext(city->quadra, p);
	}

	p = getFirst(city->hidrante);

	while(p != NULL) {
		escreverHidrante(saida, get(city->hidrante, p));

		p = getNext(city->hidrante, p);
	}

	p = getFirst(city->semaforo);

	while(p != NULL) {
		escreverSemaforo(saida, get(city->semaforo, p));

		p = getNext(city->semaforo, p);
	}

	p = getFirst(city->torre);

	while(p != NULL) {
		escreverTorre(saida, get(city->torre, p));

		p = getNext(city->torre, p);
	}
}

Lista getListaQuadra(Cidade c) {
	cidade *city;

	city = (cidade *) c;

	return (Lista) city->quadra;
}

Lista getListaHidrante(Cidade c) {
	cidade *city;

	city = (cidade *) c;

	return (Lista) city->hidrante;
}

Lista getListaSemaforo(Cidade c) {
	cidade *city;

	city = (cidade *) c;

	return (Lista) city->semaforo;
}

Lista getListaTorre(Cidade c) {
	cidade *city;

	city = (cidade *) c;

	return (Lista) city->torre;
}

void removeQuadra(Cidade c, char *cep) {
	cidade *city;
	Posic p;

	city = (cidade *) c;
	p = getFirst(city->quadra);

	while (p != NULL) {
		if (strcmp(cep, getQuadraCep(get(city->quadra, p))) == 0 ) {
			freeQuadra(get(city->quadra, p));
			break;
		}

		p = getNext(city->quadra, p);
	}

	remover(city->quadra, p);
}

void removeHidrante(Cidade c, char *id) {
	cidade *city;
	Posic p;

	city = (cidade *) c;
	p = getFirst(city->hidrante);

	while (p != NULL) {
		if (strcmp(id, getHidranteId(get(city->hidrante, p))) == 0 ) {
			freeHidrante(get(city->hidrante, p));
			break;
		}

		p = getNext(city->hidrante, p);
	}

	remover(city->hidrante, p);
}

void removeSemaforo(Cidade c, char *id) {
	cidade *city;
	Posic p;

	city = (cidade *) c;
	p = getFirst(city->semaforo);

	while (p != NULL) {
		if (strcmp(id, getSemaforoId(get(city->semaforo, p))) == 0 ) {
			freeSemaforo(get(city->semaforo, p));
			break;
		}

		p = getNext(city->semaforo, p);
	}

	remover(city->semaforo, p);
}

void removeTorre(Cidade c, char *id) {
	cidade *city;
	Posic p;

	city = (cidade *) c;
	p = getFirst(city->torre);

	while (p != NULL) {
		if (strcmp(id, getTorreId(get(city->torre, p))) == 0 ) {
			freeTorre(get(city->torre, p));
			break;
		}

		p = getNext(city->torre, p);
	}

	remover(city->torre, p);
}

void apocalypse(Cidade c) {
	char *aux;
	cidade *city;
	Posic p;

	city = (cidade *) c;

	p = getFirst(city->quadra);

	while(p != NULL) {
		aux = getQuadraCep(get(city->quadra, p));
		p = getNext(city->quadra, p);
		removeQuadra(city, aux);
	}

	p = getFirst(city->hidrante);

	while(p != NULL) {
		aux = getHidranteId(get(city->hidrante, p));
		p = getNext(city->hidrante, p);
		removeHidrante(city, aux);
	}

	p = getFirst(city->semaforo);

	while(p != NULL) {
		aux = getSemaforoId(get(city->semaforo, p));
		p = getNext(city->semaforo, p);
		removeSemaforo(city, aux);
	}

	p = getFirst(city->torre);

	while(p != NULL) {
		aux = getTorreId(get(city->torre, p));
		p = getNext(city->torre, p);
		removeTorre(city, aux);
	}

	free(city->quadra);
	free(city->hidrante);
	free(city->semaforo);
	free(city->torre);

	free(city);
}
