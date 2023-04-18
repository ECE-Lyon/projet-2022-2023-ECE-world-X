//
// Created by Félix Pignal on 18/04/2023.
//

#include "test.h"
#include "constantes.h"

void init_ennemis(Ennemi *ennemi[]) {
    int i = 0;
    for (i = 0; i < NB_MAX_ENNEMIS; i++) {
        ennemi[i]-> vitesse = 20;
        ennemi[i]-> actif = 0;
    }
}


void affiche_ennemis(Ennemi *ennemi[]) {
    int i = 0;
    for (i = 0; i < NB_MAX_ENNEMIS; i++) {
        if (ennemi[i]-> actif) {
            printf("%d\n%d\n" ,ennemi[i]-> x, ennemi[i]-> y);
            al_clear_to_color(al_map_rgb(0,0,0));
            al_draw_bitmap(al_load_bitmap("../Images/Duck.png"),ennemi[i]-> x,ennemi[i]-> y,0);
            al_flip_display();
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
            ennemi[i]-> x = 2400;
            ennemi[i]-> y = 600;
            ennemi[i]->actif = 1;
        }
    }
}