#include <stdio.h>
#include <stdlib.h>

/* Very simple program to demonstrate reading a number from the
command line.
 * Usage: 
 * 	./num some_number
 * Example:
 * 	./num 2014
 * 
 */

int main (int argc, const char* argv[]) {
  int n; // integer read from the command line goes here.

  if (argc < 2) { // check that there was an entry
    printf("You must enter a number on the command line! \n");
    return 1; // indicate failure
  }

  n = atoi(argv[1]); // Get the string from the command line, convert to int
  printf("The number you entered was: %d\n", n);
  return 0; // Indicate success!
}
