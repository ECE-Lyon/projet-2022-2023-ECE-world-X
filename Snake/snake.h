//
// Created by trist on 04/04/2023.
//

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include "miam.h"
#include "plateau.h"

#define NBHEAD 4

#ifndef SNAKE_SNAKE_H
#define SNAKE_SNAKE_H

typedef enum{HAUT,DROITE,BAS, GAUCHE} E_direction;

typedef struct Mdirec {
    int x,y;
    E_direction direction;
    struct Mdirec* next;
} Waychange;

typedef struct Part {
    int x,y;
    E_direction direction;
    ALLEGRO_BITMAP* img[NBHEAD];
    Waychange* nextchange;
    struct Part* next;
} Body;

void init_snake(Body* player);
void print_player(Body* player);
void move_player(Body* player, Damier board);
int bordure(Body* player, Damier board);
int check_food(Body *player, Food pomme);
void add_body(Body* player, Waychange* lstchange, Damier board);
void free_snake(Body* player);
void change_direction(Body* player, int direction);
Waychange* add_change_way(Body* player, Waychange** lstchange);
void move_body(Body* player, Damier board);
void debuglst (Waychange *l);
void set_change(Body* player, Waychange* lstchange);
int check_body_collision(Body* playerhead, Body* playerbody);
int size_snake(Body* player, int size);



#endif //SNAKE_SNAKE_H
