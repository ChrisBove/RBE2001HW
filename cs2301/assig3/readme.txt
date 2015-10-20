Name: Christopher Bove
Username: cpbove

Files:

  assig3.c   - c source code for assignment 3 program, main loop
  sort.h     - c header file for sort functions, contains prototypes
  sort.c     - c source code for sort functions
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


Test Examples/Data:

$ ./assig3 3 1 5 23
Unsorted List:
 3
 1
 5
 23
Sorted List:
 23
 5
 3
 1

$ ./assig3 -339 2 4 568 -48
Unsorted List:
 -339
 2
 4
 568
 -48
Sorted List:
 568
 4
 2
 -48
 -339
