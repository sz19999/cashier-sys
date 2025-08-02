#pragma once

#include "libraries.h"

// queue implementation by a linked list data structure

Queue* Queue_Create();

QueueNode* createQueueNode(char* text);

bool Queue_IsEmpty(Queue* Q);

int Queue_Size(Queue* Q);

void Queue_Enqueue(char* text, Queue* Q);

QueueNode* Queue_Dequeue(Queue* Q);

void free_QueueNode(QueueNode* node);

void DestroyQueue(Queue* Q);