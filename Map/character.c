//
// Created by trist on 19/04/2023.
//
#include "character.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>

#define MAXLETTERS 6

void init_Luke(Perso* player) {
    player->x = STARTX;
    player->y = STARTY;
    player->direction = B1;
    player->state = 0;
    player->anim[B1] = al_load_bitmap("../sprites/Luke/luke2.png");
    player->anim[B2] = al_load_bitmap("../sprites/Luke/luke1.png");
    player->anim[B3] = al_load_bitmap("../sprites/Luke/luke3.png");
    player->anim[R1] = al_load_bitmap("../sprites/Luke/luke5.png");
    player->anim[R2] = al_load_bitmap("../sprites/Luke/luke4.png");
    player->anim[R3] = al_load_bitmap("../sprites/Luke/luke6.png");
    player->anim[L1] = al_load_bitmap("../sprites/Luke/luke8.png");
    player->anim[L2] = al_load_bitmap("../sprites/Luke/luke7.png");
    player->anim[L3] = al_load_bitmap("../sprites/Luke/luke9.png");
    player->anim[T1] = al_load_bitmap("../sprites/Luke/luke11.png");
    player->anim[T2] = al_load_bitmap("../sprites/Luke/luke10.png");
    player->anim[T3] = al_load_bitmap("../sprites/Luke/luke12.png");
    for(int i=0; i<NBANIMATION; i++) {
        if(player->anim[i] == NULL) {
            printf("Erreur chargement image Luke\n");
        }
    }
}

void print_character(Perso player) {
    al_draw_bitmap(player.anim[player.direction], player.x, player.y, 0);
}
