#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "head.h"
#define MAX_LENGTH 20

int main()
{
   // char title[MAX_LENGTH + 2];
    char* title = NULL;
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
