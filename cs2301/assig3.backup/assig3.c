/**
 * @file assig2.c
 * @author Christopher Bove (cpbove)
 * @date 30 March 2015
 * @brief File for executable C program for Assignment 2.
 *
 * This program demonstrates reading up to 10 numbers from the command line, 
 *  filling a new array with them, printing that array, and then sorting the 
 *  contents from greatest to smallest, and finally printing the sorted array.
 *
 * Usage:
 *         ./num2 some_number another_num and_another_num ...
 * Example:
 *         ./num2 2014 1 7 23 8000
 *
 * Modified from Ciaraldi Lab 2 assignment by: Christopher Bove
 *   on 3/25/15
 */

#include <stdio.h>
#include <stdlib.h>

// function prototypes
int fill_array(const char *argv[], int *new_array, int max_elems, int argc);
void print_array(int *array, int num_elements); // function prototype.
void sort_array(int *array, int num_elements); // function prototype.



/**
 * @brief main function
 */
int main (int argc, const char* argv[]) {

  /* The symbolic constant MAX_NUMS sets the maximum number of numbers 
     to enter as arguments on the command line. */
#define MAX_NUMS (10)

  int nums[MAX_NUMS]; // space to store up to MAX_NUMS numbers.

  int num_nums; // How many numbers actually entered on the command line.

  num_nums = fill_array(argv, nums, MAX_NUMS, argc); // fill the array

  if (num_nums == 0) // check that numbers were actually entered.
    return 1; // indicate failure

  printf("Unsorted List:\n");
  print_array(nums, num_nums); // print the current array

  sort_array(nums, num_nums); // sort the array

  printf("Sorted List:\n");
  print_array(nums, num_nums); // print the sorted list.
  
  return 0; // Indicate success!
}



/** This function fills the elements of an array with that of another
 * @param argv const char pointer to argv array from command line
 * @param new_array pointer to first element in array to be filled
 * @param max_elems number of maximum elements that can be placed in array
 * @param argc number of arguments on command line
 * @return 0 for failure, otherwise num of elements in array
 */
int fill_array(const char *argv[], int *new_array, int max_elems, int argc) {
  int next_num; // Integer read from the command line goes here.
  int i; // array index 
  int num_nums; // How many numbers actually entered on the command line.

  if (argc < 2) { // Check that there was at least one number.
    printf("Must enter 1 to %d numbers on the command line!\n", MAX_NUMS);
    return 0; // Indicate failure
  }

  num_nums = argc - 1; // set number of numbers entered

  if (num_nums > MAX_NUMS) { // check if too many numbers were entered
    printf("You entered %d numbers, enter no more than %d!\n", num_nums, 
      MAX_NUMS);
    return 0; // Indicate failure
  }

  //const char* argv_aptr = argv;
  int* new_aptr = new_array; // pointer to base array element in array to fill
  for (i = 0; i < num_nums; i++) { // fill nums array with those in argv
    // start with argv[1] to get 0th number to put in nums[0]
    *(new_aptr++) = atoi(argv[i+1]); // get argv val, increment to next element
  }
  return num_nums;
}


/** This function prints the elements of an array, one per line.
 *  This is modified from the example in Ciaraldi's Class 7 Example on slide 36
 * @param array pointer to first element in array (base)
 * @param num_elements number of elements actually filled in the array
 * @return Nothing
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
 * @return Nothing
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
    // note - no optimization, checking them all each time
    for (i = 0; i < num_elements - 1; i++) {
      int next_val = *(aptr + 1); // store the next array value

      if ( *(aptr) < next_val) { // if this value is less than next, swap!
        in_order = 0; // signal that array was not in order

        // swap array elements
        int last_val = *(aptr); // temp. storage of last val.
        *(aptr) = next_val; // update the current value
        *(aptr + 1) = last_val; // set next element to the last value of this
      }
      aptr++; // go to next element
    }

    if (in_order == 1) { // if no swapping was done in last pass, done!
      return;
    }
  }
  return; // in case we missed a case
}
