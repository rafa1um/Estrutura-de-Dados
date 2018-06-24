siguel: siguel.o svg.o linkedlist.o io_name.o calc.o
	gcc -o siguel siguel.o svg.o linkedlist.o io_name.o calc.o -lm
siguel.o: siguel.c
	gcc -c siguel.c -o siguel.o -g -pedantic -ansi
svg.o: svg.c
	gcc -c svg.c -o svg.o -g -pedantic -ansi
linkedlist.o: linkedlist.c
	gcc -c linkedlist.c -o linkedlist.o -g -pedantic -ansi
io_name.o: io_name.c
	gcc -c io_name.c -o io_name.o -g -pedantic -ansi
calc.o: calc.c
	gcc -c calc.c -o calc.o -g -pedantic -ansi
clean:
	rm -rf *.o vgcore*
