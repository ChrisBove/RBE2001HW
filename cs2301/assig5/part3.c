#include <stdio.h>
#include <string.h>
#include <errno.h>
//needed for malloc
#include <stdlib.h>
// needed for readline
#include <readline/readline.h>
#include <readline/history.h>
//needed for type checking
#include <ctype.h>

#include "employee.h"
#include "part3.h"

#define FILE_NAME "part3.txt"

int main() {
  printf("Starting program part3.\n"); 
  int numEmp; // the number of employers there are
  int i; // index counter
  char* inputline; // store input from cmd line

  // ask how many employees there are
  inputline = readline("Enter the number of employers: ");
  numEmp = atoi(inputline); // convert to number
  
  // instantiate pointer array of right size to hold employers
  Employee2* array[numEmp];
  // prompt user to enter employees
  for(i = 0; i < numEmp; i++) {
    // allocate employee2 struct
    Employee2* emp = malloc(sizeof(Employee2));
    emp = inputEmployee2(); // set emp to hold inputted employer data
    // store that pointer in array
    array[i] = emp;
  }

  // print the data using printEmployee2Verbose
  for (i = 0; i <numEmp; i++) {
    printEmployee2Verbose(array[i]);
  }

  // write all employees to text file
  // put each piece of data on separate line
  int result = writeEmployeeLog(array, numEmp);
  if(result) // check that write to file suceeded
    return 1; // indicate failure

  // free all memory of things
  freeEmployeeArray(array, numEmp);
  // free locals
  //free(&numEmp);
  //free(&i);
  //free(inputline);
  //printf("Finished freeing memory");

  // check things are gone
  for (i = 0; i <numEmp; i++) {
    ///printEmployee2Verbose(array[i]);
  }
  return 0; // indicate success
}

/** Writes employees to a text file, each data on separate line
  @param array of employee2 pointers
  @param length of array
  @return int 1 if failed to write file, 0 if succeeded
*/
int writeEmployeeLog(Employee2* array[], int length) {
  printf("About to write to file %s.\n", FILE_NAME);
  FILE *outfile = fopen(FILE_NAME, "w"); // Open or create file for writing
  // check if file write was successful
  if (outfile == NULL) { // if outfile is null pointer
    printf("Cannot write %s! Get write permissions on the file. \n", FILE_NAME);
    printf("Error number: %d \n", errno);
    fprintf(stderr, "Can't write!\n");
    printf("Error string: %s\n", strerror(errno));
    return 1; // indicate failure
  }
  // go through each element of array and print
  int i; // for index counting
  for (i = 0; i < length; i++) {
    outputEmployee2Lines(outfile, array[i]);
  }
  fclose(outfile); // Close the file
  printf("Finished writing file.\n");
  return 0; // indicate success
}

/** Outputs one Employee2 structure in verbose form, to an open file stream
    uses one line for each data piece
 * @param stream The output stream to write to (must already be open).
 * @param employee Pointer to the structure to print
*/

void outputEmployee2Lines(FILE *stream, Employee2 *employee) {
  fprintf(stream, "%s\n%d\n", employee->name, employee->salary);
}

/** frees the employee array, and all data in it
  @param array of employee2 pointers
  @param length of array
*/
void freeEmployeeArray(Employee2* array[], int length) {
  int i; // couting
  for (i = 0; i < length; i++) {
    // free employee and its data
    //printf("trying to free employee\n");
    freeEmployee(array[i]);
    //printf("Freed employee\n");
  }
  // free the array
  //free(array);
  //printf("freed array\n");
}

/** frees the employee, and all data in it
  @param employee pointer to employee to free
*/
void freeEmployee(Employee2* employee) {
  //free(&(employee->salary));
  //printf("freed salary\n");
  //free(employee->name);
  //printf("freed name\n");
  free(employee);
}



/*
  // Anybody recognize these names?
  Employee harry; // Declare a local variable (a struct).
  harry.salary = 50000;
  strcpy(harry.name, "Harry Palmer"); // Copy into array in struct

  Employee bluejay; // Declare a local variable (a struct).
  bluejay.salary = 60000;
  strcpy(bluejay.name, "Erik Grantby"); // Copy into array in struct

  Employee testGuy; // declare test employee
  fillinEmployee(&testGuy, 23405, "Test Guy");

  Employee* eptr; // pointer to employee
  eptr = createEmployee(55555, "Pointer Guy");// eptr to point to employee


  // Employee2 testing
  Employee2* john; // declare pointer variable
  john = createEmployee2(1234, "John Cooper");

  Employee2* sandy; 
  sandy = createEmployee2(30000, "The one with the really long name");

  // Input testing
  Employee2* dilbert;
  dilbert = inputEmployee2();

  // Output the employees to a file.
  printf("About to write to file %s.\n", OUTFILENAME);
  FILE *outfile = fopen(OUTFILENAME, "w"); // Open or create file for writing
  // check if file write was successful
  if (outfile == NULL) { // if outfile is null pointer
    printf("Cannot write %s! Get write permissions on the file. \n", OUTFILENAME);
    printf("Error number: %d \n", errno);
    fprintf(stderr, "Can't write!\n");
    printf("Error string: %s\n", strerror(errno));
    return 1; // indicate failure
  }
  outputEmployeeVerbose(outfile, &harry);
  outputEmployeeVerbose(outfile, &bluejay);
  outputEmployeeVerbose(outfile, &testGuy);
  outputEmployeeVerbose(outfile, eptr);
  outputEmployee2Verbose(outfile, john);
  outputEmployee2Verbose(outfile, sandy);
  outputEmployee2Verbose(outfile, dilbert);
  fclose(outfile); // Close the file

  // Output the employees to stdout.
  printEmployeeVerbose(&harry);
  printEmployeeVerbose(&bluejay);
  printEmployeeVerbose(&testGuy);
  printEmployeeVerbose(eptr);
  printEmployee2Verbose(john);
  printEmployee2Verbose(sandy);
  printEmployee2Verbose(dilbert);

  printf("Ending program etest.\n"); 
  return 0;
*/
