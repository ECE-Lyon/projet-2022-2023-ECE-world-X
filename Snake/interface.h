//
// Created by trist on 04/04/2023.
//
#include "snake.h"
#ifndef SNAKE_INTERFACE_H
#define SNAKE_INTERFACE_H

#include "plateau.h"
#include "../Map/character.h"


#define NBSTAR 250

typedef struct {
    int x, y;
}star;

void create_star_list(star bg_star[NBSTAR]);
void startgame(ALLEGRO_FONT* police,Perso player, star bg_star[NBSTAR]);
int update(Body* player,Waychange* lstchange, Food* pomme, star bg_star[NBSTAR], Damier board, ALLEGRO_BITMAP* stormtrooper, ALLEGRO_FONT* police, int* size);

#endif //SNAKE_INTERFACE_H
