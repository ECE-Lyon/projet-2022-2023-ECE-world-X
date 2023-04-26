//
// Created by trist on 25/04/2023.
//
#include "constante.h"
#include "background.h"
#include "character.h"

#ifndef PROJET_COLLISION_H
#define PROJET_COLLISION_H

typedef struct {
    int posmapx, posmapy;
}Mapcollision;

void update_map_pos(Mapcollision* poscollision, Background bar);
void load_file_collision(char lst_collision[COLLISIONWI][COLLISIONHEI]);
int check_collision(Perso player, Mapcollision poscollision, char lst_collision[COLLISIONWI][COLLISIONHEI]);

#endif //PROJET_COLLISION_H
