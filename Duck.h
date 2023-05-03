//
// Created by Félix Pignal on 18/04/2023.
//

#ifndef PROJET_DUCK_H
#define PROJET_DUCK_H

#define NB_MAX_JARJAR 5
#include "constantes.h"
//#include "duckGame.h"
#include "boat.h"

typedef struct {
    int x, y, hauteur, largeur;
    int vitesse,actif,imageFrame;
    bool compte;
    ALLEGRO_BITMAP *Jarjar1;
    ALLEGRO_BITMAP *Jarjar2;
    ALLEGRO_BITMAP *Jarjar3;
    ALLEGRO_BITMAP *Jarjar4;
} Coin;

void init_Duck(Coin *ducks);

void printDuck(Coin *ducks);

void moveDuck(Coin *ducks);

void apparitionDuck(Coin *ducks);

void duckReposition(Coin* ducks);

bool cane_active(int x, int y, Coin* ducks);

bool duckOnBoat(Boat *smallboat, Coin *duck);

#endif //PROJET_DUCK_H
