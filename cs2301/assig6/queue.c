/**
 * @file queue.c
 * @author Christopher Bove (cpbove)
 * @date 27 April 2015
 * @brief C source code for queue creation and management functions
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

/** Create a queue by allocating a Queue structure, initializing it,
 *  and allocating memory to hold the stack entries.
 * @param max_cells Maximum entries in the queue
 * @return Pointer to newly-allocated queue structure, NULL if error.
 */
Queue *create_queue(int max_cells){
  Queue *new_queue; // holds pointer to allocated Queue
  new_queue = (Queue *) malloc(sizeof(Queue));

  if (new_queue == NULL) return NULL; // not able to allocate memory
  printf("Allocated mem for queue\n");
  // fill in queue fields
  new_queue->max_cells = max_cells;
  new_queue->cells_used = 0; // empty queue to start

  // allocate space for the number of queue elements
  new_queue->queue_base = (void **) calloc(sizeof(void *), max_cells);
  if (new_queue->queue_base == NULL){ // couldn't allocate entries, free it!
    free(new_queue);
    return NULL;
  }
  printf("Allocated mem for queue elements\n");
  new_queue->next = new_queue->queue_base; // start at base
  new_queue->head = new_queue->queue_base; // head at base
  new_queue->tail = new_queue->queue_base; // tail at base

  // find the end of the queue
  int i; // counting
  void **base_ptr = new_queue->queue_base; // to iterate up queue
  for(i = 0; i<max_cells; i++) {
    base_ptr++;
  }
  
  new_queue->queue_end = base_ptr;
  return new_queue; // return ptr to new queue
}

/** Deletes a queue, including the structure and the memory
 * for holding the queue entries, but not the entries themselves.
 * @param which_queue Pointer to Stack structure.
 */
void delete_queue(Queue *which_queue){
  // the next line is commented since it inexplicably threw errors
  //free(which_queue->queue_base); // Free memory block with queue entries.
  free(which_queue); // Then free the struct.
}

/** Queues a pointer onto a Queue.
   when entry is added, tail pointer moves to right by 1, holds new value,
     cells count is increased, 
   when tail is at end of array, we try to wrap around by checking status of 
     base/head ptrs
   when queue is full, we return a -1 to indicate a failure
    
 * @param which_queue Pointer to queue you want to enqueue to.
 * @param ptr Pointer to be queued.
 * @return 0 if successful, -1 if not.
 */
int enqueue(Queue *which_queue, void *ptr) {
  // check for overflow - do we have a full queue?
  if ((which_queue->cells_used) >= (which_queue->max_cells)) {
    which_queue->cells_used = which_queue->max_cells; // fix
    return -1;  // Queue overflow.
  }
  *(which_queue->next) = ptr;  // Store the pointer on the queue
  which_queue->tail = which_queue->next; // update tail position
  (which_queue->cells_used)++; // increase cell count
  
  // check if wraparound needs to happen, if next is at end
  if (which_queue->next == which_queue->queue_end) {
    // since we have not overflowed, the base ptr must be open
    which_queue->next = which_queue->queue_base; // set next to base
  }
  else { // not at end, so keep incrementing normally
    (which_queue->next)++; // move next pointer to next spot
  }

  return 0;  // Success
}

/** dequeues from front of queue, and returns that value.
 * @param which_queue Pointer to Queue you want to dequeue from.
 * @return Dequeued entry of queue
 */
void* dequeue(Queue *which_queue) {
  // check if queue is empty
  if ((which_queue->cells_used) <= 0) {
    which_queue->cells_used = 0; // Fix
    return NULL;  // queue empty
  }
  // pull value from head
  void* val = *(which_queue->head);

  // check if wraparound needs to happen, if head is at end
  if (which_queue->head == which_queue->queue_end) {
    // the base ptr now has the new head
    which_queue->head = which_queue->queue_base; // set head to base
  }
  else { // not at end, so keep incrementing normally
  (which_queue->head)++; // move head pointer to next spot
  }

  (which_queue->cells_used)--; // reduce cell count by one
  return val; // return front entry of queue
}

/** Peek at top of queue, without dequeueing
 * @param which_queue Pointer to Queue you want to peek into
 * @return Front entry of the Queue, NULL if queue is empty.
 */
void* peek(Queue *which_queue) {
  // Check if stack is empty
  if ((which_queue->cells_used) <= 0) {
    which_queue->cells_used = 0; // Fix
    return NULL;  // queue empty
  }

  // Return head of queue, without dequeue.
  void** front = which_queue->head;
  return (*front); // get entry
}
