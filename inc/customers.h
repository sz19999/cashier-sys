#pragma once

#include "libraries.h"

void addCustomer(List* customersList, Queue* Log);

Customer* createNewCustomer(List* customersList, Queue* Log);

void displayCustomers(List* customersList);

void printGeneralCustomerInfo(Customer* customer);

void searchCustomer(List* customersList);

void deleteCustomer(List* customersList, Queue* Log);

Customer* findCustomerByName(List* customersList, char* fullname);

bool checkIfCustomersFileExists(Queue* Log);

void createNewCustomersFile();

void loadCustomers(List* customersList);

void initializeSerialsArr(int* serialsArray, int len, List* customerItemsList);

void updateCustomersFile(List* customersList);

void writeCustomer(Customer* customer, FILE* fp, int* currentCursorPosition);

void free_customer(Customer* customer);

bool readCustomer(Customer* customer ,FILE* fp, int* currentCursorPosition);

