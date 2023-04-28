//
// Created by trist on 28/04/2023.
//

#include "dialog.h"
#include <stdio.h>
#include "constante.h"
#define TEXTSIZE 50
#define SIZEBOX 100


void init_font (ALLEGRO_FONT** police) {
    *police = al_load_ttf_font("../Map/star_jedi/Starjedi.ttf", TEXTSIZE, 0);
    if (police == NULL) {
        printf("Police doesn't load\n");
    }
}

void set_textbox() {
    al_draw_filled_rectangle(0,HEIGHT-SIZEBOX, WIDTH, HEIGHT, al_map_rgb(0,0,0));
}