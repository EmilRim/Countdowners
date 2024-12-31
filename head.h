#ifndef HEAD_H
#define HEAD_H

#include <stdio.h>

FILE *openFile(char *);
int headComponents(FILE *);
int body(FILE *, char *);
int dayCounter(FILE *file, int numberOfDays);
// cia eis visos funkcijos

#endif