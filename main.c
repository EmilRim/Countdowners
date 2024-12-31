#include <stdio.h>
#include <stdlib.h>
#include "head.h"

int main()
{

    char buttonImg[32], bottomImg[32], backgroundColor[64], fontColor[32];

    getTheme(buttonImg, bottomImg, backgroundColor, fontColor);

    printf("%s\n%s\n%s\n%s\n\n", buttonImg, bottomImg, backgroundColor, fontColor);

    return 0;
}

/*
    <style>
        body {
            background: VARIABLE;
        }
        .grid-item button span {
            color: VARIABLE;
        }
    </style>
*/
