//
// Created by trist on 04/04/2023.
//

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#ifndef SNAKE_SNAKE_H
#define SNAKE_SNAKE_H


typedef struct Part{
    int x,y;
    int speed;
    int direction;
    ALLEGRO_BITMAP* img;
    struct Part* next;
}Body;


void init_snake(Body* player);
void print_player(Body player);
void move_player(Body* player);
#endif //SNAKE_SNAKE_H
