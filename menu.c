#include "libraries.h"

void showMenu(unsigned int employeeLevel, List* employeesList, List* customersList, List* itemsList, Queue* Log) {
	List* shoppingCart = List_Create("items");
	
	int inPurchaseFlag = 0;
	int choice;
	do {
		// menu selection section
		switch (employeeLevel) {
			case 1:
				showManagerMenu();
				break;
			case 2:
				showEmployeeMenu();
				break;
			case 3:
				showTraineeMenu();
				break;
			default:
				printf("Unexpected employee level: %d\n", employeeLevel);
				return;
		}

		// actions section
		choice = getValidChoice();

		switch (choice) {
			case 0:
				exitProgram(employeesList, customersList, itemsList, Log);
				break;
			case 1:
				addCustomer(customersList, Log);
				break;
			case 2:
				displayCustomers(customersList);
				break;									
			case 3:
				searchCustomer(customersList);
				break;
			case 4:
				searchItem(itemsList, inPurchaseFlag, Log);
				break;
			case 5:
				addItem(itemsList, Log);
				break;
			case 6:
				displayInventory(itemsList);
				break;
			case 7:
				if (employeeLevel < 3) {	// modified here
					returnItem(itemsList, customersList, Log);
					break;
				}
			case 8 :
				if (employeeLevel < 3) {
					initiatePurchase(employeesList, customersList, itemsList, shoppingCart, Log);
					break;
				}
			case 9:
				if (employeeLevel < 3) {
					modifyItem(itemsList, Log);
					break;
				}
			case 10:
				if (employeeLevel < 3) {
					deleteItem(itemsList, Log);
					break;
				}
			case 11:
				if (employeeLevel < 3) {
					deleteCustomer(customersList, Log);
					break;
				}
			case 12:
				if (employeeLevel < 2) {
					addEmployee(employeesList, Log);
					break;
				}
			case 13:
				if (employeeLevel < 2) {
					displayEmployees(employeesList);
					break;
				}
			case 14:
				if (employeeLevel < 2) {
					deleteEmployee(employeesList, Log);
					break;
				}
			default:
				printf("Choice beyond limits! Please select a number within the range\n");
				printf("Press any key to continue...\n");
				_getch();
				clearScreen();
				break;
		}
	} while (choice != 0);
}

int getValidChoice() {
	int choice;
	printf(">>> ");
	while (scanf("%d", &choice) != 1) {
		printf("Invalid input! Please enter a number\n");
		printf(">>> ");
		clearBuffer();
	}
	return choice;
}

void showManagerMenu() {
	showEmployeeMenu();
	printf("12. Add employee\n");
	printf("13. Display employees\n");
	printf("14. Delete employee\n");
}

void showEmployeeMenu() {
	showTraineeMenu();
	printf("7. Return item\n");
	printf("8. Initiate purchase\n");
	printf("9. Modify item\n");
	printf("10. Delete item\n");
	printf("11. Delete customer\n");
}

void showTraineeMenu() {
	printf("*** Please select an action: ***\n");
	printf("0. Exit\n");
	printf("1. Add customer\n");
	printf("2. Display customers\n");
	printf("3. Search customer\n");
	printf("4. Search item\n");
	printf("5. Add item\n");
	printf("6. Display inventory\n");
}

void updateFiles(List* employeesList, List* customersList, List* itemsList, Queue* Log) {
	updateEmployeesFile(employeesList);
	updateCustomersFile(customersList);
	updateItemsFile(itemsList);
	updateLogFile(Log);
}

void exitProgram(List* employeesList, List* customersList, List* itemsList, Queue* Log) {
	clearScreen();

	addToLog("user has logged out, session ended\n", Log);
	updateFiles(employeesList, customersList, itemsList, Log);
	
	printf("Goodbye! See you next time!\n");
	Sleep(3500);
}

void initiatePurchase(List* employeesList, List* customersList, List* itemsList,List* shoppingCart, Queue* Log) {
	int choice;
	int inPurchaseFlag = 1;

	addToLog("started a new purchase\n", Log);
	clearScreen();

	printf("starting a new purchase...\n");
	do {
		printf("0. cancel purchase and return to menu\n");
		printf("1. continue\n");
		printf(">>> ");
		scanf("%d", &choice);
		clearBuffer();
		if (choice < 0 || choice > 1) {
			clearScreen();
			printf("please enter a valid choice!\n");
			printf("press any key to continue\n");
			_getch();
		}
		clearScreen();
	} while (choice < 0 || choice > 1);

	if (choice == 0) {
		addToLog("canceled purchase\n", Log);
		return;
	}

	int checkoutFlag = 0;
	do {
		printf("0. cancel purchase and return to menu\n");
		printf("1. add item to shopping cart\n");
		printf("2. remove item from shopping cart\n");
		printf("3. display shopping cart\n");
		printf("4. checkout\n");
		printf(">>> ");
		scanf("%d", &choice);
		clearBuffer();
		if (choice < 0 || choice > 4) {
			clearScreen();
			printf("please enter a valid choice!\n");
			printf("press any key to continue\n");
			_getch();
		}
		clearScreen();

		switch (choice) {
		case 0:
			cancelPurchase(shoppingCart, itemsList);		//done
			addToLog("canceled purchase\n", Log);
			break;
		case 1:
			addItemToCart(shoppingCart, itemsList, inPurchaseFlag, Log);		// done
			break;
		case 2:
			removeItemFromCart(shoppingCart, itemsList, Log);	// done
			break;
		case 3:
			displayCart(shoppingCart);			// done
			break;
		case 4:
			checkoutFlag = checkout(shoppingCart, customersList, Log);
			break;
		default:
			break;
		}
	} while (choice > 0 && choice < 5 && !checkoutFlag);
}