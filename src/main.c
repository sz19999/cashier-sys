/************************************************

Program: Advanced Programming Lab Final Project
Authors: Sean Zinger

*************************************************/

#include "../inc/libraries.h"

int main() {
    // creates the data structures to load the files data
     List* Employees = List_Create("employees");
     List* Customers = List_Create("customers");
     List* Items = List_Create("items");
     Queue* Log = Queue_Create();

    // checking if the needed files exist, if not, creates them
    ensureFilesExist(Log);

    // loads the files to data-structures
    loadFiles(Employees, Customers, Items);

    // extracts employee data if login was successful
    Employee currentEmployee = login();

    char* logMsg = (char*)malloc(50 * sizeof(char));
    sprintf(logMsg, "user \"%s\" has logged in\n", currentEmployee.username);
    addToLog(logMsg, Log);
    free(logMsg);

    // exits the program after 3 failed login attempts
    if (currentEmployee.level == 0) {
        addToLog("failed login attempt 3 times in a row\n", Log);
        updateLogFile(Log);
        destroyCreatedDataStructures(Employees, Customers, Items, Log);

        printf("Login failed! Try again later...\n");
        Sleep(4000);
        return 0;
    }
    
    // opens a compatible interface according to employee authorization
    showMenu(currentEmployee.level, Employees, Customers, Items, Log);

    // destroys data structures
    destroyCreatedDataStructures(Employees, Customers, Items, Log);

    return 0;
}
