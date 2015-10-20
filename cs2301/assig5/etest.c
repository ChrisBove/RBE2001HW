#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "etest.h"
#include "employee.h"

#define OUTFILENAME "etest.txt"

int main() {
  printf("Starting program etest.\n"); 

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
}
