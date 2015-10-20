#include <stdio.h>
#include <stdlib.h>

/* Very simple program to demonstrate reading up to 10 numbers from the command line.
 * Usage:
 *         ./num2 some_number
 * Example:
 *         ./num2 2014
 *
 */

int main (int argc, const char* argv[]) {

  /* The symbolic constant MAX_NUMS sets the maximum number of numbers 
     to enter as arguments on the command line. */
#define MAX_NUMS (10)
  int nums[MAX_NUMS]; // space to store up to MAX_NUMS numbers.

  int next_num; // Integer read from the command line goes here.
  int i; // array index 
  int num_nums; // How many numbers actually entered on the command line.

  if (argc < 2) { // Check that there was at least one number.
    printf("Must enter 1 to %d numbers on the command line!\n", MAX_NUMS);
    return 1; // Indicate failure
  }

  /* Example of how the first number could be read. */
  next_num = atoi(argv[1]); // Get string from command line and convert to int
  printf("The number you entered was: %d\n", next_num);
  nums[0] = next_num; // store into the array
  
  return 0; // Indicate success!
}

