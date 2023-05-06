//
// Created by benja on 27/04/2023.
//
#include "menu.h"
#include <stdbool.h>
#include <allegro5/allegro_font.h>
#include <stdio.h>

MenuItem menuItems[6] = {
        {"Choose your difficulty !!! exponential", false},
        {"Meco, Star Wars Theme",                  false},
        {"Luke Theme",                             false},
        {"Cantina Band",                           false},
        {"Meco Insane",                               false},
        {"Don't even try",                         false},
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

    int menuHeight = 30 * 6;  // Total height of the menu items
    int startY = (screen_h - menuHeight) / 2;  // Calculate the starting Y position for centering

    for (int i = 0; i < 6; i++) {
        int textWidth = al_get_text_width(font, menuItems[i].text);
        int textX = (screen_w - textWidth) / 2;  // Calculate the X position for centering
        int textY = startY + i * 30;  // Increment Y position for each menu item
        if (i == selectedItem) {
            al_draw_text(font, al_map_rgb(255, 255, 255), textX, textY, ALLEGRO_ALIGN_LEFT, menuItems[i].text);
        } else {
            al_draw_text(font, al_map_rgb(253, 245, 0), textX, textY, ALLEGRO_ALIGN_LEFT, menuItems[i].text);
        }
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
                        selectedItem = 5;
                    }
                    drawMenu(font, selectedItem, display);
                    break;
                case ALLEGRO_KEY_DOWN:
                    selectedItem++;
                    if (selectedItem > 5) {
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
            for (int i = 0; i < 5; i++) {
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


void beginning(ALLEGRO_FONT *font, ALLEGRO_EVENT_QUEUE *queue, ALLEGRO_DISPLAY *display, const char *name) {
    int displayWidth = al_get_display_width(display);
    int displayHeight = al_get_display_height(display);
    int textWidth = al_get_text_width(font, name);
    int textHeight = al_get_font_line_height(font);
    int centerX = displayWidth / 2 - textWidth / 2;
    int centerY = displayHeight / 2 - textHeight / 2;
    al_clear_to_color(al_map_rgb(0, 0, 0));
    ALLEGRO_BITMAP *background = al_load_bitmap("../design/osubg.png");
    ALLEGRO_BITMAP *buffer = al_create_bitmap(al_get_display_width(display), al_get_display_height(display));
    al_set_target_bitmap(buffer);
    al_draw_scaled_bitmap(background, 0, 0, al_get_bitmap_width(background), al_get_bitmap_height(background), 0, 0,
                          1200, 600, 0);
    al_set_target_bitmap(al_get_backbuffer(display));
    al_draw_bitmap(buffer, 0, 0, 0);
    al_draw_text(font, al_map_rgb(253, 245, 0), centerX, centerY, ALLEGRO_ALIGN_CENTER, name);
    int readyTextY = centerY + al_get_font_line_height(font);  // Adjust the Y position as needed
    al_draw_text(font, al_map_rgb(253, 245, 0), centerX, readyTextY, ALLEGRO_ALIGN_CENTER, "Are you ready? Press Enter");    al_flip_display();
    ALLEGRO_EVENT_QUEUE *eventQueue = al_create_event_queue();
    al_register_event_source(eventQueue, al_get_keyboard_event_source());

    bool enterPressed = false;

    while (!enterPressed) {
        ALLEGRO_EVENT event;
        al_wait_for_event(eventQueue, &event);

        if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                enterPressed = true;
            }
        }
    }
}
