#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "fun.h"
#include "sec.h"
#define MAX_LENGTH 20

int main()
{
    char *title = NULL;
    int number; // number of days

    // Allocate memory for title
    title = calloc(MAX_LENGTH + 2, sizeof(char));
    if (!title)
    {
        printf("Error allocating memory!\n");
        return 0;
    }

    // Open file for writing HTML
    FILE *file = openFile("test.html");
    if (!file)
    {
        free(title);
        return 0;
    }


    char buttonImg[64];
    char bottomImg[64];
    char backgroundColor[64];
    char fontColor[64];
    getTheme(buttonImg, bottomImg, backgroundColor, fontColor);

    // Write head section
    headComponents(file, backgroundColor, fontColor);
    fprintf(file, "\n  </head>");

    // Get valid title input
    title = getValidTitleInput(title, MAX_LENGTH);

    // Write body section with title
    printTitle(file, title);

    // Prompt and validate the number of days
    printf("Number of days: ");
    fscanf(stdin, "%d", &number);
    number = validationForDaysNumber(number);

    // Write days counter
    dayCounter(file, number, buttonImg);

    insertBottomImg(file, bottomImg);

    // Finalize HTML structure
    fprintf(file, "\n</main>\n");
    popUpAppear(file);
    fprintf(file, "</body>");
    fprintf(file, "\n</html>");
    fclose(file);

    // Free allocated memory
    free(title);

    // Open the HTML file in the default browser
    openHtml("test.html");

    return 0;
}