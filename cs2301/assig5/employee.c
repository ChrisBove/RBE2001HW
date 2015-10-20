#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "employee.h"
//needed for malloc
#include <stdlib.h>
// needed for readline
#include <readline/readline.h>
#include <readline/history.h>
//needed for type checking
#include <ctype.h>

/** Outputs one Employee structure in verbose form, to an open file stream
 * @param stream The output stream to write to (must already be open).
 * @param employee Pointer to the structure to print
*/

void outputEmployeeVerbose(FILE *stream, Employee *employee) {
  fprintf(stream, "Employee:. Name = %s, Salary = %d\n",
	  employee->name, employee->salary);
}

/** Outputs one Employee2 structure in verbose form, to an open file stream
 * @param stream The output stream to write to (must already be open).
 * @param employee Pointer to the structure to print
*/

void outputEmployee2Verbose(FILE *stream, Employee2 *employee) {
  fprintf(stream, "Employee2:. Name = %s, Salary = %d\n",
	  employee->name, employee->salary);
}

/** Prints one Employee structure in verbose form
 * @param employee Pointer to the structure to print
*/

void printEmployeeVerbose(Employee *employee) {
 // Save effort -- make use of other function already written!
  outputEmployeeVerbose(stdout, employee);
}

/** Prints one Employee2 structure in verbose form
 * @param employee Pointer to the structure to print
*/
void printEmployee2Verbose(Employee2 *employee) {
 // Save effort -- make use of other function already written!
  outputEmployee2Verbose(stdout, employee);
}

/** Fills in the fields of an Employee structure
 * @param emp Pointer to the struct. MUST ALREADY EXIST!
 * @param salary Annual salary in dollars
 * @param name Character string holding the name. Gets copied into struct.
 * @return Pointer to the same struct
 */
Employee* fillinEmployee(Employee* emp, int salary, char* name) {
  emp->salary = salary; // set the salary
  if (strlen(name) < MAX_NAME) { // if small enough for employee name size
    strcpy(emp->name, name); // copy in the name
  }
  else { // too big! print an error
    printf("ERROR! name is too long for space on emp");
  }
}

/** Allocates an Employee struct and fills in its fields. 
 * @param salary Annual salary in dollars
 * @param name Character string holding the name. Gets copied into struct.
 * @return Pointer to the newly-allocated struct.
 */
Employee* createEmployee(int salary, char* name) {
  Employee* ptr = malloc(sizeof(Employee)); // allocates space for employee
  fillinEmployee(ptr,salary, name); // fill in that new employee with info
  return ptr; // return the pointer to the new employee
}

/** Allocates an Employee2 struct and fills in its fields. 
 * @param salary Annual salary in dollars
 * @param name Character string holding the name. Gets copied into struct.
 * @return Pointer to the newly-allocated struct.
 */
Employee2* createEmployee2(int salary, char* name) {
  Employee2* ptr = malloc(sizeof(Employee2)); // allocates space for employee
  char* new_name = strdup(name); // duplicate string
  ptr->salary = salary; // set the salary
  ptr->name = new_name;
  //fillinEmployee(ptr,salary, new_name); // fill in that new employee with info
  return ptr; // return the pointer to the new employee
}

/** Prompts user to enter name and salary, inputs data to employee2 struct
 * @param employee Pointer to the structure to save to
   @return Pointer to new employee
   @note Checks if user actually input right data
*/
Employee2* inputEmployee2() {
  //printf("Please enter an employee name: \n");
  //char *inputline; // pointer to input line
  char *inputName; // pointer to inputted name
  char *inputSalary; // pointer to inputted salary
  //char* strings[MAXNAME+1];
  int done = 0; // Set flag to non-zero when done
  int count = 0; // Number of strings entered

  inputName = readline("Enter a name: "); // save name for later
  // Read the input line, check that its all ints
  while(!done) {
    inputSalary = readline("Enter a salary (numbers only): "); // save salary
    int i; // for counting through string
    int not_a_digit = 0;
    for (i = 0; i < strlen(inputSalary); i++) {
      if (!isdigit(inputSalary[i])) { // not a digit!
        not_a_digit = 1;
        free(inputSalary);
        printf("You need to enter a number!\n");
        break;
      }
    }
    if (not_a_digit == 0) { // all chars are numbers
      done = 1; // done
    }
  }
  
  return createEmployee2(atoi(inputSalary), inputName);
}

/** Prompts user to enter name and salary, inputs data to employee struct
 * @return Pointer to new employee
   @note Checks if user actually input right data
*/
Employee* inputEmployee() {
  //printf("Please enter an employee name: \n");
  //char *inputline; // pointer to input line
  char inputName[MAX_NAME]; // inputted name
  char* inputptr = inputName; // ptr to inputted name
  char *inputSalary; // pointer to inputted salary
  int done = 0; // Set flag to non-zero when done
  int count = 0; // Number of strings entered

  inputptr = readline("Enter a name: "); // save name for later
  strncpy(inputName, inputptr, MAX_NAME); // copy contents of string

  // Read the next input line, check that its all ints
  while(!done) {
    inputSalary = readline("Enter a salary (numbers only): "); // save salary
    int i; // for counting through string
    int not_a_digit = 0; // 1 if an int
    // for each character, check if its a digit or not.
    for (i = 0; i < strlen(inputSalary); i++) {
      if (!isdigit(inputSalary[i])) { // not a digit!
        not_a_digit = 1;
        free(inputSalary);
        printf("You need to enter a number!\n");
        break;
      }
    }
    if (not_a_digit == 0) { // all chars are numbers
      done = 1; // done
    }
  }
  
  return createEmployee(atoi(inputSalary), inputName);
}
