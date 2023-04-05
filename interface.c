//
// Created by trist on 04/04/2023.
//
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>

#include "constante.h"
#include "interface.h"
#include "snake.h"




void create_map(int longueur, int largeur) {
    int x, y;
    int indice = 0;
    x = STARTX;
    y = STARTY;

    for(int i = 0; i<SIZEGAME; i++) {
        for(int j = 0; j<SIZEGAME; j++) {
            switch (indice) {
                case 0 :
                    al_draw_filled_rectangle(x, y, x+largeur, y+longueur, al_map_rgb(173,230,200));
                    indice = 1;
                    break;
                case 1 :
                    al_draw_filled_rectangle(x, y, x+largeur, y+longueur, al_map_rgb(151,226,181));
                    indice = 0;
                    break;
            }
            x += largeur;
        }
        y+=longueur;
        x=STARTX;
    }
    al_flip_display();
}

void update(Body* player, int longueur, int largeur) {
    al_clear_to_color(al_map_rgb(212, 255, 196));
    create_map(longueur, largeur);
    move_player(player);
    print_player(*player);

}