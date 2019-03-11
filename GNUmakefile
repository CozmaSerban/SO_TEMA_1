all: build

build: tema1.o
		gcc -g -Wall tema1.o -o tema1 libcompare.so

tema1.o: tema1.c
		gcc -c tema1.c

clean:
		rm -rf *.o