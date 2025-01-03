#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "head.h"
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

    // Write head section
    headComponents(file);
    fprintf(file, "\n  </head>");

    // Get valid title input
    title = getValidTitleInput(title, MAX_LENGTH);

    // Write body section with title
    body(file, title);

    // Prompt and validate the number of days
    printf("Kiek dienų?\n");
    fscanf(stdin, "%d", &number);
    number = validationForDaysNumber(number);

    // Write days counter
    dayCounter(file, number);

    // Finalize HTML structure
    fprintf(file, "\n</main>\n</div>\n</body>");
    fprintf(file, "\n</html>");
    fclose(file);

    // Free allocated memory
    free(title);

    // Open the HTML file in the default browser
#ifdef _WIN32
    system("start test.html");
#elif __APPLE__
    system("open test.html");
#else
    system("xdg-open test.html");
#endif

    return 0;
}
