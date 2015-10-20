all:  num2 assig2

num2: num2.o
	gcc -g num2.o -o num2

num2.o: num2.c
	gcc -g -c num2.c

assig2: assig2.o
	gcc -g assig2.o -o assig2

assig2.o: assig2.c
	gcc -g -c assig2.c

clean:
	rm -f  num2.o num2 assig2.o assig2
