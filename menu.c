//
// Created by benja on 27/04/2023.
//
#include "menu.h"
#include <stdbool.h>
#include <allegro5/allegro_font.h>
#include <stdio.h>

MenuItem menuItems[11] = {
        {"Choose your difficulty, warning, difficulties are exponential", false},
        {"Meco, Star Wars Theme",               false},
        {"Option 2",               false},
        {"Cantina Band",               false},
        {"Option 4",               false},
        {"Option 5",               false},
        {"Option 6",               false},
        {"Option 7",               false},
        {"Option 8",               false},
        {"Option 9",               false},
        {"Option 10",              false}
};

void drawMenu(ALLEGRO_FONT *font, int selectedItem, ALLEGRO_DISPLAY *display) {
    al_clear_to_color(al_map_rgb(0, 0, 0));
    int screen_w = al_get_display_width(display);
    int screen_h = al_get_display_height(display);
    ALLEGRO_BITMAP *background = al_load_bitmap("../design/osubg.png");
    ALLEGRO_BITMAP *buffer = al_create_bitmap(al_get_display_width(display), al_get_display_height(display));
    al_set_target_bitmap(buffer);
    al_draw_scaled_bitmap(background, 0, 0, al_get_bitmap_width(background), al_get_bitmap_height(background), 0, 0,
                          screen_w, screen_h, 0);
    al_set_target_bitmap(al_get_backbuffer(display));
    al_draw_bitmap(buffer, 0, 0, 0);

    int y = 100;
    for (int i = 0; i < 11; i++) {
        if (i == selectedItem) {
            al_draw_text(font, al_map_rgb(255, 0, 0), 400, y, ALLEGRO_ALIGN_CENTER, menuItems[i].text);
        } else {
            al_draw_text(font, al_map_rgb(255, 255, 255), 400, y, ALLEGRO_ALIGN_CENTER, menuItems[i].text);
        }
        y += 30;
    }
    al_flip_display();
}

int inTheMenu(ALLEGRO_FONT *font, ALLEGRO_EVENT_QUEUE *queue, int selectedItem, ALLEGRO_DISPLAY *display) {
    drawMenu(font, selectedItem, display);
    int screen_width = al_get_display_width(display);
    while (1) {
        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            al_destroy_display(display);
            exit(0);
        } else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch (event.keyboard.keycode) {
                case ALLEGRO_KEY_UP:
                    selectedItem--;
                    if (selectedItem < 0) {
                        selectedItem = 10;
                    }
                    drawMenu(font, selectedItem, display);
                    break;
                case ALLEGRO_KEY_DOWN:
                    selectedItem++;
                    if (selectedItem > 10) {
                        selectedItem = 0;
                    }
                    drawMenu(font, selectedItem, display);
                    break;
                case ALLEGRO_KEY_ENTER:
                    return selectedItem;
            }

        } else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            int mouseX = event.mouse.x;
            int mouseY = event.mouse.y;
            for (int i = 0; i < 11; i++) {
                int y = 100 + i * 30;
                int text_width = al_get_text_width(font, menuItems[i].text);
                int x = (screen_width - text_width) / 2;
                if (mouseX >= x && mouseX <= x + text_width && mouseY >= y - 15 && mouseY <= y + 15) {
                    selectedItem = i;
                    drawMenu(font, selectedItem, display);
                    printf("Selected item: %d\n", selectedItem);
                    return selectedItem;
                }
            }
        }
    }
}
