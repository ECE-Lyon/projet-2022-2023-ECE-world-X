//
// Created by benja on 19/04/2023.
//
#include "beatmap.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>

#ifndef OSU_INGAME_H
#define OSU_INGAME_H

void printArr(XYT arr[], ALLEGRO_BITMAP *circle, int *score, ALLEGRO_FONT *font);

void addToPrintedArr(XYT source[], XYT dest[], int current_point);

void shiftLeft(XYT arr[]);

void IsNoteHit(int *current_point, XYT tabXYT[], int timing, int *score, int wombocombo);

void NoteMiss(int *wombocombo);

void GetInput(int current_point, XYT tabXYT[], int off_beat, int *score, int wombocombo, ALLEGRO_EVENT event);

bool IsCursorOnTarget(int current_point, XYT tabXYT[]);

#endif //OSU_INGAME_H
