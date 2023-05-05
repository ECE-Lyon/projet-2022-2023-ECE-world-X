#include "Ship.h"
#include "const.h"

#include <stdio.h>
#include <allegro5/allegro.h>

void init_ships(Ship ships[NB_SHIPS]) {
    int i = 0;
    for (i = 0; i < NB_SHIPS; i++) {
        ships[i].speed = 1 + rand() % 4;
        ships[i].destroyed = false;
        ships[i].size = (rand() % 3) + 1;
        if (ships[i].size == 1) {
            ships->ship1 = al_load_bitmap("../Ships/Pictures/ship100.png");
            ships->explosion1 = al_load_bitmap("../Ships/Pictures/explosion100.png");
            ships[i].width = ships[i].length = 100;
        } else if (ships[i].size == 2) {
            ships->ship2 = al_load_bitmap("../Ships/Pictures/ship75.png");
            ships->explosion2 = al_load_bitmap("../Ships/Pictures/explosion75.png");
            ships[i].width = ships[i].length = 75;
        } else if (ships[i].size == 3) {
            ships->ship3 = al_load_bitmap("../Ships/Pictures/ship50.png");
            ships->explosion3 = al_load_bitmap("../Ships/Pictures/explosion50.png");
            ships[i].width = ships[i].length = 50;
        }
    }
}

void spawn_ships(Ship ships[NB_SHIPS]) {
    int i = 0;
    for (i = 0; i < NB_SHIPS; i++) {
        if (ships[i].destroyed == 0) {
            ships[i].y = 10 + rand() % (400 - ships[i].length);
            if (ships[i].y >= 10 && ships[i].y <= 185) {
                ships[i].x = 65 + (rand() % (SCREEN_WIDTH - (65 + ships[i].width)));
            } else if (ships[i].y > 185 && ships[i].y <= 335) {
                ships[i].x = 250 + (rand() % (SCREEN_WIDTH - (250 + ships[i].width)));
            } else if (ships[i].y > 335 && ships[i].y <= 410) {
                ships[i].x = 350 + (rand() % (SCREEN_WIDTH - (350 + ships[i].width)));
            }
        }
    }
}

void display_ships(Ship ships[NB_SHIPS]) {
    int i = 0;
    for (i = 0; i < NB_SHIPS; i++) {
        if (ships[i].destroyed == 0) {
            if (ships[i].y >= 10 && ships[i].y + ships[i].width <= 185 && ships[i].x >= 65 &&
                ships[i].x + ships[i].width <= 1135) {
                if (ships[i].size == 1) {
                    al_draw_bitmap(ships->ship1, ships[i].x, ships[i].y, 0);
                } else if (ships[i].size == 2) {
                    al_draw_bitmap(ships->ship2, ships[i].x, ships[i].y, 0);
                } else if (ships[i].size == 3) {
                    al_draw_bitmap(ships->ship3, ships[i].x, ships[i].y, 0);
                }
            } else if (ships[i].y + ships[i].width > 185 && ships[i].y + ships[i].width <= 335 &&
                       ships[i].x + ships[i].width >= 250 &&
                       ships[i].x + ships[i].width <= 950) {
                if (ships[i].size == 1) {
                    al_draw_bitmap(ships->ship1, ships[i].x, ships[i].y, 0);
                } else if (ships[i].size == 2) {
                    al_draw_bitmap(ships->ship2, ships[i].x, ships[i].y, 0);
                } else if (ships[i].size == 3) {
                    al_draw_bitmap(ships->ship3, ships[i].x, ships[i].y, 0);
                }
            } else if (ships[i].y + ships[i].width > 335 && ships[i].y + ships[i].length <= 410 &&
                       ships[i].x + ships[i].width >= 350 &&
                       ships[i].x + ships[i].width <= 850) {
                if (ships[i].size == 1) {
                    al_draw_bitmap(ships->ship1, ships[i].x, ships[i].y, 0);
                } else if (ships[i].size == 2) {
                    al_draw_bitmap(ships->ship2, ships[i].x, ships[i].y, 0);
                } else if (ships[i].size == 3) {
                    al_draw_bitmap(ships->ship3, ships[i].x, ships[i].y, 0);
                }
            }
        }
    }
}

void move_ships(Ship ships[NB_SHIPS]) {
    srand(time(NULL));
    int i = 0;
    int direction = 0;
    for (i = 0; i < NB_SHIPS; i++) {
        if (ships[i].destroyed == 0) {
            direction = rand() % 4;
            switch (direction) {
                case 0:
                    ships[i].y -= ships[i].speed;
                    break;
                case 1:
                    ships[i].y += ships[i].speed;
                    break;
                case 2:
                    ships[i].x -= ships[i].speed;
                    break;
                case 3:
                    ships[i].x += ships[i].speed;
                    break;
            }
            if (ships[i].x < 65 && ships[i].y > 10 && ships[i].y < 185) {
                ships[i].x = 1135 - ships[i].width;

            } else if (ships[i].x + ships[i].width > 1135 && ships[i].y > 10 && ships[i].y < 185) {
                ships[i].x = 65;

            } else if (ships[i].x < 250 && ships[i].y > 185 && ships[i].y < 335) {
                ships[i].x = 950 - ships[i].width;

            } else if (ships[i].x + ships[i].width > 950 && ships[i].y > 185 && ships[i].y < 335) {
                ships[i].x = 250;

            } else if (ships[i].x < 350 && ships[i].y > 335 && ships[i].y < 410) {
                ships[i].x = 850 - ships[i].width;

            } else if (ships[i].x + ships[i].width > 850 && ships[i].y > 335 && ships[i].y < 410) {
                ships[i].x = 350;

            } else if (ships[i].y < 10) {
                if (ships[i].x > 65 && ships[i].x < 250) {
                    ships[i].y = 185;

                } else if (ships[i].x + ships[i].width < 1135 && ships[i].x + ships[i].width > 950) {
                    ships[i].y = 185;

                } else if (ships[i].x > 250 && ships[i].x < 350) {
                    ships[i].y = 335;

                } else if (ships[i].x + ships[i].width < 950 && ships[i].x + ships[i].width > 850) {
                    ships[i].y = 335;

                } else if (ships[i].x > 350 && ships[i].x < 850) {
                    ships[i].y = 410;

                }

            } else if (ships[i].y > 185 && ships[i].x > 65 && ships[i].x < 250) {
                ships[i].y = 10;

            } else if (ships[i].y > 185 && ships[i].x + ships[i].width < 1135 && ships[i].x + ships[i].width > 950) {
                ships[i].y = 10;

            } else if (ships[i].y > 335 && ships[i].x > 250 && ships[i].x < 350) {
                ships[i].y = 10;

            } else if (ships[i].y > 335 && ships[i].x + ships[i].width < 950 && ships[i].x + ships[i].width > 850) {
                ships[i].y = 10;

            } else if (ships[i].y > 410 && ships[i].x > 350 && ships[i].x < 850) {
                ships[i].y = 10;

            }
        }
    }
}