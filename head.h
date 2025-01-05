#ifndef HEAD_H
#define HEAD_H


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
 *
 * Example file content:
 * "Hello world" "Another strinx" "String with \"quotes\""
 */
int getInQuotesTextFromFile(char *fileName, char **textStrings, int maxStrings, int maxCharNumberInString);


#endif