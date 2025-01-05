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
 * @brief Extracts strings from a file and stores them in an array.
 *
 * Reads strings (delimited by newlines) from the specified file and writes them
 * to the provided string array. Each string is truncated to `maxCharNumberInString - 1`
 * characters plus a null terminator. Leading whitespace (spaces and newlines) is skipped.
 *
 * @param fileName                Name of the input file to read from
 * @param textStrings             Pre-allocated array of strings to store the results
 * @param maxStringsNumber        Maximum number of strings that can be stored in textStrings
 * @param maxCharNumberInString   Maximum length of each string (including the null terminator)
 *
 * @return Number of strings successfully read and stored (≥ 0), or -1 if the file could not be opened
 *
 * @note Each string in textStrings must be pre-allocated to hold `maxCharNumberInString` characters
 * @note Strings in the file should be separated by newlines
 * @note Leading whitespace characters are ignored
 *
 * #### Example file content:
 * ```
 * Hello world
 * Another string
 * ```
 */
int getStringsFromFile(char *fileName, char **textStrings, int maxStringsNumber, int maxCharNumberInString);

/**
 * @brief Extracts quoted strings from a file into a string array.
 *
 * Reads strings enclosed in double quotes from the specified file and writes them
 * to the provided string array. If a quoted string exceeds the maximum length,
 * it will be truncated to `maxCharNumberInString - 1` characters plus a null terminator.
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
 * @note Each string in `textStrings` must be pre-allocated to hold `maxCharNumberInString` chars
 * @note Strings in the file must be enclosed in double quotes (")
 * @note Quotes within strings can be escaped using backslash (\")
 * @note Function tooltip may not display the backslash character correctly. 
 *       See the header file for complete example with escape sequences.
 *
 * Example file content:
 * "Hello world" "Another string" "String with \"quotes\""
 */
int getQuotesFromFile(char *fileName, char **textStrings, int maxStrings, int maxCharNumberInString);

/**
 * @brief Opens an HTML file in the default web browser.
 *
 * Executes a system command to open the specified HTML file using the default web browser, 
 * with support for Windows, macOS, and Linux platforms. 
 * The function constructs a platform-specific command string to launch the file.
 *
 * @param filename   Path to the HTML file to be opened.
 *
 * @note The function uses the `system` call to execute the command, which may pose 
 *       security risks if `filename` is not sanitized properly. Ensure `filename` is 
 *       trusted and validated before calling this function.
 * @note The command buffer size is limited to 256 characters.
 *
 * 
 * #### Supported platforms:
 * 
 * Windows
 *   (uses the `start` command),
 * 
 * macOS
 *   (uses the `open` command),
 * 
 * Linux
 *   (uses the `xdg-open` command).
 *
 * #### Example usage:
 * ```c
 * openHtml("example.html"); // Opens "example.html" in the default browser.
 * ```
 */
void openHtml(const char* filename);


#endif