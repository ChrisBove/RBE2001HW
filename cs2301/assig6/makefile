# By default, make all the executables:
all: stacktest queuetest treetest part5

# Make each executable:
stacktest: stacktest.o stack.o
	gcc -g stacktest.o stack.o -o stacktest

queuetest: queuetest.o queue.o
	gcc -g queuetest.o queue.o -o queuetest

treetest: treetest.o tree.o
	gcc -g treetest.o tree.o -o treetest

part5: part5.o tree.o
	gcc -g part5.o tree.o -o part5

# Compile each source file:
stack.o: stack.c stack.h
	gcc -g -c stack.c

queue.o: queue.c queue.h
	gcc -g -c queue.c

tree.o: tree.c tree.h
	gcc -g -c tree.c

stacktest.o: stacktest.c stack.h
	gcc -g -c stacktest.c

queuetest.o: queuetest.c queue.h
	gcc -g -c queuetest.c

treetest.o: treetest.c tree.h
	gcc -g -c treetest.c

part5.o: part5.c tree.h
	gcc -g -c part5.c

# Other targets:
clean:
	rm -f *.o
	rm -f stacktest queuetest treetest part5

docs:
	doxygen
	chmod a+r html/*
	cp -p html/* ~/public_html/cs2301/assig6
