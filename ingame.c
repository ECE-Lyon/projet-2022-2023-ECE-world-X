#include <stdio.h>
#include <stdlib.h>
#include "ingame.h"

#define MAXHITOBJECT 5000

void printArr(XYT arr[], ALLEGRO_BITMAP *circle) {
    int i;
    for (i = 0; i < 20; i++) {
        if (arr[i].timing != 0) {
            al_draw_bitmap(circle, arr[i].x, arr[i].y, 0);
        }
    }
    al_flip_display();

    // remove points that are missed
    int j = 0;
    while (j < i && arr[j].timing < clock() - 500) {
        for (; j < 20 - 1; j++) {
            arr[j] = arr[j + 1];
        }
        i--;
    }
}


void addToPrintedArr(XYT source[], XYT dest[], int current_point) {
    dest[19].x = source[current_point].x;
    dest[19].y = source[current_point].y;
    dest[19].timing = source[current_point].timing;
    shiftLeft(dest);
}

void shiftLeft(XYT arr[]) {
    for (int i = 0; i < 20 - 1; i++) {
        arr[i] = arr[i + 1];
    }
    arr[20 - 1].x = 0;
    arr[20 - 1].y = 0;
    arr[20 - 1].timing = 0;

}


void checkForKeyboardInput(ALLEGRO_EVENT_QUEUE *event_queue, int current_point, XYT tabXYT[], int timing, int score,
                           int wombocombo, int life) {
    ALLEGRO_EVENT event;
    al_get_next_event(event_queue, &event);

    if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
        switch (event.keyboard.keycode) {
            case ALLEGRO_KEY_Q:
                IsNoteHit(current_point, tabXYT, timing, score, wombocombo, life);
            case ALLEGRO_KEY_S:
                printf("S\n");
                break;
            default:
                break;
        }
    }
}

void IsNoteHit(int current_point, XYT tabXYT[], int offbeat, int score, int wombocombo, int life) {
    printf("Hit Detected ! \n");
    if (tabXYT[current_point].timing >= clock()-offbeat - 200 || tabXYT[current_point].timing <= clock()-offbeat + 200) {
        wombocombo += 1;
        score += 3 * wombocombo;
        printf("Yay\n");
    }
    else if (tabXYT[current_point].timing >= clock()-offbeat - 400 || tabXYT[current_point].timing <= clock()-offbeat + 400) {
        wombocombo += 1;
        score += 1 * wombocombo;
        printf("Mouais\n");
    }
    else{
        NoteMiss(wombocombo, life);
    }
}

void NoteMiss(int wombocombo, int life){
    wombocombo = 0;
    life-=1;
}