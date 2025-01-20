#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "fun.h"

FILE *openFile(char *name)
{
    FILE *file = fopen(name, "w");
    if (file == NULL)
    {
        perror("Error opening file");
        return 0;
    }
    return file;
}

char *getValidTitleInput(char *input, size_t maxLength)
{
    size_t len;

    printf("Choose a name for your wesite.\n");

    while (1)
    {
        printf("Enter a string (max %zu characters): ", maxLength);

        if (fgets(input, maxLength + 2, stdin))
        {
            len = strlen(input);
            if (input[len - 1] == '\n')
            {
                input[len - 1] = '\0';
                len--;
            }
            else
            {
                printf("Input is too long! Please try again.\n");
                int ch;
                while ((ch = getchar()) != '\n' && ch != EOF)
                    ;
                continue;
            }

            if (len == 0)
            {
                printf("Title cannot be empty! Please try again.\n");
            }
            else
            {
                if (!detectXSSAttack(input))
                    return input;
                else
                {
                    printf("I see you tried to inject something!");
                    return "<script>window.location.href = 'https://www.youtube.com/watch?v=dQw4w9WgXcQ';</script>";
                }
            }
        }
        else
        {
            printf("Error reading input. Please try again.\n");
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF)
                ;
        }
    }
}

int detectXSSAttack(const char *input)
{
    if (!input)
        return -1; // Handle NULL input

    // Common XSS patterns to check
    const char *patterns[] = {
        "<script", "javascript:", "vbscript:", "data:",
        "onerror=", "onload=", "onmouseover=", "onclick=",
        "onmouseout=", "ondblclick=", "onkeypress=", "onkeydown=",
        "onkeyup=", "onsubmit=", "onready=", "onchange=",
        "alert(", "prompt(", "confirm(", "eval(",
        "execute(", "setTimeout(", "setInterval(", "new function(",
        "<img", "<iframe", "<embed", "<object",
        "document.cookie", "document.write", "document.location",
        "window.location", "innerHTML", "outerHTML",
        ".href=", "\\x", "\\u", "&#",
        "expression(", "url(", "/*", "-->", "]]>"};
    const int patternCount = sizeof(patterns) / sizeof(patterns[0]);

    // Allocate memory for normalized string (lowercase, no whitespace)
    size_t len = strlen(input);
    char *normalized = (char *)malloc(len + 1);
    if (!normalized)
        return -1; // Memory allocation failed

    // Normalize the input string: convert to lowercase and remove whitespace
    int j = 0;
    for (size_t i = 0; i < len; i++)
    {
        if (!isspace(input[i]))
        {
            normalized[j++] = tolower(input[i]);
        }
    }
    normalized[j] = '\0';

    // Check for hexadecimal encoding patterns (%XX)
    for (int i = 0; normalized[i + 2] != '\0'; i++)
    {
        if (normalized[i] == '%' &&
            isxdigit(normalized[i + 1]) &&
            isxdigit(normalized[i + 2]))
        {
            free(normalized);
            return 1; // Suspicious encoding found
        }
    }

    // Check for all patterns
    for (int i = 0; i < patternCount; i++)
    {
        // Create lowercase version of pattern
        size_t pattern_len = strlen(patterns[i]);
        char *pattern_lower = (char *)malloc(pattern_len + 1);
        if (!pattern_lower)
        {
            free(normalized);
            return -1; // Memory allocation failed
        }

        // Convert pattern to lowercase
        for (size_t k = 0; k < pattern_len; k++)
        {
            pattern_lower[k] = tolower(patterns[i][k]);
        }
        pattern_lower[pattern_len] = '\0';

        // Check if pattern exists in normalized input
        if (strstr(normalized, pattern_lower) != NULL)
        {
            free(pattern_lower);
            free(normalized);
            return 1; // XSS pattern found
        }

        free(pattern_lower);
    }

    free(normalized);
    return 0; // No XSS detected
}

int getQuotesFromFile(char *fileName, char **textStrings, int maxStringsNumber, int maxCharNumberInString)
{
    FILE *inputFile = fopen(fileName, "r");
    if (inputFile == NULL)
    {
        perror("Error opening file");
        return -1;
    }

    char buffer[maxCharNumberInString];
    char c = 0;
    char previousC = 0;
    int bufferSize = 0;
    int stringsFound = 0;

    while (stringsFound < maxStringsNumber)
    {

        while ((c = fgetc(inputFile)) != EOF && c != '"')
            ;

        if (c == EOF)
        {
            fclose(inputFile);
            return stringsFound;
        }

        bufferSize = 0;
        previousC = 0;

        while (bufferSize < maxCharNumberInString - 1)
        {

            c = fgetc(inputFile);
            if (c == EOF)
            {
                fclose(inputFile);
                return -2;
            }

            if (c == '"' && previousC != '\\')
            {
                break;
            }

            if (!(previousC == '\\' && c == '"'))
            {
                buffer[bufferSize++] = c;
            }
            previousC = c;
        }

        buffer[bufferSize] = '\0';

        strncpy(textStrings[stringsFound], buffer, maxCharNumberInString - 1);
        textStrings[stringsFound][maxCharNumberInString - 1] = '\0';
        stringsFound++;

        if (bufferSize >= maxCharNumberInString - 1)
        {
            while ((c = fgetc(inputFile)) != EOF)
            {
                if (c == '"' && previousC != '\\')
                {
                    break;
                }
                previousC = c;
            }
            if (c == EOF)
            {
                fclose(inputFile);
                return -2;
            }
        }
    }

    fclose(inputFile);
    return stringsFound;
}

int getStringsFromFile(char *fileName, char **textStrings, int maxStringsNumber, int maxCharNumberInString)
{
    FILE *inputFile = fopen(fileName, "r");
    if (inputFile == NULL)
    {
        perror("Error opening file");
        return -1;
    }

    char buffer[maxCharNumberInString];
    char c = 0;
    int bufferSize = 0;
    int stringsFound = 0;

    while (stringsFound < maxStringsNumber)
    {

        c = fgetc(inputFile);
        while (c == '\n' || c == ' ')
        {
            c = fgetc(inputFile);
        }

        bufferSize = 0;

        while (bufferSize < maxCharNumberInString - 1)
        {

            if (c == '\n' || c == EOF)
            {
                break;
            }

            buffer[bufferSize++] = c;
            c = fgetc(inputFile);
        }

        buffer[bufferSize] = '\0';

        strncpy(textStrings[stringsFound], buffer, maxCharNumberInString - 1);
        textStrings[stringsFound][maxCharNumberInString - 1] = '\0';
        stringsFound++;

        if (c == EOF)
        {
            break;
        }

        if (bufferSize >= maxCharNumberInString - 1)
        {
            while ((c = fgetc(inputFile)) != EOF)
            {
                if (c == '\n')
                {
                    break;
                }
            }
            if (c == EOF)
            {
                fclose(inputFile);
                return stringsFound;
            }
        }
    }

    fclose(inputFile);
    return stringsFound;
}

void openHtml(const char *filename)
{
    char command[256];

#ifdef _WIN32
    snprintf(command, sizeof(command), "start %s", filename);
    system(command);
#elif __APPLE__
    snprintf(command, sizeof(command), "open %s", filename);
    system(command);
#else
    snprintf(command, sizeof(command), "xdg-open %s", filename);
    system(command);
#endif
}