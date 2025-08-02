#pragma once

#include "libraries.h"

/************************************* item input functions ******************************************/

char* getBookFields(Book* book, List* itemsList);

char* getMagazineFields(Magazine* magazine, List* itemsList);

char* getBoardgameFields(Boardgame* boardgame, List* itemsList);

char* getItemFields(Items* item, List* itemsList);

int getNewSerialNumber(List* itemsList);

/************************************* end of item input functions ******************************************/




/************************************* file functions ******************************************/

bool readItem(Items* item, FILE* fp, int* currentCursorPosition);

void writeItem(Items* currentItem, FILE* fp, int* currentCursorPosition);

bool checkIfItemsFileExists(Queue* Log);

void createNewItemsFile();

void loadItems(List* ItemsList);

void updateItemsFile(List* itemsList);

/************************************* end of file functions ***********************************/




/************************************* search functions ******************************************/

void searchItem(List* itemsList, int inPurchaseFlag, Queue* Log);

// name
Items* findItemByName(char* itemName, List* itemsList);

void searchItemByName(List* itemsList);

// date
void searchItemByDate(List* itemsList);

Items* findItemByDate(char* itemDate, List* itemsList);

void searchItemsAfterDate(List* itemsList);

void searchItemsBeforeDate(List* itemsList);

void searchItemsBetweenDates(List* itemsList);

int compareDates(char* date1, char* date2);

char* getItemReleaseDate(Items* item);

// serial
void searchItemBySerial(List* itemsList);

Items* findItemBySerial(int serialNumber, List* itemsList);

int getItemSerial(Items* item);

// stock
void searchItemByStock(List* itemsList);

void searchItemsBelowStock(List *itemsList);

void searchItemsAboveOrEqualStock(List* itemsList);

int getItemStock(Items* item);

// bestseller
void searchItemByBestSellerStatus(List* itemsList);

bool getItemBestsellerStat(Items* item);

// price
void searchItemByPrice(List* itemsList);

void searchItemsAboveOrEqualPrice(List* itemsList);

void searchItemsBelowPrice(List* itemsList);

float getItemPrice(Items* item);

// product type
void searchByProductType(List* itemsList);

// product type + date
void searchBothByProductTypeAndDate(List* itemsList);

void searchItemsWithGivenTypeAfterDate(List* itemsList, char* itemType);

void searchItemsWithGivenTypeBeforeDate(List* itemsList, char* itemType);

void searchItemsWithGivenTypeBetweenDates(List* itemsList, char* itemType);


/************************************* end of search functions ***********************************/




/************************************* items list functions ******************************************/

void addItem(List* itemsList, Queue* Log);

void returnItem(List* itemsList, List* customersList, Queue* Log);

bool canReturnItem(char* lastPurchaseDate);

void displayLastPurchasedItem(Customer* customer);

void modifyItem(List* itemsList, Queue* Log);

void modifyBook(Book* book);

void modifyMagazine(Magazine* magazine);

void modifyBoardgame(Boardgame* boardgame);

void deleteItem(List* itemsList, Queue* Log);

void displayInventory(List* ItemsList);

void printItem(Items* item);

void printFullItemData(Items* item);

void displayItemsByCategory(List* itemsList);

/************************************* end of items list functions ***********************************/




/************************************* shopping cart functions ***********************************/

void addItemToCart(List* shoppingCart, List* itemsList, int inPurchaseFlag, Queue* Log);

void removeItemFromCart(List* shoppingCart, List* itemsList, Queue* Log);

void displayCart(List* shoppingCart);

void cancelPurchase(List* shoppingCart, List* itemsList);

int checkout(List* shoppingCart, List* customersList, Queue* Log);

void addItemToCartByName(List* shoppingCart, List* itemsList, Queue* Log);

void decrementStock(Items* item);

bool itemIsAvailable(char* itemName, List* itemsList);

void incrementStock(Items* item);

/************************************* end of shopping cart functions ***********************************/

