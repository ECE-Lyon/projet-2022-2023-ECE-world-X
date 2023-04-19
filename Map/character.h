//
// Created by trist on 19/04/2023.
//
#include <allegro5/allegro.h>
#define NBANIMATION 12
#define STARTX 600
#define STARTY 300

#ifndef PROJET_CHARACTER_H
#define PROJET_CHARACTER_H

enum{B1, B2, B3, L1, L2, L3, R1, R2, R3, T1, T2, T3}; //B = bot, L = Left, R = Right, T = Top


typedef struct{
    int x,y, direction, state;
    ALLEGRO_BITMAP* anim[NBANIMATION];
}Perso;

void init_Luke(Perso* player);
void print_character(Perso player);

#endif //PROJET_CHARACTER_H
