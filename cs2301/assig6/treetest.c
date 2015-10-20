/**
 * @file treetest.c
 * @author Christopher Bove (cpbove)
 * @date 27 April 2015
 * @brief File for executable C program for testing out trees.
 *
 * This program tests out some basic tree creation functions and 
 * that the tree was properly sorted in ascending (a-z) order.
 */

#include <stdlib.h>
#include <stdio.h>
#include "tree.h"

int main() {
  // make a tree
  Tnode* t1 = NULL; // declare pointer to the root node and init to NULL 
  // add some data to the tree
  t1 = add_tnode(t1, "Who?");
  add_tnode(t1, "Knock, Knock");
  add_tnode(t1, "Hi!");
  add_tnode(t1, "Who's there?");
  
  // print the tree in ascending order
  print_tnode(t1);

  return 0;
}
