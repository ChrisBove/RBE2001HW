#ifndef PART6_H
#define PART6_H

int writeEmployeeLog(Employee array[], int length);
void outputEmployee2Lines(int *fd, Employee employee);
void freeEmployeeArray(Employee array[], int length);
void freeEmployee(Employee employee);

#endif
