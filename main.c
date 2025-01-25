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

    printf("Welcome!"
"To use this program, please create a text file named strings.txt in the same folder as this program.\n\n"

"* Each line of the file will appear as a separate pop-up message.\n"
"* If the file has fewer lines than needed, some pop-ups will say, \"No input provided.\"\n"
"* If it has extra lines, only the first few will be used.\n\n");
    printf("The pop-up messages are stored in a \"strings.txt\" file. If you want to make changes to the file please do it now. Do you want to continue? (y/n): ");
    char answer = 0;
    scanf("%c", &answer);
    while(answer != 'y' && answer != 'n'){
        printf("Please enter y/n: ");
        scanf(" %c", &answer);
    }
    if(answer == 'n'){
        printf("The program is closing now.");
        return 0;
    }
    while (getchar() != '\n');

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
    number = getNumberOfDays(number);

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
    fprintf(file, "\n    </main>\n");
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