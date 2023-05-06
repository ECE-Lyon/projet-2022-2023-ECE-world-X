//
// Created by benja on 02/05/2023.
//

#include "countdown.h"
#include <allegro5/allegro_font.h>
void countdown(ALLEGRO_FONT *font) {
    int countdown_duration = 3;
    int screen_w = al_get_display_width(al_get_current_display());
    int screen_h = al_get_display_height(al_get_current_display());

    for (int i = countdown_duration; i > 0; i--) {
        al_clear_to_color(al_map_rgb(0, 0, 0));
        int textWidth = al_get_text_width(font, "3");
        int textHeight = al_get_font_line_height(font);
        int textX = (screen_w - textWidth) / 2;
        int textY = (screen_h - textHeight) / 2;

        al_draw_textf(font, al_map_rgb(255, 255, 255), textX, textY, ALLEGRO_ALIGN_LEFT, "%d", i);
        al_flip_display();
        al_rest(1.0);
    }
}
