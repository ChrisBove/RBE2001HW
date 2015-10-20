/**
 * @file queuetest.c
 * @author Christopher Bove (cpbove)
 * @date 27 April 2015
 * @brief Executable C program for testing out queue functions 
 *
 * This program creates some arbitrary data and tests out some basic queue
 * creation functions and allows the user to check that the test was good. 
 */
#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

typedef struct {
  int x;
  double y;
} Foo; // Just some arbitrary struct

int main() {

  const int max_entries = 5; // size of queue
  Foo* new_foo1;
  Foo* new_foo2; 
  Foo* new_foo3;
  Foo* new_foo4;
  Foo* new_foo5;
  Foo* returned_foo;

  // First, create a queue
  Queue *new_queue = create_queue(max_entries);

  // check if queue was made
  if (new_queue == NULL) {
    printf("THE QUEUE COULD NOT BE MADE!\n");
    return 1;
  }

  // Allocate a Foo and queue it
  new_foo1 = (Foo *) malloc(sizeof(Foo));
  new_foo1->x = 6;
  new_foo1->y = 14.79;
  printf("Queueing: x = %5d, y = %10.3f\n", new_foo1->x, new_foo1->y);
  enqueue(new_queue, (void *) new_foo1);
  // Peek at the top of the queue
  returned_foo = (Foo *) peek(new_queue);
  printf("Peeked:  x = %5d, y = %10.3f\n", returned_foo->x, returned_foo->y);
  
  // Allocate another Foo and queue it
  new_foo2 = (Foo *) malloc(sizeof(Foo));
  new_foo2->x = 217;
  new_foo2->y = 3.14159;
  printf("Queueing: x = %5d, y = %10.3f\n", new_foo2->x, new_foo2->y);
  enqueue(new_queue, (void *) new_foo2);
  // Peek at the top of the queue
  returned_foo = (Foo *) peek(new_queue);
  printf("Peeked:  x = %5d, y = %10.3f\n", returned_foo->x, returned_foo->y);

  // Retrieve the Foos and print them.
  returned_foo = (Foo *) dequeue(new_queue);
  printf("Dequeued:  x = %5d, y = %10.3f\n", returned_foo->x, returned_foo->y);
  // Peek at the top of the queue
  returned_foo = (Foo *) peek(new_queue);
  printf("Peeked:  x = %5d, y = %10.3f\n", returned_foo->x, returned_foo->y);

  returned_foo = (Foo *) dequeue(new_queue);
  printf("Dequeued:  x = %5d, y = %10.3f\n", returned_foo->x, returned_foo->y);
  // Peek at the top of the queue
  returned_foo = (Foo *) peek(new_queue);
  if (returned_foo == NULL) {
    printf("NULL peek returned! Empty\n");
  }
  else printf("Peeked:  x = %5d, y = %10.3f\n", returned_foo->x, returned_foo->y);
  printf("End of first basic test.\n\n");
  
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

  // queue elements onto the stack
  printf("Queueing: x = %5d, y = %10.3f\n", new_foo1->x, new_foo1->y);
  enqueue(new_queue, (void *) new_foo1);
  printf("Queueing: x = %5d, y = %10.3f\n", new_foo2->x, new_foo2->y);
  enqueue(new_queue, (void *) new_foo2);
  printf("Queueing: x = %5d, y = %10.3f\n", new_foo3->x, new_foo3->y);
  enqueue(new_queue, (void *) new_foo3);
  printf("Queueing: x = %5d, y = %10.3f\n", new_foo4->x, new_foo4->y);
  enqueue(new_queue, (void *) new_foo4);
  printf("Queueing: x = %5d, y = %10.3f\n", new_foo5->x, new_foo5->y);
  enqueue(new_queue, (void *) new_foo5);

  // dequeu some
  returned_foo = (Foo *) dequeue(new_queue);
  printf("Dequeued:  x = %5d, y = %10.3f\n", returned_foo->x, returned_foo->y);
  returned_foo = (Foo *) dequeue(new_queue);
  printf("Dequeued:  x = %5d, y = %10.3f\n", returned_foo->x, returned_foo->y);

  // queue some more
  printf("Queueing: x = %5d, y = %10.3f\n", new_foo5->x, new_foo5->y);
  enqueue(new_queue, (void *) new_foo5);
  printf("Queueing: x = %5d, y = %10.3f\n", new_foo4->x, new_foo4->y);
  enqueue(new_queue, (void *) new_foo4);

  printf("*Check the order here- dequeueing things:\n");
  // check order- we expect foos
  int i; // for iterating through
  for(i = 0; i < 5; i ++) {
    returned_foo = (Foo *) dequeue(new_queue);
    printf("Dequeued:  x = %5d, y = %10.3f\n", returned_foo->x, returned_foo->y);
  }

  printf("Try queueing more than 5 elements (6):\n");
  // queue more than 5 elements
  printf("Queueing: x = %5d, y = %10.3f\n", new_foo1->x, new_foo1->y);
  enqueue(new_queue, (void *) new_foo1);
  printf("Queueing: x = %5d, y = %10.3f\n", new_foo2->x, new_foo2->y);
  enqueue(new_queue, (void *) new_foo2);
  printf("Queueing: x = %5d, y = %10.3f\n", new_foo3->x, new_foo3->y);
  enqueue(new_queue, (void *) new_foo3);
  printf("Queueing: x = %5d, y = %10.3f\n", new_foo4->x, new_foo4->y);
  printf("  Result: %d\n",enqueue(new_queue, (void *) new_foo4));
  printf("Queueing: x = %5d, y = %10.3f\n", new_foo5->x, new_foo5->y);
  printf("  Result: %d\n",enqueue(new_queue, (void *) new_foo5));
  printf("Queueing: x = %5d, y = %10.3f\n", new_foo1->x, new_foo1->y);
  printf("  Result: %d\n", enqueue(new_queue, (void *) new_foo1));
  // verify function handles overflow
    // nothing occurred when the overflow happened.
  // verify proper return status
    // function returned -1 when an overflow happened
  printf("You should have seen a -1 for the last result\n:");

  printf("check the queue is in the right order, dequeue it all!\n");
  // verify stack is in right state
  for(i = 0; i < 5; i ++) {
    returned_foo = (Foo *) dequeue(new_queue);
    if (returned_foo == NULL)
      printf("we tried to dequeue an empty queue! Caught error\n");
    else
      printf("Dequeued:  x = %5d, y = %10.3f\n", returned_foo->x, returned_foo->y);
  }
  // dequeue resulted in correct order


  printf("Try to dequeue more elements than there are\n");
  // try dequeueing off more elements than there are
  returned_foo = (Foo *) dequeue(new_queue);
  if (returned_foo == NULL)
    printf("we tried to dequeu an empty queue! Caught error\n");
  else
    printf("Dequeued:  x = %5d, y = %10.3f\n", returned_foo->x, returned_foo->y);
  // confirm function handles this - no crashing, proper return, queue in state
    // looks good!
  printf("You should have seen a caught error message!\n");

  printf("Try to peek an empty queue:\n");
  returned_foo = (Foo *) peek(new_queue);
    if (returned_foo == NULL)
      printf("we tried to peek an empty queue! Caught error\n");
    else 
      printf("Peeked:  x = %5d, y = %10.3f\n", returned_foo->x, returned_foo->y);
  printf("You should have seen a caught error message.\n");

  // Clean up
  printf("Starting cleanup...\n");
  delete_queue(new_queue);
  printf("Freed the queue!\n");
  // the next line is commented since it strangely threw errors
  //free(new_foo1);
  free(new_foo2);
  free(new_foo3);
  free(new_foo4);
  free(new_foo5);
  printf("Freed all the foos!\n");

  return 0;
}
