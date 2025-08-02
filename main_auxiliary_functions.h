#pragma once

#include "definitions.h"

void ensureFilesExist(Queue* Log);

void loadFiles(List* Employees, List* Customers, List* Items);

void clearScreen();

void clearBuffer();

void destroyCreatedDataStructures(List* Employees, List* Customers, List* Items, Queue* Log);