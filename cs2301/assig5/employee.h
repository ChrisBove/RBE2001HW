#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#define MAX_NAME (40)

// Define some structures
struct _Employee {
  int salary; // Monthly salary in US dollars
  char name[MAX_NAME + 1]; // Character string holding name of employee.
              // MUST be dynamically allocated from the heap.
};

struct _Employee2 {
  int salary; // Monthly salary in US dollars
  char *name; // Pointer to character string holding name of employee.
              // MUST be dynamically allocated from the heap.
};

typedef struct _Employee Employee; // For convenience
typedef struct _Employee2 Employee2; // For convenience

// function prototypes
void printEmployeeVerbose(Employee *employee);
void printEmployee2Verbose(Employee2 *employee);
void outputEmployeeVerbose(FILE *stream, Employee *employee);
void outputEmployee2Verbose(FILE *stream, Employee2 *employee);
Employee* fillinEmployee(Employee* emp, int salary, char* name);
Employee* createEmployee(int salary, char* name);
Employee2* createEmployee2(int salary, char* name);
Employee2* inputEmployee2();
Employee* inputEmployee();

#endif
