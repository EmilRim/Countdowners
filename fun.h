#ifndef HEAD_H
#define HEAD_H

#include <stdio.h>

#define MAX_DAYS 30
#define MIN_DAYS 1

FILE *openFile(char *);
int headComponents(FILE *);
int body(FILE *, char *);
char* getValidTitleInput(char *, size_t);
int printTitle(FILE *, char *);
int testForInjection(char *);
int dayCounter(FILE *file, int numberOfDays);
int validationForDaysNumber(int number);

/**
 * @brief Extracts quoted strings from a file into a string array.
 *
 * Reads strings enclosed in double quotes from the specified file and writes them
 * to the provided string array. If a quoted string exceeds the maximum length,
 * it will be truncated to maxCharNumberInString-1 characters plus a null terminator.
 * Escaped quotes (\") within strings are handled properly.
 *
 * @param fileName                Name of the input file to read from
 * @param textStrings             Pre-allocated array of strings to store results
 * @param maxStringsNumber        Maximum number of strings that can be stored in textStrings
 * @param maxCharNumberInString   Maximum length of each string (including null terminator)
 *
 * @return Number of strings successfully read and stored (≥ 0), or:
 *         -1 if the file could not be opened
 *         -2 if the file has an unmatched quotation mark
 *
 * @note Each string in textStrings must be pre-allocated to hold maxCharNumberInString chars
 * @note Strings in the file must be enclosed in double quotes (")
 * @note Quotes within strings can be escaped using backslash (\")
 * @note Function tooltip may not display the backslash character correctly. 
 *       See the header file for complete example with escape sequences.
 *
 * Example file content:
 * "Hello world" "Another string" "String with \"quotes\""
 */
int getInQuotesTextFromFile(char *fileName, char **textStrings, int maxStrings, int maxCharNumberInString);

#endif