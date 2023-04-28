//
// Created by Félix Pignal on 18/04/2023.
//

#include "constantes.h"

void init_Duck(Coin *ducks) {
    int i = 0;
    for (i = 0; i < NB_MAX_ENNEMIS; i++) {
        ducks[i].x = 0;
        ducks[i].y = 0;
        ducks[i].vitesse = 2 + rand() % 3;
        ducks[i].actif = 0;
        ducks[i].duckimage = al_load_bitmap("../Images/Duck.png");
        ducks[i].largeur = al_get_bitmap_width(ducks[i].duckimage);
        ducks[i].hauteur = al_get_bitmap_height(ducks[i].duckimage);
    }
}


void printDuck(Coin *ducks) {
    int i = 0;
    for (i = 0; i < NB_MAX_ENNEMIS; i++) {
        if (ducks[i].actif) {
            al_draw_bitmap(ducks[i].duckimage, ducks[i].x, ducks[i].y, ALLEGRO_FLIP_HORIZONTAL);
        }
    }
}

void moveDuck(Coin *ducks) {
    int i = 0;
    for (i = 0; i < NB_MAX_ENNEMIS; i++) {
        if (ducks[i].actif) {
            ducks[i].x -= ducks[i].vitesse;
            if (ducks[i].x < 0) {
                ducks[i].actif = 0;
            }
        }
    }
}

void apparitionDuck(Coin *ducks) {
    int i = 0;
    for (i = 0; i < NB_MAX_ENNEMIS; i++) {
        if (!ducks[i].actif) {
            ducks[i].x = LARGEUR - ducks[i].largeur;
            ducks[i].y = ducks[i].hauteur + rand() % (HAUTEURMAX - (ducks[i].hauteur * 2));
            ducks[i].actif = 1;
        }
    }
}


void duckReposition(Coin* ducks) {
    for (int i = 0; i < NB_MAX_ENNEMIS; i++) {
        if(ducks[i].x < 0) { ducks[i].x = 0; }
        if(ducks[i].y < 0) { ducks[i].y = 0; }
        if(ducks[i].x+ducks[i].largeur > LARGEUR) { ducks[i].x = LARGEUR - ducks[i].largeur; }
        if(ducks[i].y+ducks[i].hauteur > HAUTEUR) { ducks[i].y = HAUTEUR - ducks[i].hauteur; }
    }
}
bool cane_on_duck(int x, int y, int x1, int y1, int x2, int y2){
    printf("x >= %d && %d <= %d && %d >= %d && %d < %d\n", x, x1, x, x2, y, y1, y, y2);
    return x >= x1 && x <= x2 && y >= y1 && y < y2;
}

/*bool cane_active(int x, int y, Coin* ducks) {
    return cane_on_duck(x, y, ducks->x, ducks->y, ducks->x + ducks->largeur, ducks->y + ducks->hauteur);
}*/

bool cane_active(int x, int y, Coin *duck) {
    printf("Mouse click: x = %d, y = %d\n", x, y);
    printf("Duck bounding box: x = %d, y = %d, width = %d, height = %d\n", duck->x, duck->y, duck->largeur, duck->hauteur);
    return (x >= duck->x && x <= (duck->x + duck->largeur) && y >= duck->y && y <= (duck->y + duck->hauteur));
}