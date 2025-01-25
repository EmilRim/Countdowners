#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "fun.h"
#include "sec.h"
#define MAX_LENGTH 25

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
    FILE *file = openFile("calendar.html");
    if (!file)
    {
        free(title);
        return 0;
    }

    printf("!!!WRITE PROGRAM DESCRIPTION!!!\n");
    printf("The pop-up messages are stored in a \"strings.txt\" file. If you want to make changes to the file please do it now. Do you want to continue? (y/n)\n");
    char answer = 0;
    scanf("%c", &answer);
    while(answer != 'y' && answer != 'n'){
        printf("Please enter y/n: ");
        scanf(" %c", &answer);
    }
    if(answer == 'n'){
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

    char **strings = malloc(number * sizeof(char *));
    for(int i = 0; i < number; ++i){
        strings[i] = malloc(64 * sizeof(char));
    }
    getStringsFromFile("strings.txt", strings, number, 64);
    removeQuotes(strings, number);

    // Write days counter
    dayCounter(file, number, buttonImg, strings);

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
    openHtml("calendar.html");

    return 0;
}