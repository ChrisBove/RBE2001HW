/**
 * @file stacktest.c
 * @author Ciaraldi, modified by Christopher Bove (cpbove)
 * @date 27 April 2015
 * @brief C executable for testing stack creation and management functions
 * Tests out all the stack functions and the user varifies they work.
 */

#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

typedef struct {
  int x;
  double y;
} Foo; // Just some arbitrary struct

int main() {
  const int max_entries = 5; // size of stack
  Foo* new_foo1;
  Foo* new_foo2; 
  Foo* new_foo3;
  Foo* new_foo4;
  Foo* new_foo5;
  Foo* returned_foo;

  // First, create a stack
  Stack *new_stack = create_stack(max_entries);

  // Allocate a Foo and push it onto the stack.
  new_foo1 = (Foo *) malloc(sizeof(Foo));
  new_foo1->x = 6;
  new_foo1->y = 14.79;
  printf("Pushing: x = %5d, y = %10.3f\n", new_foo1->x, new_foo1->y);
  push(new_stack, (void *) new_foo1);

  // Allocate another Foo and push it onto the stack.
  new_foo2 = (Foo *) malloc(sizeof(Foo));
  new_foo2->x = 217;
  new_foo2->y = 3.14159;
  printf("Pushing: x = %5d, y = %10.3f\n", new_foo2->x, new_foo2->y);
  push(new_stack, (void *) new_foo2);

  // Peek at the top of the stack
  returned_foo = (Foo *) peek(new_stack);
  printf("Peeked:  x = %5d, y = %10.3f\n", returned_foo->x, returned_foo->y);

  // Retrieve the Foos and print them.
  returned_foo = (Foo *) pop(new_stack);
  printf("Popped:  x = %5d, y = %10.3f\n", returned_foo->x, returned_foo->y);
  returned_foo = (Foo *) pop(new_stack);
  printf("Popped:  x = %5d, y = %10.3f\n", returned_foo->x, returned_foo->y);

  // make some new elements
  new_foo3 = (Foo *) malloc(sizeof(Foo));
  new_foo3->x = 333;
  new_foo3->y = 3.333;
  new_foo4 = (Foo *) malloc(sizeof(Foo));
  new_foo4->x = 0;
  new_foo4->y = 0;
  new_foo5 = (Foo *) malloc(sizeof(Foo));
  new_foo5->x = -3;
  new_foo5->y = -1;

  // push elements onto the stack
  printf("Pushing: x = %5d, y = %10.3f\n", new_foo1->x, new_foo1->y);
  push(new_stack, (void *) new_foo1);
  printf("Pushing: x = %5d, y = %10.3f\n", new_foo2->x, new_foo2->y);
  push(new_stack, (void *) new_foo2);
  printf("Pushing: x = %5d, y = %10.3f\n", new_foo3->x, new_foo3->y);
  push(new_stack, (void *) new_foo3);
  printf("Pushing: x = %5d, y = %10.3f\n", new_foo4->x, new_foo4->y);
  push(new_stack, (void *) new_foo4);
  printf("Pushing: x = %5d, y = %10.3f\n", new_foo5->x, new_foo5->y);
  push(new_stack, (void *) new_foo5);

  // pop some off
  returned_foo = (Foo *) pop(new_stack);
  printf("Popped:  x = %5d, y = %10.3f\n", returned_foo->x, returned_foo->y);
  returned_foo = (Foo *) pop(new_stack);
  printf("Popped:  x = %5d, y = %10.3f\n", returned_foo->x, returned_foo->y);

  // push some more
  printf("Pushing: x = %5d, y = %10.3f\n", new_foo5->x, new_foo5->y);
  push(new_stack, (void *) new_foo5);
  printf("Pushing: x = %5d, y = %10.3f\n", new_foo4->x, new_foo4->y);
  push(new_stack, (void *) new_foo4);

  // check order- we expect 4,5,3,2,1 foos
  int i; // for iterating through
  for(i = 0; i < 5; i ++) {
    returned_foo = (Foo *) pop(new_stack);
    printf("Popped:  x = %5d, y = %10.3f\n", returned_foo->x, returned_foo->y);
  }

  // push more than 5 elements
  printf("Pushing: x = %5d, y = %10.3f\n", new_foo1->x, new_foo1->y);
  push(new_stack, (void *) new_foo1);
  printf("Pushing: x = %5d, y = %10.3f\n", new_foo2->x, new_foo2->y);
  push(new_stack, (void *) new_foo2);
  printf("Pushing: x = %5d, y = %10.3f\n", new_foo3->x, new_foo3->y);
  push(new_stack, (void *) new_foo3);
  printf("Pushing: x = %5d, y = %10.3f\n", new_foo4->x, new_foo4->y);
  printf("Result: %d\n",push(new_stack, (void *) new_foo4));
  printf("Pushing: x = %5d, y = %10.3f\n", new_foo5->x, new_foo5->y);
  printf("Result: %d\n",push(new_stack, (void *) new_foo5));
  printf("Pushing: x = %5d, y = %10.3f\n", new_foo1->x, new_foo1->y);
  printf("Result: %d\n", push(new_stack, (void *) new_foo1));
  // verify function handles overflow
    // nothing occurred when the overflow happened.
  // verify proper return status
    // function returned -1 when an overflow happened
  // verify stack is in right state
  for(i = 0; i < 5; i ++) {
    returned_foo = (Foo *) pop(new_stack);
    if (returned_foo == NULL)
      printf("we tried to pop off an empty stack! Caught error\n");
    else
      printf("Popped:  x = %5d, y = %10.3f\n", returned_foo->x, returned_foo->y);
  }
  // pop resulted in correct order - 5,4,3,2,1


  // try popping off more elements than there are
  returned_foo = (Foo *) pop(new_stack);
  if (returned_foo == NULL)
    printf("we tried to pop off an empty stack! Caught error\n");
  else
    printf("Popped:  x = %5d, y = %10.3f\n", returned_foo->x, returned_foo->y);
  // confirm function handles this - no crashing, proper return, stack in state
    // looks good!
  returned_foo = (Foo *) peek(new_stack);
    if (returned_foo == NULL)
      printf("we tried to peek an empty stack! Caught error\n");
    else 
      printf("Peeked:  x = %5d, y = %10.3f\n", returned_foo->x, returned_foo->y);

  printf("Starting cleanup...\n");
  // Clean up by deleting all the things...
  delete_stack(new_stack);
  free(new_foo1);
  free(new_foo2);
  free(new_foo3);
  free(new_foo4);
  free(new_foo5);
  printf("Done cleaning up foos!\n");

  return 0;
}
