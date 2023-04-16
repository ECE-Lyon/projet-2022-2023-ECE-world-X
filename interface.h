//
// Created by trist on 04/04/2023.
//
#include "snake.h"
#ifndef SNAKE_INTERFACE_H
#define SNAKE_INTERFACE_H

#include "plateau.h"

#define NBSTAR 25

typedef struct {
    int x, y;
}star;

void create_star_list(star bg_star[NBSTAR]);
int update(Body* player,Waychange* lstchange, Food* pomme, star bg_star[NBSTAR], Damier board);

#endif //SNAKE_INTERFACE_H
