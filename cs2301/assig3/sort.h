/**
 * @file sort.h
 * @author Christopher Bove (cpbove)
 * @date 6 April 2015
 * @brief Header file for sorting functions for assignment 3
 *
 */

#ifndef SORT_H
#define SORT_H

// function prototypes
int* allocate_array(const char *argv[], int argc, int *num_elems);
void fill_array(const char *argv[], int *new_array, int *num_elems);
void print_array(int *array, int num_elements); // function prototype.
void sort_array(int *array, int num_elements); // function prototype.

#endif
