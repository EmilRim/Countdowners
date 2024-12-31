#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "head.h"
#define MAX_LENGTH 20

#define MAX_DAYS 30
#define MIN_DAYS 1

int main()
{

   // char title[MAX_LENGTH + 2];
    char* title = NULL;
    int number; //number of days
    title = calloc(MAX_LENGTH+2, sizeof(char));
    if(!title)
    {
        printf("Error allocating memory!");
        return 0;   
    }

    FILE *file = openFile("test.html");
    headComponents(file);
    fprintf(file, "\n  </head>");
    title = getValidTitleInput(title, MAX_LENGTH);
    printTitle(file, title);
    printf("kiek dienu?\n");
    fscanf(stdin, "%d", &number);

    while(number < MIN_DAYS || number > MAX_DAYS)
    {
        printf("Please enter a number in a range [%d; %d]: ", MIN_DAYS, MAX_DAYS);
        fscanf(stdin, "%d", &number);
    }
    dayCounter(file, number);
    fprintf(file, "\n</main>\n</body>");
    fprintf(file, "\n</html>");
    fclose(file);

     //Open the HTML file in the default browser
#ifdef _WIN32
    system("start test.html");
#elif __APPLE__
    system("open test.html");
#else
    system("xdg-open test.html");
#endif

    return 0;

}