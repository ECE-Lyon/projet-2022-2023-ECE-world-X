//
// Created by trist on 08/05/2023.
//
#define NBGAME 4
#define SIZECHAR 3
#include <stdlib.h>
#include <stdio.h>

void readscore() {
    char superscore[NBGAME][3];
    char line[3];
    FILE *fp = fopen("../Map/bestscore.txt", "r");
    for(int i=0; i<NBGAME; i++) {
        superscore[i] = fgets(line, sizeof(line), fp);
        printf("%s\n", superscore[i]);
    }
    fclose(fp);
}