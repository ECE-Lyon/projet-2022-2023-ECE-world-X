//
// Created by Félix Pignal on 19/04/2023.
//

#ifndef PROJET_BOAT_H
#define PROJET_BOAT_H

typedef struct {
    int x, y, h, l, frame, fps;
    int score, actif;
    ALLEGRO_BITMAP *boaty;
} Boat;

void printBoat(Boat* smallboat);

void init_boat(Boat* smallBoat);



#endif //PROJET_BOAT_H
