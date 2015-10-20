all: etest part3 part5 part6 part7

employee.o: employee.c employee.h
	gcc -g -c employee.c -lreadline -lncurses

etest: etest.o employee.o
	gcc -g etest.o employee.o -lreadline -lncurses -o etest

etest.o: etest.c etest.h
	gcc -g -c etest.c

part3: part3.o employee.o
	gcc -g part3.o employee.o -lreadline -lncurses -o part3

part3.o: part3.c part3.h employee.h
	gcc -g -c part3.c

part5: part5.o employee.o
	gcc -g part5.o employee.o -lreadline -lncurses -o part5

part5.o: part5.c part5.h employee.h
	gcc -g -c part5.c

part6: part6.o employee.o
	gcc -g part6.o employee.o -lreadline -lncurses -o part6

part6.o: part6.c part6.h employee.h
	gcc -g -c part6.c

part7: part7.o employee.o
	gcc -g part7.o employee.o -lreadline -lncurses -o part7

part7.o: part7.c part7.h employee.h
	gcc -g -c part7.c

clean:
	rm -f *.o etest part3 part6 part7

docs:
	doxygen
	chmod a+r html/*
	cp -p -r html/* ~/public_html/cs2301/assig5
