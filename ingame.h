//
// Created by benja on 19/04/2023.
//
#include "beatmap.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#ifndef OSU_INGAME_H
#define OSU_INGAME_H

void printArr(XYT arr[], ALLEGRO_BITMAP* circle, int wombocombo, int life);

void addToPrintedArr(XYT source[], XYT dest[], int current_point);

void shiftLeft(XYT arr[]);

void checkForKeyboardInput(ALLEGRO_EVENT_QUEUE* event_queue, int current_point, XYT tabXYT[], int timing, int score, int wombocombo, int life);

void IsNoteHit(int *current_point, XYT tabXYT[], int timing, int score, int wombocombo, int life);

void NoteMiss(int* wombocombo, int *life);

void GetInput(int current_point, XYT tabXYT[], int off_beat, int score, int wombocombo, int life, ALLEGRO_EVENT event);

bool IsCursorOnTarget(int current_point, XYT tabXYT[]);
#endif //OSU_INGAME_H
