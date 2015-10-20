Name: Christopher Bove
Username: cpbove

Files:

  ctest.c   - c source code for assignment 4 program, main loop, runs tests
  mystring.h- c header file for custom string functions
  mystring.c- c file for custom string functions
  mystrlen.h- c header file for custom string length function
  mystrlen.c- c file for custom string length function
  makefile   - c code compiling configuration, makes .o's and executables
  Doxyfile   - doxygen template for creating html documentation of this code
  readme.txt - (this file) - readme for this directory

To compile code:
  Have standard gcc compiler. Type "make" in the terminal within this 
directory to make three executable files from code mentioned above. Doing 
"make" will create object files from each source code file and automatically
link them appropriately to create executables. See makefile for details.

To generate Doxygen files:
  run "make docs" to generate the html files in the directory specified by the
make file. Then those files are copied to cpbove's public directory. Change as
appropriate.

Test Data:
./ctest
Pointers: a1 = 0x7fff91aaa410, a2 = 0x7fff91aaa470, a3 = 0x7fff91aaa3e0
          p1 = 0x400c0c p2 = 0x400b20
Contents of a1 = Hi
Contents of a2 = Hello
Contents of a3 = Hello, also
After concatenating, contents of a1 = HiHello
After concatenating, contents of a1 = HiHelloHello
After concatenating, contents of a1 = HiHelloHelloHello, a
Before dup, pointer a2 = 0x7fff91aaa470, contents = Hello
After dup, pointer p2 = 0xdddb010, contents = Hello
Copying 6 elements in a1 to a4: HiHell
STD Copying 6 elements in a1 to a4: HiHell
Before ndup, n = 12, pointer a1 = 0x7fff91aaa410, contents = HiHelloHelloHello, a
After ndup, n = 12, pointer p2 = 0xdddb030, contents = HiHelloHello
