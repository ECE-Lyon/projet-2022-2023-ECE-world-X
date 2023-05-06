//
// Created by benja on 06/05/2023.
//

#include "endgame.h"

void save(const char *name, int score, int i) {
    FILE *file = NULL;
    if (i == 0) {
        file = fopen("../score.txt", "r"); // To delete previous scores
    } else {
        file = fopen("../score.txt", "a");
    }
    if (file == NULL) {
        printf("Error opening the file.\n");
        return;
    }
    fprintf(file, "Name: %s, Score: %d\n", name, score);
    fclose(file);
}

