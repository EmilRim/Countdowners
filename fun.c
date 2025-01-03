#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "head.h"

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

int body(FILE *file, char *title)
{
    fprintf(file, "<body>\n");
    // Spinner wrapper
    fprintf(file, "  <div class=\"spinner-wrapper\">\n");
    fprintf(file, "    <div id=\"spinner\"></div>\n");
    fprintf(file, "  </div>\n");
    
    // Main content
    fprintf(file, "  <div id=\"main-content\">\n");
    fprintf(file, "    <main>\n");
    fprintf(file, "      <h1>%s</h1>\n", title);
    fprintf(file, "    </main>\n");
    fprintf(file, "  </div>\n");
    fprintf(file, "</body>\n");
    return 0;
}

int headComponents(FILE *file)
{
    fprintf(file, "<!DOCTYPE html>\n<html lang=\"en\">\n<head>\n");
    
    // Put ONLY the spinner styles first
    fprintf(file, "<style>\n");
    fprintf(file, "    .spinner-wrapper {\n");
    fprintf(file, "        position: fixed;\n");
    fprintf(file, "        top: 0;\n");
    fprintf(file, "        left: 0;\n");
    fprintf(file, "        right: 0;\n");
    fprintf(file, "        bottom: 0;\n");
    fprintf(file, "        background-color: white;\n");
    fprintf(file, "        z-index: 999999;\n");
    fprintf(file, "    }\n");
    fprintf(file, "    #spinner {\n");
    fprintf(file, "        position: absolute;\n");
    fprintf(file, "        top: 50%%;\n");
    fprintf(file, "        left: 50%%;\n");
    fprintf(file, "        transform: translate(-50%%, -50%%);\n");
    fprintf(file, "        width: 50px;\n");
    fprintf(file, "        height: 50px;\n");
    fprintf(file, "        border: 6px solid #f3f3f3;\n");
    fprintf(file, "        border-top: 6px solid #3498db;\n");
    fprintf(file, "        border-radius: 50%%;\n");
    fprintf(file, "        animation: spin 1s linear infinite;\n");
    fprintf(file, "    }\n");
    fprintf(file, "    @keyframes spin {\n");
    fprintf(file, "        0%% { transform: translate(-50%%, -50%%) rotate(0deg); }\n");
    fprintf(file, "        100%% { transform: translate(-50%%, -50%%) rotate(360deg); }\n");
    fprintf(file, "    }\n");
    fprintf(file, "    #main-content { display: none; }\n");
    fprintf(file, "</style>\n");

    // Add immediate loading script
    fprintf(file, "<script>\n");
    fprintf(file, "    window.addEventListener('load', function() {\n");
    fprintf(file, "        document.querySelector('.spinner-wrapper').style.display = 'none';\n");
    fprintf(file, "        document.getElementById('main-content').style.display = 'block';\n");
    fprintf(file, "    });\n");
    fprintf(file, "</script>\n");

    // Then add all other resources
    fprintf(file, "<meta charset=\"UTF-8\">\n");
    fprintf(file, "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n");
    fprintf(file, "<link href=\"https://fonts.googleapis.com/css?family=Krona One\" rel=\"stylesheet\">\n");
    fprintf(file, "<link rel=\"stylesheet\" type=\"text/css\" href=\"//fonts.googleapis.com/css?family=Anonymous+Pro\">\n");
    fprintf(file, "<link rel=\"stylesheet\" href=\"styles.css\">\n");
    fprintf(file, "<script src=\"java.js\" defer></script>\n");
    fprintf(file, "<title>My Website</title>\n</head>\n");
    
    return 0;
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

int testForInjection(char *input) 
{
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
    for (int i = 0; i < sizeof(xssPatterns) / sizeof(xssPatterns[0]); ++i) 
    {
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