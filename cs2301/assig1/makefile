all: lab1 num leap

lab1: lab1.o
	gcc lab1.o -o lab1

lab1.o: lab1.c
	gcc -c lab1.c

num: num.o
	gcc num.o -o num

num.o: num.c
	gcc -c num.c

leap: leap.o
	gcc leap.o -o leap

leap.o: leap.c
	gcc -c leap.c

clean:
	rm -f lab1.o lab1 num.o num leap.o leap
