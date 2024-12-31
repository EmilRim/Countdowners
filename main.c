#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "head.h"

int main()
{
    char title[255];
    int number; //number of days
    printf("maine\n");
    FILE * file = openFile("test.html");
    headComponents(file);
    fprintf(file, "\n  </head>");
    printf("kokio title nori?\n");
    fscanf(stdin, "%255[^\n]", &title);
    body(file, title);
    printf("kiek dienu?\n");
    fscanf(stdin, "%d", &number);

    while(number < 1 || number > 30)
    {
        printf("Please enter a number in a range [1; 30]: ");
        fscanf(stdin, "%d", &number);
    }
    dayCounter(file, number);

    fprintf(file, "\n</main>\n</body>");
    fprintf(file, "\n</html>");
    fclose(file);

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