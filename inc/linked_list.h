#pragma once

#include "libraries.h"

List* List_Create(char* type);

bool List_IsEmpty(List* L);

void List_Append(void* data, List* L);

Node* List_Find(void* data, List* L);

void List_DeleteFirst(List* L);

void List_Delete(void* data, List* L);

void List_InsertFirst(void* data, List* L);

Node* CreateNode(char* type, void* data);

int List_Size(List* L);

void DestroyList(List* L);

// auxiliary functions
void free_product(Product* product, const char* itemType);

void free_data(Data* data, char* type);

void free_node(Node* node, char* type);

bool compare_items(Items* items, void* data);

bool compare_data(char* type, Data* current_data, void* data);