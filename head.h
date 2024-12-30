#ifndef HEAD_H
#define HEAD_H

#include <stdio.h>

FILE *openFile(char *);
int headComponents(FILE *);
int body(FILE *, char *);
char* getValidTitleInput(char *, size_t);
int printTitle(FILE *, char *);
int testForInjection(char *);
// cia eis visos funkcijos

#endif