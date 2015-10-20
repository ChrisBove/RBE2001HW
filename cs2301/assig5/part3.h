#ifndef PART3_H
#define PART3_H

int writeEmployeeLog(Employee2* array[], int length);
void outputEmployee2Lines(FILE *stream, Employee2 *employee);
void freeEmployeeArray(Employee2* array[], int length);
void freeEmployee(Employee2* employee);

#endif
