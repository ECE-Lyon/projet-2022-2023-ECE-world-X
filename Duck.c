//
// Created by Félix Pignal on 18/04/2023.
//

#include "constantes.h"

void init_Duck(Coin *ducks) {
    int i = 0;
    for (i = 0; i < NB_MAX_ENNEMIS; i++) {
        ducks[i].x = 0;
        ducks[i].y = 0;
        ducks[i].vitesse = 5 + rand() % 10;
        ducks[i].actif = 0;
        ducks[i].compte = false;
        ducks[i].Jarjar1 = al_load_bitmap("../Images/JarJar1.png");
        ducks[i].Jarjar2 = al_load_bitmap("../Images/JarJar2.png");
        ducks[i].Jarjar3 = al_load_bitmap("../Images/JarJar3.png");
        ducks[i].Jarjar4 = al_load_bitmap("../Images/JarJar4.png");
        ducks[i].largeur = al_get_bitmap_width(ducks[i].Jarjar1);
        ducks[i].hauteur = al_get_bitmap_height(ducks[i].Jarjar1);
        ducks[i].imageFrame = 0;

    }
}


void printDuck(Coin *ducks) {
    int i = 0;
    int fps = 0;
    for (i = 0; i < NB_MAX_ENNEMIS; i++) {
        if (ducks[i].actif) {
            fps ++;
            if(fps >=5){
                ducks[i].imageFrame++;
                fps = 0;
            }
            switch (ducks[i].imageFrame) {
                case 0:{
                    al_draw_bitmap(ducks[i].Jarjar1,ducks[i].x,ducks[i].y,ALLEGRO_FLIP_HORIZONTAL);
                    ducks[i].imageFrame+=1;
                    break;
                }
                case 1:{
                    al_draw_bitmap(ducks[i].Jarjar2,ducks[i].x,ducks[i].y,ALLEGRO_FLIP_HORIZONTAL);
                    ducks[i].imageFrame+=1;
                    break;
                }
                case 2:{
                    al_draw_bitmap(ducks[i].Jarjar3,ducks[i].x,ducks[i].y,ALLEGRO_FLIP_HORIZONTAL);
                    ducks[i].imageFrame+=1;
                    break;
                }
                case 3:{
                    al_draw_bitmap(ducks[i].Jarjar4,ducks[i].x,ducks[i].y,ALLEGRO_FLIP_HORIZONTAL);
                    ducks[i].imageFrame = 0;
                    break;
                }
            }
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
    int i = 0;
    for (int i = 0; i < NB_MAX_ENNEMIS; i++) {
        if(ducks[i].x < 0) { ducks[i].x = 0; }
        if(ducks[i].y < 0) { ducks[i].y = 0; }
        if(ducks[i].x+ducks[i].largeur > LARGEUR) { ducks[i].x = LARGEUR - ducks[i].largeur; }
        if(ducks[i].y+ducks[i].hauteur > HAUTEUR) { ducks[i].y = HAUTEUR - ducks[i].hauteur; }
    }
}

bool cane_active(int x, int y, Coin *duck) {
    return (x >= duck->x && x <= (duck->x + duck->largeur) && y >= duck->y && y <= (duck->y + duck->hauteur));
}

bool duckOnBoat(Boat *smallboat, Coin *duck) {
    return (duck->x >= smallboat->x && duck->x <= smallboat->x + smallboat->l && duck->y >= smallboat->y && duck->y <= smallboat->y + smallboat->h);
}