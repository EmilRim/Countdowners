#ifndef WEBFUN_H
#define WEBFUN_H

#include <stdio.h>

/**
* @brief Opens a file in write mode with error checking.
*
* Attempts to open the specified file for writing. If the file cannot be opened,
* prints an error message with details about the failure using perror().
*
* @param name    Name/path of the file to open for writing
*
* @return
* - FILE pointer to the opened file if successful
* - 0 (NULL) if file opening fails
*
* @note Opens file in write mode ("w") which will:
*       - Create new file if it doesn't exist
*       - Truncate existing file if it exists
* @note Caller is responsible for closing the file when done
*
* #### Example usage:
* ```c
* FILE *fp = openFile("output.txt");
* if (fp) {
*     fprintf(fp, "Some text");
*     fclose(fp);
* }
* ```
*/
FILE *openFile(char *);
/**
* @brief Gets and validates user input for a title field with XSS protection.
*
* Prompts the user to enter a string and performs validation including:
* - Length checking against maximum allowed length
* - Empty string prevention
* - XSS attack pattern detection
* - Input buffer overflow prevention
*
* @param input      Pre-allocated buffer to store the input string
* @param maxLength  Maximum allowed length of input string (excluding null terminator)
*
* @return 
* - Pointer to validated input string if successful
* - Pointer to rick-roll script if XSS attack is detected
* - Will continue prompting until valid input is received
*
* @note Automatically trims trailing newline from input
* @note Clears input buffer on overflow attempts
* @note Requires testForInjection() function for XSS detection
*
* #### Example usage:
* ```c
* char buffer[100];
* char *title = getValidTitleInput(buffer, 99);
* printf("Validated title: %s\n", title);
* ```
*
* #### Input handling:
* - Empty input -> Prompts for retry
* - Too long -> Clears buffer and prompts for retry
* - XSS attempt -> Returns rick-roll script
* - Valid input -> Returns sanitized string
*/
char* getValidTitleInput(char *, size_t);

/**
 * @brief Detects potential XSS (Cross-Site Scripting) attacks in input strings with whitespace normalization.
 *
 * Examines input strings for malicious patterns while accounting for common evasion techniques.
 * Performs case-insensitive matching and removes all whitespace characters (spaces, tabs, newlines)
 * before checking against known XSS patterns. Also detects hexadecimal encoding commonly used
 * in attacks.
 *
 * @param input    Null-terminated string to check for XSS patterns
 *
 * @return
 *   - 1  if potential XSS is detected
 *   - 0  if input appears safe
 *   - -1 if error occurs (NULL input or memory allocation failure)
 *
 * @note This function detects both standard and whitespace-obfuscated attacks
 * @note Memory is dynamically allocated and freed within the function
 * @note Case-insensitive matching is performed on all patterns
 *
 * #### Example usage:
 * ```c
 * const char* input = "< s c r i p t >alert(1)</script>";
 * switch(detectXSSAttack(input)) {
 *     case 1:  printf("XSS detected\n"); break;
 *     case 0:  printf("Input is safe\n"); break;
 *     case -1: printf("Error occurred\n"); break;
 * }
 * ```
 *
 * #### Attack patterns detected include:
 * - Script tags and events (e.g., <script>, onclick)
 * - JavaScript protocols and functions
 * - DOM manipulation methods
 * - HTML entities and encoding
 * - CSS expression patterns
 * - Encoded character sequences
 */
int detectXSSAttack(const char*);

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