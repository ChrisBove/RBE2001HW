/** @file ctest.c
 * @brief Program to demonstrate character arrays and
 * dynamically-allocated memory.
 * @author Mike Ciaraldi
 * @author Christopher Bove - modified from Ciaraldi's original work
 * @date 4-13-15
 */

#include <stdio.h>
#include <string.h>
// string.h covers the C-style string functions.
#include "mystring.h"

const int MAX_CHARS = 20; // Maximum number of characters in array

int main()
{
  char a1[MAX_CHARS + 1]; // Character array--initially empty
  char a2[] = "Hello"; // Character array--unsized but initialized
  char a3[MAX_CHARS + 1]; // Character array--we will underfill it
  char a4[MAX_CHARS + 1]; // char array - used to test strncpy
  char a5[MAX_CHARS + 1]; // char array - used to test strncpy
  char* p1 = "Hello"; // Pointer to constant string
  char* p2;           // Will be a pointer to dynamically-allocated string
  int copy_limit;     // Maximum characters to copy.

  mystrcpy(a3, "Hello, also"); // Initialize underfilled character array

  /* Print the pointers.
     Note: this example prints
     the values of the pointers themselves, not the targets.
  */
  printf("Pointers: a1 = %p, a2 = %p, a3 = %p\n", a1, a2, a3);
  printf("          p1 = %p p2 = %p\n", p1, p2);

  mystrcpy(a1, "Hi"); // Initialize character array

  printf("Contents of a1 = %s\n", a1);
  printf("Contents of a2 = %s\n", a2);
  printf("Contents of a3 = %s\n", a3);

  // Concatenate two character arrays, then print.
  mystrcat(a1, a2);
  printf("After concatenating, contents of a1 = %s\n", a1);

  // Concatenate two character arrays safely, then print.
  copy_limit = MAX_CHARS - mystrlen(a1); // How much space is left?
  if (copy_limit > 0) mystrncat(a1, a2, copy_limit);
  printf("After concatenating, contents of a1 = %s\n", a1);

  // Concatenate two character arrays safely, then print.
  copy_limit = MAX_CHARS - mystrlen(a1); // How much space is left?
  if (copy_limit > 0) mystrncat(a1, a3, copy_limit);
  printf("After concatenating, contents of a1 = %s\n", a1);

  // Duplicate a string, using my function, then print
  printf("Before dup, pointer a2 = %p, contents = %s\n", a2, a2);
  p2 = mystrdup(a2);
  printf("After dup, pointer p2 = %p, contents = %s\n", p2, p2);

  // test mystrncpy: copy first 6 elements of a1 to a4
  p2 = mystrncpy(a4, a1, 6); // contents should be HiHell
  printf("Copying 6 elements in a1 to a4: %s\n", p2);
  p2 = strncpy(a5, a1, 6);
  printf("STD Copying 6 elements in a1 to a4: %s\n", p2);
  
  // test mystrndup: duplicate a string and print
  printf("Before ndup, n = 12, pointer a1 = %p, contents = %s\n", a1, a1);
  p2 = mystrndup(a1, 12); // contents should be HiHelloHello
  printf("After ndup, n = 12, pointer p2 = %p, contents = %s\n", p2, p2);

  return 0; // indicate success!
}
