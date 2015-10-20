/**
 * @file assig3.c
 * @author Christopher Bove (cpbove)
 * @date 6 April 2015
 * @brief File for executable C program for Assignment 3.
 *
 * This program demonstrates reading any number of ints from the command line, 
 *  filling a new array with them, printing that array, and then sorting the 
 *  contents from greatest to smallest, and finally printing the sorted array.
 *
 * Usage:
 *         ./assig3 some_number another_num and_another_num ...
 * Example:
 *         ./assig3 2014 1 7 23 8000
 *
 * Modified from Ciaraldi Lab 2 assignment by: Christopher Bove
 *   on 3/25/15
 * Modified again for pointer enhancements and no number limit on cmd line
 *   on 4/6/2015
 */

#include <stdio.h>
#include <stdlib.h>
#include "sort.h"

/**
 * @brief main function
 */
int main (int argc, const char* argv[]) {

  int* nums; // space to store numbers.
  int num_nums; // How many numbers in array/entered

  if (argc < 2) { // Check that there was at least one number.
    printf("Must enter at least 1 number on the command line!\n");
    return 0; // Indicate failure
  }

  nums = allocate_array(argv, argc, &num_nums); // make new array to store
  fill_array(argv, nums, &num_nums); // fill the array

  printf("Unsorted List:\n");
  print_array(nums, num_nums); // print the current array

  sort_array(nums, num_nums); // sort the array

  printf("Sorted List:\n");
  print_array(nums, num_nums); // print the sorted list.
  
  return 0; // Indicate success!
}
