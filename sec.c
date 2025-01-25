#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "sec.h"
#include "fun.h"

int headComponents(FILE *file, char *backgroundColor, char *fontColor)
{
    fprintf(file,
            "<!DOCTYPE html>\n"
            "<html lang=\"en\">\n"
            "<head>\n"
            "    <meta charset=\"UTF-8\">\n"
            "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
            "    <meta name=\"description\" content=\"An Advent Calendar\">\n"
            "    <meta name=\"author\" content=\"Countdowners\">\n"
            "    <link href=\"https://fonts.googleapis.com/css?family=Krona+One\" rel=\"stylesheet\">\n"
            "    <link rel=\"stylesheet\" type=\"text/css\">\n"
            "    <link rel=\"icon\" type=\"image/x-icon\" href=\"present.png\">\n"
            "    <style>\n"
            "        body {\n"
            "            background: %s;\n"
            "        }\n"
            "        .grid-item button span {\n"
            "            color: %s;\n"
            "        }\n"
            "    </style>\n"
            "    <link rel=\"stylesheet\" href=\"styles.css\">\n"
            "    <script src=\"java.js\"></script>\n"
            "    <title>My Website</title>\n"
            "</head>\n",
            backgroundColor, fontColor);

    return 0;
}

int printTitle(FILE *file, char *title)
{
    fprintf(file,
            "<body>\n"
            "    <main id=\"blur\">\n"
            "        <h1>%s</h1>\n",
            title);

    return 0;
}

int dayCounter(FILE *file, int numberOfDays, char* buttonImg, char **texts)
{
    fprintf(file,
    "<div class=\"grid-container\">\n"
);
    for (int i = 1; i <= numberOfDays; ++i)
    {
        fprintf(file,
        "    <div class=\"grid-item\">\n"
        "        <button onclick=\"openPopup('%s')\">\n"
        "            <img src=%s>\n"
        "            <span>%d</span>\n"
        "        </button>\n"
        "    </div>\n",
        texts[i-1], buttonImg, i);
    }
    fprintf(file, "        </div>\n");

    return 0;
}

int getNumberOfDays(int number)
{
    printf("Please enter a number of days that you want in your Advent Calendar (max %d): ", MAX_DAYS);
    while(1){
        if (scanf("%d", &number) == 1 && (getchar() == '\n')) {
            if (number >= MIN_DAYS && number <= MAX_DAYS) {
                break;
            } else {
                printf("Invalid input. Please enter a number in a range [%d; %d]: ",  MIN_DAYS, MAX_DAYS);
            }
        } else {
            printf("Invalid input. Enter an integer: ");
            while (getchar() != '\n');
        }
    }

    return number;
}

void getTheme(char *buttonImg, char *bottomImg, char *backgroundColor, char *fontColor)
{
    int theme = 0;

    printf("Choose a website theme (enter only a number):\n");
    printf("1. Snow\n");
    printf("2. Christmas\n");

    while (1) {
        if (scanf("%d", &theme) == 1 && (getchar() == '\n')) {
            if (theme >= 1 && theme <= 2) {
                break;
            } else {
                printf("Invalid input. The options are 1 or 2: ");
            }
        } else {
            printf("Invalid input. Please enter an integer: ");
            while (getchar() != '\n');
        }
    }

    if (theme == 2)
    {
        strcpy(buttonImg, "\"present.svg\"");
        strcpy(bottomImg, "\"lights.svg\"");
        strcpy(backgroundColor, "linear-gradient(#562923 0%, #562923 40%, #562923 100%)");
        strcpy(fontColor, "rgb(255, 255, 255)");
    }
    else
    {
        strcpy(buttonImg, "\"snowball.svg\"");
        strcpy(bottomImg, "\"trees.svg\"");
        strcpy(backgroundColor, "linear-gradient(#6E8D97 0%, #C3D0D5 40%, #DEE4E6 100%)");
        strcpy(fontColor, "rgb(64, 136, 140)");
    }
}

void insertBottomImg(FILE *file, char *bottomImg)
{
    fprintf(file,
            "        <div class=\"trees\">\n"
            "            <img src=%s alt=\"BottomImg\">\n"
            "        </div>\n",
            bottomImg);
}

void popUpAppear(FILE *file)
{
    fprintf(file,
    "    <div class=\"popup-overlay\" id=\"popupOverlay\"></div>\n"
    "    <div class=\"popup\" id=\"popup\">\n"
    "        <p id=\"popupText\"></p>\n"
    "        <button onclick=\"togglePopup()\">Close</button>\n"
    "    </div>\n");
}

void removeQuotes(char **strings, int arraySize) {
    for (int i = 0; i < arraySize; ++i) {
        int len = strlen(strings[i]);
        for (int j = 0; j < len; j++) {
            if (strings[i][j] == 39 || strings[i][j] == 34) {
                memmove(strings[i] + j + 1, strings[i] + j, len - j + 1);
                strings[i][j] = 92;
                strings[i][j+1] = 39;
                len++;
                j++;
            }
        }
    }
}
