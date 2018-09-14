siguel: siguel.o svg.o linkedlist.o io_name.o calc.o hidrante.o quadra.o semaforo.o torre.o
	gcc -o siguel siguel.o svg.o linkedlist.o io_name.o calc.o hidrante.o quadra.o semaforo.o torre.o -lm
siguel.o: siguel.c
	gcc -c siguel.c -o siguel.o -g -pedantic -ansi -std=c99 -fstack-protector-all -lm
svg.o: svg.c
	gcc -c svg.c -o svg.o -g -pedantic -ansi -std=c99 -fstack-protector-all -lm
linkedlist.o: linkedlist.c
	gcc -c linkedlist.c -o linkedlist.o -g -pedantic -ansi -std=c99 -fstack-protector-all -lm
io_name.o: io_name.c
	gcc -c io_name.c -o io_name.o -g -pedantic -ansi -std=c99 -fstack-protector-all -lm
calc.o: calc.c
	gcc -c calc.c -o calc.o -g -pedantic -ansi -std=c99 -fstack-protector-all -lm
hidrante.o: hidrante.c
	gcc -c hidrante.c -o hidrante.o -g -pedantic -ansi -std=c99 -fstack-protector-all -lm
quadra.o: quadra.c
	gcc -c quadra.c -o quadra.o -g -pedantic -ansi -std=c99 -fstack-protector-all -lm
semaforo.o: semaforo.c
	gcc -c semaforo.c -o semaforo.o -g -pedantic -ansi -std=c99 -fstack-protector-all -lm
torre.o: torre.c
	gcc -c torre.c -o torre.o -g -pedantic -ansi -std=c99 -fstack-protector-all -lm
clean:
	rm -rf *.o vgcore*
