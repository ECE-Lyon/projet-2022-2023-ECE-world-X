//
// Created by trist on 19/04/2023.
//
#include <allegro5/allegro.h>
#include "constante.h"
#define NBANIMATION 12


#ifndef PROJET_CHARACTER_H
#define PROJET_CHARACTER_H

enum{B1, B2, B3, L1, L2, L3, R1, R2, R3, T1, T2, T3}; //B = bot, L = Left, R = Right, T = Top


typedef struct{
    int x,y, direction, state, ticket;
    ALLEGRO_BITMAP* anim[NBANIMATION];
    ALLEGRO_BITMAP* img;
}Perso;

void init_Luke(Perso* player);
void print_character(Perso player);
void animation(Perso* player, int Keys[NBKEYS]);

#endif //PROJET_CHARACTER_H
