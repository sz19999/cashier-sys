#include "../inc/libraries.h"

List* List_Create(char* type) {
	List* L = (List*)malloc(sizeof(List));
	if (L == NULL)
		return NULL;
	L->head = NULL;
	L->tail = NULL;
	strcpy(L->type, type);
	return L;
}

Node* CreateNode(char* type, void* data) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	if (newNode == NULL)
		return NULL;

	newNode->data = (Data*)malloc(sizeof(Data));
	if (newNode->data == NULL) {
		free(newNode);
		return NULL;
	}

	if (!strcmp(type, "items")) {									
		newNode->data->items = (Items*)malloc(sizeof(Items));
		newNode->data->items->product = (Product*)malloc(sizeof(Product));
		memcpy(newNode->data->items->itemType, ((Items*)data)->itemType, 10);

		if (!strcmp(((Items*)data)->itemType, "book")) {
			newNode->data->items->product->book = (Book*)malloc(sizeof(Book));
			memcpy(newNode->data->items->product->book, ((Items*)data)->product->book, sizeof(Book));
		}

		else if (!strcmp(((Items*)data)->itemType, "magazine")) {
			newNode->data->items->product->magazine = (Magazine*)malloc(sizeof(Magazine));
			memcpy(newNode->data->items->product->magazine, ((Items*)data)->product->magazine, sizeof(Magazine));
		}

		else if (!strcmp(((Items*)data)->itemType, "boardgame")) {
			newNode->data->items->product->boardgame = (Boardgame*)malloc(sizeof(Boardgame));
			memcpy(newNode->data->items->product->boardgame, ((Items*)data)->product->boardgame, sizeof(Boardgame));
		}
	}

	else if (!strcmp(type, "employees")) {
		newNode->data->employee = (Employee*)malloc(sizeof(Employee));
		memcpy(newNode->data->employee, data, sizeof(Employee));
	}

	else if (!strcmp(type, "customers")) {
		newNode->data->customer = (Customer*)malloc(sizeof(Customer));
		memcpy(newNode->data->customer, data, sizeof(Customer));
	}

	newNode->next = NULL;
	return newNode;
}

bool List_IsEmpty(List* L) {
	return L->head == NULL ? true : false;
}

void List_InsertFirst(void* data, List* L) {	// x is a pointer to some struct, could be an item/employee/customer struct
	Node* newNode = CreateNode(L->type, data);

	if (newNode != NULL) {
		newNode->next = L->head;
		L->head = newNode;
	}
}

void List_Append(void* data, List* L) {
	if (List_IsEmpty(L)) {
		List_InsertFirst(data, L);
		L->tail = L->head;
	}
	else {
		Node* newNode = CreateNode(L->type, data);
		if (newNode != NULL) {
			Node* last = L->tail;
			last->next = newNode;
			L->tail = newNode;
		}
	}
}

Node* List_Find(void* data, List* L) {
	if (List_IsEmpty(L)) {
		return NULL;
	}
	else {
		Node* current = L->head;
		// traverse the list to find data, if found returns the found node 
		while (current != NULL) {
			if (compare_data(L->type, current->data, data)) {
				return current;
			}
			current = current->next;
		}
		return NULL;
	}
}

void List_DeleteFirst(List* L) {
	if (List_IsEmpty(L)) {
		return;
	}
	else {
		Node* newHead = L->head->next;
		free_node(L->head, L->type);
		L->head = newHead;

		// if the list is empty now, update the tail pointer also
		if (L->head == NULL)
			L->tail = NULL;
	}
}

void List_Delete(void* data, List* L) {
	if (List_IsEmpty(L)) {
		return;
	}
	// if the first node's data is the data we're looking for
	if (compare_data(L->type, L->head->data, data)) {
		List_DeleteFirst(L);
		return;
	}
	if (List_Size(L) >= 2) {
		Node* current = L->head->next;
		Node* previous = L->head;
		// traverse the list to find the data
		while (current != NULL) {
			if (compare_data(L->type, current->data, data)) {
				previous->next = current->next;
				if (previous->next == NULL) {
					L->tail = previous;
				}
				free_node(current, L->type);
				return;
			}
			previous = current;
			current = current->next;
		}
	}
}

int List_Size(List* L) {
	if (List_IsEmpty(L)) {
		return 0;
	}
	else {
		Node* current = L->head;
		int len = 0;
		while (current != NULL) {
			current = current->next;
			len++;
		}
		return len;
	}
}

void DestroyList(List* L) {
	if (List_IsEmpty(L)) {
		free(L);
	}
	else {
		Node* current = L->head;
		while (current != NULL) {
			Node* previous = current;
			current = current->next;
			free_node(previous, L->type);
		}
		// delete the list
		free(L);
	}
}

// auxiliary functions
void free_product(Product* product, const char* itemType) {
	if (!strcmp(itemType, "book") && product->book) {
		free(product->book);
	}
	else if (!strcmp(itemType, "magazine") && product->magazine) {
		free(product->magazine);
	}
	else if (!strcmp(itemType, "boardgame") && product->boardgame) {
		free(product->boardgame);
	}
	free(product);
}

void free_data(Data* data, char* type) {
	if (data == NULL)
		return;
	if (!strcmp(type, "items")) {
		free_product(data->items->product, data->items->itemType);
		free(data->items);
	}
	else if (!strcmp(type, "employees")) {
		free(data->employee);
	}
	else if (!strcmp(type, "customers")) {
		free_customer(data->customer);
	}
	free(data);
}

void free_node(Node* node, char* type) {
	free_data(node->data, type);
	free(node);
}

bool compare_items(Items* items, void* data) {
	Product* product = ((Items*)data)->product;

	if (!strcmp(items->itemType, "book") && !memcmp(items->product->book, product->book, sizeof(Book))) {
		return true;
	}
	else if (!strcmp(items->itemType, "magazine") && !memcmp(items->product->magazine, product->magazine, sizeof(Magazine))) {
		return true;
	}
	else if (!strcmp(items->itemType, "boardgame") && !memcmp(items->product->boardgame, product->boardgame, sizeof(Boardgame))) {
		return true;
	}
	return false;
}

bool compare_data(char* type, Data* current_data, void* data) {
	if (!strcmp(type, "items")) {
		return compare_items(current_data->items, data);
	}
	else if (!strcmp(type, "employees")) {
		return !memcmp(current_data->employee, data, sizeof(Employee)) ? true : false;
	}
	else if (!strcmp(type, "customers")) {
		int size = sizeof(current_data->customer->fullname) + sizeof(current_data->customer->joiningDate) + sizeof(float) +
			sizeof(current_data->customer->lastPurchaseDate) + sizeof(unsigned char) + sizeof(int);
		return !memcmp(current_data->customer, data, size) ? true : false;
	}
	return false;
}
