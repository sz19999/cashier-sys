#pragma once

#include "libraries.h"

// general functions
bool checkIfEmployeeFileExists(Queue* Log);

Employee login();

void loadEmployees(List* EmployeesList);

void updateEmployeesFile(List* employeesList);

// menu interface functions
void addEmployee(List* employeesList, Queue* Log);

void displayEmployees(List* employeesList);

void deleteEmployee(List* employeesList, Queue* Log);

// auxiliary functions
void createDefaultAdmin(Queue* Log);

Employee findEmployeeByUserInFile(char* username);

Employee* findEmployeeByUser(char* username, List* employeesList);

void ensureEmployeesFileCursorPos(FILE* fp, int* currentCursorPosition);