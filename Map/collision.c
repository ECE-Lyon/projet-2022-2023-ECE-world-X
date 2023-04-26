//
// Created by trist on 25/04/2023.
//

#include "collision.h"
#include "character.h"
#include "background.h"


#include <stdlib.h>
#include <stdio.h>

void update_map_pos(Mapcollision* poscollision, Background bar) {
    poscollision->posmapx = abs(bar.x-STARTX)/SIZECOLLISION-1;
    poscollision->posmapy = abs(bar.y-STARTY)/SIZECOLLISION-1;
}

void load_file_collision(char lst_collision[COLLISIONWI][COLLISIONHEI]) {
    //Résoudre lecture fichier.... indice/boucle
    FILE* lst = fopen("../Map/collision.txt", "r");
    if (lst == NULL) {
        printf("Can't open file\n");
    }
    for(int i=0; i<COLLISIONWI; i++) {
        for(int j=0; j<COLLISIONHEI; j++) {
            fscanf(lst, "%c", &lst_collision[i][j]);
        }
    }
    printf("%c\n", lst_collision[76][28]);
    for(int i=0; i<COLLISIONWI; i++) {
        for(int j=0; j<COLLISIONHEI; j++) {
            printf("%c", lst_collision[i][j]);
        }
        printf("\n");
    }
    fclose(lst);
}


int check_collision(Perso player, Mapcollision poscollision, char lst_collision[COLLISIONWI][COLLISIONHEI]) {
    char collision;
    switch (player.direction) {
        case B1:
        case B2:
        case B3:
            printf("%c x:%d, y:%d\n", lst_collision[poscollision.posmapx][poscollision.posmapy], poscollision.posmapx, poscollision.posmapy);
            if(lst_collision[poscollision.posmapx*COLLISIONWI][poscollision.posmapy*COLLISIONHEI] == '0') {
                //
            }
            break;
    }
}