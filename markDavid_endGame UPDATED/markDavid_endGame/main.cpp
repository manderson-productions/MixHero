//
//  main.cpp
//  markDavid_endGame but mainly davidEndGame....actually, mostly mark...
//
//  Created by Mark Anderson on 12/8/11.
//  Copyright 2011 markmakingmusic. All rights reserved.
//


//BITMAPS
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

//#include "main.h"

#define WIDTH 640
#define HEIGHT 480

int main (int argc, char **argv)
{
	//primitive variable
	bool done = false;
    
    //radius of the image: gives center of image
    //int imageRad = 20;
    
    int imageWidth = 0;
    int imageHeight = 0;
    
	//Allegro variables
	ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_BITMAP *image = NULL;
        
	//Initialization Functions
	if(!al_init())
		return -1;
    
	display = al_create_display(WIDTH, HEIGHT);
    
	if(!display)
		return -1;
    
    al_install_keyboard();
    al_init_image_addon();

    //create a 40 x 40 bitmap
    image = al_load_bitmap("logo.jpg");
    
    imageWidth = al_get_bitmap_width(image);
    imageHeight = al_get_bitmap_height(image);
    
    //the backbuffer is a bitmap...we always draw to that bitmap and it brings it to the front and draw it to screen
    
    //create event queue
    event_queue = al_create_event_queue();
        
    
    al_register_event_source (event_queue, al_get_keyboard_event_source());
    //al_register_event_source(event_queue, al_get_display_event_source(display));
    
       
	while (!done)
	{
        ALLEGRO_EVENT ev;
        al_wait_for_event (event_queue, &ev);
        
        if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch (ev.keyboard.keycode)
            {
                case ALLEGRO_KEY_ESCAPE:
                    done = true;
                    break;
            }
            //draws it from the upper left hand corner of the bmp...to center it, use the below code:
            al_draw_bitmap(image, WIDTH / 2 - imageWidth / 2, HEIGHT / 2 - imageHeight / 2, 0);
            al_flip_display();
            al_clear_to_color(al_map_rgb(0,0,0));
        }   
	}
    
    al_destroy_bitmap(image);
	al_destroy_display (display);	
    al_destroy_event_queue (event_queue);
       
	return 0;
}



/*
//FULL ASTEROIDS GAME BELOW USING PRIMITIVES AND FONTS:
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "main.h"

//GLOBALS==============================
const int WIDTH = 800;
const int HEIGHT = 400;
const int NUM_BULLETS = 5;
const int NUM_COMETS = 10;
enum KEYS {UP, DOWN, LEFT, RIGHT, SPACE};
bool keys[5] = {false, false, false, false, false};

//prototypes
void InitShip(SpaceShip &ship);
void DrawShip(SpaceShip &ship);
void MoveShipUp (SpaceShip &ship);
void MoveShipDown (SpaceShip &ship);
void MoveShipLeft (SpaceShip &ship);
void MoveShipRight (SpaceShip &ship);

void InitBullet (Bullet bullet[], int size);
void DrawBullet (Bullet bullet[], int size);
void FireBullet (Bullet bullet[], int size, SpaceShip &ship);
void UpdateBullet (Bullet bullet[], int size);
void CollideBullet (Bullet bullet[], int bSize, Comet comets[], int cSize, SpaceShip &ship);
void CollideComet (Comet comets[], int cSize, SpaceShip &ship);

void InitComet (Comet comets[], int size);
void DrawComet (Comet comets[], int size);
void StartComet (Comet comets[], int size);
void UpdateComet (Comet comets[], int size);

int main (int argc, char **argv)
{
	//primitive variable
	bool done = false;
    bool redraw = true;
    const int FPS = 60;
    bool isGameOver = false;
    
	//object variables
	SpaceShip ship;
    Bullet bullets[NUM_BULLETS];
    Comet comets[NUM_COMETS];
    
	//Allegro variables
	ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_FONT *font18 = NULL;
    
	//Initialization Functions
	if(!al_init())
		return -1;
    
	display = al_create_display(WIDTH, HEIGHT);
    
	if(!display)
		return -1;
    
	al_init_primitives_addon();
    al_install_keyboard();
    al_init_font_addon();
    al_init_ttf_addon();
    
    //create event queue
    event_queue = al_create_event_queue();
    timer = al_create_timer(1.0 / FPS);
    
    srand((int)time(NULL));
    
	InitShip(ship);
    InitBullet(bullets, NUM_BULLETS);
    InitComet (comets, NUM_COMETS);
    
    font18 = al_load_font("arial.ttf", 18, 0);
                        
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_display_event_source(display));
   
    al_start_timer(timer);
    
	while(!done)
	{
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);
    
        //this will only get run 1/60 of a second
        if (ev.type == ALLEGRO_EVENT_TIMER) {
            
            redraw = true;  
            
            if (keys[UP])
                MoveShipUp(ship);
            if (keys[DOWN])
                MoveShipDown(ship);
            if (keys[LEFT])
                MoveShipLeft(ship);
            if (keys[RIGHT])
                MoveShipRight(ship);

            //we only want these to happen if the game is over
            if (!isGameOver) {
                //update the bullets
                UpdateBullet (bullets, NUM_BULLETS);
                StartComet (comets, NUM_COMETS);
                UpdateComet (comets, NUM_COMETS);
                CollideBullet (bullets, NUM_BULLETS, comets, NUM_COMETS, ship);
                CollideComet (comets, NUM_COMETS, ship);
                
                //if two collisions occur we odnt want negative lives
                if (ship.lives <= 0)
                    isGameOver = true;
            }
        }
        else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            done = true;
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch (ev.keyboard.keycode)
            {
                case ALLEGRO_KEY_ESCAPE:
                    done = true;
                    break;
                case ALLEGRO_KEY_UP:
                    keys[UP] = true;
                    break;
                case ALLEGRO_KEY_DOWN:
                    keys[DOWN] = true;
                    break;
                case ALLEGRO_KEY_LEFT:
                    keys[LEFT] = true;
                    break;
                case ALLEGRO_KEY_RIGHT:
                    keys[RIGHT] = true;
                    break;
                case ALLEGRO_KEY_SPACE:
                    keys[SPACE] = true;
                    FireBullet (bullets, NUM_BULLETS, ship);
                    break;
            }
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
            switch (ev.keyboard.keycode)
            {
                case ALLEGRO_KEY_ESCAPE:
                    done = false;
                    break;
                case ALLEGRO_KEY_UP:
                    keys[UP] = false;
                    break;
                case ALLEGRO_KEY_DOWN:
                    keys[DOWN] = false;
                    break;
                case ALLEGRO_KEY_LEFT:
                    keys[LEFT] = false;
                    break;
                case ALLEGRO_KEY_RIGHT:
                    keys[RIGHT] = false;
                    break;
                case ALLEGRO_KEY_SPACE:
                    keys[SPACE] = false;
                    break;
            }
        }
        if (redraw && al_is_event_queue_empty(event_queue)) {
            
            redraw = false;
            
            if (!isGameOver) {
                DrawShip (ship);
                DrawBullet (bullets, NUM_BULLETS);
                DrawComet (comets, NUM_COMETS);
                
                al_draw_textf (font18, al_map_rgb(255, 0, 255), 5, 5, 0, "Player has %d lives left. Player has destroyed %d objects", ship.lives, ship.score);
            }
            else {
                al_draw_textf (font18, al_map_rgb(0, 255, 255), WIDTH /2, HEIGHT / 2, ALLEGRO_ALIGN_CENTRE, "Game Over. Final Score: %d", ship.score);
            }
            al_flip_display();
            al_clear_to_color(al_map_rgb(0,0,0));

        }   
	}
    
	al_destroy_display(display);	
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);
    al_destroy_font(font18);
    
	return 0;
}

void InitShip (SpaceShip &ship)
{
	ship.x = 20;
	ship.y = HEIGHT / 2;
	ship.ID = PLAYER;
	ship.lives = 3;
	ship.speed = 7;
	ship.boundx = 6;
	ship.boundy = 7;
	ship.score = 0;
}

void DrawShip (SpaceShip &ship)
{
	al_draw_filled_rectangle(ship.x, ship.y - 9, ship.x + 10, ship.y - 7, al_map_rgb(255, 0, 0));
	al_draw_filled_rectangle(ship.x, ship.y + 9, ship.x + 10, ship.y + 7, al_map_rgb(255, 0, 0));
    
	al_draw_filled_triangle(ship.x - 12, ship.y - 17, ship.x + 12, ship.y, ship.x - 12, ship.y + 17, al_map_rgb(0, 255, 0));
	al_draw_filled_rectangle(ship.x - 12, ship.y - 2, ship.x + 15, ship.y + 2, al_map_rgb(0, 0, 255));
}

void MoveShipUp (SpaceShip &ship) {
    ship.y -= ship.speed;
    if (ship.y < 0)
        ship.y = 0;
}
void MoveShipDown (SpaceShip &ship) {
    ship.y += ship.speed;
    if (ship.y > HEIGHT)
        ship.y = HEIGHT;
}
void MoveShipLeft (SpaceShip &ship) {
    ship.x -= ship.speed;
    if (ship.x < 0)
        ship.x = 0;
}
void MoveShipRight (SpaceShip &ship) {
    ship.x += ship.speed;
    if (ship.x > 300)
        ship.x = 300;
}

void InitBullet (Bullet bullet[], int size) {
    for (int i = 0; i < size; i++) {
        bullet[i].ID = BULLET;
        bullet[i].speed = 10;
        bullet[i].live = false;
    }
}
void DrawBullet (Bullet bullet[], int size) {
    for (int i = 0; i < size; i++) {
        if (bullet[i].live)
            al_draw_filled_circle(bullet[i].x, bullet[i].y, 2, al_map_rgb(255, 0, 255));
    }
}
void FireBullet (Bullet bullet[], int size, SpaceShip &ship) {
    for (int i = 0; i < size; i++) {
        if (!bullet[i].live) {
            bullet[i].x = ship.x + 17;
            bullet[i].y = ship.y;
            bullet[i].live = true;
            //stops all five bullets from firing
            break;
        }
    }
}

//updates the positioning of the bullet
void UpdateBullet (Bullet bullet[], int size) {
    for (int i = 0; i < size; i++) {
        if (bullet[i].live) {
            bullet[i].x += bullet[i].speed;
            if (bullet[i].x > WIDTH)
                bullet[i].live = false;
        }
    }
}

void InitComet (Comet comets[], int size) {
    for (int i = 0; i < size; i++) {
        
        comets[i].ID = ENEMY;
        comets[i].live = false;
        comets[i].speed = 5;
        comets[i].boundx = 18;
        comets[i].boundy = 18;
    }
}
void DrawComet (Comet comets[], int size) {
    for (int i = 0; i < size; i++) {
        if (comets[i].live) {
            al_draw_filled_circle(comets[i].x, comets[i].y, 20, al_map_rgb (255, 0, 0));
        }
    }
}
void StartComet (Comet comets[], int size) {
    for (int i = 0; i < size; i++) {
        if (!comets[i].live) {
            //every cycle we're randomly generating number. A zero will randomly generate once every 500 times
            if (rand() % 500 == 0) {
                comets[i].live = true;
                comets[i].x = WIDTH;
                comets[i].y = 30 + rand() % (HEIGHT - 60);
                
                break;
            }
        }
    }
    
}
void UpdateComet (Comet comets[], int size) {
    for (int i = 0; i < size; i++) {
        if (comets[i].live) {
            comets[i].x -= comets[i].speed;
           
        }
    }
}
void CollideBullet (Bullet bullet[], int bSize, Comet comets[], int cSize, SpaceShip &ship) {
    //need to iterate through the array of bullets and array of comets and test to see whether or not
    //they are inside each other
    for (int i = 0; i < bSize; i++) {
        if (bullet[i].live) {
            for (int j = 0; j < cSize; j++) {
                if (comets[j].live) {
                    //if up is more up than the down. if down is more down than the up. if left is more left than the right. if right is more right than the left
                    //just going to use an x y of the bullet...
                    if (bullet[i].x > (comets[j].x - comets[j].boundx) && bullet[i].x < (comets[j].x + comets[j].boundx) && bullet[i].y > (comets[j].y - comets[j].boundy) && bullet[i].y < (comets[j].y + comets[j].boundy)) {
                       
                        bullet[i].live = false;
                        comets[j].live = false;
                        
                        ship.score++;
                    }
                }
                
            }
        }
    }
}
void CollideComet (Comet comets[], int cSize, SpaceShip &ship) {
    for (int i = 0; i < cSize; i++) {
        if (comets[i].live) {
            //using 2 bounding boxes for comet and the player
            if (comets[i].live) {
                //if left side of comet is more left than right side of ship
                
                if (comets[i].x - comets[i].boundx < ship.x + ship.boundx && 
                    comets[i].x + comets[i].boundx > ship.x - ship.boundx && 
                    comets[i].y - comets[i].boundy < ship.y + ship.boundy && 
                    comets[i].y + comets[i].boundy > ship.y - ship.boundy) 
                {

                    ship.lives--;
                    comets[i].live = false;
                }
                //if the comet goes off the screen, you lose a life as well
                else if (comets[i].x < 0) {
                    comets[i].live = false;
                    ship.lives--;
                }
            }
        }
    }
}
*/

