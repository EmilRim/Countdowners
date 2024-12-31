#ifndef HEAD_H
#define HEAD_H

#include <stdio.h>

#define MAX_DAYS 30
#define MIN_DAYS 1

FILE *openFile(char *);
int headComponents(FILE *);
int body(FILE *, char *);
int dayCounter(FILE *file, int numberOfDays);
int validationForDaysNumber(int number);
// cia eis visos funkcijos

#endif