#include "libraries.h"

bool checkIfLogFileExists(Queue* Log) {
	FILE* fp = fopen("log.txt", "r");

	if (fp == NULL) {
		addToLog("log file doesn't exist, created new log file\n", Log);
		return false;
	}
	else {
		fclose(fp);
		return true;
	}
}

void createNewLogFile() {
	FILE* fp = fopen("log.txt", "w");
	fclose(fp);
}

void updateLogFile(Queue* Log) {
	FILE* fp = fopen("log.txt", "a");

	QueueNode* currentNode = Log->head;
	while (currentNode != NULL) {
		QueueNode* msgNode = Queue_Dequeue(Log);
		fprintf(fp, "%s", msgNode->text);
		currentNode = Log->head;

		// frees the allocated memory from the dequeue operation
		free_QueueNode(msgNode);
	}
	fclose(fp);
}

char* getTodaysDate() {
	time_t currentTime;
	struct tm* timeInfo;
	char* date = (char*)malloc(11 * sizeof(char));		// DD-MM-YYYY + 1

	time(&currentTime);
	timeInfo = localtime(&currentTime);
	strftime(date, 11, "%d-%m-%Y", timeInfo);

	return date;
}

char* getCurrentTime() {
	time_t currentTime;
	struct tm* timeInfo;
	char* time_str = (char*)malloc(9 * sizeof(char));	// 00:00:00 + 1

	time(&currentTime);
	timeInfo = localtime(&currentTime);
	strftime(time_str, 9, "%H:%M:%S", timeInfo);

	return time_str;
}

// parses the date to seconds since epoch time
time_t parseDate(char* date) {
	struct tm tm = { 0 };
	sscanf(date, "%02d-%02d-%04d", &tm.tm_mday, &tm.tm_mon, &tm.tm_year);
	tm.tm_year -= 1900; // Adjust year
	tm.tm_mon -= 1;     // Adjust month
	return mktime(&tm);
}

void addToLog(char* msg, Queue* Q) {
	char* time = getCurrentTime();
	char* date = getTodaysDate();

	
	int newLen = strlen(date) + strlen(time) + strlen(msg) + 5;
	date = (char*)realloc(date, newLen * sizeof(char));

	strcat(date, " ");
	strcat(date, time);
	strcat(date, " | ");
	strcat(date, msg);

	Queue_Enqueue(date, Q);

	free(time);
	free(date);
}