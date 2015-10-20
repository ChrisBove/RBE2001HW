/** @file mystring.c
 * @author Mike Ciaraldi - for mystrdup
 * @author Christopher Bove (cpbove) for other functions
 * @date 4-13-15
 * @brief Custom versions of some of the C-style string functions
*/
#include <string.h>
#include <stdlib.h>
// stdlib.h is needed to use malloc()
#include "mystring.h"
#include "mystrlen.h"

/** Duplicates a C-style string.
 @param src Pointer to string to be copied
 @return Pointer to freshly-allocated string containing a duplicate of src
         or null if no memory is available
*/

char* mystrdup(const char* src) {
  int length; // Length of the source string
  char* newstr; // Pointer to memory which will hold new string

  length = mystrlen(src) + 1;  // Leave space for the terminator
  newstr = (char*) malloc(length); // Must cast!

  // If no memory was available, return immediately
  if (newstr == 0) return (char *) 0;

  // Otherwise, copy the string and return pointer to new string
  mystrcpy(newstr, src);
  return newstr;
}

/** Duplicates the strcpy function of C: 
    string pointed to by src is copied into array pointed to by dest.
    dest must be large enough to receive the copy.
 @param dest pointer to string to have contents of src copied into
 @param src Pointer to string to be copied
 @return Pointer to the destination string dest
 @note copies src including null terminator character
*/
char *mystrcpy(char *dest, const char *src) {
  // copy src into dest
  char *dest_temp = dest; // pointer to dest, incremented for copying fuction

  while (1) { // still parts of string left to copy
    *dest_temp = *src; // copy contents
    if (*src == '\0') // if reached end of src, stop copying - done!
      return dest;
    // not finished copying, increment pointers
    dest_temp++;
    src++;
  }
  return dest; // in case a case was missed, but you probably seg fault instead
}

/** Duplicates the strncpy function of C: 
    string pointed to by src is copied into array pointed to by dest.
    dest must be large enough to receive the copy. Not more than n bytes
    are copied, so if no null terminator is in first n bytes, it is not copied.
    Also, if src length is less than n, remainder of dest is filled with nulls
 @param dest pointer to string to have contents of src copied into
 @param src Pointer to string to be copied
 @return Pointer to the destination string dest
 @param n number of bytes to copy from src into dest
 @note copies src including null term. character
*/
char *mystrncpy(char *dest, const char *src, int n) {
  // copy n bytes of src into dest
  char *dest_temp = dest; // pointer to dest, incremented for copying fuction
  int num_copied = 0; // number of bytes of src copied so far
  int done_copy = 0; // whether we are done copying the string or not
  int dest_length = mystrlen(dest); // lenth of destination string
  int null_index = 0; // index to track element for adding \0 to things

  while (num_copied < n && !done_copy) { // n bytes have not yet been copied
    *dest_temp = *src; // copy contents
    if (*src == '\0') { // if reached end of src, stop copying - done!
      done_copy = 1; // done copying
    }
    else {
      // not finished copying, increment pointers
      dest_temp++;
      src++;
    }
    num_copied++; // increment number copied.
  }

  null_index = num_copied; // set null_index to what we've filled so far
  // fill rest of dest with null pointers
  while(null_index <= dest_length) { // 
    *dest_temp = '\0'; // fill with null terminator
    dest_temp++;
    null_index++;
  }

  return dest; // return the pointer to the finished string
}

/** Duplicates the strcat function of C: 
    appends the src string to the dest string, the terminator is overwritten
    on dest and terminator is then added. Strings cannot overlap. dest must be
    large enough for the operation.
 @param dest pointer to string to have contents of src appended onto
 @param src Pointer to string to be appended
 @return Pointer to the destination string dest
*/
char *mystrcat(char *dest, const char *src) {
  int dest_length = mystrlen(dest); // calc and store num characters of dest.
  int i; // for incrementing in indexes

  // get to end of stuff in dest
  for (i = 0; i < dest_length; i++) { // get dest pointer to the end of dest
    dest++; // increment pointer along destination
  }

  // now at \0 position in dest

  // copy contents of src onto dest
  while (*src != '\0') {
    *(dest++) = *(src++); // append src element to dest, increment
  }

  // add \0
  *dest = '\0'; // set elem. to null terminator
  return dest;
}

/** Duplicates the strncat function of C: 
    appends the src string to the dest string, but only n characters of it
    the null terminator is overwritten on dest and null term. is then added. 
    Strings cannot overlap. dest must be large enough for the operation.
 @param dest pointer to string to have contents of src appended onto
 @param src Pointer to string to be appended
 @param n number of characters to duplicate
 @return Pointer to the destination string dest
*/
char *mystrncat(char *dest, const char *src, int n) {
  int dest_length = mystrlen(dest); // calc and store num characters of dest.
  int i; // for incrementing in indexes
  int src_chars_left = n; // number of chars that still need to be appended

  // get to end of stuff in dest
  for (i = 0; i < dest_length; i++) { // get dest pointer to the end of dest
    dest++; // increment pointer along destination
  }

  // now at \0 position in dest

  // copy contents of src onto dest, only using n characters
  while (*src != '\0' && src_chars_left != 0) {
    *(dest++) = *(src++); // append src element to dest, increment
    src_chars_left--; // one char copied, so one less left to copy
  }

  // add \0
  *dest = '\0'; // set elem. to null terminator
  return dest;
}

/** Duplicates a C-style string, copying at most n characters, null terminator
    is added
 @param src Pointer to string to be copied
 @param n number of characters to duplicate
 @return Pointer to freshly-allocated string containing a duplicate of src
         or null if no memory is available
 @note Modified from Ciaraldi's original mystrdup function
*/
char *mystrndup(const char *src, int n) {
  int length; // Length of the source string
  char* newstr; // Pointer to memory which will hold new string

  length = mystrlen(src) + 1;  // Leave space for the terminator
  newstr = (char*) malloc(length); // Must cast!

  // If no memory was available, return immediately
  if (newstr == 0) return (char *) 0;

  // Otherwise, copy the string and return pointer to new string, using only n
  mystrncpy(newstr, src, n);
  return newstr;
}
