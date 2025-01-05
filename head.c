#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "head.h"


int getInQuotesTextFromFile(char *fileName, char **textStrings, int maxStringsNumber, int maxCharNumberInString)
{
    FILE *inputFile = fopen(fileName, "r");
    if (inputFile == NULL) {
        perror("Error opening file");
        return -1;
    }

    char buffer[maxCharNumberInString];
    char c = 0;
    char previousC = 0;
    int bufferSize = 0;
    int stringsFound = 0;

    while (stringsFound < maxStringsNumber) {

        while ((c = fgetc(inputFile)) != EOF && c != '"');
    
        if (c == EOF) {
            fclose(inputFile);
            return stringsFound;
        }

        bufferSize = 0;
        previousC = 0;

        while (bufferSize < maxCharNumberInString - 1){

            c = fgetc(inputFile);
            if (c == EOF) {
                fclose(inputFile);
                return -2;
            }

            if (c == '"' && previousC != '\\') {
                break;
            }

            if (!(previousC == '\\' && c == '"')) {
                buffer[bufferSize++] = c;
            }
            previousC = c;
        }

        buffer[bufferSize] = '\0';

        strncpy(textStrings[stringsFound], buffer, maxCharNumberInString - 1);
        textStrings[stringsFound][maxCharNumberInString - 1] = '\0';
        stringsFound++;

        if (bufferSize >= maxCharNumberInString - 1) {
            while ((c = fgetc(inputFile)) != EOF) {
                if (c == '"' && previousC != '\\') {
                    break;
                }
                previousC = c;
            }
            if (c == EOF) {
                fclose(inputFile);
                return -2;  // Unclosed quote error
            }
        }
    }
        
    fclose(inputFile);
    return stringsFound;
}