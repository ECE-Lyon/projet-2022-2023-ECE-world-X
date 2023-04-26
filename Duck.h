//
// Created by Félix Pignal on 18/04/2023.
//

#ifndef PROJET_TEST_H
#define PROJET_TEST_H

#define NB_MAX_ENNEMIS 5
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <assert.h>

typedef struct {
    int x, y, z, hauteur, largeur;
    int vitesse;
    int actif;
    int width, height;
    ALLEGRO_BITMAP *duckimage;
} Coin;

void init_Duck(Coin *ducks);

void printDuck(Coin *ducks);

void moveDuck(Coin *ducks);

void apparitionDuck(Coin *ducks);

void duckReposition(Coin* ducks);

bool cane_on_duck(int x, int y, int x1, int y1, int x2, int y2);

bool cane_active(int x, int y, Coin* ducks);

#endif //PROJET_TEST_H
