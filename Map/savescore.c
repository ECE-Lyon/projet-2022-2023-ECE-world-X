//
// Created by trist on 08/05/2023.
//
#define SIZECHAR 3
#include <stdlib.h>
#include <stdio.h>
#include "constante.h"

void readscore(int superscore[NBGAME]) {
    int indice =0 ;
    FILE *filescore = fopen("../Map/bestscore.txt", "r");
    char line[100];
    int num;

    if(filescore == NULL) {
        printf("File doesn't load\n");
        return;
    }

    while(fgets(line, sizeof(line), filescore)) {
        num = atoi(line);
        superscore[indice] = num;
        indice++;
    }
    fclose(filescore);

}

void writescore(int superscore[NBGAME]) {
    FILE *filescore = fopen("../Map/bestscore.txt", "w");
    for(int i=0; i<NBGAME; i++) {
        fprintf(filescore, "%d\n", superscore[i]);
    }
    fclose(filescore);
}