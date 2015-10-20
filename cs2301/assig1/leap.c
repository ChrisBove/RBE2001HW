#include <stdio.h>
#include <stdlib.h>

/** Program that checks whether a passed Gregorian calendar year is a leap 
 * year or not.
 * 
 * Usage: 
 * 	./leap some_year
 * Example:
 * 	./leap 2014
 * 
 * Modified from num.c program from WPI's CS 2301 class.
 *
 * Author: 
 * 	Christopher Bove
 * Date last modified:
 * 	3/23/15
 */

int main (int argc, const char* argv[]) {
  int n; // integer read from the command line goes here
  int result = 0; // is a leap year if 1, not a leap year if 0

  if (argc < 2) { // check that there was an entry
    printf("You must enter a number year! \n"); // print error
    return 1; // indicate failure
  }

  // otherwise, we have at least one entry
  n = atoi(argv[1]); // Get the string from the command line, convert to int

  if (n < 1582) { // check that n is a valid Gregorian calendar year
    printf("We can only check years from 1582 onward! You entered %d. \n", n);
    return 1; // indicate a failure
  }  
  
  // check if n is a leap year or not
  // a leap year occurs when the year is evenly divisable by 4
  // an exception is when the year is both divisible by 100 but not by 400
  //   the years that are exceptions so far are 1700, 1800, and 1900

  // check for exception in leap year rule
  if ( (n % 100 == 0) && (n % 400 != 0)) { //divisible by 100 but not 400?
    result = 0; // not a leap year
  } else {
    // can check if it is a leap year by dividing by 4
    if (n % 4 == 0) // evenly divisible by 4
      result = 1; // is a leap year
    // otherwise, result already = 0 (not a leap year)
  }

  // based on whether n is a leap year or not, print appropriately
  if (result == 1) // is a leap year
    printf("The year %d is a leap year!\n", n); // print yes message
  else // not a leap year
    printf("The year %d is NOT a leap year!\n", n); // print no message

  return 0; // Indicate success!
}
