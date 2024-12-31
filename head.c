#include <stdio.h>
#include <string.h>
#include "head.h"

void getTheme(char *buttonImg, char *bottomImg, char *backgroundColor, char *fontColor)
{
    int theme = 0;

    while (1) {
        printf("Nustatykite svetainės temą (įrašykite tik skaičių):\n");
        printf("1. Snow\n");
        printf("2. Christmas\n");

        if (scanf("%d", &theme) == 1 && (getchar() == '\n')) {
            if (theme >= 1 && theme <= 2) {
                break;
            } else {
                printf("\nNetinkama įvestis. Turi būti skaičius 1 arba 2.\n");
            }
        } else {
            printf("Netinkama įvestis. Prašome įvesti skaičių.\n");
            while (getchar() != '\n');
        }
    }

    if(theme == 2){
        strcpy(buttonImg, "\"present.svg\"");
        strcpy(bottomImg, "\"lights.svg\"");
        strcpy(backgroundColor, "#562923");
        strcpy(fontColor, "rgb(255, 255, 255)");
    }
    else {
        strcpy(buttonImg, "\"snowball.svg\"");
        strcpy(bottomImg, "\"trees.svg\"");
        strcpy(backgroundColor, "linear-gradient(#6E8D97 0\%, #C3D0D5 40\%, #DEE4E6 100\%)");
        strcpy(fontColor, "rgb(64, 136, 140)");
    }
    
}