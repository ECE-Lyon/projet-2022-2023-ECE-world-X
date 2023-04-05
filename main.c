#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "beatmap.h"



int main() {
    int difficulty = 0;
    while (difficulty <= 0 && difficulty <= 10){
        printf("Choisissez votre difficulté (attention elle est exponentielle), entre 1 et 10 inclus\n");
        scanf("%d", &difficulty);
    }
    getTimeXY(difficulty);
// create circles
    return 0;
}
