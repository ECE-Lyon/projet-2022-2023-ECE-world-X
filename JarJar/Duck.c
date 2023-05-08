//
// Created by Félix Pignal on 18/04/2023.
//

#include "constantes.h"
#include "Duck.h"

void init_Duck(Coin *ducks) {
    int i = 0;
    for (i = 0; i < NB_MAX_JARJAR; i++) {// contion pour que tous les canards soient bien lancees sans depaser le nombre max defini
        ducks[i].x = 0;
        ducks[i].y = 0;
        ducks[i].vitesse = 3 + rand() % 10; // vitesse differente pour chaque canard
        ducks[i].actif = 0;// les canards ne sont pas appeles (en mode off)
        ducks[i].compte = false; //etat qui permet de verifier si les canards on bien ete pris en compte par le bateau
        ducks[i].Jarjar2 = al_load_bitmap("../JarJar/Images/JarJar2.png");// premiere image de l'animation
        ducks[i].Jarjar1 = al_load_bitmap("../JarJar/Images/JarJar1.png");
        ducks[i].Jarjar3 = al_load_bitmap("../JarJar/Images/JarJar3.png");
        ducks[i].Jarjar4 = al_load_bitmap("../JarJar/Images/JarJar4.png");
        ducks[i].largeur = al_get_bitmap_width(ducks[i].Jarjar1);
        ducks[i].hauteur = al_get_bitmap_height(ducks[i].Jarjar4);
        ducks[i].imageFrame = 0;// selection pour le switch case de l'animation
        ducks[i].fps = 0;

    }
}


void printDuck(Coin *ducks) {
    int i = 0;
    for (i = 0; i < NB_MAX_JARJAR; i++) {
        if (ducks[i].actif) {// si les canards sont actifs soit = 1
            ducks[i].fps += 1;
            if(ducks[i].fps >= 20){ //fonction qui permet le ralentissement de l'animation sans timer allegro
                ducks[i].imageFrame+=1;// changement de bitmap, passage a la suivante
                ducks[i].fps = 0;
            }
            switch (ducks[i].imageFrame) {
                case 0:{
                    al_draw_bitmap(ducks[i].Jarjar1,ducks[i].x,ducks[i].y,ALLEGRO_FLIP_HORIZONTAL);
                    break;
                }
                case 1:{
                    al_draw_bitmap(ducks[i].Jarjar2,ducks[i].x,ducks[i].y,ALLEGRO_FLIP_HORIZONTAL);
                    break;
                }
                case 2:{
                    al_draw_bitmap(ducks[i].Jarjar3,ducks[i].x,ducks[i].y,ALLEGRO_FLIP_HORIZONTAL);
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


void moveDuck(Coin *ducks) {// la fonction qui permet au cannetons de se deplacer le long de l'image
    int i = 0;
    for (i = 0; i < NB_MAX_JARJAR; i++) {
        if (ducks[i].actif) {
            ducks[i].x -= ducks[i].vitesse;//comme il commencent a gauche on soustrait a x et non pas ajouter a x
            if (ducks[i].x < 0) {
                ducks[i].actif = 0;// si les cannetons depase l'ecran a gauche, on les turn off, ceci libere une place dans notre tableau pour genere un nouveau canard
            }
        }
    }
}

void apparitionDuck(Coin *ducks) {
    int i = 0;
    for (i = 0; i < NB_MAX_JARJAR; i++) {
        if (!ducks[i].actif) {
            ducks[i].x = LARGEUR - ducks[i].largeur;//pour eviter qu'ils apparaissent en dehors de l'ecran
            ducks[i].y = ducks[i].hauteur + rand() % (HAUTEURMAX - (ducks[i].hauteur * 2));// fait apparaitre a des hauteur differentes
            ducks[i].actif = 1;//canard turn on
        }
    }
}


void duckReposition(Coin *ducks) {//si jamais le canneton est attrape par la cane peche
    int i = 0;
    for (int i = 0; i < NB_MAX_JARJAR; i++) {
        if(ducks[i].x < 0) { ducks[i].x = 0; }
        if(ducks[i].y < 0) { ducks[i].y = 0; }
        if(ducks[i].x+ducks[i].largeur > LARGEUR) { ducks[i].x = LARGEUR - ducks[i].largeur; }
        if(ducks[i].y+ducks[i].hauteur > HAUTEUR) { ducks[i].y = HAUTEUR - ducks[i].hauteur; }
    }
}

bool cane_active(int x, int y, Coin *duck) {// le canneton est survole par la cane a peche
    return (x >= duck->x && x <= (duck->x + duck->largeur) && y >= duck->y && y <= (duck->y + duck->hauteur));
}

bool duckOnBoat(Boat *smallboat, Coin *duck) {// retourne vrai pour la prise en compte du canard et le comptabiliser
    return (duck->x >= smallboat->x && duck->x <= smallboat->x + smallboat->l && duck->y >= smallboat->y && duck->y <= smallboat->y + smallboat->h);
}