#include "libraries.h"

// general functions
bool checkIfEmployeeFileExists(Queue* Log) {
	FILE* fp = fopen("employees.bin", "rb");
	
	if (fp == NULL) {
		addToLog("employees file doesn't exist, created new employees file\n", Log);
		return false;
	}
	fclose(fp);
	return true;
}

void createDefaultAdmin(Queue* Log) {
	FILE* fp = fopen("employees.bin", "wb");

	Employee defaultEmployee = {
		"admin",
		"manager",
		"12345678",
		1
	};

	addToLog("added a new employee with user \"admin\"\n", Log);
	fwrite(&defaultEmployee, sizeof(Employee), 1, fp);
	fclose(fp);
}

Employee login() {
	char username[20];
	char password[10];

	Employee nullEmployee = {"0", "0", "0", 0};
	Employee employee;
	int ctr = 1;

	printf("*** Welcome!, Please enter your username and password ***\n");
	do {
		printf("username: ");
		scanf("%s", username);
		clearBuffer();

		printf("password: ");
		scanf("%s", password);
		clearBuffer();

		employee = findEmployeeByUserInFile(username);

		if (employee.level == 0 || strcmp(employee.password, password) != 0) {
			clearScreen();
			if (ctr < 3) {
				printf("username or password are incorrect, please try again! login attempts: %d out of 3\n", ctr);
				printf("Press any key to continue...");
				_getch();
				clearScreen();
			}
			if (ctr == 3) {
				printf("username or password are incorrect! login attempts: %d out of 3\n", ctr);
			}
			ctr++;
			continue;
		}

		clearScreen();
		return employee;

	} while (ctr <= 3);

	return nullEmployee;
}

Employee findEmployeeByUserInFile(char* username) {
	FILE* fp = fopen("employees.bin", "rb");

	// null employee struct
	Employee NullEmployee = {"0", "0", "0", 0};

	Employee CurrentEmployee;
	int found = 0;

	while (!feof(fp)) {
		fread(&CurrentEmployee, sizeof(Employee), 1, fp);
		if (!strcmp(CurrentEmployee.username, username)) {
			found = 1;
			break;
		}
	}

	fclose(fp);
	return found ? CurrentEmployee : NullEmployee;
}

void loadEmployees(List* employeesList) {
	FILE* fp = fopen("employees.bin", "rb");
	if (!fp) return;

	Employee currentEmployee;
	while (fread(&currentEmployee, sizeof(Employee), 1, fp) == 1) {
		List_Append(&currentEmployee, employeesList);
	}
	fclose(fp);
}

void addEmployee(List* employeesList, Queue* Log) {
	clearScreen();

	printf("adding employee... please select an action\n");
	printf("0. return to main menu\n");
	printf("1. continue\n");

	int choice;
	do {
		printf(">>> ");
		scanf("%d", &choice);
		clearBuffer();
		if (choice < 0 || choice > 1) {
			printf("Please enter a select a valid choice number\n");
		}
	} while (choice < 0 || choice > 1);

	clearScreen();

	if (choice == 0) {
		return;
	}

	Employee employee;

	// gets new employee fields from user
	printf("Username (20 characters max): ");
	scanf("%s", &employee.username);
	clearBuffer();

	printf("Firstname (10 characters max): ");
	scanf("%s", &employee.firstname);
	clearBuffer();
	
	printf("Password (10 characters max): ");
	scanf("%s", &employee.password);
	clearBuffer();

	printf("Authorization level (integer between 1 to 3 -> 1 = admin, 2 = employee, 3 = trainee): ");
	scanf("%d", &employee.level);
	clearBuffer();

	// appends new user to the employees list if doesn't exist already
	Employee* foundEmployee = findEmployeeByUser(employee.username, employeesList);
	if (foundEmployee == NULL) {
		List_Append(&employee, employeesList);

		char* logMsg = (char*)malloc(70 * sizeof(char));
		sprintf(logMsg, "added an employee with user \"%s\"\n", employee.username);
		addToLog(logMsg, Log);
		free(logMsg);
	}
	else {
		clearScreen();
		printf("employee with such username already exists!\n");
		printf("press any key to continue...");
		_getch();
	}
	clearScreen();
}

void displayEmployees(List* employeesList) {
	clearScreen();
	printf("username     firstname     authorization\n");

	Node* currentEmployee = employeesList->head;
	while (currentEmployee != NULL) {
		printf("%-15s", currentEmployee->data->employee->username);
		printf("%-15s", currentEmployee->data->employee->firstname);
		printf("%-15d", currentEmployee->data->employee->level);
		printf("\n");
		currentEmployee = currentEmployee->next;
	}

	printf("\nPress any key to continue...");
	_getch();
	clearScreen();
}

void deleteEmployee(List* employeesList, Queue* Log) {
	clearScreen();

	printf("deleting employee... please select an action\n");
	printf("0. return to main menu\n");
	printf("1. continue\n");

	int choice;
	do {
		printf(">>> ");
		scanf("%d", &choice);
		clearBuffer();
		if (choice < 0 || choice > 1) {
			printf("Please enter a select a valid choice number\n");
		}
	} while (choice < 0 || choice > 1);

	clearScreen();

	if (choice == 0) {
		return;
	}

	// gets employee's username
	char username[10];
	printf("Employee to delete (username): ");
	scanf("%s", &username);
	clearBuffer();

	// finds and removes employee from employees list
	Employee* employee = findEmployeeByUser(username, employeesList);
	if (employee != NULL) {
		List_Delete(employee, employeesList);
		printf("successfully deleted employee: %s", username);

		char* logMsg = (char*)malloc(70 * sizeof(char));
		sprintf(logMsg, "deleted an employee with user \"%s\"\n", username);
		addToLog(logMsg, Log);
		free(logMsg);
	}
	else {
		printf("couldn't find employee! please try again");
	}

	printf("\npress any key to continue...");
	_getch();
	clearScreen();
}

void updateEmployeesFile(List* employeesList) {
	FILE* fp = fopen("employees.bin", "wb");
	if (!fp) return;

	Node* currentNode = employeesList->head;
	int currentCursorPosition = 0;

	while (currentNode != NULL) { 
		Employee* currentEmployee = currentNode->data->employee;

		fwrite(currentEmployee, sizeof(Employee), 1, fp);
		ensureEmployeesFileCursorPos(fp, &currentCursorPosition);

		currentNode = currentNode->next;
	}

	fclose(fp);
}

void ensureEmployeesFileCursorPos(FILE* fp, int* currentCursorPosition) {
	*currentCursorPosition += sizeof(Employee);
	fseek(fp, *currentCursorPosition, SEEK_SET);
}

Employee* findEmployeeByUser(char* username, List* employeesList) {
	Node* currentNode = employeesList->head;
	while (currentNode != NULL) {
		if (!strcmp(currentNode->data->employee->username, username))
			return currentNode->data->employee;
		currentNode = currentNode->next;
	}
	return NULL;
}