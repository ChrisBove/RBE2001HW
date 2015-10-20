/**
 * @file tree.h
 * @author Christopher Bove (cpbove)
 * @date 27 April 2015
 * @brief Header for tree functions
 *
 * Includes Tnode struct for storing trees and functions to add and print them
 */

#ifndef TREE_H
#define TREE_H

typedef struct _Tnode Tnode;

/** Struct to define a tree node; each entry can hold a pointer to anything.
 */
struct _Tnode {
  char* value; // Pointer to C style string
  Tnode *left; // pointer to left child
  Tnode *right; // pointer to right child
};

// Function prototypes
Tnode *add_tnode(Tnode *current_tnode, char* value);
void print_tnode(Tnode *current_tnode);
void free_nodes(Tnode *current_tnode);

#endif
