#include <stdio.h>

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <assert.h>

#include "snake.h"
#include "constante.h"
#include "interface.h"


#define FPS 60.0 //Timer


ALLEGRO_DISPLAY*setting( ){
    assert(al_init());
    ALLEGRO_DISPLAY*display=NULL;
    display=al_create_display(LARGEUR, LONGUEUR);
    assert(display!=NULL);
    //Initialiser avec assert le reste
    assert(al_init_image_addon());
    assert(al_init_primitives_addon());
    assert(al_install_keyboard());
    al_set_window_title(display,"Title");
    al_set_window_position(display,200,100);
    al_flip_display();
    return display;

}

void game(){
    ALLEGRO_DISPLAY* display=setting(LONGUEUR,LARGEUR);
    int isEnd=0;
    int longueur, largeur;
    longueur = LGAME/SIZEGAME;
    largeur = LARGAME/SIZEGAME;
    ALLEGRO_EVENT_QUEUE*queue;

    //Créer un timer si nécéssaire
    ALLEGRO_TIMER*timer=al_create_timer(1/FPS);
    al_start_timer(timer);
    queue=al_create_event_queue();
    assert(queue);

    al_register_event_source(queue,al_get_display_event_source(display));
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue,al_get_timer_event_source(timer));

    Body player;
    init_snake(&player);

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
                        printf("PIF HAUT");
                        player.direction = HAUT;
                        break;
                    case ALLEGRO_KEY_RIGHT :
                        player.direction = DROITE;
                        break;
                    case ALLEGRO_KEY_DOWN :
                        player.direction = BAS;
                        break;
                    case ALLEGRO_KEY_LEFT :
                        player.direction = GAUCHE;
                        break;
                }
                break;
            case ALLEGRO_EVENT_TIMER :
                update(&player, longueur, largeur);
                break;
        }




    }
    al_destroy_event_queue(queue);
}

int main() {
    game();
    return 0;
}
