#include "../inc/libraries.h"

// general functions
bool checkIfCustomersFileExists(Queue* Log) {
	FILE* fp = fopen("build/customers.bin", "rb");
	if (!fp) {
		addToLog("customers file doesn't exist, created new customers file\n", Log);
		return false;
	}
	fclose(fp);
	return true;
}

void createNewCustomersFile() {
	FILE* fp = fopen("build/customers.bin", "wb");
	fclose(fp);
}

void loadCustomers(List* customersList) {
	FILE* fp = fopen("build/customers.bin", "rb");
	if (!fp) return;

	// reads all of the customers from the file and creates a list of items purchased for each customer
	Customer customer;
	int currentCursorPosition = 0;
	while (readCustomer(&customer, fp, &currentCursorPosition)) {
		List_Append(&customer, customersList);
	}
	fclose(fp);
}

void free_customer(Customer* customer) {
	if (customer->ItemsPurchased != NULL) {
		DestroyList(customer->ItemsPurchased);
		customer->ItemsPurchased = NULL;
	}
	if (customer->lastPurchaseItemsSerials != NULL) {
		free(customer->lastPurchaseItemsSerials);
		customer->lastPurchaseItemsSerials = NULL;
	}
}

bool readCustomer(Customer* customer ,FILE* fp, int* currentCursorPosition) {
	if (fread(customer->fullname, sizeof(customer->fullname), 1, fp) != 1) return false;
	if (fread(customer->joiningDate, sizeof(customer->joiningDate), 1, fp) != 1) return false;
	if (fread(&customer->totalMoneySpent, sizeof(customer->totalMoneySpent), 1, fp) != 1) return false;
	if (fread(customer->lastPurchaseDate, sizeof(customer->lastPurchaseDate), 1, fp) != 1) return false;
	if (fread(&customer->lastPurchaseItemsQuantity, sizeof(customer->lastPurchaseItemsQuantity), 1, fp) != 1) return false;
	if (fread(&customer->totalItemsPurchased, sizeof(customer->totalItemsPurchased), 1, fp) != 1) return false;

	*currentCursorPosition += sizeof(customer->fullname) + sizeof(customer->joiningDate) +
		sizeof(customer->totalMoneySpent) + sizeof(customer->lastPurchaseDate) +
		sizeof(customer->lastPurchaseItemsQuantity) + sizeof(customer->totalItemsPurchased);

	if (customer->totalItemsPurchased == 0) {
		customer->ItemsPurchased = NULL;
		customer->lastPurchaseItemsSerials = NULL;
	}
	else {
		customer->ItemsPurchased = List_Create("items");
		List* customerItemsList = customer->ItemsPurchased;

		Items item;
		// reads the items one by one from the file
		while (readItem(&item, fp, currentCursorPosition)) {
			List_Append(&item, customerItemsList);
		}
	
		int lastPurchaseItemsQuantity = customer->lastPurchaseItemsQuantity;
	
		customer->lastPurchaseItemsSerials = (int*)malloc(lastPurchaseItemsQuantity * sizeof(int));
		int* serialsArray = customer->lastPurchaseItemsSerials;
		initializeSerialsArr(serialsArray, lastPurchaseItemsQuantity, customer->ItemsPurchased);
	}
	return true;
}

void initializeSerialsArr(int* serialsArray, int len, List* customerItemsList) {
	Node* currentNode = customerItemsList->head;
	int totalNodes = List_Size(customerItemsList);

	// Ensure len does not exceed totalNodes
	if (len > totalNodes) {
		return;
	}

	// find the starting node for the last 'len' nodes
	currentNode = customerItemsList->head;
	for (int i = 0; i < totalNodes - len; i++) {
		currentNode = currentNode->next;
	}

	// extract serial numbers from the last 'len' nodes
	for (int i = 0; i < len; i++) {
		if (currentNode != NULL) {
			if (!strcmp(currentNode->data->items->itemType, "book")) {
				serialsArray[i] = currentNode->data->items->product->book->serialNumber;
			}
			else if (!strcmp(currentNode->data->items->itemType, "magazine")) {
				serialsArray[i] = currentNode->data->items->product->magazine->serialNumber;
			}
			else if (!strcmp(currentNode->data->items->itemType, "boardgame")) {
				serialsArray[i] = currentNode->data->items->product->boardgame->serialNumber;
			}
			currentNode = currentNode->next;
		}
	}
}

void updateCustomersFile(List* customersList) {
	FILE* fp = fopen("build/customers.bin", "wb");

	int currentCursorPosition = 0;
	Node* currentNode = customersList->head;

	while (currentNode != NULL) {
		Customer* currentCustomer = currentNode->data->customer;
		writeCustomer(currentCustomer, fp, &currentCursorPosition);
		currentNode = currentNode->next;
	}

	fclose(fp);
}

void writeCustomer(Customer* customer, FILE* fp, int* currentCursorPosition) {
	fwrite(customer->fullname, sizeof(customer->fullname), 1, fp);
	fwrite(customer->joiningDate, sizeof(customer->joiningDate), 1, fp);
	fwrite(&customer->totalMoneySpent, sizeof(customer->totalMoneySpent), 1, fp);
	fwrite(customer->lastPurchaseDate, sizeof(customer->lastPurchaseDate), 1, fp);
	fwrite(&customer->lastPurchaseItemsQuantity, sizeof(customer->lastPurchaseItemsQuantity), 1, fp);
	fwrite(&customer->totalItemsPurchased, sizeof(customer->totalItemsPurchased), 1, fp);

	*currentCursorPosition += sizeof(customer->fullname) + sizeof(customer->joiningDate) + 
		sizeof(customer->totalMoneySpent) + sizeof(customer->lastPurchaseDate) + 
		sizeof(customer->lastPurchaseItemsQuantity) + sizeof(customer->totalItemsPurchased);

	if (customer->totalItemsPurchased > 0) {
		Node* currentNode = customer->ItemsPurchased->head;

		while (currentNode != NULL) {
			Items* currentItem = currentNode->data->items;
			writeItem(currentItem, fp, currentCursorPosition);
			currentNode = currentNode->next;
		}
	}
	fseek(fp, *currentCursorPosition, SEEK_SET);
}

// menu interface functions
void displayCustomers(List* customersList) {
	clearScreen();

	printf("fullname       joining_date       total_items_bought       total_spent\n");
	printf("------------------------------------------------------------------------\n");

	Node* currentNode = customersList->head;
	while (currentNode != NULL) {
		printGeneralCustomerInfo(currentNode->data->customer);
		currentNode = currentNode->next;
	}

	printf("\npress any key to continue...");
	_getch();
	clearScreen();
}

void printGeneralCustomerInfo(Customer* customer) {
	printf("%-14s %-26s %-16d %-15.2f\n", customer->fullname, customer->joiningDate, customer->totalItemsPurchased, customer->totalMoneySpent);
}

void searchCustomer(List* customersList) {
	clearScreen();

	char input[20];
	printf("searching customer...\n");
	printf("full name: ");
	clearBuffer();
	scanf("%[^\n]", input);
	clearBuffer();

	Customer* foundCustomer = findCustomerByName(customersList, input);

	if (foundCustomer == NULL) {
		clearScreen();
		printf("no customer with such name! try again\n");
		printf("press any key to continue...");
		_getch();
		clearScreen();
		return;
	}
	clearScreen();

	printf("fullname       joining_date       total_items_bought       total_spent\n");
	printf("------------------------------------------------------------------------\n");
	printGeneralCustomerInfo(foundCustomer);

	displayItemsByCategory(foundCustomer->ItemsPurchased);

	printf("\n\n\npress any key to continue...");
	_getch();
	clearScreen();
}

void deleteCustomer(List* customersList, Queue* Log) {
	clearScreen();

	printf("deleting customer... please select an action\n");
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

	// gets customer's full name
	char fullname[20];
	printf("full name: ");
	scanf("%[^\n]", fullname);
	clearBuffer();
	clearScreen();

	//finds and removes the customer from the customers list
	Customer* foundCustomer = findCustomerByName(customersList, fullname);
	if (foundCustomer == NULL) {
		printf("no customer with such name!\n");
	}
	else {
		List_Delete(foundCustomer, customersList);
		printf("successfully deleted customer: %s\n", fullname);

		char* logMsg = (char*)malloc(70 * sizeof(char));
		sprintf(logMsg, "customer \"%s\" has been deleted\n", foundCustomer->fullname);
		addToLog(logMsg, Log);
		free(logMsg);
	}
	printf("press any key to continue...");
	_getch();
	clearScreen();
}

Customer* findCustomerByName(List* customersList, char* fullname) {
	Node* currentNode = customersList->head;
	while (currentNode != NULL) { 
		if (!strcmp(currentNode->data->customer->fullname, fullname)) {
			return currentNode->data->customer;
		}
		currentNode = currentNode->next;
	}
	return NULL;
}

void addCustomer(List* customersList, Queue* Log) {
	clearScreen();
	
	printf("adding customer... please select an action\n");
	printf("please select an action: \n");
	printf("0. return to main menu\n");
	printf("1. continue\n");

	int choice;
	do {
		printf(">>> ");
		scanf("%d", &choice);
		clearBuffer();
		if (choice < 0 || choice > 1)
			printf("Please enter a select a valid action between 0-1\n");
	} while (choice < 0 || choice > 1);
	clearScreen();

	if (choice == 0) {
		return;
	}
	
	createNewCustomer(customersList, Log);
}

Customer* createNewCustomer(List* customersList, Queue* Log) {
	Customer customer;

	printf("full name (max 40 characters): ");
	scanf("%[^\n]", customer.fullname);
	clearBuffer();

	printf("joining date (DD-MM-YYYY): ");
	scanf("%s", customer.joiningDate);
	clearBuffer();
	clearScreen();

	customer.ItemsPurchased = 0;
	customer.lastPurchaseItemsQuantity = 0;
	customer.totalItemsPurchased = 0;
	customer.lastPurchaseItemsSerials = NULL;
	customer.ItemsPurchased = NULL;
	customer.totalMoneySpent = 0;
	memset(customer.lastPurchaseDate, 0, sizeof(customer.lastPurchaseDate));
	
	// checks if customer already exists
	Customer* foundCustomer = findCustomerByName(customersList, customer.fullname);

	if (foundCustomer == NULL) {
		List_Append(&customer, customersList);

		char* logMsg = (char*)malloc(70 * sizeof(char));
		sprintf(logMsg, "customer \"%s\" has been added\n", customer.fullname);
		addToLog(logMsg, Log);
		free(logMsg);
	}
	else {
		printf("customer with the same name already exists!\n");
		printf("press any key to continue...");
		_getch();
		clearScreen();
	}

	// returns the address of the created customer
	if (foundCustomer == NULL)
		return findCustomerByName(customersList, customer.fullname);
	else
		return foundCustomer;
}