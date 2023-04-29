//
// Created by Félix Pignal on 18/04/2023.
//

#ifndef PROJET_TEST_H
#define PROJET_TEST_H

#define NB_MAX_ENNEMIS 5
#include "constantes.h"
#include "duckGame.h"
#include "boat.h"

typedef struct {
    int x, y, hauteur, largeur;
    int vitesse;
    int actif;
    bool compte;
    ALLEGRO_BITMAP *duckimage;
} Coin;

void init_Duck(Coin *ducks);

void printDuck(Coin *ducks);

void moveDuck(Coin *ducks);

void apparitionDuck(Coin *ducks);

void duckReposition(Coin* ducks);

bool cane_active(int x, int y, Coin* ducks);

bool duckOnBoat(Boat *smallboat, Coin *duck);

#endif //PROJET_TEST_H
