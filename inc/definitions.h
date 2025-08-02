#pragma once

typedef struct book {
    int serialNumber;
    char name[30];
    char author[20];
    char releaseDate[11];
    float price;
    bool bestSeller;
    int stock;
    int numOfPages;
    char genre[15]; // book genre (fantasy, horror, ...)
    int volume;     // the number of book in a certain series
} Book;

typedef struct boardgame {
    int serialNumber;   
    char name[30];      
    char manufacturer[20];
    char releaseDate[11];
    float price;
    bool bestSeller;
    int stock;
    int minAge;       // minimum age it requires to play
    int participants; // max number of participants
} Boardgame;

typedef struct magazine {
    int serialNumber;
    char name[30];
    char publisher[20];
    char releaseDate[11];
    float price;
    bool bestSeller;
    int stock;
    char type[15]; // What type is a the magazine (scientific, motorsport, ...)
} Magazine;

// employees
typedef struct employee {
    char username[20];
    char firstname[10];
    char password[10];
    int level; // 1 - admin, 2 - employee, 3 - trainee
} Employee;

// customers
typedef struct customer {
    char fullname[40];
    char joiningDate[11];
    float totalMoneySpent;
    char lastPurchaseDate[11];
    int lastPurchaseItemsQuantity;  // indicates when the last purchase stops in the file
    int totalItemsPurchased;
    int* lastPurchaseItemsSerials;            // array of serial numbers from the last purchase
    struct List* ItemsPurchased;
} Customer;

// linked list
typedef union product {
    Book* book;
    Boardgame* boardgame;
    Magazine* magazine;
} Product;

typedef struct items {
    char itemType[10];
    Product* product;
} Items;

typedef union Data {
    Items* items;
    Customer* customer;
    Employee* employee;
} Data;

typedef struct Node {
    Data* data;
    struct Node* next;
} Node;

typedef struct List {
    char type[10];		// list type - "customers"/"employees"/"items"
    Node* head;
    Node* tail;
} List;

// queue
typedef struct QueueNode {
    char* text;
    struct QueueNode* next;
} QueueNode;


typedef struct Queue {
    QueueNode* head;
    QueueNode* tail;
} Queue;
