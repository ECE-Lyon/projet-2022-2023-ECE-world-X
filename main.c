#include <stdio.h>

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

#include "snake.h"
#include "constante.h"
#include "interface.h"
#include "miam.h"


#define FPS 6.0 //Timer


ALLEGRO_DISPLAY* setting(){
    assert(al_init());
    ALLEGRO_DISPLAY*display=NULL;
    display=al_create_display(WIDTH, HEIGHT);
    assert(display!=NULL);
    //Initialiser avec assert le reste
    assert(al_init_image_addon());
    assert(al_init_primitives_addon());
    assert(al_install_keyboard());
    al_set_window_title(display,"Title");
    al_set_window_position(display,200,100);
    al_flip_display();
    srand(time(NULL));
    return display;

}

void game(){
    ALLEGRO_DISPLAY* display=setting();
    int isEnd=0;
    int heightsquare, widthsquare;
    float fps;

    fps = 7.0f;
    widthsquare = WIGAME/NBSQUARE;
    heightsquare = HEIGAME/NBSQUARE;
    ALLEGRO_EVENT_QUEUE* queue;

    //Créer un timer si nécéssaire
    ALLEGRO_TIMER*timer=al_create_timer(1/fps);
    al_start_timer(timer);
    queue=al_create_event_queue();
    assert(queue);

    al_register_event_source(queue,al_get_display_event_source(display));
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue,al_get_timer_event_source(timer));

    Body* player;
    player = malloc(sizeof(Body));
    star bg_star[NBSTAR];
    Food pomme;

    init_snake(player);
    create_star_list(bg_star);
    init_apple(&pomme, widthsquare, heightsquare);

    enum {HAUT, DROITE, BAS, GAUCHE};

    while(!isEnd){
        ALLEGRO_EVENT event={0};
        al_wait_for_event(queue,&event);

        switch(event.type){//en fonction de son type (événement de souris,du clavier...),on agit
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                isEnd=1;
                break;
            case ALLEGRO_EVENT_KEY_DOWN://Si on arrive ici, c'est qu'on a pioché un événement du clavier de type touche  enfoncée
                switch(event.keyboard.keycode){//On vérifie de quelle touche il s'agit
                    case ALLEGRO_KEY_ESCAPE://on ne gère quel cas où la touche en foncée est ECHAP
                        isEnd=1;
                        break;
                    case ALLEGRO_KEY_UP :
                        if (player->direction != BAS) {
                            player->direction = HAUT;
                        }
                        break;
                    case ALLEGRO_KEY_RIGHT :
                        if (player->direction != GAUCHE) {
                            player->direction = DROITE;
                        }
                        break;
                    case ALLEGRO_KEY_DOWN :
                        if (player->direction != HAUT) {
                            player->direction = BAS;
                        }
                        break;
                    case ALLEGRO_KEY_LEFT :
                        if (player->direction != DROITE) {
                            player->direction = GAUCHE;
                        }
                        break;
                }
                break;
            case ALLEGRO_EVENT_TIMER :
                update(player, &pomme, bg_star, widthsquare, heightsquare);
                print_apple(pomme);
                break;
        }
    }
    al_destroy_event_queue(queue);
    free_snake(player);

}

int main() {
    game();
    return 0;
}
