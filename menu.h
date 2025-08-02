#pragma once

#include "libraries.h"

void showMenu(unsigned int employeeLevel, List* employeesList, List* customersList, List* itemsList, Queue* Log);

void showManagerMenu();

void showEmployeeMenu();

void showTraineeMenu();

void exitProgram(List* employeesList, List* customersList, List* itemsList, Queue* Log);

// auxiliary functions
int getValidChoice();

void initiatePurchase(List* employeesList, List* customersList, List* itemsList, List* shoppingCart, Queue* Log);