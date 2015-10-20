/**
 * @file part5.c
 * @author Christopher Bove (cpbove)
 * @date 27 April 2015
 * @brief Executable C program for testing out tree functions with random strs
 *
 * This program creates some random strings and tests out some basic tree
 * creation functions and allows the user to check that the order was good. 
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tree.h"

#define COUNT (10)
#define MAX_CHARS (10)
#define STRINGS_TO_MAKE (5)

int main() {
  srand(time(0)); // change the seed

  int i; // counter for creating random chars
  int s_count; // counter for creating the strings
  int randNum; // holds a random number
  char randChar; // random char
  char c[MAX_CHARS]; // random char array
  char* strings[STRINGS_TO_MAKE]; // strings

  // generate some random strings
  for (s_count = 0; s_count < STRINGS_TO_MAKE; s_count++) {
    for (i = 0; i < COUNT; i++) {
      // pick num b/w 0 and 25
      randNum = 26 * (rand() / (RAND_MAX + 1.0));

      // The ASCII code for ‘a’ is 97, so
      // add 97 to the random number to get
      // a lower case letter.
      randNum = randNum + 97;

      // Type cast to character to convert
      // it to a char type.
      randChar = (char) randNum;
      c[i] = randChar;
    }
    c[COUNT] = 0; // add terminator
    //printf("%s\n", c); // print the string
    // save this rand. string by duping into array of str.
    strings[s_count] = strdup(c); 
  }

  // make a tree
  Tnode* t1 = NULL; // declare pointer to the root node and init to NULL 
  
  printf("The list of random strings:\n");
  // print the string to make sure we stored it right
  for (i = 0; i < STRINGS_TO_MAKE; i++)
    printf("%s\n",strings[i]);
  printf("\n"); // add a return

  // add the strings to the tree
  t1 = add_tnode(t1, strings[0]);
  add_tnode(t1, strings[1]);
  add_tnode(t1, strings[2]);
  add_tnode(t1, strings[3]);
  add_tnode(t1, strings[4]);
  
  // print the tree in ascending order
  printf("Print the tree:\n");
  print_tnode(t1);

  printf("Free up the tree:\n");
  free_nodes(t1);
  printf("Tree freed!\n");
  return 0;
}
