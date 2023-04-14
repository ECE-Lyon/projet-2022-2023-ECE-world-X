//
// Created by Félix Pignal on 14/04/2023.
//

#ifndef PROJET_DUCK_H
#define PROJET_DUCK_H

typedef struct {
    int x, y, largeur, hauteur;
} Duck;

void duckReposition(Duck* r);

void duckPosition(Duck* r, int lar, int haut);

void dessiner(Duck r);

bool pointEstDansRect(int x, int y, Duck r);

bool pointEstDansZone(int x, int y, int x1, int y1, int x2, int y2);
#endif //PROJET_DUCK_H
