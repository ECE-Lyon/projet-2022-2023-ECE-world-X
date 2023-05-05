//
// Created by trist on 19/04/2023.
//
#include "character.h"
#include "constante.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>

#define MAXLETTERS 6

void init_Luke(Perso* player) {
    player->x = STARTXPERSO;
    player->y = STARTYPERSO;
    player->direction = B1;
    player->state = 0;
    player->score = 0;
    player->anim[B1] = al_load_bitmap("../sprites/Luke/luke2.png");
    player->anim[B2] = al_load_bitmap("../sprites/Luke/luke1.png");
    player->anim[B3] = al_load_bitmap("../sprites/Luke/luke3.png");
    player->anim[L1] = al_load_bitmap("../sprites/Luke/luke5.png");
    player->anim[L2] = al_load_bitmap("../sprites/Luke/luke4.png");
    player->anim[L3] = al_load_bitmap("../sprites/Luke/luke6.png");
    player->anim[R1] = al_load_bitmap("../sprites/Luke/luke8.png");
    player->anim[R2] = al_load_bitmap("../sprites/Luke/luke7.png");
    player->anim[R3] = al_load_bitmap("../sprites/Luke/luke9.png");
    player->anim[T1] = al_load_bitmap("../sprites/Luke/luke11.png");
    player->anim[T2] = al_load_bitmap("../sprites/Luke/luke10.png");
    player->anim[T3] = al_load_bitmap("../sprites/Luke/luke12.png");
    player->img = player->anim[B1];
    player->ticket = NBTICKET;
    for(int i=0; i<NBANIMATION; i++) {
        if(player->anim[i] == NULL) {
            printf("Erreur chargement image Luke\n");
        }
    }
}

void init_vador(Perso* player) {
    player->x = STARTXPERSO;
    player->y = STARTYPERSO;
    player->direction = B1;
    player->state = 0;
    player->score = 0;
    player->anim[B1] = al_load_bitmap("../sprites/Vador/Vador1.png");
    player->anim[B2] = al_load_bitmap("../sprites/Vador/Vador2.png");
    player->anim[B3] = al_load_bitmap("../sprites/Vador/Vador3.png");
    player->anim[L1] = al_load_bitmap("../sprites/Vador/Vador4.png");
    player->anim[L2] = al_load_bitmap("../sprites/Vador/Vador5.png");
    player->anim[L3] = al_load_bitmap("../sprites/Vador/Vador6.png");
    player->anim[R1] = al_load_bitmap("../sprites/Vador/Vador7.png");
    player->anim[R2] = al_load_bitmap("../sprites/Vador/Vador8.png");
    player->anim[R3] = al_load_bitmap("../sprites/Vador/Vador9.png");
    player->anim[T1] = al_load_bitmap("../sprites/Vador/Vador10.png");
    player->anim[T2] = al_load_bitmap("../sprites/Vador/Vador11.png");
    player->anim[T3] = al_load_bitmap("../sprites/Vador/Vador12.png");
    player->img = player->anim[B1];
    player->ticket = NBTICKET;
    for(int i=0; i<NBANIMATION; i++) {
        if(player->anim[i] == NULL) {
            printf("Erreur chargement image Luke\n");
        }
    }
}

void print_character(Perso player) {
    al_draw_bitmap(player.img, player.x, player.y, 0);
}

void animation(Perso* player, int Keys[NBKEYS]) {
    int v1 = -1;
    int v2 = -1;
    if (Keys[HAUT] == 1) {
        v1 = T2;
        v2 = T3;
    }
    else if (Keys[GAUCHE] == 1) {
        v1 = L2;
        v2 = L3;
    }
    else if (Keys[DROITE] == 1){
        v1 = R2;
        v2 = R3;
    }
    else if (Keys[BAS] == 1) {
        v1 = B2;
        v2 = B3;
    }
    if (v1 != -1 && v2 != -1) {
        switch(player->state) {
            case 0:
                player->img = player->anim[v1];
                player->state = 1;
                break;
            case 1 :
                player->img = player->anim[v2];
                player->state = 0;
                break;
        }
    }
}