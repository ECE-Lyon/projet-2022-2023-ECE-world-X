//
// Created by trist on 04/04/2023.
//

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "miam.h"

#ifndef SNAKE_SNAKE_H
#define SNAKE_SNAKE_H

typedef struct Part{
    int x,y;
    int direction;
    ALLEGRO_BITMAP* img;
    struct Part* next;
}Body;

void init_snake(Body* player);
void print_player(Body player);
void move_player(Body* player, int wi, int hei);
int bordure(Body player, int wi, int hei);
int check_food(Body player, Food pomme);

#endif //SNAKE_SNAKE_H
