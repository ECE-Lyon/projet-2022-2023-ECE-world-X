#include <stdio.h>
#include "ingame.h"

#define MAXHITOBJECT 5000

void printArr(XYT arr[], ALLEGRO_BITMAP *circle, int wombocombo, int life) {
    int i;
    for (i = 0; i < 20; i++) {
        if (arr[i].timing != 0) {
            al_draw_bitmap(circle, arr[i].x, arr[i].y, 0);
        }
    }
    al_flip_display();

    // remove points that need to be removed
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

void IsNoteHit(int *current_point, XYT tabXYT[], int offbeat, int score, int wombocombo, int life) {
    if (tabXYT[*current_point].timing >= clock() - offbeat - 200 ||
        tabXYT[*current_point].timing <= clock() - offbeat + 200) {
        wombocombo += 1;
        score += 3 * wombocombo;
        (*current_point)++;
        printf("yay");
    } else if (tabXYT[*current_point].timing >= clock() - offbeat - 400 ||
               tabXYT[*current_point].timing <= clock() - offbeat + 400) {
        wombocombo += 1;
        score += score * wombocombo;
        (*current_point)++;
        printf("mouais");
    } else {
        NoteMiss(&wombocombo, &life);
        (*current_point)++;
    }
}

void NoteMiss(int *wombocombo, int *life) {
    *wombocombo = 0;
    *life -= 1;
    printf("Nope");
}

bool IsCursorOnTarget(int current_point, XYT tabXYT[]) {
    ALLEGRO_MOUSE_STATE mouse_state;
    al_get_mouse_state(&mouse_state);
    int x = mouse_state.x;
    int y = mouse_state.y;
    if (tabXYT[current_point].x - 64 < x && tabXYT[current_point].x + 64 > x && tabXYT[current_point].y - 64 < y &&
        tabXYT[current_point].y + 64 > y) {
        return true;
    } else {
        return false;
    }
}


void GetInput(int current_point, XYT tabXYT[], int off_beat, int score, int wombocombo, int life, ALLEGRO_EVENT event) {
    if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
        switch (event.type) {
            case ALLEGRO_EVENT_KEY_DOWN:
                if (IsCursorOnTarget(current_point, tabXYT)) {
                    IsNoteHit(&current_point, tabXYT, off_beat, score, wombocombo, life);
                    break;
                } else {
                    NoteMiss(&wombocombo, &life);
                }
        }
    }
}


