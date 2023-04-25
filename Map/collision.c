//
// Created by trist on 25/04/2023.
//

#include "collision.h"
#include "character.h"
#include "background.h"


#include <stdlib.h>
#include <stdio.h>

void load_file_collision(char lst_collision[COLLISIONWI][COLLISIONHEI]) {
    FILE* lst = fopen("../Map/collision.txt", "r");
    if (lst == NULL) {
        printf("Can't open file\n");
    }
    for(int i=0; i<COLLISIONWI; i++) {
        for(int j=0; j<COLLISIONHEI; j++) {
            lst_collision[i][j] = fgetc(lst);
        }
    }
    /*for(int i=0; i<COLLISIONWI; i++) {
        for(int j=0; j<COLLISIONHEI; j++) {
            printf("%c", lst_collision[i][j]);
        }
        printf("\n");
    }*/
    fclose(lst);
}


int check_collision(Perso player,Background bar, int lst_collision[COLLISIONWI][COLLISIONHEI]) {
    char collision;
    switch (player.direction) {
        case B1:
        case B2:
        case B3:
            collision = lst_collision[abs(bar.x/SIZECOLLISION)][abs(bar.y/SIZECOLLISION+1)];
            if (bar.y-=SIZECOLLISION )
    }
}