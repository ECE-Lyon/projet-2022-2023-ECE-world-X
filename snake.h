//
// Created by trist on 04/04/2023.
//

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include "miam.h"
#include "plateau.h"

#ifndef SNAKE_SNAKE_H
#define SNAKE_SNAKE_H

enum{HAUT,DROITE,BAS, GAUCHE};


typedef struct Part{
    int x,y;
    int direction;
    ALLEGRO_BITMAP* img;
    struct Part* next;
}Body;

void init_snake(Body* player);
void print_player(Body* player);
void move_player(Body* player, Damier board);
int bordure(Body* player, Damier board);
int check_food(Body *player, Food pomme);
void add(Body* player, Damier board);
void free_snake(Body* player);
void change_all_direction(Body* player, int direction);

#endif //SNAKE_SNAKE_H
