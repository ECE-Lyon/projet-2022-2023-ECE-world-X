//
// Created by benja on 19/04/2023.
//
#include "beatmap.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#ifndef OSU_INGAME_H
#define OSU_INGAME_H

void removeFirst(XYT tab[], int size);
void draw_circles(XYT tabXYT[], int off_beat);
void addObjectsArr(XYT source[], XYT dest[], int current_point);

void printArr(XYT arr[], int current_time, int size);

#endif //OSU_INGAME_H
