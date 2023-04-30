//
// Created by trist on 25/04/2023.
//
#include "constante.h"
#include "background.h"
#include "character.h"
#include "dialog.h"

#ifndef PROJET_COLLISION_H
#define PROJET_COLLISION_H

typedef struct {
    int posmapx, posmapy;
}Mapcollision;

void update_map_pos(Mapcollision* poscollision, Background bar);
void load_file_collision(int lst_collision[COLLISIONHEI][COLLISIONWI]);
int check_collision(Perso player, Mapcollision poscollision, int lst_collision[COLLISIONHEI][COLLISIONWI], int Keys[NBKEYS]);
int check_eventmap(Perso player,Mapcollision poscollision,Background *bar, int lst_collision[COLLISIONHEI][COLLISIONWI], int Keys[NBKEYS]);
void choose_event_pnj (Choose bb8, ALLEGRO_FONT* police, int res, int* dialogstate);


#endif //PROJET_COLLISION_H
