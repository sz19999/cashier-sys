#include "../inc/libraries.h"
// a queue implemented by a linked list

Queue* Queue_Create() {
	Queue* Q = (Queue*)malloc(sizeof(Queue));
	if (Q != NULL) {
		Q->head = NULL;
		Q->tail = NULL;
	}
	return Q;
}

QueueNode* createQueueNode(char* inputText) {
	QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
	if (newNode != NULL) {
		newNode->next = NULL;

		int inputTextLen = strlen(inputText) + 1;
		newNode->text = (char*)malloc(inputTextLen * sizeof(char));
		strcpy(newNode->text, inputText);
	}
	return newNode;
}

bool Queue_IsEmpty(Queue* Q) {
	return Q->head == NULL;
}

int Queue_Size(Queue* Q) {
	int len = 0;
	QueueNode* currentNode = Q->head;
	while (currentNode != NULL) {
		len++;
		currentNode = currentNode->next;
	}
	return len;
}

void Queue_Enqueue(char* inputText, Queue* Q) {
	QueueNode* newNode = createQueueNode(inputText);
	if (newNode == NULL) {
		return;
	}
	
	if (Queue_IsEmpty(Q)) {
		Q->tail = newNode;
		Q->head = newNode;
	}
	else {
		Q->tail->next = newNode;
		Q->tail = newNode;
	}
}

QueueNode* Queue_Dequeue(Queue* Q) {
	if (Queue_IsEmpty(Q)) {
		return NULL;
	}

	QueueNode* temp = createQueueNode(Q->head->text);
	temp->next = Q->head->next;

	if (Queue_Size(Q) == 1) {
		free_QueueNode(Q->head);
		Q->head = NULL;
		Q->tail = NULL;
	}
	else {
		free_QueueNode(Q->head);
		Q->head = temp->next;
	}
	return temp;
}

void free_QueueNode(QueueNode* node) {
	free(node->text);
	free(node);
}

void DestroyQueue(Queue* Q) {
	if (Queue_IsEmpty(Q)) {
		free(Q);
		return;
	}

	QueueNode* currentNode = Q->head;
	while (currentNode != NULL) {
		QueueNode* previousNode = currentNode;
		currentNode = currentNode->next;
		free_QueueNode(previousNode);
	}
	free(Q);
}