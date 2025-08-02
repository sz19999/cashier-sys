#include "libraries.h"

void ensureFilesExist(Queue* Log) {
    if (!checkIfLogFileExists(Log)) {
        createNewLogFile();
    }
    if (!checkIfItemsFileExists(Log)) {
        createNewItemsFile();
    }
    if (!checkIfCustomersFileExists(Log)) {
        createNewCustomersFile();
    }
    if (!checkIfEmployeeFileExists(Log)) {
        createDefaultAdmin(Log);
    }
}

void loadFiles(List* Employees, List* Customers, List* Items) {
    loadEmployees(Employees);
    loadCustomers(Customers);
    loadItems(Items);
}

void clearScreen() {
    printf("\033[2J\033[H");  // clear screen and move cursor to top-left
}

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void destroyCreatedDataStructures(List* Employees, List* Customers, List* Items, Queue* Log) {
    DestroyList(Employees);
    DestroyList(Customers);
    DestroyList(Items);
    DestroyQueue(Log);
}