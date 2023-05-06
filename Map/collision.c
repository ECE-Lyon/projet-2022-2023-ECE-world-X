//
// Created by trist on 25/04/2023.
//

#include "collision.h"
#include "character.h"
#include "background.h"
#include "dialog.h"


#include <stdlib.h>
#include <stdio.h>

void update_map_pos(Mapcollision* poscollision, Background bar) {
    poscollision->posmapx = abs(bar.x-STARTXPERSO)/SIZECOLLISION;
    poscollision->posmapy = abs(bar.y-STARTYPERSO)/SIZECOLLISION;
}

void load_file_collision(int lst_collision[COLLISIONHEI][COLLISIONWI]) {
    FILE *fp = fopen("../Map/collision.txt", "r");

    // vérifier si le fichier a été ouvert avec succès
    if (fp == NULL) {
        printf("Impossible d'ouvrir le fichier\n");
    }
    for (int i = 0; i < COLLISIONHEI; i++) {
        for (int j = 0; j < COLLISIONWI; j++) {
            lst_collision[i][j] = getc(fp);
        }
    }

    // fermer le fichier
    fclose(fp);

    // afficher le tableau
    /*for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }*/
}

int check_eventmap(Perso player,Mapcollision poscollision,Background *bar, int lst_collision[COLLISIONHEI][COLLISIONWI], int Keys[NBKEYS]) {
    if(Keys[ENTER] == 1 && player.direction == B1 && lst_collision[poscollision.posmapy][poscollision.posmapx] == DEUX) {
        bar->y -= ENTERBAR;
    }
    else if(Keys[ENTER] == 1 && player.direction == T1 && lst_collision[poscollision.posmapy][poscollision.posmapx] == TROIS) {
        bar->y += ENTERBAR;
    }
    else if(Keys[ENTER] == 1 && player.direction == T1 && lst_collision[poscollision.posmapy][poscollision.posmapx] == QUATRE) {
        bar->y += ENTERSHIP;
    }
    else if(Keys[ENTER] == 1 && player.direction == B1 && lst_collision[poscollision.posmapy][poscollision.posmapx] == CINQ) {
        bar->y -= ENTERSHIP;
    }
    else if(Keys[ENTER] == 1 && player.direction == T1 && lst_collision[poscollision.posmapy][poscollision.posmapx] == SIX) {
        bar->y += ENTERTOILET;
    }
    else if(Keys[ENTER] == 1 && player.direction == B1 && lst_collision[poscollision.posmapy][poscollision.posmapx] == SEPT) {
        bar->y -= ENTERTOILET;
    }
    else if (Keys[ENTER] == 1 && lst_collision[poscollision.posmapy][poscollision.posmapx] == HUIT) {
        return PECHE;
    }
    else if (Keys[ENTER] == 1 && lst_collision[poscollision.posmapy][poscollision.posmapx] == S) {
        return SNAKE;
    }
    else if (Keys[ENTER] == 1 && lst_collision[poscollision.posmapy][poscollision.posmapx] == C) {
        return SHIP;
    }
    else if (Keys[ENTER] == 1 && lst_collision[poscollision.posmapy][poscollision.posmapx] == M) {
        return OSU;
    }
    else if (Keys[ENTER] == 1 && lst_collision[poscollision.posmapy][poscollision.posmapx] == YODA) {
        return TAPETAUPE;
    }
    else if (Keys[ENTER] == 1 && lst_collision[poscollision.posmapy][poscollision.posmapx] == NEUF) {
        return COURSE;
    }
    else if (Keys[ENTER] == 1 && lst_collision[poscollision.posmapy][poscollision.posmapx] == W) {
        return BARMAN;
    }
    else if (Keys[ENTER] == 1 && lst_collision[poscollision.posmapy][poscollision.posmapx] == P) {
        return STAT;
    }
    return 0;
}


int check_collision(Perso player, Mapcollision poscollision, int lst_collision[COLLISIONHEI][COLLISIONWI], int Keys[NBKEYS]) {
    //printf("%c lst[%d][%d]\n", lst_collision[poscollision.posmapy][poscollision.posmapx], poscollision.posmapx, poscollision.posmapy);
    switch (player.direction) {
        case B1:
            if(lst_collision[poscollision.posmapy+1][poscollision.posmapx] == ZERO && Keys[BAS] == 1) {
                return 1;
            }
            break;
        case T1 :
            if(lst_collision[poscollision.posmapy-1][poscollision.posmapx] == ZERO && Keys[HAUT] == 1) {
                return 1;
            }
            break;
        case R1 :
            if(lst_collision[poscollision.posmapy][poscollision.posmapx+1] == ZERO && Keys[DROITE] == 1) {
                return 1;
            }
            break;
        case L1 :
            if(lst_collision[poscollision.posmapy][poscollision.posmapx-1] == ZERO && Keys[GAUCHE] == 1) {
                return 1;
            }
            break;
    }
    return 0;
}