//
// Created by benja on 02/05/2023.
//

#include "countdown.h"
#include <allegro5/allegro_font.h>
void countdown(ALLEGRO_FONT *font){
    int countdown_duration = 3;
    for (int i = countdown_duration; i > 0; i--)
    {
        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_textf(font, al_map_rgb(255, 255, 255), 320, 240, ALLEGRO_ALIGN_CENTER, "%d", i);
        al_flip_display();
        al_rest(1.0);
    }

}