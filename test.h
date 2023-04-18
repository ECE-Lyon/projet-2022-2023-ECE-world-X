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
} Ennemi;

void init_ennemis(Ennemi *ennemi[]);

void affiche_ennemis(Ennemi *ennemi[]);

void mouvement_ennemis(Ennemi *ennemi[]);

void apparition_ennemis(Ennemi *ennemi[]);


#endif //PROJET_TEST_H
