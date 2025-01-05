#ifndef SEC_H
#define SEC_H

#include <stdio.h>

#define MIN_DAYS 1
#define MAX_DAYS 30

int headComponents(FILE *file);
int printTitle(FILE *file, char *title);
int dayCounter(FILE *file, int numberOfDays);
int validationForDaysNumber(int number);

#endif
