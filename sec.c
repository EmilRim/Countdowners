#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "sec.h"

int headComponents(FILE *file)
{
    fprintf(file, "<!DOCTYPE html>\n\
<html lang=\" en \">\n<head>\n<meta charset=\" UTF -8 \" />\n<meta name=\" viewport \" content=\" width = device - width,initial - scale = 1.0 \" />\n\
<meta name=\"description\" content=\"An Advent Calendar\">\n\
  <meta name=\"author\" content=\"Countdowners\">\n\
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
}

int printTitle(FILE *file, char *title)
{
    fprintf(file, "<body>\n\
    <main id=\"blur\">\n");
    fprintf(file, "<h1>%s</h1>", title);
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
                "</div>\n",
                i);
    }
    fprintf(file, "</div>\n");
}

int validationForDaysNumber(int number)
{
    while (number < MIN_DAYS || number > MAX_DAYS)
    {
        printf("Please enter a number in a range [%d; %d]: ", MIN_DAYS, MAX_DAYS);
        fscanf(stdin, "%d", &number);
    }

    return number;
}

void getTheme(char *buttonImg, char *bottomImg, char *backgroundColor, char *fontColor)
{
    int theme = 0;

    while (1) {
        printf("Nustatykite svetainės temą (įrašykite tik skaičių):\n");
        printf("1. Snow\n");
        printf("2. Christmas\n");

        if (scanf("%d", &theme) == 1 && (getchar() == '\n')) {
            if (theme >= 1 && theme <= 2) {
                break;
            } else {
                printf("\nNetinkama įvestis. Turi būti skaičius 1 arba 2.\n");
            }
        } else {
            printf("Netinkama įvestis. Prašome įvesti skaičių.\n");
            while (getchar() != '\n');
        }
    }

    if(theme == 2){
        strcpy(buttonImg, "\"present.svg\"");
        strcpy(bottomImg, "\"lights.svg\"");
        strcpy(backgroundColor, "#562923");
        strcpy(fontColor, "rgb(255, 255, 255)");
    }
    else {
        strcpy(buttonImg, "\"snowball.svg\"");
        strcpy(bottomImg, "\"trees.svg\"");
        strcpy(backgroundColor, "linear-gradient(#6E8D97 0\%, #C3D0D5 40\%, #DEE4E6 100\%)");
        strcpy(fontColor, "rgb(64, 136, 140)");
    }
    
}