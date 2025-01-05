#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include "head.h"

int main()
{
    char **strings = (char**)malloc(sizeof(char*) * 10);
    
    for(int i = 0; i < 10; ++i){
        strings[i] = (char*)malloc(sizeof(char) * 64);
    }

    int a = getInQuotesTextFromFile("test.txt", strings, 10, 64);

    printf("%d\n", a);

    for(int i = 0; i < a; ++i){
        printf("%s\n", strings[i]);
    }
    return 0;
}