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
// need for open/close
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "employee.h"
#include "part5.h"

#define FILE_NAME "part6.txt"

int main() {
  // declare variables
  int numEmp = numEmployees(); // number of employees in file
  int i; // for indexing
  int salary = 0; // initialize variables
  char myName[MAX_NAME];

  // instantiate pointer array of right size to hold employers
  Employee* array[numEmp];

  // for each employee in file
  for (i = 0; i < numEmp; i++) {
    //Employee emp; // make employee
    Employee* emp = malloc(sizeof(Employee)); // allocate employee
    readEmployeeLog(i, myName, &salary); // read the desired employee, set data
    //Employee2* emp = malloc(sizeof(Employee2)); // allocate employee
    // fill in employee data
    emp->salary = salary;
    *(emp->name) = *strdup(myName); // duplicate string, needed to allocate mem
    // store that pointer in array
    array[i] = emp;
  }

  // print out the contents of array
  for (i = 0; i < numEmp; i++) {
    printEmployeeVerbose(array[i]);
  }
  
  /*int salary = 0;
  int* salaryptr = &salary;
  char name[BUFSIZ];
  char* nameptr = name;
  readEmployeeLog(0, name, &salary);
  printf("%s, %d\n", name, salary);
  // while haven't hit end of file
    // read employee and save
    // check if we're at the end */
  return 0;
}

/** Calculates number of employees in text file
  @return number of employees
  @note still uses fgets since that was only way to count lines
*/
int numEmployees() {
  char line_buffer[BUFSIZ]; // from stdio
  char line_number; // line number to be on
  int numEmploy; // the actual number of employees in the file
  //open the file
  //int fd = open(FILE_NAME, O_RDONLY); // open up the file descriptor
  FILE *infile = fopen(FILE_NAME, "r");
  // check if file read was successful
  if (infile == NULL) { // file wasn't read properly!
    printf("Cannot read %s! Get read permissions on the file. \n", FILE_NAME);
    printf("Error number: %d \n", errno);
    fprintf(stderr, "Can't read!\n");
    printf("Error string: %s\n", strerror(errno));
    return 0; // indicate failure
  }

  line_number = 0; // reset count
  while (fgets(line_buffer, sizeof(line_buffer), infile)) { // while still on ln 
    line_number++; // keep track of the line we're on
  } 
 
  fclose(infile);
  numEmploy = (line_number)/2; // 2 lines for each employee
  return numEmploy;
}


/** Reads 1 employee from a text file
  @param index of the employee number to retrieve
  @param name of employer to save to
  @param salary pointer to save information to
  @return int 1 if failed to read file, 0 if succeeded
*/
int readEmployeeLog(int index, char* name, int* salary) {
  char line_buffer[BUFSIZ]; // from stdio
  char line_number; // line number to be on
  int actualLine; // real line to pull from
  //open the file
  FILE *infile = fopen(FILE_NAME, "r");
  //int fd = open(FILE_NAME, O_RDONLY); // open up the file descriptor
  // check if file read was successful
  if (infile == NULL) { // if outfile had an error
  //if (fd == 0) { // if outfile had an error
    printf("Cannot read %s! Get read permissions on the file. \n", FILE_NAME);
    printf("Error number: %d \n", errno);
    fprintf(stderr, "Can't read!\n");
    printf("Error string: %s\n", strerror(errno));
    return 1; // indicate failure
  }

  actualLine = index*2; // since an employee takes up 2 lines.
  
  line_number = 0; // reset count
  /*Employee temp; // create employee to temp fill
  while
  ssize_t count = read(fd, &temp, sizeof(Employee)); //get from file
  if (count != sizeof(Employee)) {
    printf("Only able to read %d bytes.\n", count);
    return 1;
  }
  while(*/
  while (fgets(line_buffer, sizeof(line_buffer), infile)) { // while still on ln
   //printf("%4d: %s", line_number, line_buffer); 
    if(line_number == actualLine) { // we are on the desired name line
      // copy the line into the name string, but skip the newline character
      strncpy(name, line_buffer, strlen(line_buffer)-1);
      //printf("%s\n", name); 
    }
    if(line_number == (actualLine + 1)){ // on the desired salary line
      *salary = atoi(line_buffer); // store as integer in salary
      line_number++; // increment now cause we'll break
      break; // for some efficiency - skip rest of file
    }
    line_number++; // keep track of the line we're on
  } 
  //printf("\nTotal number of lines = %d\n", line_number);

  fclose(infile);
  //calculate index to search
  //actualLine = index*2; // since an employee takes up 2 lines.
  // obtain name
  //sscanf (line, "%ld", &elapsed_seconds);
  // increase row
  // obtain salary
  // close file
}
