all: assig3

assig2: assig3.o
	gcc -g assig3.o -o assig3

assig2.o: assig3.c
	gcc -g -c assig3.c

clean:
	rm -f assig3.o assig3

docs:
	doxygen
	chmod a+r html/*
	cp -p html/* ~/public_html/cs2301/assig3
