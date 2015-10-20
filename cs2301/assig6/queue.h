/**
 * @file queue.h
 * @author Christopher Bove (cpbove)
 * @date 27 April 2015
 * @brief C header for queue struct, and creation and management functions
 *
 */

#ifndef QUEUE_H
#define QUEUE_H

/** @brief Struct to define a queue; each entry can hold a pointer to anything.
 */
struct _Queue {
  int cells_used; // size of queue
  int max_cells; // Maximum number of entries in the stack
  void **head; // head pointer, points to first cell of queue
  void **tail; // tail pointer, points to last cell of queue
  void **queue_base; // location of the queue buffer in memory
  void **queue_end; // location of end of buffer in memory
  void **next;  // Pointer to next free cell after the tail
};

typedef struct _Queue Queue;

// Function prototypes

Queue *create_queue(int max_cells);
void delete_queue(Queue *which_queue);
int enqueue(Queue *which_queue, void *ptr);
void* dequeue(Queue *which_queue);
void* peek(Queue *which_queue);

#endif
