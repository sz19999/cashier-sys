#include "libraries.h"

/************************************* item input functions ******************************************/

char* getBookFields(Book* book, List* itemsList) {
    int serialNumber = getNewSerialNumber(itemsList);
    book->serialNumber = serialNumber;
    
    printf("Book name: ");
    scanf("%[^\n]", book->name);
    clearBuffer();

    printf("Author: ");
    scanf("%[^\n]", book->author);
    clearBuffer();

    printf("Release date (format: DD-MM-YYYY): ");
    scanf("%s", book->releaseDate);
    clearBuffer();

    printf("Price: ");
    scanf("%f", &book->price);
    clearBuffer();

    int flag;
    printf("BestSeller (1 for true, 0 for false): ");
    scanf("%d", &flag);
    clearBuffer();
    book->bestSeller = (flag ? true : false);

    printf("Stock: ");
    scanf("%d", &book->stock);
    clearBuffer();

    printf("Number of pages: ");
    scanf("%d", &book->numOfPages);
    clearBuffer();

    printf("Volume: ");
    scanf("%d", &book->volume);
    clearBuffer();

    printf("Genre: ");
    scanf("%s", book->genre);
    clearBuffer();

    return book->name;
}

char* getMagazineFields(Magazine* magazine, List* itemsList) {
    int serialNumber = getNewSerialNumber(itemsList);
    magazine->serialNumber = serialNumber;

    printf("Magazine name: ");
    scanf("%[^\n]", magazine->name);
    clearBuffer();

    printf("Publisher: ");
    scanf("%[^\n]", magazine->publisher);
    clearBuffer();

    printf("Release date (format: DD-MM-YYYY): ");
    scanf("%s", magazine->releaseDate);
    clearBuffer();

    printf("Price: ");
    scanf("%f", &magazine->price);
    clearBuffer();

    int flag;
    printf("BestSeller (1 for true, 0 for false): ");
    scanf("%d", &flag);
    clearBuffer();
    magazine->bestSeller = (flag ? true : false);

    printf("Stock: ");
    scanf("%d", &magazine->stock);
    clearBuffer();

    printf("Magazine type: ");
    scanf("%s", magazine->type);
    clearBuffer();

    return magazine->name;
}

char* getBoardgameFields(Boardgame* boardgame, List* itemsList) {
    int serialNumber = getNewSerialNumber(itemsList);
    boardgame->serialNumber = serialNumber;

    printf("Boardgame name: ");
    scanf("%[^\n]", boardgame->name);
    clearBuffer();

    printf("Manufacturer: ");
    scanf("%[^\n]", boardgame->manufacturer);
    clearBuffer();

    printf("Release date (format: DD-MM-YYYY): ");
    scanf("%s", boardgame->releaseDate);
    clearBuffer();

    printf("Price: ");
    scanf("%f", &boardgame->price);
    clearBuffer();

    int flag;
    printf("BestSeller (1 for true, 0 for false): ");
    scanf("%d", &flag);
    clearBuffer();
    boardgame->bestSeller = (flag ? true : false);

    printf("Stock: ");
    scanf("%d", &boardgame->stock);
    clearBuffer();

    printf("Minimum age: ");
    scanf("%d", &boardgame->minAge);
    clearBuffer();

    printf("Number of participants: ");
    scanf("%d", &boardgame->participants);
    clearBuffer();

    return boardgame->name;
}

char* getItemFields(Items* item, List* itemsList) {
    if (!strcmp(item->itemType, "book")) {
        item->product->book = (Book*)malloc(sizeof(Book));
        Book* book = item->product->book;
        return getBookFields(book, itemsList);
    }
    else if (!strcmp(item->itemType, "magazine")) {
        item->product->magazine = (Magazine*)malloc(sizeof(Magazine));
        Magazine* magazine = item->product->magazine;
        return getMagazineFields(magazine, itemsList);
    }
    else if (!strcmp(item->itemType, "boardgame")) {
        item->product->boardgame = (Boardgame*)malloc(sizeof(Boardgame));
        Boardgame* boardgame = item->product->boardgame;
        return getBoardgameFields(boardgame, itemsList);
    }
    return NULL;
}

int getNewSerialNumber(List* itemsList) {
    if (List_IsEmpty(itemsList)) {
        return 1;
    }

    char itemType[10];
    strcpy(itemType, itemsList->tail->data->items->itemType);

    if (!strcmp(itemType, "book"))
        return itemsList->tail->data->items->product->book->serialNumber + 1;
    else if (!strcmp(itemType, "magazine"))
        return itemsList->tail->data->items->product->magazine->serialNumber + 1;
    else if (!strcmp(itemType, "boardgame"))
        return itemsList->tail->data->items->product->boardgame->serialNumber + 1;

    return -1;
}

/************************************* end of item input functions ***************************************/





/************************************* search functions ******************************************/

void searchItem(List* itemsList, int inPurchaseFlag, Queue* Log) {
    clearScreen();
    
    if (List_IsEmpty(itemsList)) {
        printf("items list is empty!\n");
        printf("press any key to continue...");
        _getch();
        return;
    }

    printf("search item, please select an action: \n");     // add later a search func that uses two text fields
    printf("0. return to main menu\n");
    printf("1. search by name\n");
    printf("2. search by date\n");
    printf("3. search by serial number\n");
    printf("4. search by stock\n");
    printf("5. search by bestseller status\n");
    printf("6. search by price\n");
    printf("7. search by product type\n");
    printf("8. search both by type and date\n");

    int choice;
    do {
        printf(">>> ");
        scanf("%d", &choice);
        clearBuffer();
        if (choice < 0 || choice > 8)
            printf("Please enter a select a valid action between 0-1\n");
    } while (choice < 0 || choice > 8);
    clearScreen();

    if (choice == 0) {
        return;
    }

    switch (choice) {
        case 1:
            searchItemByName(itemsList);
            break;
        case 2:
            searchItemByDate(itemsList);
            break;
        case 3:
            searchItemBySerial(itemsList);
            break;
        case 4:
            searchItemByStock(itemsList);
            break;
        case 5:
            searchItemByBestSellerStatus(itemsList);
            break;
        case 6:
            searchItemByPrice(itemsList);
            break;
        case 7:
            searchByProductType(itemsList);
            break;
        case 8:
            searchBothByProductTypeAndDate(itemsList);
            break;
        default:
            break;
    }

    if (inPurchaseFlag == 0) {
        // allows the user to modify items if he wants to
        printf("\nplease select an action\n");
        printf("0. return to main menu\n");
        printf("1. modify an item\n");

        do {
            printf(">>> ");
            scanf("%d", &choice);
            clearBuffer();
            if (choice < 0 || choice > 1)
                printf("Please enter a select a valid action between 0-1\n");
        } while (choice < 0 || choice > 1);

        if (choice == 0) {
            clearScreen();
            return;
        }

        modifyItem(itemsList, Log);
    }
}

// name
Items* findItemByName(char* itemName, List* itemsList) {
    Node* currentNode = itemsList->head;
    
    while (currentNode != NULL) {
        char currentItemType[10];
        strcpy(currentItemType, currentNode->data->items->itemType);

        if (!strcmp(currentItemType, "book") && !strcmp(currentNode->data->items->product->book->name, itemName))
            return currentNode->data->items;
        else if (!strcmp(currentItemType, "magazine") && !strcmp(currentNode->data->items->product->magazine->name, itemName))
            return currentNode->data->items;
        else if (!strcmp(currentItemType, "boardgame") && !strcmp(currentNode->data->items->product->boardgame->name, itemName))
            return currentNode->data->items;

        currentNode = currentNode->next;
    }

    return NULL;
}

void searchItemByName(List* itemsList) {
    char itemName[30];

    printf("item name: ");
    scanf("%[^\n]", itemName);
    clearBuffer();

    Items* foundItem = findItemByName(itemName, itemsList);

    if (foundItem != NULL) {
        clearScreen();
        printf("serial    name                           type        stock       price       date\n");
        printf("--------------------------------------------------------------------------------------\n");
        printItem(foundItem);
    }
    else {
        printf("there's no item with such name! try again\n");
    }
}

// serial
Items* findItemBySerial(int serialNumber, List* itemsList) {
    Node* currentNode = itemsList->head;

    while (currentNode != NULL) {
        Items* currentItem = currentNode->data->items;

        if (!strcmp(currentItem->itemType, "book")) {
            if (currentItem->product->book->serialNumber == serialNumber) {
                return currentItem;
            }
        }
        else if (!strcmp(currentItem->itemType, "magazine")) {
            if (currentItem->product->magazine->serialNumber == serialNumber) {
                return currentItem;
            }
        }
        else if (!strcmp(currentItem->itemType, "boardgame")) {
            if (currentItem->product->boardgame->serialNumber == serialNumber) {
                return currentItem;
            }
        }
        currentNode = currentNode->next;
    }

    return NULL;
}

void searchItemBySerial(List* itemsList) {
    int serialNumber;

    printf("searching item by serial number...\n");
    printf("serial number: ");
    scanf("%d", &serialNumber);
    clearBuffer();

    Items* foundItem = findItemBySerial(serialNumber, itemsList);

    if (foundItem != NULL) {
        clearScreen();
        printf("serial    name                           type        stock       price       date\n");
        printf("--------------------------------------------------------------------------------------\n");
        printItem(foundItem);
    }
    else {
        printf("there's no item with such name! try again\n");
    }

    printf("press any key to continue...");
    _getch();
    clearScreen();
}

// date
Items* findItemByDate(char* itemDate, List* itemsList) {
    Node* currentNode = itemsList->head;

    while (currentNode != NULL) {
        char currentItemType[10];
        strcpy(currentItemType, currentNode->data->items->itemType);

        if (!strcmp(currentItemType, "book") && !strcmp(currentNode->data->items->product->book->releaseDate, itemDate))
            return currentNode->data->items;
        else if (!strcmp(currentItemType, "magazine") && !strcmp(currentNode->data->items->product->magazine->releaseDate, itemDate))
            return currentNode->data->items;
        else if (!strcmp(currentItemType, "boardgame") && !strcmp(currentNode->data->items->product->boardgame->releaseDate, itemDate))
            return currentNode->data->items;

        currentNode = currentNode->next;
    }

    return NULL;
}

void searchItemByDate(List* itemsList) {
    printf("searching item by date... \n");     // add later a search func that uses two text fields
    printf("1. search items after a date\n");
    printf("2. search items before a date\n");
    printf("3. search items between dates\n");

    int choice;
    do {
        printf(">>> ");
        scanf("%d", &choice);
        clearBuffer();
        if (choice < 1 || choice > 3)
            printf("Please enter a select a valid action between 0-3\n");
    } while (choice < 1 || choice > 3);

    clearScreen();

    switch (choice) {
        case 1:
            searchItemsAfterDate(itemsList);
            break;
        case 2:
            searchItemsBeforeDate(itemsList);
            break;
        case 3:
            searchItemsBetweenDates(itemsList);
            break;
        default:
            break;
    }
}

void searchItemsAfterDate(List* itemsList) {
    char itemDate[11];
    printf("date (DD-MM-YYYY): ");
    scanf("%s", itemDate);
    clearBuffer();

    clearScreen();
    printf("serial    name                           type        stock       price       date\n");
    printf("--------------------------------------------------------------------------------------\n");

    Node* currentNode = itemsList->head;

    while (currentNode != NULL) {
        Items* currentItem = currentNode->data->items;
        char* releaseDate = NULL;
        
        releaseDate = getItemReleaseDate(currentItem);

        if (compareDates(releaseDate, itemDate) > 0) {
            printItem(currentItem);
        }

        currentNode = currentNode->next;
    }
}

void searchItemsBeforeDate(List* itemsList) {
    char itemDate[11];
    printf("date (DD-MM-YYYY): ");
    scanf("%s", itemDate);
    clearBuffer();

    clearScreen();
    printf("serial    name                           type        stock       price       date\n");
    printf("--------------------------------------------------------------------------------------\n");

    Node* currentNode = itemsList->head;

    while (currentNode != NULL) {
        Items* currentItem = currentNode->data->items;
        char* releaseDate = NULL;

        releaseDate = getItemReleaseDate(currentItem);

        if (compareDates(releaseDate, itemDate) < 0) {
            printItem(currentItem);
        }

        currentNode = currentNode->next;
    }
}

void searchItemsBetweenDates(List* itemsList) {
    char itemDate1[11];
    char itemDate2[11];

    printf("date1 (DD-MM-YYYY): ");
    scanf("%s", itemDate1);
    clearBuffer();

    printf("date2 (DD-MM-YYYY): ");
    scanf("%s", itemDate2);
    clearBuffer();

    clearScreen();
    printf("serial    name                           type        stock       price       date\n");
    printf("--------------------------------------------------------------------------------------\n");

    Node* currentNode = itemsList->head;

    while (currentNode != NULL) {
        Items* currentItem = currentNode->data->items;
        char* releaseDate = NULL;

        releaseDate = getItemReleaseDate(currentItem);

        if (compareDates(releaseDate, itemDate1) > 0 && compareDates(releaseDate, itemDate2) < 0) {
            printItem(currentItem);
        }

        currentNode = currentNode->next;
    }
}

char* getItemReleaseDate(Items* item) {
    char* releaseDate = NULL;

    if (!strcmp(item->itemType, "book")) {
        releaseDate = item->product->book->releaseDate;
    }
    else if (!strcmp(item->itemType, "magazine")) {
        releaseDate = item->product->magazine->releaseDate;
    }
    else if (!strcmp(item->itemType, "boardgame")) {
        releaseDate = item->product->boardgame->releaseDate;
    }

    return releaseDate;
}

int compareDates(char* date1, char* date2) {
    int day1, month1, year1;
    int day2, month2, year2;

    // Parse the dates into day, month, and year
    sscanf(date1, "%02d-%02d-%04d", &day1, &month1, &year1);
    sscanf(date2, "%02d-%02d-%04d", &day2, &month2, &year2);

    if (year1 != year2) {
        return (year1 > year2) ? 1 : -1;
    }

    if (month1 != month2) {
        return (month1 > month2) ? 1 : -1;
    }

    return (day1 > day2) ? 1 : (day1 < day2) ? -1 : 0;
}

// stock
void searchItemByStock(List* itemsList) {
    printf("searching item by stock...\n");
    printf("1. items above specified stock\n");
    printf("2. items under specified stock\n");

    int choice;
    do {
        printf(">>> ");
        scanf("%d", &choice);
        clearBuffer();
        if (choice < 1 || choice > 2)
            printf("Please enter a select a valid action between 0-3\n");
    } while (choice < 1 || choice > 2);

    clearScreen();

    switch (choice) {
    case 1:
        searchItemsAboveOrEqualStock(itemsList);
        break;
    case 2:
        searchItemsBelowStock(itemsList);
        break;
    default:
        break;
    }
}

void searchItemsBelowStock(List* itemsList) {
    int stock;
    printf("searching items below stock...\n");
    printf("stock: ");
    scanf("%d", &stock);
    clearBuffer();

    clearScreen();
    printf("serial    name                           type        stock       price       date\n");
    printf("--------------------------------------------------------------------------------------\n");

    Node* currentNode = itemsList->head;

    while (currentNode != NULL) {
        Items* currentItem = currentNode->data->items;
        int ItemStock = getItemStock(currentItem);

        if (ItemStock < stock) {
            printItem(currentItem);
        }

        currentNode = currentNode->next;
    }
}

void searchItemsAboveOrEqualStock(List* itemsList) {
    int stock;
    printf("searching items below stock...\n");
    printf("stock: ");
    scanf("%d", &stock);
    clearBuffer();

    clearScreen();
    printf("serial    name                           type        stock       price       date\n");
    printf("--------------------------------------------------------------------------------------\n");

    Node* currentNode = itemsList->head;

    while (currentNode != NULL) {
        Items* currentItem = currentNode->data->items;
        int ItemStock = getItemStock(currentItem);

        if (ItemStock >= stock) {
            printItem(currentItem);
        }

        currentNode = currentNode->next;
    }
}

int getItemStock(Items* item) {
    if (!strcmp(item->itemType, "book")) {
        return item->product->book->stock;
    }
    else if (!strcmp(item->itemType, "magazine")) {
        return item->product->magazine->stock;
    }
    else if (!strcmp(item->itemType, "boardgame")) {
        return item->product->boardgame->stock;
    }
}

// bestseller
void searchItemByBestSellerStatus(List* itemsList) {
    int bestseller;
    printf("searching item by bestseller status...\n");
    printf("bestseller? (1 = yes, 0 = no): ");
    scanf("%d", &bestseller);
    clearBuffer();
    bestseller = (bestseller != 0);

    clearScreen();
    printf("serial    name                           type        stock       price       date\n");
    printf("--------------------------------------------------------------------------------------\n");

    Node* currentNode = itemsList->head;

    while (currentNode != NULL) {
        Items* currentItem = currentNode->data->items;
        bool itemBestseller = getItemBestsellerStat(currentItem);

        if (itemBestseller == bestseller) {
            printItem(currentItem);
        }

        currentNode = currentNode->next;
    }
}

bool getItemBestsellerStat(Items* item) {
    if (!strcmp(item->itemType, "book")) {
        return item->product->book->bestSeller;
    }
    else if (!strcmp(item->itemType, "magazine")) {
        return item->product->magazine->bestSeller;
    }
    else if (!strcmp(item->itemType, "boardgame")) {
        return item->product->boardgame->bestSeller;
    }
}

// price
void searchItemByPrice(List* itemsList) {
    printf("searching item by price...\n");
    printf("1. items above specified price\n");
    printf("2. items under specified price\n");

    int choice;
    do {
        printf(">>> ");
        scanf("%d", &choice);
        clearBuffer();
        if (choice < 1 || choice > 2)
            printf("Please enter a select a valid action between 0-3\n");
    } while (choice < 1 || choice > 2);

    clearScreen();

    switch (choice) {
    case 1:
        searchItemsAboveOrEqualPrice(itemsList);
        break;
    case 2:
        searchItemsBelowPrice(itemsList);
        break;
    default:
        break;
    }
}

void searchItemsAboveOrEqualPrice(List *itemsList) {
    float price;
    printf("searching items above price...\n");
    printf("price: ");
    scanf("%f", &price);
    clearBuffer();

    clearScreen();
    printf("serial    name                           type        stock       price       date\n");
    printf("--------------------------------------------------------------------------------------\n");

    Node* currentNode = itemsList->head;

    while (currentNode != NULL) {
        Items* currentItem = currentNode->data->items;
        float ItemPrice = getItemPrice(currentItem);

        if (ItemPrice >= price) {
            printItem(currentItem);
        }

        currentNode = currentNode->next;
    }
}

void searchItemsBelowPrice(List* itemsList) {
    float price;
    printf("searching items below price...\n");
    printf("price: ");
    scanf("%f", &price);
    clearBuffer();

    clearScreen();
    printf("serial    name                           type        stock       price       date\n");
    printf("--------------------------------------------------------------------------------------\n");

    Node* currentNode = itemsList->head;

    while (currentNode != NULL) {
        Items* currentItem = currentNode->data->items;
        float ItemPrice = getItemPrice(currentItem);

        if (ItemPrice < price) {
            printItem(currentItem);
        }

        currentNode = currentNode->next;
    }
}

float getItemPrice(Items* item) {
    if (!strcmp(item->itemType, "book")) {
        return item->product->book->price;
    }
    else if (!strcmp(item->itemType, "magazine")) {
        return item->product->magazine->price;
    }
    else if (!strcmp(item->itemType, "boardgame")) {
        return item->product->boardgame->price;
    }
}

// type
void searchByProductType(List* itemsList) {
    char itemType[10];
    printf("searching by product type...\n");
    printf("type (book/magazine/boardgame): ");
    scanf("%s", itemType);
    clearBuffer();

    while (strcmp(itemType, "book") && strcmp(itemType, "magazine") && strcmp(itemType, "boardgame")) {
        printf("\nError! Wrong item entered! please enter (book/magazine/boardgame): ");
        scanf("%s", itemType);
        clearBuffer();
        clearScreen();
    }
    clearScreen();

    printf("serial    name                           type        stock       price       date\n");
    printf("--------------------------------------------------------------------------------------\n");

    Node* currentNode = itemsList->head;

    while (currentNode != NULL) {
        Items* currentItem = currentNode->data->items;

        if (!strcmp(itemType, currentItem->itemType)) {
            printItem(currentItem);
        }

        currentNode = currentNode->next;
    }
}

// type + date
void searchBothByProductTypeAndDate(List* itemsList) {
    char itemType[10];
    printf("searching by product type and date...\n");
    printf("type (book/magazine/boardgame): ");
    scanf("%s", itemType);
    clearBuffer();

    while (strcmp(itemType, "book") && strcmp(itemType, "magazine") && strcmp(itemType, "boardgame")) {
        printf("\nError! Wrong item entered! please enter (book/magazine/boardgame): ");
        scanf("%s", itemType);
        clearBuffer();
        clearScreen();
    }
    clearScreen();

    printf("1. search items after a date\n");
    printf("2. search items before a date\n");
    printf("3. search items between dates\n");

    int choice;
    do {
        printf(">>> ");
        scanf("%d", &choice);
        clearBuffer();
        if (choice < 1 || choice > 3)
            printf("Please enter a select a valid action between 0-3\n");
    } while (choice < 1 || choice > 3);

    clearScreen();

    switch (choice) {
    case 1:
        searchItemsWithGivenTypeAfterDate(itemsList, itemType);
        break;
    case 2:
        searchItemsWithGivenTypeBeforeDate(itemsList, itemType);
        break;
    case 3:
        searchItemsWithGivenTypeBetweenDates(itemsList, itemType);
        break;
    default:
        break;
    }
}

void searchItemsWithGivenTypeAfterDate(List* itemsList, char* itemType) {
    char itemDate[11];
    printf("date (DD-MM-YYYY): ");
    scanf("%s", itemDate);
    clearBuffer();

    clearScreen();
    printf("serial    name                           type        stock       price       date\n");
    printf("--------------------------------------------------------------------------------------\n");

    Node* currentNode = itemsList->head;

    while (currentNode != NULL) {
        Items* currentItem = currentNode->data->items;
        char* releaseDate = NULL;

        releaseDate = getItemReleaseDate(currentItem);

        if (!strcmp(currentItem->itemType, itemType) && compareDates(releaseDate, itemDate) > 0) {
            printItem(currentItem);
        }

        currentNode = currentNode->next;
    }
}

void searchItemsWithGivenTypeBeforeDate(List* itemsList, char* itemType) {
    char itemDate[11];
    printf("date (DD-MM-YYYY): ");
    scanf("%s", itemDate);
    clearBuffer();

    clearScreen();
    printf("serial    name                           type        stock       price       date\n");
    printf("--------------------------------------------------------------------------------------\n");

    Node* currentNode = itemsList->head;

    while (currentNode != NULL) {
        Items* currentItem = currentNode->data->items;
        char* releaseDate = NULL;

        releaseDate = getItemReleaseDate(currentItem);

        if (!strcmp(currentItem->itemType, itemType) && compareDates(releaseDate, itemDate) < 0) {
            printItem(currentItem);
        }

        currentNode = currentNode->next;
    }
}

void searchItemsWithGivenTypeBetweenDates(List* itemsList, char* itemType) {
    char itemDate1[11];
    char itemDate2[11];

    printf("date1 (DD-MM-YYYY): ");
    scanf("%s", itemDate1);
    clearBuffer();

    printf("date2 (DD-MM-YYYY): ");
    scanf("%s", itemDate2);
    clearBuffer();

    clearScreen();
    printf("serial    name                           type        stock       price       date\n");
    printf("--------------------------------------------------------------------------------------\n");

    Node* currentNode = itemsList->head;

    while (currentNode != NULL) {
        Items* currentItem = currentNode->data->items;
        char* releaseDate = NULL;

        releaseDate = getItemReleaseDate(currentItem);

        if (!strcmp(currentItem->itemType, itemType) && compareDates(releaseDate, itemDate1) > 0 && compareDates(releaseDate, itemDate2) < 0) {
            printItem(currentItem);
        }

        currentNode = currentNode->next;
    }
}

/************************************* end of search functions ***********************************/





/************************************* file functions ******************************************/

bool readItem(Items* item, FILE* fp, int* currentCursorPosition) {

    // reads the item's type from the file
    if (fread(item->itemType, sizeof(item->itemType), 1, fp) != 1) return false;
    
    // if the item type is of a valid type then do
    if (!strcmp(item->itemType, "book") || !strcmp(item->itemType, "boardgame") || !strcmp(item->itemType, "magazine")) {
        *currentCursorPosition += sizeof(item->itemType);
        item->product = (Product*)malloc(sizeof(Product));
    
        // reads the item itself according to its type
        if (!strcmp(item->itemType, "book")) {
            item->product->book = (Book*)malloc(sizeof(Book));
            if (fread(item->product->book, sizeof(Book), 1, fp) != 1) return false;
            *currentCursorPosition += sizeof(Book);
        }
        else if (!strcmp(item->itemType, "magazine")) {
            item->product->magazine = (Magazine*)malloc(sizeof(Magazine));
            if (fread(item->product->magazine, sizeof(Magazine), 1, fp) != 1) return false;
            *currentCursorPosition += sizeof(Magazine);
        }
        else if (!strcmp(item->itemType, "boardgame")) {
            item->product->boardgame = (Boardgame*)malloc(sizeof(Boardgame));
            if (fread(item->product->boardgame, sizeof(Boardgame), 1, fp) != 1) return false;
            *currentCursorPosition += sizeof(Boardgame);
        }

        fseek(fp, *currentCursorPosition, SEEK_SET);
        return true;
    }

  fseek(fp, *currentCursorPosition, SEEK_SET);
  return false;
}

void writeItem(Items* item, FILE* itemsFile, int* currentCursorPosition) {
    // writes the type of the product
    fwrite(item->itemType, sizeof(item->itemType), 1, itemsFile);
    *currentCursorPosition += sizeof(item->itemType);

    // writes the item itself according to its type
    if (!strcmp(item->itemType, "book")) {
        fwrite(item->product->book, sizeof(Book), 1, itemsFile);
        *currentCursorPosition += sizeof(Book);
    }
    else if (!strcmp(item->itemType, "magazine")) {
        fwrite(item->product->magazine, sizeof(Magazine), 1, itemsFile);
        *currentCursorPosition += sizeof(Magazine);
    }
    else if (!strcmp(item->itemType, "boardgame")) {
        fwrite(item->product->boardgame, sizeof(Boardgame), 1, itemsFile);
        *currentCursorPosition += sizeof(Boardgame);
    }
    fseek(itemsFile, *currentCursorPosition, SEEK_SET);
}

bool checkIfItemsFileExists(Queue* Log) {
    FILE* fp = fopen("items.bin", "rb");

    if (!fp) { 
        addToLog("items file doesn't exist, created new items file\n", Log);
        return false;   
    }
    else {
        fclose(fp);
        return true;
    }
}

void createNewItemsFile() {
    FILE* fp = fopen("items.bin", "wb");
    fclose(fp);
}

void loadItems(List* itemsList) {
    FILE* fp = fopen("items.bin", "rb");
    if (!fp) return;

    int currentCursorPosition = 0;
    Items item;
    // reads the items one by one from the file
    while (readItem(&item, fp, &currentCursorPosition)) {
        List_Append(&item, itemsList);
        free_product(item.product, itemsList->head->data->items->itemType);
    }
    fclose(fp);
}

void updateItemsFile(List* itemsList) {
    FILE* fp = fopen("items.bin", "wb");
    
    int currentCursorPosition = 0;
    Node* currentNode = itemsList->head;

    while (currentNode != NULL) {
        Items* currentItem = currentNode->data->items;
        writeItem(currentItem, fp, &currentCursorPosition);
        currentNode = currentNode->next;
    }

    fclose(fp);
}

/************************************* end of file functions ***********************************/






/************************************* shopping cart functions ***********************************/

void addItemToCart(List* shoppingCart, List* itemsList, int inPurchaseFlag, Queue* Log) {
    clearScreen();

    int choice;
    do {
        if (List_Size(shoppingCart) == 3) {
            printf("reached maximum cart capacity (3 items max)\n");
            printf("press any key to continue...");
            _getch();
            clearScreen();
            return;
        }
    
        printf("adding item to cart...\n");
        printf("0. return to purchase\n");
        printf("1. search item\n");
        printf("2. add item to shopping cart\n");
    
        do {
            printf(">>> ");
            scanf("%d", &choice);
            clearBuffer();
            if (choice < 0 || choice > 2)
                printf("Please enter a select a valid action between 0-2\n");
        } while (choice < 0 || choice > 2);
        clearScreen();

        switch (choice) {
            case 0:
                return;
                break;
            case 1:
                searchItem(itemsList, inPurchaseFlag, Log);
                break;
            case 2:
                addItemToCartByName(shoppingCart, itemsList, Log);
                break;
            default:
                break;
        }
        printf("\n");
    } while (choice > 0 && choice < 3);

    clearScreen();
}

void addItemToCartByName(List* shoppingCart, List* itemsList, Queue* Log) {
    char itemName[30];
    printf("enter item name: ");
    scanf("%[^\n]", itemName);
    clearBuffer();
    clearScreen();

    Items* foundItem = findItemByName(itemName, itemsList);

    // checks if item exists and is available
    if (foundItem != NULL && itemIsAvailable(itemName, itemsList)) {
        decrementStock(foundItem);
        List_Append(foundItem, shoppingCart);

        printf("added item to cart successfully\n");
        printf("press any key to continue...");
        _getch();
        clearScreen();

        char* logMsg = (char*)malloc(70 * sizeof(char));
        sprintf(logMsg, "item \"%s\" has been added to cart\n", itemName);
        addToLog(logMsg, Log);
        free(logMsg);
    }
    else if (foundItem != NULL && !itemIsAvailable(itemName, itemsList)) {
        printf("item out of stock!\n");
        printf("press any key to continue...");
        _getch();
    }
    else if (foundItem == NULL){
        printf("item doesn't exist! try again\n");
        printf("press any key to continue...");
        _getch();
        clearScreen();
    }
}

void removeItemFromCart(List* shoppingCart, List* itemsList, Queue* Log) {
    clearScreen();

    if (List_IsEmpty(shoppingCart)) {
        printf("shopping cart is empty!\n");
        printf("press any key to continue...");
        _getch();
        clearScreen();
        return;
    }

    printf("shopping cart, please select an action:\n");
    printf("0. return to purchase\n");
    printf("1. remove item from shopping cart\n");

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
        clearScreen();
        return;
    }

    char itemName[30];
    printf("item name: ");
    scanf("%[^\n]", itemName);
    clearBuffer();

    Items* item = findItemByName(itemName, shoppingCart);

    if (item == NULL) {
        printf("couldn't find item! please try again\n");
        printf("press any key to continue...");
        _getch();
        clearScreen();
        return;
    }

    List_Delete(item, shoppingCart);

    Items* originalItem = findItemByName(itemName, itemsList);
    incrementStock(originalItem);

    char* logMsg = (char*)malloc(70 * sizeof(char));
    sprintf(logMsg, "item \"%s\" has been removed from cart\n", itemName);
    addToLog(logMsg, Log);
    free(logMsg);

    printf("removed item: %s from cart successfully\n", itemName);
    printf("press any key to continue...");
    _getch();
    clearScreen();
}

void displayCart(List* shoppingCart) {
    displayInventory(shoppingCart);
}

void cancelPurchase(List* shoppingCart, List* itemsList) {
    Node* currentShoppingCartNode = shoppingCart->head;
    while (currentShoppingCartNode != NULL) {
        
        int serial = getItemSerial(currentShoppingCartNode->data->items);
        Items* ItemFromOriginalItemsList = findItemBySerial(serial, itemsList);
        
        incrementStock(ItemFromOriginalItemsList);
        List_Delete(currentShoppingCartNode->data->items, shoppingCart);

        currentShoppingCartNode = shoppingCart->head;
    }
}

int getItemSerial(Items* item) {
    if (!strcmp(item->itemType, "book")) {
        return item->product->book->serialNumber;
    }
    else if (!strcmp(item->itemType, "magazine")) {
        return item->product->magazine->serialNumber;
    }
    else if (!strcmp(item->itemType, "boardgame")) {
        return item->product->boardgame->serialNumber;
    }
}

int checkout(List* shoppingCart, List* customersList, Queue* Log) {
    if (List_Size(shoppingCart) == 0) {
        printf("shopping cart is empty!\n");
        printf("press any key to continue...");
        _getch();
        clearScreen();
        return 0;
    }

    printf("charging customer...\n");
    printf("0. cancel and return to purchase\n");
    printf("1. continue to billing customer\n");

    int choice;
    do {
        printf(">>> ");
        scanf("%d", &choice);
        clearBuffer();
        if (choice < 0 || choice > 1) {
            printf("please select a valid action\n");
            printf("press any key to continue...\n");
            _getch();
            clearScreen();
        }
    } while (choice < 0 || choice > 1);
    clearScreen();

    if (choice == 0) return 0;

    char customerName[20];
    printf("customer name: ");
    scanf("%[^\n]", customerName);
    clearBuffer();
    clearScreen();

    Customer* foundCustomer = findCustomerByName(customersList, customerName);

    if (foundCustomer == NULL) {
        foundCustomer = createNewCustomer(customersList, Log);
    }

    // editing customer fields after adding the customer
    char date[11];
    printf("enter purchase date (DD-MM-YYYY): ");
    scanf("%s", date);
    clearBuffer();
    strcpy(foundCustomer->lastPurchaseDate, date);
    clearScreen();


    // creates the items list for customer if needed
    if (foundCustomer->ItemsPurchased == NULL) {
        foundCustomer->ItemsPurchased = List_Create("items");
    }
    
    // creates a new last purchase serials array
    int sizeOfShoppingCart = List_Size(shoppingCart);
    
    if (foundCustomer->lastPurchaseItemsSerials != NULL) {
        free(foundCustomer->lastPurchaseItemsSerials);
    }
    foundCustomer->lastPurchaseItemsSerials = (int*)malloc(sizeOfShoppingCart * sizeof(int));
    int* serialsArray = foundCustomer->lastPurchaseItemsSerials;

    // associates the items in the cart to the customer
    float shoppingBalance = 0;
    Node* currentShoppingCartNode = shoppingCart->head;

    while (currentShoppingCartNode != NULL) {
        Items* currentItem = currentShoppingCartNode->data->items;

        shoppingBalance += getItemPrice(currentItem);
        List_Append(currentItem, foundCustomer->ItemsPurchased);

        currentShoppingCartNode = currentShoppingCartNode->next;
    }

    foundCustomer->totalMoneySpent += shoppingBalance;
    foundCustomer->lastPurchaseItemsQuantity = sizeOfShoppingCart;
    foundCustomer->totalItemsPurchased += foundCustomer->lastPurchaseItemsQuantity;
    initializeSerialsArr(serialsArray, sizeOfShoppingCart, foundCustomer->ItemsPurchased);


    char* logMsg = (char*)malloc(100 * sizeof(char));
    sprintf(logMsg, "customer \"%s\" has completed a transaction of %0.2f\n", foundCustomer->fullname, shoppingBalance);
    addToLog(logMsg, Log);
    free(logMsg);


    // empties shopping cart after purchase
    Node* currentNode = shoppingCart->head;
    while (currentNode != NULL) {
        List_DeleteFirst(shoppingCart);
        currentNode = shoppingCart->head;
    }

    return 1;
}

bool itemIsAvailable(char* itemName, List* itemsList) {
    Items* foundItem = findItemByName(itemName, itemsList);
    int stock = getItemStock(foundItem);

    return stock > 0 ? true : false;
}

void decrementStock(Items* item) {
    if (!strcmp(item->itemType, "book")) {
        (item->product->book->stock)--;
    }
    else if (!strcmp(item->itemType, "magazine")) {
        (item->product->magazine->stock)--;
    }
    else if (!strcmp(item->itemType, "boardgame")) {
        (item->product->boardgame->stock)--;
    }
}

void incrementStock(Items* item) {
    if (!strcmp(item->itemType, "book")) {
        (item->product->book->stock)++;
    }
    else if (!strcmp(item->itemType, "magazine")) {
        (item->product->magazine->stock)++;
    }
    else if (!strcmp(item->itemType, "boardgame")) {
        (item->product->boardgame->stock)++;
    }
}

/************************************* end of shopping cart functions ***********************************/





/************************************* items list functions ******************************************/

void addItem(List* itemsList, Queue* Log) {
    clearScreen();

    printf("adding item... please select an action\n");
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

    // allocates memory for data received from the user
    Data* data = (Data*)malloc(sizeof(Data));
    data->items = (Items*)malloc(sizeof(Items));
    data->items->product = (Product*)malloc(sizeof(Product));

    // gets item type from user
    printf("Please enter item type (book/magazine/boardgame): ");
    scanf("%s", data->items->itemType);
    clearBuffer();
    
    // verifies user enters a valid item type
    while (strcmp(data->items->itemType, "book") && strcmp(data->items->itemType, "magazine") && strcmp(data->items->itemType, "boardgame")) {
        printf("\nError! Wrong item entered! please enter (book/magazine/boardgame): ");
        scanf("%s", data->items->itemType);
        clearBuffer();
        clearScreen();
    }

    // gets item fields according to item type specified
    char* itemName = getItemFields(data->items, itemsList);

    // checks if the same item already exists
    Items* item = findItemByName(itemName, itemsList);
    if (item != NULL) {
        clearScreen();
        printf("couldn't add item! an item under this name already exists! please try again.\n");
        printf("press any key to continue...");
        _getch();
        return;
    }

    // after getting fields from user, appends the item to the items list
    List_Append(data->items, itemsList);

    char* logMsg = (char*)malloc(70 * sizeof(char));
    sprintf(logMsg, "item \"%s\" has been added to inventory\n", itemName);
    addToLog(logMsg, Log);
    free(logMsg);

    // frees allocated memory
    free_data(data, itemsList->type);
    clearScreen();
}

void returnItem(List* itemsList, List* customersList, Queue* Log) {
    clearScreen();

    printf("returning item... please select an action\n");
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

    char input[40];
    printf("customer name: ");
    scanf("%[^\n]", input);
    clearBuffer();
    clearScreen();

    Customer* foundCustomer = findCustomerByName(customersList, input);
    if (foundCustomer == NULL) {
        printf("no customer with such name!\n");
        printf("press any key to continue...");
        _getch();
        clearScreen();
        return;
    }

    if (foundCustomer->lastPurchaseItemsQuantity == 0) {
        printf("%s has no items to return!\n", foundCustomer->fullname);
        printf("press any key to continue...");
        _getch();
        clearScreen();
        return;
    }

    if (canReturnItem(foundCustomer->lastPurchaseDate)) {
        displayLastPurchasedItem(foundCustomer);

        int validateChoice;
        do {
            printf("\n");
            printf("choose an item to return (by serial)\n");

            do {
                printf(">>>");
                scanf("%d", &choice);
                clearBuffer();
                if (choice < 1) {
                    printf("please enter a valid serial number!\n");
                }
            } while (choice < 1);

            printf("returning item with serial %d...\n", choice);
            printf("0. cancel\n");
            printf("1. confirm and continue\n");
            printf(">>> ");
            scanf("%d", &validateChoice);
            clearBuffer();
            if (validateChoice < 0 || validateChoice > 1) {
                printf("please select an action between 0-1!\n");
            }
        } while (validateChoice < 0 || validateChoice > 1);
        clearScreen();

        if (validateChoice == 0) return;
        
        // searches for the serial number between the last purchased items
        int* serialsArray = foundCustomer->lastPurchaseItemsSerials;
        int len = foundCustomer->lastPurchaseItemsQuantity;

        int chosenSerial = 0;
        for (int i = 0; i < len; i++) {
            if (choice == serialsArray[i]) {
                chosenSerial = serialsArray[i];
                break;
            }
        }

        // if no item with such serial was found
        if (!chosenSerial) {
            printf("no item with such serial number in the last purchase!\n");
            printf("press any key to continue...");
            _getch();
            clearScreen();
            return;
        }

        // finds the item in the customer's items list
        Node* currentNode = foundCustomer->ItemsPurchased->head;
        while (currentNode != NULL) {
            int currentItemSerial = getItemSerial(currentNode->data->items);
            if (currentItemSerial == chosenSerial) {
                break;
            }
            currentNode = currentNode->next;
        }

        // searches the original shop items list for the chosen item
        Node* foundNode = NULL;
        if (currentNode != NULL) {
            foundNode = List_Find(currentNode->data->items, itemsList);
        }

        // if the item is found in the shop
        if (foundNode != NULL) {
            (foundCustomer->totalItemsPurchased)--;
            foundCustomer->totalMoneySpent -= getItemPrice(currentNode->data->items);
            List_Delete(currentNode->data->items, foundCustomer->ItemsPurchased);
            incrementStock(foundNode->data->items);

            char* logMsg = (char*)malloc(100 * sizeof(char));
            sprintf(logMsg, "item with serial \"%d\" has been returned by customer \"%s\"\n", chosenSerial, foundCustomer->fullname);
            addToLog(logMsg, Log);
            free(logMsg);

            return;
        }
        else {
            printf("couldn't return item! item doesn't exist in data base\n");
            printf("press any key to continue...");
            _getch();
            clearScreen();
        }
    }
    else {
        printf("the return period has expired!\n");
        printf("press any key to continue...");
        _getch();
    }

    clearScreen();
}

bool canReturnItem(char* lastPurchaseDate) {
    char* currentDate = getTodaysDate();

    time_t lastPurchaseTime = parseDate(lastPurchaseDate);
    time_t currentTime = parseDate(currentDate);

    double secondsDifference = difftime(currentTime, lastPurchaseTime);
    int daysDifference = (int)(secondsDifference / (60 * 60 * 24));

    free(currentDate);
    return daysDifference <= 14;
}

void displayLastPurchasedItem(Customer* customer) {
    int totalNodes = List_Size(customer->ItemsPurchased);
    int len = customer->lastPurchaseItemsQuantity;

    // find the starting node for the last 'len' nodes
    Node* currentNode = customer->ItemsPurchased->head;
    for (int i = 0; i < totalNodes - len; i++) {
        currentNode = currentNode->next;
    }

    printf("serial    name                           type        stock       price       date\n");
    printf("--------------------------------------------------------------------------------------\n");

    // extract serial numbers from the last 'len' nodes
    for (int i = 0; i < len; i++) {
        if (currentNode != NULL) {
            printItem(currentNode->data->items);
            currentNode = currentNode->next;
        }
    }
}

void modifyItem(List* itemsList, Queue* Log) {
    clearScreen();

    if (List_IsEmpty(itemsList)) {
        printf("items list is empty!\n");
        printf("press any key to continue...");
        _getch();
        clearScreen();
        return;
    }

    printf("modifying item... please select an action\n");
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

    int serialNumber;

    printf("enter item's serial number: ");
    scanf("%d", &serialNumber);
    clearBuffer();
    clearScreen();

    Node* currentNode = itemsList->head;

    while (currentNode != NULL) {
        Items* currentItem = currentNode->data->items;

        if (!strcmp(currentItem->itemType, "book")) {
            if (currentItem->product->book->serialNumber == serialNumber) {

                char* logMsg = (char*)malloc(70 * sizeof(char));
                sprintf(logMsg, "item \"%s\" has been modified\n", currentItem->product->book->name);
                addToLog(logMsg, Log);
                free(logMsg);
                
                modifyBook(currentItem->product->book);
                return;
            }
        }
        else if (!strcmp(currentItem->itemType, "magazine")) {
            if (currentItem->product->magazine->serialNumber == serialNumber) {
                
                char* logMsg = (char*)malloc(70 * sizeof(char));
                sprintf(logMsg, "item \"%s\" has been modified\n", currentItem->product->magazine->name);
                addToLog(logMsg, Log);
                free(logMsg);
                
                modifyMagazine(currentItem->product->magazine);
                return;
            }
        }
        else if (!strcmp(currentItem->itemType, "boardgame")) {
            if (currentItem->product->boardgame->serialNumber == serialNumber) {
                char* logMsg = (char*)malloc(70 * sizeof(char));
                sprintf(logMsg, "item \"%s\" has been modified\n", currentItem->product->boardgame->name);
                addToLog(logMsg, Log);
                free(logMsg);

                modifyBoardgame(currentItem->product->boardgame);
                return;
            }
        }

        currentNode = currentNode->next;
    }

    printf("Item with serial number %d not found.\n", serialNumber);
    printf("Press any key to continue...");
    _getch();
    clearScreen();
}

void modifyBook(Book* book) {
    int choice;
    do {
        printf("please select field to modify\n");
        printf("0. return to main menu\n");
        printf("1. name\n");
        printf("2. author\n");
        printf("3. release date\n");
        printf("4. price\n");
        printf("5. best seller status\n");
        printf("6. stock\n");
        printf("7. number of pages\n");
        printf("8. genre\n");
        printf("9. volume\n");
        printf(">>> ");
        scanf("%d", &choice);
        clearBuffer();
        clearScreen();

        switch (choice) {
            case 0:
                clearScreen();
                break;
            case 1:
                printf("name: ");
                scanf("%[^\n]", book->name);
                clearBuffer();
                break;
            case 2:
                printf("author: ");
                scanf("%[^\n]", book->author);
                clearBuffer();
                break;
            case 3:
                printf("release date (DD-MM-YYYY): ");
                scanf("%s", book->releaseDate);
                clearBuffer();
                break;
            case 4:
                printf("price: ");
                scanf("%f", &book->price);
                clearBuffer();
                break;
            case 5:
                printf("bestseller status (1/0): ");
                int flag;
                scanf("%d", &flag);
                clearBuffer();
                book->bestSeller = (flag != 0);
                break;
            case 6:
                printf("stock: ");
                scanf("%d", &book->stock);
                clearBuffer();
                break;
            case 7:
                printf("number of pages: ");
                scanf("%d", &book->numOfPages);
                clearBuffer();
                break;
            case 8:
                printf("genre: ");
                scanf("%s", book->genre);
                clearBuffer();
                break;
            case 9:
                printf("volume: ");
                scanf("%d", &book->volume);
                clearBuffer();
                break;
            default:
                printf("Choice beyond limits! Please select a number within the range\n");
                printf("Press any key to continue...\n");
                _getch();
                clearScreen();
                break;
        }
        clearScreen();
    } while (choice != 0);
}

void modifyMagazine(Magazine* magazine) {
    int choice;
    do {
        printf("please select field to modify\n");
        printf("0. return to main menu\n");
        printf("1. name\n");
        printf("2. publisher\n");
        printf("3. release date\n");
        printf("4. price\n");
        printf("5. best seller status\n");
        printf("6. stock\n");
        printf("7. type\n");
        printf(">>> ");
        scanf("%d", &choice);
        clearBuffer();
        clearScreen();

        switch (choice) {
        case 0:
            clearScreen();
            break;
        case 1:
            printf("name: ");
            scanf("%[^\n]", magazine->name);
            clearBuffer();
            break;
        case 2:
            printf("publisher: ");
            scanf("%[^\n]", magazine->publisher);
            clearBuffer();
            break;
        case 3:
            printf("release date (DD-MM-YYYY): ");
            scanf("%s", magazine->releaseDate);
            clearBuffer();
            break;
        case 4:
            printf("price: ");
            scanf("%f", &magazine->price);
            clearBuffer();
            break;
        case 5:
            printf("bestseller status (1/0): ");
            int flag;
            scanf("%d", &flag);
            clearBuffer();
            magazine->bestSeller = (flag != 0);
            break;
        case 6:
            printf("stock: ");
            scanf("%d", &magazine->stock);
            clearBuffer();
            break;
        case 7:
            printf("type: ");
            scanf("%s", magazine->type);
            clearBuffer();
            break;
        default:
            printf("Choice beyond limits! Please select a number within the range\n");
            printf("Press any key to continue...\n");
            _getch();
            clearScreen();
            break;
        }
        clearScreen();
    } while (choice != 0);
}

void modifyBoardgame(Boardgame* boardgame) {
    int choice;
    do {
        printf("please select field to modify\n");
        printf("0. return to main menu\n");
        printf("1. name\n");
        printf("2. manufacturer\n");
        printf("3. release date\n");
        printf("4. price\n");
        printf("5. best seller status\n");
        printf("6. stock\n");
        printf("7. minimum age\n");
        printf("8. number of participants\n");
        printf(">>> ");
        scanf("%d", &choice);
        clearBuffer();
        clearScreen();

        switch (choice) {
        case 0:
            clearScreen();
            break;
        case 1:
            printf("name: ");
            scanf("%[^\n]", boardgame->name);
            clearBuffer();
            break;
        case 2:
            printf("manufacturer: ");
            scanf("%[^\n]", boardgame->manufacturer);
            clearBuffer();
            break;
        case 3:
            printf("release date (DD-MM-YYYY): ");
            scanf("%s", boardgame->releaseDate);
            clearBuffer();
            break;
        case 4:
            printf("price: ");
            scanf("%f", &boardgame->price);
            clearBuffer();
            break;
        case 5:
            printf("bestseller status (1/0): ");
            int flag;
            scanf("%d", &flag);
            clearBuffer();
            boardgame->bestSeller = (flag != 0);
            break;
        case 6:
            printf("stock: ");
            scanf("%d", &boardgame->stock);
            clearBuffer();
            break;
        case 7:
            printf("minimum age: ");
            scanf("%d", &boardgame->minAge);
            clearBuffer();
            break;
        case 8:
            printf("number of participants: ");
            scanf("%d", &boardgame->participants);
            clearBuffer();
            break;
        default:
            printf("Choice beyond limits! Please select a number within the range\n");
            printf("Press any key to continue...\n");
            _getch();
            clearScreen();
            break;
        }
        clearScreen();
    } while (choice != 0);
}

void deleteItem(List* itemsList, Queue* Log) {
    clearScreen();

    // gets item's name
    char itemName[30];
    printf("deleting item... please select an action\n");
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

    printf("Item to delete (name): ");
    scanf("%[^\n]", itemName);
    clearBuffer();

    // finds and removes item from the items list
    Items* item = findItemByName(itemName, itemsList);
    if (item != NULL) {
        List_Delete(item, itemsList);
        printf("successfully deleted item: %s", itemName);

        char* logMsg = (char*)malloc(70 * sizeof(char));
        sprintf(logMsg, "item \"%s\" has been deleted from inventory\n", itemName);
        addToLog(logMsg, Log);
        free(logMsg);
    }
    else {
        printf("couldn't find item! please try again");
    }

    printf("\npress any key to continue...");
    _getch();
    clearScreen();
}

void displayInventory(List* itemsList) {
    clearScreen();
    printf("serial    name                           type        stock       price       date\n");
    printf("--------------------------------------------------------------------------------------\n");

    Node* currentNode = itemsList->head;

    while (currentNode != NULL) {
        printItem(currentNode->data->items);
        currentNode = currentNode->next;
    }

    displayItemsByCategory(itemsList);

    printf("\npress any key to continue...");
    _getch();
    clearScreen();
}

void printItem(Items* item) {
    char name[30];
    int serial;
    int stock;
    float price;
    char date[11];
    char type[10];

    strcpy(type, item->itemType);

    if (!strcmp(item->itemType, "book")) {
        serial = item->product->book->serialNumber;
        stock = item->product->book->stock;
        price = item->product->book->price;
        strcpy(name, item->product->book->name);
        strcpy(date, item->product->book->releaseDate);
    }
    else if (!strcmp(item->itemType, "magazine")) {
        serial = item->product->magazine->serialNumber;
        stock = item->product->magazine->stock;
        price = item->product->magazine->price;
        strcpy(name, item->product->magazine->name);
        strcpy(date, item->product->magazine->releaseDate);
    }
    else if (!strcmp(item->itemType, "boardgame")) {
        serial = item->product->boardgame->serialNumber;
        stock = item->product->boardgame->stock;
        price = item->product->boardgame->price;
        strcpy(name, item->product->boardgame->name);
        strcpy(date, item->product->boardgame->releaseDate);
    }
    
    printf("%-9d %-30s %-11s %-11d %-10.2f %-11s\n", serial, name, type, stock, price, date);
}

void printFullItemData(Items* item) {
    int stock;
    char name[30];
    int serial;
    float price;
    char date[11];
    char type[10];
    int bestseller;
    // book
    char author[20];
    int numOfPages;
    char genre[15];
    int volume;
    // boardgame
    char manufacturer[20];
    int minAge;
    int participants;
    // magazine
    char publisher[20];
    char category[15];


    strcpy(type, item->itemType);

    if (!strcmp(item->itemType, "book")) {
        bestseller = item->product->book->bestSeller ? 1 : 0;
        serial = item->product->book->serialNumber;
        stock = item->product->book->stock;
        price = item->product->book->price;
        numOfPages = item->product->book->numOfPages;
        volume = item->product->book->volume;
        strcpy(name, item->product->book->name);
        strcpy(date, item->product->book->releaseDate);
        strcpy(author, item->product->book->author);
        strcpy(genre, item->product->book->genre);

        printf("%-9d %-30s %-10s %-14s %-13s %-15.2f %-12d %-11d %-11d %-13s %d\n", serial, name, type, author, date, price, bestseller, stock, numOfPages, genre, volume);
    }
    else if (!strcmp(item->itemType, "magazine")) {
        bestseller = item->product->magazine->bestSeller ? 1 : 0;
        serial = item->product->magazine->serialNumber;
        stock = item->product->magazine->stock;
        price = item->product->magazine->price;
        strcpy(name, item->product->magazine->name);
        strcpy(date, item->product->magazine->releaseDate);
        strcpy(publisher, item->product->magazine->publisher);
        strcpy(category, item->product->magazine->type);
        
        printf("%-9d %-30s %-10s %-14s %-12s %-15.2f %-12d %-11d %-9s\n", serial, name, type, publisher, date, price, bestseller, stock, category);
    }
    else if (!strcmp(item->itemType, "boardgame")) {
        bestseller = item->product->boardgame->bestSeller ? 1 : 0;
        serial = item->product->boardgame->serialNumber;
        stock = item->product->boardgame->stock;
        price = item->product->boardgame->price;
        minAge = item->product->boardgame->minAge;
        participants = item->product->boardgame->participants;
        strcpy(name, item->product->boardgame->name);
        strcpy(date, item->product->boardgame->releaseDate);
        strcpy(manufacturer, item->product->boardgame->manufacturer);

        printf("%-9d %-30s %-10s %-16s %-12s %-15.2f %-12d %-13d %-15d %d\n", serial, name, type, manufacturer, date, price, bestseller, stock, minAge, participants);
    }
}

void displayItemsByCategory(List* itemsList) {
    if (itemsList != NULL) {
        printf("\n\n\n");
        printf("Books:\n\n");
        printf("serial    name                           type       author         date          price       bestseller       stock       pages       genre       volume\n");
        printf("--------------------------------------------------------------------------------------------------------------------------------------------------------\n");

        

        Node* currentNode = itemsList->head;
        while (currentNode != NULL) {
            Items* currentItem = currentNode->data->items;
            if (!strcmp(currentItem->itemType, "book")) {
                printFullItemData(currentItem);
            }
            currentNode = currentNode->next;
        }

        printf("\n\n\n\nMagazines:\n\n");
        printf("serial    name                           type       publisher         date      price       bestseller       stock       category\n");
        printf("--------------------------------------------------------------------------------------------------------------------------------------\n");

        currentNode = itemsList->head;
        while (currentNode != NULL) {
            Items* currentItem = currentNode->data->items;
            if (!strcmp(currentItem->itemType, "magazine")) {
                printFullItemData(currentItem);
            }
            currentNode = currentNode->next;
        }

        printf("\n\n\n\nBoardgames:\n\n");
        printf("serial    name                           type       manufacturer        date      price       bestseller      stock       min_age       participants\n");
        printf("------------------------------------------------------------------------------------------------------------------------------------------------------\n");

        currentNode = itemsList->head;
        while (currentNode != NULL) {
            Items* currentItem = currentNode->data->items;
            if (!strcmp(currentItem->itemType, "boardgame")) {
                printFullItemData(currentItem);
            }
            currentNode = currentNode->next;
        }
    }
}

/************************************* end of items list functions ***********************************/