/**
 * @file mystrlen.c
 * @author Christopher Bove (cpbove)
 * @date 8 April 2015
 * @brief File for string length for assignment 4
 *
 */

#include <string.h>

/** This function calculates the length of a string s
 * @param s pointer to string to check
 * @return The number of characters in s.
 * @note The null terminator is not included
 */
int mystrlen(const char *s) {
  int result = 0;
  while (*s != '\0') {
    result++;
    s++;
  }
  return result;
}
