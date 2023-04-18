//
// Created by Félix Pignal on 18/04/2023.
//

#include "test.h"
#include "constantes.h"

void init_ennemis(DuckStruct canard[]) {
    int i = 0;
    for (i = 0; i < NB_MAX_ENNEMIS; i++) {
        canard[i].vitesse = 2 + rand() % 3;
        canard[i].actif = 0;
    }
}


void afficheDuck(DuckStruct canard[]) {
    int i = 0;
    for (i = 0; i < NB_MAX_ENNEMIS; i++) {
        if (canard[i].actif) {
            al_load_bitmap("../Images/Duck.png");
        }
    }
}

void mouvement_ennemis(DuckStruct canard[]) {
    int i = 0;
    for (i = 0; i < NB_MAX_ENNEMIS; i++) {
        if (canard[i].actif) {
            canard[i].x -= canard[i].vitesse;
            if (canard[i].x - canard[i].width < 0) {
                canard[i].actif = 0;
            }
        }
    }
}

void apparition_ennemis(DuckStruct canard[]) {
    int i = 0;
    for (i = 0; i < NB_MAX_ENNEMIS; i++) {
        if (!canard[i].actif && rand() % 1000 < 10) {
            canard[i].x = LARGEUR - canard[i].width;
            canard[i].y = canard[i].height + rand() % (HAUTEUR - (canard[i].height * 2));
            canard[i].actif = 1;
        }
    }
}