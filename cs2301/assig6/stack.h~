#ifndef STACK_H
#define STACK_H

/** Struct to define a stack; each entry can hold a pointer to anything.
 */
struct _Stack {
  void **stack_base; // Pointer to base of stack
  void **next;  // Pointer to next free cell;
  int max_cells; // Maximum number of entries in the stack
  int cells_used; // Currently used number of cells
};

typedef struct _Stack Stack;

// Function prototypes

Stack *create_stack(int max_cells);
void delete_stack(Stack *which_stack);
int push(Stack *which_stack, void *ptr);
void* pop(Stack *which_stack);
void* peek(Stack *which_stack);

#endif
