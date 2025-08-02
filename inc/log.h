#pragma once

#include "libraries.h"

bool checkIfLogFileExists(Queue* Log);

void createNewLogFile();

void updateLogFile(Queue* Log);

char* getTodaysDate();

char* getCurrentTime();

time_t parseDate(char* date);

void addToLog(char* smg, Queue* Q);

