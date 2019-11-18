all: dir.o
	gcc -o program dir.o
dir.o: dir.c
	gcc -c dir.c
run:
	./program
clean:
	rm *.o
	rm *~
