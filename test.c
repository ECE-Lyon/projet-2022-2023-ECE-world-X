//
// Created by Félix Pignal on 18/04/2023.
//

#include <stdlib.h>
#include <allegro5/allegro.h>
#include "test.h"
#include "constantes.h"

void init_ennemis(Ennemi *ennemi[]) {
    int i = 0;
    for (i = 0; i < NB_MAX_ENNEMIS; i++) {
        ennemi[i]-> vitesse = 2 + rand() % 3;
        ennemi[i]-> actif = 0;
        ennemi[i]-> width = 10 + rand() % 20;
        ennemi[i]-> height = ennemi[i]-> width * 2 / 3;
        ennemi[i] -> duck = al_load_bitmap("../Images/Duck.png");
    }
}


void affiche_ennemis(Ennemi *ennemi[]) {
    int i = 0;
    for (i = 0; i < NB_MAX_ENNEMIS; i++) {
        if (ennemi[i]-> actif) {
            printf("%d\n%d\n" ,ennemi[i]-> x, ennemi[i]-> y);
            al_draw_bitmap(ennemi[i] -> duck, ennemi[i]-> x, ennemi[i]-> y, ALLEGRO_FLIP_HORIZONTAL);
        }
    }
}

void mouvement_ennemis(Ennemi *ennemi[]) {
    int i = 0;
    for (i = 0; i < NB_MAX_ENNEMIS; i++) {
        if (ennemi[i]->actif) {
            ennemi[i]-> x -= ennemi[i]-> vitesse;
            if (ennemi[i]-> x < 0) {
                ennemi[i]->actif = 0;
            }
        }
    }
}

void apparition_ennemis(Ennemi *ennemi[]) {
    int i = 0;
    for (i = 0; i < NB_MAX_ENNEMIS; i++) {
        if (!ennemi[i]->actif) {
            ennemi[i]-> x = LARGEUR - ennemi[i]-> width;
            ennemi[i]-> y = ennemi[i]-> height + rand() % (HAUTEURMAX - (ennemi[i]-> height * 2));
            ennemi[i]->actif = 1;
        }
    }
}