//
// Created by benja on 19/04/2023.
//
#include "beatmap.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#ifndef OSU_INGAME_H
#define OSU_INGAME_H

void printArr(XYT arr[], ALLEGRO_BITMAP* circle);

void addToPrintedArr(XYT source[], XYT dest[], int current_point);

void shiftLeft(XYT arr[]);

void checkForKeyboardInput(ALLEGRO_EVENT_QUEUE* event_queue);
#endif //OSU_INGAME_H
