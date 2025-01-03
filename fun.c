#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "fun.h"

// programos funkcijos
FILE *openFile(char *name)
{
    FILE *file = fopen(name, "w");
    if (file == NULL)
    {
        perror("whoossie");
        return 0;
    }
    return file;
}

int headComponents(FILE *file)
{
    fprintf(file, "<!DOCTYPE html>\n\
<html lang=\" en \">\n<head>\n<meta charset=\" UTF -8 \" />\n<meta name=\" viewport \" content=\" width = device - width,initial - scale = 1.0 \" />\n\
<link\
      href=\"https://fonts.googleapis.com/css?family=Krona One\"\n\
      rel=\"stylesheet\"/>\n\
    <link\n\
      rel=\"stylesheet\"\n\
      type=\"text/css\"\n\
    <link rel=\"stylesheet\" href=\"styles.css\" />\n\
    <script src=\"java.js\"></script>\n\
    <title>My Website</title>");
    return 0;
    //href=\"//fonts.googleapis.com/css?family=Anonymous+Pro\"/>\n\ - isemiau sita fonta
}
int printTitle(FILE *file, char *title)
{
    fprintf(file, "<body>\n\
    <main id=\"blur\">\n");
    fprintf(file, "<h1>%s</h1>", title);
}

char *getValidTitleInput(char *input, size_t maxLength) {
    size_t len;

    while (1) {
        printf("Enter a string (max %zu characters): ", maxLength);

        if (fgets(input, maxLength + 2, stdin)) {
            len = strlen(input);
            if (input[len - 1] == '\n') {
                input[len - 1] = '\0';
                len--;
            } else {
                printf("Input is too long! Please try again.\n");
                int ch;
                while ((ch = getchar()) != '\n' && ch != EOF);
                continue;
            }

            if (len == 0) {
                printf("Title cannot be empty! Please try again.\n");
            } else {
                if(!testForInjection(input))
                return input;
                else 
                {
                    printf("I see you tried to inject something!");
                    return "<script>window.location.href = 'https://www.youtube.com/watch?v=dQw4w9WgXcQ';</script>";
                }
            }
        } else {
            printf("Error reading input. Please try again.\n");
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF);
        }
    }
}

int testForInjection(char *input) {
    // Define common XSS patterns
    const char *xssPatterns[] = {
        "<script>",
        "javascript:",
        "onerror=",
        "onload=",
        "alert(",
        "prompt(",
        "confirm("
    };

    // Check if the input contains any of the XSS patterns
    for (int i = 0; i < sizeof(xssPatterns) / sizeof(xssPatterns[0]); ++i) {
        if (strstr(input, xssPatterns[i]) != NULL) {
            return 1; // XSS injection found
        }
    }
    return 0; // No XSS injection detected
}
int dayCounter(FILE *file, int numberOfDays)
{
    fprintf(file, "<div class=\"grid-container\">\n");
    for (int i = 1; i <= numberOfDays; ++i) 
    {
        fprintf(file,
                "<div class=\"grid-item\">\n"
                "  <button onclick=\"openPopup('First button popup text')\">\n"
                "    <img src=\"snowball.svg\">\n"
                "    <span>%d</span>\n"
                "  </button>\n"
                "</div>\n", i);
    }
    fprintf(file, "</div>\n");
}

int validationForDaysNumber(int number)
{
  while(number < MIN_DAYS || number > MAX_DAYS)
    {
        printf("Please enter a number in a range [%d; %d]: ", MIN_DAYS, MAX_DAYS);
        fscanf(stdin, "%d", &number);
    }

  return number;
}
