#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "head.h"

// programos funkcijos
FILE *openFile(char *name)
{
    FILE *file = fopen(name, "w");
    if (file == NULL)
    {
        printf("AAAAAAAAA");
        perror("whoossie");
        return 0;
    }
    printf("whoop\n");
    return file;
}

int headComponents(FILE *file)
{
    printf("whoopwhoop\n");
    fprintf(file, "<!DOCTYPE html>\n\
<html lang=\" en \">\n<head>\n<meta charset=\" UTF -8 \" />\n<meta name=\" viewport \" content=\" width = device - width,initial - scale = 1.0 \" />\n\
<link\
      href=\"https://fonts.googleapis.com/css?family=Krona One\"\n\
      rel=\"stylesheet\"/>\n\
    <link\n\
      rel=\"stylesheet\"\n\
      type=\"text/css\"\n\
      href=\"//fonts.googleapis.com/css?family=Anonymous+Pro\"/>\n\
    <link rel=\"stylesheet\" href=\"styles.css\" />\n\
    <script src=\"java.js\"></script>\n\
    <title>My Website</title>");
    return 0;
}

int body(FILE *file, char *title)
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
                "</div>\n", i);
    }
    fprintf(file, "</div>\n");
}
