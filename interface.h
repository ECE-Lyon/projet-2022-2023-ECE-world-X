//
// Created by trist on 04/04/2023.
//
#include "snake.h"
#ifndef SNAKE_INTERFACE_H
#define SNAKE_INTERFACE_H

#define NBSTAR 500

typedef struct {
    int x, y;
}star;

void create_star_list(star bg_star[NBSTAR]);
void update(Body* player,Food* pomme, star bg_star[NBSTAR], int longueur, int largeur);

#endif //SNAKE_INTERFACE_H
