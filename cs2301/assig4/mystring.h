/** @file mystring.h
 * @author Mike Ciaraldi
 * @author Christopher Bove - modified from Ciaraldi's original work
 * @date 4-13-15
 * @brief Custom versions of some of the C-style string functions
*/

char* mystrdup(const char* src);
char *mystrcpy(char *dest, const char *src);
char *mystrncpy(char *dest, const char *src, int n);
char *mystrcat(char *dest, const char *src);
char *mystrncat(char *dest, const char *src, int n);
char *mystrndup(const char *src, int n);
