#ifndef SEC_H
#define SEC_H

#include <stdio.h>

#define MIN_DAYS 1
#define MAX_DAYS 30

int headComponents(FILE *file, char *backgroundColor, char *fontColor);
int printTitle(FILE *file, char *title);
int dayCounter(FILE *file, int numberOfDays, char* buttonImg, char **texts);
int getNumberOfDays(int number);
void getTheme(char *buttonImg, char *bottomImg, char *backgroundColor, char *fontColor);
void insertBottomImg(FILE *file, char *bottomImg);
void popUpAppear(FILE *file);
void removeQuotes(char **strings, int arraySize);

#endif
