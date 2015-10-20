Name: Christopher Bove
Username: cpbove

Files:

  stack.c   - stack source code
  stack.h   - stack header file
  stacktest.c - c executable for testing stack implementation
  queue.c   - queue source code
  queue.h   - queue header file
  queuetest.c - c executable for testing queue implementation
  tree.c   - tree source code
  tree.h   - tree header file
  treetest.c - c executable for testing tree implementation
  part5.c   - c executable for testing tree implementation in part 5
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
