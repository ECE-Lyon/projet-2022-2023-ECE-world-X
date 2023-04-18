//
// Created by Félix Pignal on 18/04/2023.
//

#ifndef PROJET_TEST_H
#define PROJET_TEST_H

#define NB_MAX_ENNEMIS 10
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

typedef struct {
    int x, y, z;
    int vitesse;
    int actif;
} DuckStruct;

void init_ennemis(DuckStruct canard[]);

void afficheDuck(DuckStruct canard[]);

void mouvement_ennemis(DuckStruct canard[]);

void apparition_ennemis(DuckStruct canard[]);


#endif //PROJET_TEST_H
