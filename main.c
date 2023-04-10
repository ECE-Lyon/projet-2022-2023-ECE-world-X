#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "beatmap.h"



int main() {
    int difficulty = 0;
    while (difficulty <= 0 && difficulty <= 10) {
        printf("Choose your difficulty (warning it is exponential)\n");
        scanf("%d", &difficulty);
    }
    getXYTime(difficulty);
    return 0;
}
// create circles

