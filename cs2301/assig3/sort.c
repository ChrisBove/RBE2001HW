/**
 * @file sort.c
 * @author Christopher Bove (cpbove)
 * @date 6 April 2015
 * @brief File for sorting functions for assignment 3
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "sort.h"


/** This function allocates an array of a sufficient size to store the numbers
 *  passed in argv[].
 * @param argv const char pointer to argv array from command line
 * @param argc number of arguments on command line
 * @return pointer to base of array of numbers
 * @note This does not check type of string on line. It is assumed to be int.
 */
int* allocate_array(const char *argv[], int argc, int *num_elems) {
  *num_elems = argc - 1; // update value of num_elems to num entered on cmd
  return calloc(*num_elems, sizeof(int)); // alocate memory for array of ints
}


/** This function fills the elements of an array with that of argv
 * @param argv const char pointer to argv array from command line
 * @param new_array pointer to first element in array to be filled
 * @param max_elems number of maximum elements that can be placed in array
 * @param argc number of arguments on command line
 */
void fill_array(const char *argv[], int *new_array, int *num_elems) {
  int i; // array index 

  // check for no characters moved to main.
  // check for too many numbers removed.

  int* new_aptr = new_array; // pointer to base array element in array to fill
  for (i = 0; i < *num_elems; i++) { // fill nums array with those in argv
    // start with argv[1] to get 0th number to put in nums[0]
    *(new_aptr++) = atoi( *++argv); // set elements in new to those in argv
    // pointers are incremented in line above.
  }
}


/** This function prints the elements of an array, one per line.
 *  This is modified from the example in Ciaraldi's Class 7 Example on slide 36
 * @param array pointer to first element in array (base)
 * @param num_elements number of elements actually filled in the array
 * @note the highest index should be num_elements-1
 */
void print_array(int *array, int num_elements) {
  int* aptr = array; // pointer to array base element
  int i; // for stepping through array
  for (i = 0; i < num_elements; i ++) { // go through contents of array
    printf(" %d\n", *(aptr++)); //print the current number, increment to next
  }
}


/** This function sorts the elements of an array of ints from greatest to least
 *  This is modified from the example in Ciaraldi's Class 7 Example on slide 28
 * @param array pointer to first element in array (base)
 * @param num_elements number of elements actually filled in the array
 * @note uses bubble sort algorithm developed by tcpong @ cs.ust.hk
 */
void sort_array(int *array, int num_elements) {
  int* aptr; // pointer to array element
  int round; // track round of sorting
  int i; // used for internal loop index tracking
  int in_order; // 1 if array is in order

  // go round until we are down to one pass, should all be sorted by then
  for (round = num_elements; round > 0; round-- ) {
    in_order = 1; // array is in order (till we know its not)
    aptr = array; // set sptr back to base

    // check all needed items in this round
    // optimization- skip another element for each round - it is in right spot
    for (i = num_elements - round; i < num_elements - 1; i++) {
      int* this_val_ptr = aptr; // store pointer of first element
      int* next_val_ptr = aptr + 1; // store pointer of next

      if ( *this_val_ptr < *next_val_ptr) { // if less than next, swap!
        in_order = 0; // signal that array was not in order

        // swap array elements
        int last_val = *(this_val_ptr); // temp. storage of last val.
        *(aptr++) = *next_val_ptr; // set the current value to next one, increm
        *(aptr) = last_val; // set next element to the last value of the one bf
      }
      else // if these 2 elements are in order
        aptr++; // go to next element, it was done incremented in true case
    }

    if (in_order == 1) { // if no swapping was done in last pass, done!
      return;
    }
  }
  return; // in case we missed a case
}
