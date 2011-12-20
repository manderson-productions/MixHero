//
//  main.c
//  Mix Hero
//
//  Created by Mark Anderson and David Forshee
//  
//  C Programming for Music Technology
//  Final Project

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <math.h>
#include "mainStuff.h"


// GLOBAL VARIABLES
bool isRoundOver = false;
bool isStartMenu = true;
bool isEndOfMonth = false;
bool isAboutScreen = false;

// Bool flags for each character
bool isKennyG = false;
bool isPDiddy = false;
bool isKingTubby = false;
bool isDimebagDarrell = false;

// Flag is needed to know when to draw the backbuffer to the front
bool redraw = false;

// Float used for Frames per Second
const float FPS = 60.0;

// Defines game screen width and height
#define WIDTH 950
#define HEIGHT 800

// Main function
int main (int argc, char **argv)
{
	// Primitive variables
	bool done = false;
    bool isScoreCalculated = false;
    
    // Float values for scoring
    const float ideal_hiphop_ratio1 = .903, ideal_hiphop_ratio2 = 1.067, ideal_hiphop_ratio3 = .891;
    const float ideal_rock_ratio1 = 1.109, ideal_rock_ratio2 = .914, ideal_rock_ratio3 = 1.085;
    const float ideal_jazz_ratio1 = 1.139, ideal_jazz_ratio2 = .878, ideal_jazz_ratio3 =  1.085;
    const float ideal_reggae_ratio1 = .900, ideal_reggae_ratio2 = .930, ideal_reggae_ratio3 = 1.093;
    float user_ratio1, user_ratio2, user_ratio3;
    float results1, results2, results3, results_total, mixScore;
    int reggaeScore = 0;
    int hiphopScore = 0;
    int rockScore = 0;
    int jazzScore = 0;
    int score = 0;
    
    // Round counter:
    int i = 1;
    
    // Allegro variables
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    
    // Timer variable set up:
    ALLEGRO_TIMER *timer = NULL;
    
    // Font ttf bitmap instances
    ALLEGRO_FONT *fontHeader = NULL;
    ALLEGRO_FONT *fontMain = NULL;
    ALLEGRO_FONT *fontScore = NULL;
    ALLEGRO_FONT *fontThanks = NULL;
    
    // Mixer, border, button, fader, and mixbutton bitmaps
    ALLEGRO_BITMAP *mixerbmp = NULL;
    ALLEGRO_BITMAP *mixerborderbmp = NULL;
    ALLEGRO_BITMAP *buttonbmp = NULL;
    ALLEGRO_BITMAP *faderbmp = NULL;
    ALLEGRO_BITMAP *mixbuttonbmp = NULL;
    ALLEGRO_BITMAP *logobmp = NULL;
    
    // Character bitmaps
    ALLEGRO_BITMAP *kennygbmp = NULL;
    ALLEGRO_BITMAP *kennyghappybmp = NULL;
    ALLEGRO_BITMAP *kennygpissedbmp = NULL;
    ALLEGRO_BITMAP *dimebagbmp = NULL;
    ALLEGRO_BITMAP *dimebaghappybmp = NULL;
    ALLEGRO_BITMAP *dimebagpissedbmp = NULL;
    ALLEGRO_BITMAP *pdiddybmp = NULL;
    ALLEGRO_BITMAP *pdiddyhappybmp = NULL;
    ALLEGRO_BITMAP *pdiddypissedbmp = NULL;
    ALLEGRO_BITMAP *kingtubbybmp = NULL;
    ALLEGRO_BITMAP *kingtubbyhappybmp;
    ALLEGRO_BITMAP *kingtubbypissedbmp = NULL;
    ALLEGRO_BITMAP *urihappybmp = NULL;
    ALLEGRO_BITMAP *uripissedbmp = NULL;
    ALLEGRO_BITMAP *urigameoverbmp = NULL;
    ALLEGRO_BITMAP *urimenubmp = NULL;
    ALLEGRO_BITMAP *moneybmp = NULL;
    ALLEGRO_BITMAP *evictionbmp = NULL;
    
    // Dialog boxes bitmaps
    ALLEGRO_BITMAP *uridialogbmp = NULL;
    ALLEGRO_BITMAP *uridialoghappybmp = NULL;
    ALLEGRO_BITMAP *uridialogpissedbmp = NULL;
    ALLEGRO_BITMAP *pdiddydialogbmp = NULL;
    ALLEGRO_BITMAP *pdiddydialoghappybmp = NULL;
    ALLEGRO_BITMAP *pdiddydialogpissedbmp = NULL;
    ALLEGRO_BITMAP *kennygdialogbmp = NULL;
    ALLEGRO_BITMAP *kennygdialoghappybmp = NULL;
    ALLEGRO_BITMAP *kennygdialogpissedbmp = NULL;
    ALLEGRO_BITMAP *kingtubbydialogbmp = NULL;
    ALLEGRO_BITMAP *kingtubbydialoghappybmp = NULL;
    ALLEGRO_BITMAP *kingtubbydialogpissedbmp = NULL;
    ALLEGRO_BITMAP *dimebagdialogbmp;
    ALLEGRO_BITMAP *dimebagdialoghappybmp = NULL;
    ALLEGRO_BITMAP *dimebagdialogpissedbmp = NULL;
    ALLEGRO_BITMAP *uridialogwinbmp = NULL;
    
    // Win screen bitmaps
    ALLEGRO_BITMAP *kennygwinbmp = NULL;
    ALLEGRO_BITMAP *pdiddywinbmp = NULL;
    ALLEGRO_BITMAP *dimebagwinbmp = NULL;
    ALLEGRO_BITMAP *kingtubbywinbmp = NULL;
    ALLEGRO_BITMAP *tryagainbuttonbmp = NULL;
    ALLEGRO_BITMAP *quitbuttonbmp = NULL;
    ALLEGRO_BITMAP *uriwinbmp = NULL;
    
    // ALLEGRO Samples
    ALLEGRO_SAMPLE *hiphop1 = NULL;
    ALLEGRO_SAMPLE *hiphop2 = NULL;
    ALLEGRO_SAMPLE *hiphop3 = NULL;
    ALLEGRO_SAMPLE *hiphop4 = NULL;
    ALLEGRO_SAMPLE *rock1 = NULL;
    ALLEGRO_SAMPLE *rock2 = NULL;
    ALLEGRO_SAMPLE *rock3 = NULL;
    ALLEGRO_SAMPLE *rock4 = NULL;
    ALLEGRO_SAMPLE *jazz1 = NULL;
    ALLEGRO_SAMPLE *jazz2 = NULL;
    ALLEGRO_SAMPLE *jazz3 = NULL;
    ALLEGRO_SAMPLE *jazz4 = NULL;
    ALLEGRO_SAMPLE *reggae1 = NULL;
    ALLEGRO_SAMPLE *reggae2 = NULL;
    ALLEGRO_SAMPLE *reggae3 = NULL;
    ALLEGRO_SAMPLE *reggae4 = NULL;

    // Allegro sample instance instances
    ALLEGRO_SAMPLE_INSTANCE *hiphop1inst = NULL;
    ALLEGRO_SAMPLE_INSTANCE *hiphop2inst = NULL;
    ALLEGRO_SAMPLE_INSTANCE *hiphop3inst = NULL;
    ALLEGRO_SAMPLE_INSTANCE *hiphop4inst = NULL;
    ALLEGRO_SAMPLE_INSTANCE *rock1inst = NULL;
    ALLEGRO_SAMPLE_INSTANCE *rock2inst = NULL;
    ALLEGRO_SAMPLE_INSTANCE *rock3inst = NULL;
    ALLEGRO_SAMPLE_INSTANCE *rock4inst = NULL;
    ALLEGRO_SAMPLE_INSTANCE *jazz1inst = NULL;
    ALLEGRO_SAMPLE_INSTANCE *jazz2inst = NULL;
    ALLEGRO_SAMPLE_INSTANCE *jazz3inst = NULL;
    ALLEGRO_SAMPLE_INSTANCE *jazz4inst = NULL;
    ALLEGRO_SAMPLE_INSTANCE *reggae1inst = NULL;
    ALLEGRO_SAMPLE_INSTANCE *reggae2inst = NULL;
    ALLEGRO_SAMPLE_INSTANCE *reggae3inst = NULL;
    ALLEGRO_SAMPLE_INSTANCE *reggae4inst = NULL;
    
    // Error checking to make sure allegro starts correctly:
    if(!al_init()) {
        fprintf(stderr, "Failed to initialize Allegro!\n");
		return -1;
    }
    
    // Creates a new display and checks to see if it loaded correctly:
    display = al_create_display(WIDTH, HEIGHT);
    if(!display) {
        fprintf(stderr, "Failed to create display!\n");
        return -1;
    }
    
    // Installs the mouse to allow the use of mouse events:
    if (!al_install_mouse()) {
        fprintf(stderr, "Failed to install the mouse!\n");
        return -1;
    }
    
    // Loads the image addon to allow the importing/ usage of bitmaps
    if (!al_init_image_addon()) {
        fprintf(stderr, "Failed to initialize the image addon!\n");
        return -1;
    }
    
    // Initializes the font addon:::there is not a way of error checking this
    // as it is a void function...
    al_init_font_addon();
    
    // Loads the ttf addon to allow importing/ using custom ttf fonts
    if (!al_init_ttf_addon()) {
        fprintf(stderr, "Failed to initialize ttf addon!\n");
        return -1;
    }   
    
    // Creates the audio addon and error checks to make sure it loads
    if (!al_install_audio()) {
        fprintf(stderr, "Failed to install the audio!\n");
        return -1;
    }
    
    // Initialize the acodec allegro addon and error checks to make sure it loads
    if (!al_init_acodec_addon()) {
        fprintf(stderr, "Failed to initialize the audio codec addon!\n");
        return -1;
    }
    
    // Reserve samples:
    al_reserve_samples(16);
    
    // Assigns our timer variable...will update 1 / 60 of a second
    timer = al_create_timer(1.0 / FPS);
    if (!timer) {
        fprintf(stderr, "failed to create timer!\n");
        return -1;
    }
    
    // Dialog boxes bitmaps
    uridialogbmp = al_load_bitmap("uri1.png");
    uridialoghappybmp = al_load_bitmap("urione.png");
    uridialogpissedbmp= al_load_bitmap("uri3.png");
    pdiddydialogbmp = al_load_bitmap("hiphopintro.png");
    pdiddydialoghappybmp = al_load_bitmap("hiphopgood.png");
    pdiddydialogpissedbmp = al_load_bitmap("hiphopbad.png");
    kennygdialogbmp = al_load_bitmap("jazzintro.png");
    kennygdialoghappybmp = al_load_bitmap("jazzgood.png");
    kennygdialogpissedbmp = al_load_bitmap("jazzbad.png");
    kingtubbydialogbmp = al_load_bitmap("reggaeintro.png");
    kingtubbydialoghappybmp = al_load_bitmap("reggaegood.png");
    kingtubbydialogpissedbmp = al_load_bitmap("reggaebad.png");
    dimebagdialogbmp = al_load_bitmap("rockintro.png");
    dimebagdialoghappybmp = al_load_bitmap("rockgood.png");
    dimebagdialogpissedbmp = al_load_bitmap("rockbad.png");
    
    // Dialog winning boxes
    uridialogwinbmp = al_load_bitmap("uri2new.png");
    uriwinbmp = al_load_bitmap("uriwinbmp.png");
    kennygwinbmp = al_load_bitmap("jazzwinbmp.png");
    pdiddywinbmp = al_load_bitmap("hiphopwinbmp.png");
    dimebagwinbmp = al_load_bitmap("rockwinbmp.png");
    kingtubbywinbmp = al_load_bitmap("reggaewinbmp.png");
    
    // Loads bitmaps for the mixer, border, fader, button and mix button:
    mixerbmp = al_load_bitmap("mixernewbmp.png");
    mixerborderbmp = al_load_bitmap("mixerborder.png");
    faderbmp = al_load_bitmap("fader.png");
    buttonbmp = al_load_bitmap("buttonone.png");
    mixbuttonbmp = al_load_bitmap("mixbutton.png");
    logobmp = al_load_bitmap("logobmp.png");
    
    // Restart / quit button bitmaps
    tryagainbuttonbmp = al_load_bitmap("tryagainbutton.png");
    quitbuttonbmp = al_load_bitmap("quitbutton.png");
    
    // Load bitmaps for all the characters and money:
    evictionbmp = al_load_bitmap("eviction2.png");
    moneybmp = al_load_bitmap("moneybmp.png");
    urimenubmp = al_load_bitmap("uriMENU.png");
    urihappybmp = al_load_bitmap("uribest.png");
    uripissedbmp = al_load_bitmap("uriworst.png");
    urigameoverbmp = al_load_bitmap("urihomeless.png");
    kingtubbybmp = al_load_bitmap("kingtubbybmp.png");
    kingtubbyhappybmp = al_load_bitmap("kingtubbyhappybmp.png");
    kingtubbypissedbmp = al_load_bitmap("kingtubbypissedbmp.png");
    kennygbmp = al_load_bitmap("kennygamebmp.png");
    kennyghappybmp = al_load_bitmap("kennygtwobmp.png");
    kennygpissedbmp = al_load_bitmap("kennygonebmp.png");
    pdiddybmp = al_load_bitmap("pdiddybmp.png");
    pdiddyhappybmp = al_load_bitmap("pdiddyhappybmp.png");
    pdiddypissedbmp = al_load_bitmap("pdiddypissedbmp.png");
    dimebagbmp = al_load_bitmap("dimebagbmp.png");
    dimebaghappybmp = al_load_bitmap("dimebaghappybmp.png");
    dimebagpissedbmp = al_load_bitmap("dimebagpissedbmp.png");
    
    // Load all the fonts:
    fontHeader = al_load_font("Comic Sans MS Bold.ttf", 50, 0);
    fontMain = al_load_font("Arial.ttf", 18, 0);
    fontScore = al_load_font("EuphemiaCASRegular.ttf", 25, 0);
    fontThanks = al_load_font("EuphemiaCASRegular.ttf", 18, 0);
    
    // Create new Event Queue instance:
    event_queue = al_create_event_queue();
    
    // Loads all the samples into memory
    hiphop1 = al_load_sample("hiphop1.wav");
    hiphop2 = al_load_sample("hiphop2.wav");
    hiphop3 = al_load_sample("hiphop3.wav");
    hiphop4 = al_load_sample("hiphop4.wav");
    rock1 = al_load_sample("rock1.wav");
    rock2 = al_load_sample("rock2.wav");
    rock3 = al_load_sample("rock3.wav");
    rock4 = al_load_sample("rock4.wav");
    jazz1 = al_load_sample("jazzdrums.wav");
    jazz2 = al_load_sample("jazzbass.wav");
    jazz3 = al_load_sample("jazzflute.wav");
    jazz4 = al_load_sample("jazzpiano.wav");
    reggae1 = al_load_sample("reggae1.wav");
    reggae2 = al_load_sample("reggae2.wav");
    reggae3 = al_load_sample("reggae3.wav");
    reggae4 = al_load_sample("reggae4.wav");
        
    // Creates sample instances for all the tracks:
    hiphop1inst = al_create_sample_instance(hiphop1);
    hiphop2inst = al_create_sample_instance(hiphop2);
    hiphop3inst = al_create_sample_instance(hiphop3);
    hiphop4inst = al_create_sample_instance(hiphop4);
    rock1inst = al_create_sample_instance(rock1);
    rock2inst = al_create_sample_instance(rock2);
    rock3inst = al_create_sample_instance(rock3);
    rock4inst = al_create_sample_instance(rock4);
    jazz1inst = al_create_sample_instance(jazz1);
    jazz2inst = al_create_sample_instance(jazz2);
    jazz3inst = al_create_sample_instance(jazz3);
    jazz4inst = al_create_sample_instance(jazz4);
    reggae1inst = al_create_sample_instance(reggae1);
    reggae2inst = al_create_sample_instance(reggae2);
    reggae3inst = al_create_sample_instance(reggae3);
    reggae4inst = al_create_sample_instance(reggae4);
    
    // Set sample playback mode to LOOP
    al_set_sample_instance_playmode(hiphop1inst, ALLEGRO_PLAYMODE_LOOP);
    al_set_sample_instance_playmode(hiphop2inst, ALLEGRO_PLAYMODE_LOOP);
    al_set_sample_instance_playmode(hiphop3inst, ALLEGRO_PLAYMODE_LOOP);
    al_set_sample_instance_playmode(hiphop4inst, ALLEGRO_PLAYMODE_LOOP);
    al_set_sample_instance_playmode(rock1inst, ALLEGRO_PLAYMODE_LOOP);
    al_set_sample_instance_playmode(rock2inst, ALLEGRO_PLAYMODE_LOOP);
    al_set_sample_instance_playmode(rock3inst, ALLEGRO_PLAYMODE_LOOP);
    al_set_sample_instance_playmode(rock4inst, ALLEGRO_PLAYMODE_LOOP);
    al_set_sample_instance_playmode(jazz1inst, ALLEGRO_PLAYMODE_LOOP);
    al_set_sample_instance_playmode(jazz2inst, ALLEGRO_PLAYMODE_LOOP);
    al_set_sample_instance_playmode(jazz3inst, ALLEGRO_PLAYMODE_LOOP);
    al_set_sample_instance_playmode(jazz4inst, ALLEGRO_PLAYMODE_LOOP);
    al_set_sample_instance_playmode(reggae1inst, ALLEGRO_PLAYMODE_LOOP);
    al_set_sample_instance_playmode(reggae2inst, ALLEGRO_PLAYMODE_LOOP);
    al_set_sample_instance_playmode(reggae3inst, ALLEGRO_PLAYMODE_LOOP);
    al_set_sample_instance_playmode(reggae4inst, ALLEGRO_PLAYMODE_LOOP);
    
    // Attach sample instance to mixer
    al_attach_sample_instance_to_mixer(hiphop1inst, al_get_default_mixer());
    al_attach_sample_instance_to_mixer(hiphop2inst, al_get_default_mixer());
    al_attach_sample_instance_to_mixer(hiphop3inst, al_get_default_mixer());
    al_attach_sample_instance_to_mixer(hiphop4inst, al_get_default_mixer());
    al_attach_sample_instance_to_mixer(rock1inst, al_get_default_mixer());
    al_attach_sample_instance_to_mixer(rock2inst, al_get_default_mixer());
    al_attach_sample_instance_to_mixer(rock3inst, al_get_default_mixer());
    al_attach_sample_instance_to_mixer(rock4inst, al_get_default_mixer());
    al_attach_sample_instance_to_mixer(jazz1inst, al_get_default_mixer());
    al_attach_sample_instance_to_mixer(jazz2inst, al_get_default_mixer());
    al_attach_sample_instance_to_mixer(jazz3inst, al_get_default_mixer());
    al_attach_sample_instance_to_mixer(jazz4inst, al_get_default_mixer());
    al_attach_sample_instance_to_mixer(reggae1inst, al_get_default_mixer());
    al_attach_sample_instance_to_mixer(reggae2inst, al_get_default_mixer());
    al_attach_sample_instance_to_mixer(reggae3inst, al_get_default_mixer());
    al_attach_sample_instance_to_mixer(reggae4inst, al_get_default_mixer());
    
    // Set sample gains
    al_set_sample_instance_gain(hiphop1inst, 0);
    al_set_sample_instance_gain(hiphop2inst, 0);
    al_set_sample_instance_gain(hiphop3inst, 0);
    al_set_sample_instance_gain(hiphop4inst, 0);
    al_set_sample_instance_gain(rock1inst, 0);
    al_set_sample_instance_gain(rock2inst, 0);
    al_set_sample_instance_gain(rock3inst, 0);
    al_set_sample_instance_gain(rock4inst, 0);
    al_set_sample_instance_gain(jazz1inst, 0);
    al_set_sample_instance_gain(jazz2inst, 0);
    al_set_sample_instance_gain(jazz3inst, 0);
    al_set_sample_instance_gain(jazz4inst, 0);
    al_set_sample_instance_gain(reggae1inst, 0);
    al_set_sample_instance_gain(reggae2inst, 0);
    al_set_sample_instance_gain(reggae3inst, 0);
    al_set_sample_instance_gain(reggae4inst, 0);
    
    // Creates new instances of the mixer and the faders
    Mixer mixer;
    Fader faderOne;
    Fader faderTwo;
    Fader faderThree;
    Fader faderFour;
    
    // Creates new instances of all buttons and the mix button
    Button buttonOne;
    Button buttonTwo;
    Button buttonThree;
    Button buttonFour;
    Button buttonFive;
    Button buttonSix;
    Button buttonSeven;
    Button buttonEight;
    Button buttonNine;
    Button buttonTen;
    Button buttonEleven;
    Button buttonTwelve;
    Button buttonThirteen;
    Button buttonFourteen;
    Button buttonFifteen;
    Button buttonSixteen;
    MixButton mixbutton;
    
    // Initializes the mixer and faders
    InitMixer(&mixer, mixerbmp);
    InitFader(&faderOne, faderbmp);
    InitFader(&faderTwo, faderbmp);
    InitFader(&faderThree, faderbmp);
    InitFader(&faderFour, faderbmp);
    
    // Initialize the buttons
    InitButtons(&buttonOne, buttonbmp);
    InitButtons(&buttonTwo, buttonbmp);
    InitButtons(&buttonThree, buttonbmp);
    InitButtons(&buttonFour, buttonbmp);
    InitButtons(&buttonFive, buttonbmp);
    InitButtons(&buttonSix, buttonbmp);
    InitButtons(&buttonSeven, buttonbmp);
    InitButtons(&buttonEight, buttonbmp);
    InitButtons(&buttonNine, buttonbmp);
    InitButtons(&buttonTen, buttonbmp);
    InitButtons(&buttonEleven, buttonbmp);
    InitButtons(&buttonTwelve, buttonbmp);
    InitButtons(&buttonThirteen, buttonbmp);
    InitButtons(&buttonFourteen, buttonbmp);
    InitButtons(&buttonFifteen, buttonbmp);
    InitButtons(&buttonSixteen, buttonbmp);
    InitMixButton(&mixbutton, mixbuttonbmp);
    
    // Sets stuff in the correct place on screen
    SetFaderOne(&faderOne, &mixer);
    SetFaderTwo(&faderTwo, &mixer);
    SetFaderThree(&faderThree, &mixer);
    SetFaderFour(&faderFour,&mixer);
    
    SetMixButton(&mixbutton);
    SetButtonOne(&buttonOne, &mixer);
    SetButtonTwo(&buttonTwo, &mixer);
    SetButtonThree(&buttonThree, &mixer);
    SetButtonFour(&buttonFour, &mixer);
    SetButtonFive(&buttonFive, &mixer);
    SetButtonSix(&buttonSix, &mixer);
    SetButtonSeven(&buttonSeven, &mixer);
    SetButtonEight(&buttonEight, &mixer);
    SetButtonNine(&buttonNine, &mixer);
    SetButtonTen(&buttonTen, &mixer);
    SetButtonEleven(&buttonEleven, &mixer);
    SetButtonTwelve(&buttonTwelve, &mixer);
    SetButtonThirteen(&buttonThirteen, &mixer);
    SetButtonFourteen(&buttonFourteen, &mixer);
    SetButtonFifteen(&buttonFifteen, &mixer);
    SetButtonSixteen(&buttonSixteen, &mixer);
    
    // Begins playback for all the samples
    al_play_sample_instance(hiphop1inst);
    al_play_sample_instance(hiphop2inst);
    al_play_sample_instance(hiphop3inst);
    al_play_sample_instance(hiphop4inst);
    al_play_sample_instance(rock1inst);
    al_play_sample_instance(rock2inst);
    al_play_sample_instance(rock3inst);
    al_play_sample_instance(rock4inst);
    al_play_sample_instance(jazz1inst);
    al_play_sample_instance(jazz2inst);
    al_play_sample_instance(jazz3inst);
    al_play_sample_instance(jazz4inst);
    al_play_sample_instance(reggae1inst);
    al_play_sample_instance(reggae2inst);
    al_play_sample_instance(reggae3inst);
    al_play_sample_instance(reggae4inst);
    
    // Clears the screen to black before we start the game
    al_clear_to_color(al_map_rgb(0,0,0));
    
    // Sets our backbuffer as the target
    al_set_target_bitmap(al_get_backbuffer(display));
    
    // Register event sources for our event queue (basically just listening for input
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    
    // Clears the screen again and flips the backbuffer (display) to the front
    al_clear_to_color(al_map_rgb(0,0,0));
    al_flip_display();
    
    // Starts the timer:
    al_start_timer(timer);
    
    // Start Main game loop
	while (!done) {
        
        // Start Menu
        while (isStartMenu && !done) {
            
            // WE ALWAYS BEGIN BY WAITING FOR ANY EVENTS TO OCCUR THAT WE REGISTERED ABOVE:
            ALLEGRO_EVENT ev;
            al_wait_for_event (event_queue, &ev);

            // This event tells us that we will redraw the screen based on our timer update
            // of 1 /60 of a second. 
            if (ev.type == ALLEGRO_EVENT_TIMER) {
                redraw = true;
            }
            
            // This always exits the game if we click the 'close box'
            else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) 
            {
                done = true;
            }
            
            // This listens for any mouse button 'up' clicks.
            else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) { 
                // If the mouse coordinates are within the range of the
                // logo on the lower right of the screen, we will enter the
                // 'About Screen' loop. Mouse button & 1 is a bitwise
                // representing the left mouse button
                if (ev.mouse.x > 872 &&
                    ev.mouse.x < 927 &&
                    ev.mouse.y > 692 &&
                    ev.mouse.y < 777 &&
                    ev.mouse.button &1) {
                    isAboutScreen = true;
                }
                
                // If we click anywhere besides the box above, we go to the main game screen
                else {
                    isStartMenu = false;
                }
            }
            
            // Start of the 'About Screen' loop
            while (isAboutScreen && !done) {
                
                // Same event checking as above. Always do this at the beginning of
                // new while loop:
                ALLEGRO_EVENT ev;
                al_wait_for_event (event_queue, &ev);
                
                // This event tells us that we will redraw the screen based on our timer update
                // of 1 /60 of a second.
                if (ev.type == ALLEGRO_EVENT_TIMER) {
                    redraw = true;
                }
                
                // This always exits the game if we click the 'close box'
                else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
                    done = true;
                }
                
                // This listens for any mouse button 'up' clicks.
                else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
                    isAboutScreen = false;
                }
                
                // This is our redraw material within the 'About Screen'. The front
                // buffer is cleared to black (0,0,0), new text and bitmaps are drawn
                // to the backbuffer and then at the end, the backbuffer is flipped to the 
                // front. This is all done at 1 / 60 of a second, the rate of our timer
                if (redraw && al_is_event_queue_empty(event_queue)) {
                    
                    // Redraw is set back to false because we only need to do this once every
                    // timer cycle
                    redraw = false;
                    
                    // Clears the front buffer to black so that the screen can be redrawn
                    // and flipped back to the front:
                    al_clear_to_color(al_map_rgb(0,0,0));
                    
                    // This is the Allegro equivalent of printf. It takes quite a few arguments,
                    // including color, font type (as declared above the main), position on screen,
                    // flags for text justification and finally, the actual text to be displayed.
                    al_draw_textf(fontHeader, al_map_rgb(255,0,255), WIDTH / 2, 100, 
                                  ALLEGRO_ALIGN_CENTRE, "STREET CREDS:");
                    al_draw_textf(fontScore, al_map_rgb(255,255,255), WIDTH / 2, 100 + 
                                  al_get_font_line_height(fontHeader), 
                                  ALLEGRO_ALIGN_CENTRE, "everything by Mark Anderson && David Forshee!!!");
                    
                    // Displays the special thanks on screen
                    al_draw_textf(fontScore, al_map_rgb(255,255,255), WIDTH / 2, 100 +
                                  (al_get_font_line_height(fontHeader) * 2), 
                                  ALLEGRO_ALIGN_CENTRE, "Special thanks to:"); 
                    
                    al_draw_textf(fontThanks, al_map_rgb(255,0,255), WIDTH / 2, 100 +
                                  (al_get_font_line_height(fontHeader) * 3), 
                                  ALLEGRO_ALIGN_CENTRE, "Oriol Nieto, Mary Farbood, Kenny G, P Diddy, King Tubby, and Dimebag Darrell");
                    
                    // Draws "mixHero->plot = NULL"
                    al_draw_textf(fontScore, al_map_rgb(255,255,255), WIDTH / 2 - 150, HEIGHT / 2, 
                                  0, "mixHero->    = ");
                    al_draw_textf(fontScore, al_map_rgb(34,139,34), WIDTH / 2 - 150, HEIGHT / 2, 
                                  0, "         plot");
                    al_draw_textf(fontScore, al_map_rgb(255,0,255), WIDTH / 2 - 150, HEIGHT / 2, 
                                  0, "              NULL");
                    
                    // Flips the drawn elements to the front buffer so they are now displayed:
                    al_flip_display();
                }
            }
            
            // This is within our 'Start Menu' while loop: it does the same as before: resets the redraw flag,
            // clears the front buffer to black, draws whatever we want displayed on the screen onto the backbuffer,
            // and then flips the backbuffer to the front again.
            if (redraw && al_is_event_queue_empty(event_queue)) {
                redraw = false;
                
                // Clears the front buffer to black to allow backbuffer be drawn:
                al_clear_to_color(al_map_rgb(0,0,0));
                
                // Displays uri's main bitmap
                al_draw_bitmap(urimenubmp, 375, HEIGHT / 2 - al_get_font_line_height(fontHeader), 0);
                
                // This displays uri's main dialog box as a scaled image. 
                al_draw_scaled_bitmap(uridialogbmp, 0, 0, al_get_bitmap_width(uridialogbmp), 
                                      al_get_bitmap_height(uridialogbmp), WIDTH / 2 + 75, HEIGHT / 2 - 100, 
                                      al_get_bitmap_width(uridialogbmp) / 2, 
                                      al_get_bitmap_height(uridialogbmp) / 2, 0);
                
                // Draws our M D logo onto the bottom right corner of the screen. 
                al_draw_bitmap(logobmp, WIDTH - (al_get_bitmap_width(logobmp) + 25), HEIGHT - (al_get_bitmap_height(logobmp) + 25), 0);
                
                // Displays the header text on the screen
                al_draw_textf(fontHeader, al_map_rgb(255,0,255), WIDTH / 2, 100, 
                              ALLEGRO_ALIGN_CENTRE, "MIX HERO!!!");
                
                // Displays Click to Begin text:
                al_draw_textf(fontMain, al_map_rgb(255,0,255), WIDTH / 2, 100 + 
                              al_get_font_line_height(fontHeader), 
                              ALLEGRO_ALIGN_CENTRE, "(click to begin)");
                
                // Flips the drawn elements to the front buffer so they are now displayed:
                al_flip_display();
            }
        }
        
        // We won't use these bitmap anymore...
        al_destroy_bitmap(uridialogbmp);
        al_destroy_bitmap(logobmp);
        
        // This is the while loop where the main gameplay takes place.
        while (!isRoundOver && !done) {
            
            // Same event queue as before with an added "event mouse axes", which checks for mouse movement
            // on the screen (i.e. for fader updates)
            ALLEGRO_EVENT ev;
            al_wait_for_event (event_queue, &ev);
            
            // Checks if an event timer event has occurred (1/60 second). If so, the screen is redrawn
            if (ev.type == ALLEGRO_EVENT_TIMER) {
                redraw = true;
            }
            
            // If the user closes the display, the game quits
            else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) 
            {
                done = true;
            }
            
            // Listens for mouse movement on the screen:
            else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES) 
            {
                // Checks to see if the mouse is clicked within faderOne box
                if (ev.mouse.x > WIDTH / 2 - 240 && 
                    ev.mouse.x < WIDTH / 2 - 240 + faderOne.width && 
                    ev.mouse.y > HEIGHT / 2 - 50 && 
                    ev.mouse.y < HEIGHT / 2 + 150 && 
                    ev.mouse.button & 1) {
                    
                    // Update sample instance gains when fader is moved
                    if (buttonOne.isClicked) {
                        al_set_sample_instance_gain(hiphop1inst, (abs( (faderOne.y - 549) ) / (float) 198));
                    }
                    if (buttonTwo.isClicked) {
                        al_set_sample_instance_gain(rock1inst, (abs( (faderOne.y - 549) ) / (float) 198));
                    }
                    if (buttonThree.isClicked) {
                        al_set_sample_instance_gain(jazz1inst, (abs( (faderOne.y - 549) ) / (float) 198));
                    }
                    if (buttonFour.isClicked) {
                        al_set_sample_instance_gain(reggae1inst, (abs( (faderOne.y - 549) ) / (float) 198));
                    }
                    
                    // Updates the Fader when it is moved:
                    UpdateFaderOne(&faderOne, &mixer, &ev, faderbmp);
                }
                
                // Checks to see if the mouse is clicked within faderTwo box
                if (ev.mouse.x > WIDTH / 2 - 127 && 
                    ev.mouse.x < WIDTH / 2 - 127 + faderTwo.width && 
                    ev.mouse.y > HEIGHT / 2 - 50 && 
                    ev.mouse.y < HEIGHT / 2 + 150 && 
                    ev.mouse.button & 1) {
                    
                    // Update sample instance gains when fader is moved
                    if (buttonFive.isClicked) {
                        al_set_sample_instance_gain(reggae2inst, (abs( (faderTwo.y - 549) ) / (float) 198));
                    }
                    if (buttonSix.isClicked) {
                        al_set_sample_instance_gain(jazz2inst, (abs( (faderTwo.y - 549) ) / (float) 198));
                    }
                    if (buttonSeven.isClicked) {
                        al_set_sample_instance_gain(rock2inst, (abs( (faderTwo.y - 549) ) / (float) 198));
                    }
                    if (buttonEight.isClicked) {
                        al_set_sample_instance_gain(hiphop2inst, (abs( (faderTwo.y - 549) ) / (float) 198));
                    }
                    
                    // Updates the Fader when it is moved:
                    UpdateFaderTwo(&faderTwo, &mixer, &ev, faderbmp);
                }
                
                // Checks to see if the mouse is clicked within faderThree box
                if (ev.mouse.x > WIDTH / 2 + 95 && 
                    ev.mouse.x < WIDTH / 2 + 95 + faderThree.width && 
                    ev.mouse.y > HEIGHT / 2 - 50 && 
                    ev.mouse.y < HEIGHT / 2 + 150 && 
                    ev.mouse.button & 1) {
                    
                    // Update sample instance gains when fader is moved
                    if (buttonNine.isClicked) {
                        al_set_sample_instance_gain(rock3inst, (abs( (faderThree.y - 549) ) / (float) 198));
                    }
                    if (buttonTen.isClicked) {
                        al_set_sample_instance_gain(hiphop3inst, (abs( (faderThree.y - 549) ) / (float) 198));       
                    }
                    if (buttonEleven.isClicked) {
                        al_set_sample_instance_gain(reggae3inst, (abs( (faderThree.y - 549) ) / (float) 198));
                    }
                    if (buttonTwelve.isClicked) {
                        al_set_sample_instance_gain(jazz3inst, (abs( (faderThree.y - 549) ) / (float) 198));
                    }
                    
                    // Updates the Fader when it is moved:
                    UpdateFaderThree(&faderThree, &mixer, &ev, faderbmp);
                }
                
                // Checks to see if the mouse is clicked within faderFour box
                if (ev.mouse.x > WIDTH / 2 + 199 && 
                    ev.mouse.x < WIDTH / 2 + 199 + faderFour.width && 
                    ev.mouse.y > HEIGHT / 2 - 50 && 
                    ev.mouse.y < HEIGHT / 2 + 150 && 
                    ev.mouse.button & 1) {
                    
                    // Update sample instance gains when fader is moved
                    if (buttonThirteen.isClicked) {
                        al_set_sample_instance_gain(reggae4inst, (abs( (faderFour.y - 549) ) / (float) 198));
                    }
                    if (buttonFourteen.isClicked) {
                        al_set_sample_instance_gain(jazz4inst, (abs( (faderFour.y - 549) ) / (float) 198));
                    }
                    if (buttonFifteen.isClicked) {
                        al_set_sample_instance_gain(rock4inst, (abs( (faderFour.y - 549) ) / (float) 198));
                    }
                    if (buttonSixteen.isClicked) {
                        al_set_sample_instance_gain(hiphop4inst, (abs( (faderFour.y - 549) ) / (float) 198));
                    }
                    
                    // Updates the Fader when it is moved:
                    UpdateFaderFour(&faderFour, &mixer, &ev, faderbmp);
                }
            } 
            
            // Updates the current muted track when a mouse up event is detected
            else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) 
            {
                
                // Checks if the user clicks within buttonOne box
                if (ev.mouse.x > buttonOne.x &&
                    ev.mouse.x < buttonOne.x + buttonOne.width &&
                    ev.mouse.y > buttonOne.y &&
                    ev.mouse.y < buttonOne.y + buttonOne.height &&
                    ev.mouse.button & 1) {
                    
                    // If button is not clicked, sets it to on position and the rest of the group
                    // to off position. Else, button is already on and is reset back to off
                    if (buttonOne.isClicked == false) {
                        buttonOne.isClicked = true;
                        buttonTwo.isClicked = false;
                        buttonThree.isClicked = false;
                        buttonFour.isClicked = false;
                    }
                    else 
                        buttonOne.isClicked = false;
                    
                    // Update sample instance gains when button is pressed
                    al_set_sample_instance_gain(hiphop1inst, (abs( (faderOne.y - 549) ) / (float) 198));
                }
                
                // Checks if the user clicks within buttonTwo box
                else if (ev.mouse.x > buttonTwo.x &&
                         ev.mouse.x < buttonTwo.x + buttonTwo.width &&
                         ev.mouse.y > buttonTwo.y &&
                         ev.mouse.y < buttonTwo.y + buttonTwo.height &&
                         ev.mouse.button & 1) {
                    
                    // If button is not clicked, sets it to on position and the rest of the group
                    // to off position. Else, button is already on and is reset back to off
                    if (buttonTwo.isClicked == false) {
                        buttonOne.isClicked = false;
                        buttonTwo.isClicked = true;
                        buttonThree.isClicked = false;
                        buttonFour.isClicked = false;
                    }
                    else 
                        buttonTwo.isClicked = false;
                    
                    // Update sample instance gains when button is pressed
                    al_set_sample_instance_gain(rock1inst, (abs( (faderOne.y - 549) ) / (float) 198));                    
                }
                
                // Checks if the user clicks within buttonThree box
                else if (ev.mouse.x > buttonThree.x &&
                         ev.mouse.x < buttonThree.x + buttonThree.width &&
                         ev.mouse.y > buttonThree.y &&
                         ev.mouse.y < buttonThree.y + buttonThree.height &&
                         ev.mouse.button & 1) {
                    
                    // If button is not clicked, sets it to on position and the rest of the group
                    // to off position. Else, button is already on and is reset back to off
                    if (buttonThree.isClicked == false) {
                        buttonOne.isClicked = false;
                        buttonTwo.isClicked = false;
                        buttonThree.isClicked = true;
                        buttonFour.isClicked = false;
                    }
                    else
                        buttonThree.isClicked = false;
                    
                    // Update sample instance gains when button is pressed
                    al_set_sample_instance_gain(jazz1inst, (abs( (faderOne.y - 549) ) / (float) 198));
                }
                
                // Checks if the user clicks within buttonFour box
                else if (ev.mouse.x > buttonFour.x &&
                         ev.mouse.x < buttonFour.x + buttonFour.width &&
                         ev.mouse.y > buttonFour.y &&
                         ev.mouse.y < buttonFour.y + buttonFour.height &&
                         ev.mouse.button & 1) {
                    
                    // If button is not clicked, sets it to on position and the rest of the group
                    // to off position. Else, button is already on and is reset back to off
                    if (buttonFour.isClicked == false) {
                        buttonOne.isClicked = false;
                        buttonTwo.isClicked = false;
                        buttonThree.isClicked = false;
                        buttonFour.isClicked = true;
                    }
                    else
                        buttonFour.isClicked = false;
                    
                    // Update sample instance gains when button is pressed
                    al_set_sample_instance_gain(reggae1inst, (abs( (faderOne.y - 549) ) / (float) 198));
                }
                
                // Checks if the user clicks within buttonFive box
                else if (ev.mouse.x > buttonFive.x &&
                         ev.mouse.x < buttonFive.x + buttonFive.width &&
                         ev.mouse.y > buttonFive.y &&
                         ev.mouse.y < buttonFive.y + buttonFive.height &&
                         ev.mouse.button & 1) {
                    
                    // If button is not clicked, sets it to on position and the rest of the group
                    // to off position. Else, button is already on and is reset back to off
                    if (buttonFive.isClicked == false) {
                        buttonFive.isClicked = true;
                        buttonSix.isClicked = false;
                        buttonSeven.isClicked = false;
                        buttonEight.isClicked = false;
                    }
                    else
                        buttonFive.isClicked = false;
                    
                    // Update sample instance gains when button is pressed
                    al_set_sample_instance_gain(reggae2inst, (abs( (faderTwo.y - 549) ) / (float) 198));
                }
                
                // Checks if the user clicks within buttonSix box
                else if (ev.mouse.x > buttonSix.x &&
                         ev.mouse.x < buttonSix.x + buttonSix.width &&
                         ev.mouse.y > buttonSix.y &&
                         ev.mouse.y < buttonSix.y + buttonSix.height &&
                         ev.mouse.button & 1) {
                    
                    // If button is not clicked, sets it to on position and the rest of the group
                    // to off position. Else, button is already on and is reset back to off
                    if (buttonSix.isClicked == false) {
                        buttonFive.isClicked = false;
                        buttonSix.isClicked = true;
                        buttonSeven.isClicked = false;
                        buttonEight.isClicked = false;
                    }
                    else
                        buttonSix.isClicked = false;
                    
                    // Update sample instance gains when button is pressed
                    al_set_sample_instance_gain(jazz2inst, (abs( (faderTwo.y - 549) ) / (float) 198));
                }
                
                // Checks if the user clicks within buttonSeven box
                else if (ev.mouse.x > buttonSeven.x &&
                         ev.mouse.x < buttonSeven.x + buttonSeven.width &&
                         ev.mouse.y > buttonSeven.y &&
                         ev.mouse.y < buttonSeven.y + buttonSeven.height &&
                         ev.mouse.button & 1) {
                    
                    // If button is not clicked, sets it to on position and the rest of the group
                    // to off position. Else, button is already on and is reset back to off
                    if (buttonSeven.isClicked == false) {
                        buttonFive.isClicked = false;
                        buttonSix.isClicked = false;
                        buttonSeven.isClicked = true;
                        buttonEight.isClicked = false;
                    }
                    else
                        buttonSeven.isClicked = false;

                    // Update sample instance gains when button is pressed
                    al_set_sample_instance_gain(rock2inst, (abs( (faderTwo.y - 549) ) / (float) 198));
                }
                
                // Checks if the user clicks within buttonEight box
                else if (ev.mouse.x > buttonEight.x &&
                         ev.mouse.x < buttonEight.x + buttonEight.width &&
                         ev.mouse.y > buttonEight.y &&
                         ev.mouse.y < buttonEight.y + buttonEight.height &&
                         ev.mouse.button & 1) {
                    
                    // If button is not clicked, sets it to on position and the rest of the group
                    // to off position. Else, button is already on and is reset back to off
                    if (buttonEight.isClicked == false) {
                        buttonFive.isClicked = false;
                        buttonSix.isClicked = false;
                        buttonSeven.isClicked = false;
                        buttonEight.isClicked = true;
                    }
                    else
                        buttonEight.isClicked = false;
                
                    // Update sample instance gains when button is pressed
                    al_set_sample_instance_gain(hiphop2inst, (abs( (faderTwo.y - 549) ) / (float) 198));
                }
                
                // Checks if the user clicks within buttonNine box
                else if (ev.mouse.x > buttonNine.x &&
                         ev.mouse.x < buttonNine.x + buttonNine.width &&
                         ev.mouse.y > buttonNine.y &&
                         ev.mouse.y < buttonNine.y + buttonNine.height &&
                         ev.mouse.button & 1) {
                    
                    // If button is not clicked, sets it to on position and the rest of the group
                    // to off position. Else, button is already on and is reset back to off
                    if (buttonNine.isClicked == false) {
                        buttonNine.isClicked = true;
                        buttonTen.isClicked = false;
                        buttonEleven.isClicked = false;
                        buttonTwelve.isClicked = false;
                    }
                    else
                        buttonNine.isClicked = false;
                    
                    // Update sample instance gains when button is pressed
                    al_set_sample_instance_gain(rock3inst, (abs( (faderThree.y - 549) ) / (float) 198));
                }
                
                // Checks if the user clicks within buttonTen box
                else if (ev.mouse.x > buttonTen.x &&
                         ev.mouse.x < buttonTen.x + buttonTen.width &&
                         ev.mouse.y > buttonTen.y &&
                         ev.mouse.y < buttonTen.y + buttonTen.height &&
                         ev.mouse.button & 1) {
                    
                    // If button is not clicked, sets it to on position and the rest of the group
                    // to off position. Else, button is already on and is reset back to off
                    if (buttonTen.isClicked == false) {
                        buttonNine.isClicked = false;
                        buttonTen.isClicked = true;
                        buttonEleven.isClicked = false;
                        buttonTwelve.isClicked = false;
                    }
                    else
                        buttonTen.isClicked = false;
                    
                    // Update sample instance gains when button is pressed
                    al_set_sample_instance_gain(hiphop3inst, (abs( (faderThree.y - 549) ) / (float) 198));
                    
                }
                
                // Checks if the user clicks within buttonEleven box
                else if (ev.mouse.x > buttonEleven.x &&
                         ev.mouse.x < buttonEleven.x + buttonEleven.width &&
                         ev.mouse.y > buttonEleven.y &&
                         ev.mouse.y < buttonEleven.y + buttonEleven.height &&
                         ev.mouse.button & 1) {
                    
                    // If button is not clicked, sets it to on position and the rest of the group
                    // to off position. Else, button is already on and is reset back to off
                    if (buttonEleven.isClicked == false) {
                        buttonNine.isClicked = false;
                        buttonTen.isClicked = false;
                        buttonEleven.isClicked = true;
                        buttonTwelve.isClicked = false;
                    }
                    else
                        buttonEleven.isClicked = false;
                    
                    // Update sample instance gains when button is pressed
                    al_set_sample_instance_gain(reggae3inst, (abs( (faderThree.y - 549) ) / (float) 198));
                }
                
                // Checks if the user clicks within buttonTwelve box
                else if (ev.mouse.x > buttonTwelve.x &&
                         ev.mouse.x < buttonTwelve.x + buttonTwelve.width &&
                         ev.mouse.y > buttonTwelve.y &&
                         ev.mouse.y < buttonTwelve.y + buttonTwelve.height &&
                         ev.mouse.button & 1) {
                    
                    // If button is not clicked, sets it to on position and the rest of the group
                    // to off position. Else, button is already on and is reset back to off
                    if (buttonTwelve.isClicked == false) {
                        buttonNine.isClicked = false;
                        buttonTen.isClicked = false;
                        buttonEleven.isClicked = false;
                        buttonTwelve.isClicked = true;
                    }
                    else
                        buttonTwelve.isClicked = false;
                    
                    // Update sample instance gains when button is pressed
                    al_set_sample_instance_gain(jazz3inst, (abs( (faderThree.y - 549) ) / (float) 198)); 
                }
                
                // Checks if the user clicks within buttonThirteen box
                else if (ev.mouse.x > buttonThirteen.x &&
                         ev.mouse.x < buttonThirteen.x + buttonThirteen.width &&
                         ev.mouse.y > buttonThirteen.y &&
                         ev.mouse.y < buttonThirteen.y + buttonThirteen.height &&
                         ev.mouse.button & 1) {
                    
                    // If button is not clicked, sets it to on position and the rest of the group
                    // to off position. Else, button is already on and is reset back to off
                    if (buttonThirteen.isClicked == false) {
                        buttonThirteen.isClicked = true;
                        buttonFourteen.isClicked = false;
                        buttonFifteen.isClicked = false;
                        buttonSixteen.isClicked = false;
                    }
                    else
                        buttonThirteen.isClicked = false;  
                    
                    // Update sample instance gains when button is pressed
                    al_set_sample_instance_gain(reggae4inst, (abs( (faderFour.y - 549) ) / (float) 198));
                }
                
                // Checks if the user clicks within buttonFourteen box
                else if (ev.mouse.x > buttonFourteen.x &&
                         ev.mouse.x < buttonFourteen.x + buttonFourteen.width &&
                         ev.mouse.y > buttonFourteen.y &&
                         ev.mouse.y < buttonFourteen.y + buttonFourteen.height &&
                         ev.mouse.button & 1) {
                    
                    // If button is not clicked, sets it to on position and the rest of the group
                    // to off position. Else, button is already on and is reset back to off
                    if (buttonFourteen.isClicked == false) {
                        buttonThirteen.isClicked = false;
                        buttonFourteen.isClicked = true;
                        buttonFifteen.isClicked = false;
                        buttonSixteen.isClicked = false;
                    }
                    else
                        buttonFourteen.isClicked = false;  
                    
                    // Update sample instance gains when button is pressed
                    al_set_sample_instance_gain(jazz4inst, (abs( (faderFour.y - 549) ) / (float) 198));
                }
                
                // Checks if the user clicks within buttonFifteen box
                else if (ev.mouse.x > buttonFifteen.x &&
                         ev.mouse.x < buttonFifteen.x + buttonFifteen.width &&
                         ev.mouse.y > buttonFifteen.y &&
                         ev.mouse.y < buttonFifteen.y + buttonFifteen.height &&
                         ev.mouse.button & 1) {
                    
                    // If button is not clicked, sets it to on position and the rest of the group
                    // to off position. Else, button is already on and is reset back to off
                    if (buttonFifteen.isClicked == false) {
                        buttonThirteen.isClicked = false;
                        buttonFourteen.isClicked = false;
                        buttonFifteen.isClicked = true;
                        buttonSixteen.isClicked = false;
                    }
                    else
                        buttonFifteen.isClicked = false;   
                    
                    // Update sample instance gains when button is pressed
                    al_set_sample_instance_gain(rock4inst, (abs( (faderFour.y - 549) ) / (float) 198));
                }
                
                // Checks if the user clicks within buttonSixteen box
                else if (ev.mouse.x > buttonSixteen.x &&
                         ev.mouse.x < buttonSixteen.x + buttonSixteen.width &&
                         ev.mouse.y > buttonSixteen.y &&
                         ev.mouse.y < buttonSixteen.y + buttonSixteen.height &&
                         ev.mouse.button & 1) {
                    
                    // If button is not clicked, sets it to on position and the rest of the group
                    // to off position. Else, button is already on and is reset back to off
                    if (buttonSixteen.isClicked == false) {
                        buttonThirteen.isClicked = false;
                        buttonFourteen.isClicked = false;
                        buttonFifteen.isClicked = false;
                        buttonSixteen.isClicked = true;
                    }
                    else
                        buttonSixteen.isClicked = false; 
                    
                    // Update sample instance gains when button is pressed
                    al_set_sample_instance_gain(hiphop4inst, (abs( (faderFour.y - 549) ) / (float) 198));   
                }
                
                // Checks to see if the mixbutton box was clicked
                else if (ev.mouse.x > mixbutton.x &&
                         ev.mouse.x < mixbutton.x + mixbutton.width &&
                         ev.mouse.y > mixbutton.y &&
                         ev.mouse.y < mixbutton.y + mixbutton.height &&
                         ev.mouse.button & 1) {
                    
                    // This flag is set to true so that we enter the score screen when we click the
                    // mix button
                    isRoundOver = true;
                    
                    // The counter variable 'i' is checked before we enter the score screen so that
                    // we enter the correct calculations
                    if (i == 1) 
                        isKennyG = true;
                    if (i == 2)
                        isPDiddy = true;
                    if (i == 3)
                        isKingTubby = true;
                    if (i == 4)
                        isDimebagDarrell = true; 
                }
            }
            
            // Update for the 'Round Screen'...it redraws at the rate of our game timer. Same as before,
            // clear the screen to black, draw bitmaps/ text to the backbuffer, and then flip that to the front
            if (redraw && al_is_event_queue_empty(event_queue)) {
                redraw = false;
                
                al_clear_to_color(al_map_rgb(0,0,0));
                
                // Draws the Mixer first so that it will be on the back layer
                SetMixer(&mixer);
                
                // Display the mixer, its border and uri:
                al_draw_bitmap(mixerbmp, mixer.x, mixer.y, 0);
                
                // Redraws the faders based on game timer (FPS)
                al_draw_bitmap(faderbmp, faderOne.x, faderOne.y, 0);
                al_draw_bitmap(faderbmp, faderTwo.x, faderTwo.y, 0);
                al_draw_bitmap(faderbmp, faderThree.x, faderThree.y, 0);
                al_draw_bitmap(faderbmp, faderFour.x, faderFour.y, 0);
                
                // Draws the mixer border and uri
                al_draw_bitmap(mixerborderbmp, mixer.x, mixer.y, 0); 
                al_draw_bitmap(urimenubmp, 20, HEIGHT / 2 - 100, 0);
                
                // This will display the total score on the screen
                al_draw_textf(fontScore, al_map_rgb(255,255,255), WIDTH / 2, 20, 
                              ALLEGRO_ALIGN_CENTRE, "Cash Money: ");

                // This adds space between the dollar sign so that it doesn't collide with the text as numbers get larger:
                if ((jazzScore + rockScore + hiphopScore + reggaeScore) == 0) {
                    al_draw_textf(fontScore, al_map_rgb(34,139,34), WIDTH / 2, 20, 
                                  ALLEGRO_ALIGN_CENTRE, "               $%d", 
                                  jazzScore + rockScore + hiphopScore + reggaeScore);
                }
                
                // Simply shifts the score to the right so it looks nicer on the display
                else {
                    al_draw_textf(fontScore, al_map_rgb(34,139,34), WIDTH / 2, 20, 
                                  ALLEGRO_ALIGN_CENTRE, "                 $%d", 
                                  jazzScore + rockScore + hiphopScore + reggaeScore);
                }
                
                // If it is round one: kenny g is drawn to the screen
                if (i == 1) {
                    al_draw_bitmap(kennygbmp, WIDTH - 250, 140, 0);
                    al_draw_scaled_bitmap(kennygdialogbmp, 0, 0, al_get_bitmap_width(kennygdialogbmp), 
                                          al_get_bitmap_height(kennygdialogbmp), WIDTH / 2 + 150, 100, 
                                          al_get_bitmap_width(kennygdialogbmp) / 4, 
                                          al_get_bitmap_height(kennygdialogbmp) / 4, 0);
                }
                
                // If it is round two: pdiddy is drawn to the screen
                if (i == 2) {
                    al_draw_bitmap(pdiddybmp, WIDTH - 200, HEIGHT - (al_get_bitmap_height(pdiddybmp) + 40), 0);
                    al_draw_scaled_bitmap(pdiddydialogbmp, 0, 0, al_get_bitmap_width(pdiddydialogbmp), 
                                          al_get_bitmap_height(pdiddydialogbmp), WIDTH / 2 + 230, 350, 
                                          al_get_bitmap_width(pdiddydialogbmp) / 4, 
                                          al_get_bitmap_height(pdiddydialogbmp) / 4, 0);
                }
                
                // If it is round three: kingtubby is drawn to the screen
                if (i == 3) {
                    al_draw_bitmap(kingtubbybmp, WIDTH - 250, 20, 0);
                    al_draw_scaled_bitmap(kingtubbydialogbmp, 0, 0, al_get_bitmap_width(kingtubbydialogbmp), 
                                          al_get_bitmap_height(kingtubbydialogbmp), WIDTH / 2 + 100, 75, 
                                          al_get_bitmap_width(kingtubbydialogbmp) / 4, 
                                          al_get_bitmap_height(kingtubbydialogbmp) / 4, 0);
                }
                
                // If it is round four: dimebag darrell is drawn to the screen
                if (i == 4) {
                    al_draw_bitmap(dimebagbmp, WIDTH - 250, HEIGHT - (al_get_bitmap_height(dimebagbmp) + 25), 0);
                    al_draw_scaled_bitmap(dimebagdialogbmp, 0, 0, al_get_bitmap_width(dimebagdialogbmp), 
                                          al_get_bitmap_height(dimebagdialogbmp), WIDTH / 2 + 230, 320, 
                                          al_get_bitmap_width(dimebagdialogbmp) / 4, 
                                          al_get_bitmap_height(dimebagdialogbmp) / 4, 0);
                }
                
                // If faderOne is not moved, the bitmap will continuously be drawn in its 'Set' position
                if (!faderOne.isMoved) 
                {                
                    SetFaderOne(&faderOne, &mixer);
                    al_draw_bitmap(faderbmp, faderOne.x, faderOne.y, 0);
                }
                
                // If faderTwo is not moved, the bitmap will continuously be drawn in its 'Set' position
                if (!faderTwo.isMoved)
                {
                    SetFaderTwo(&faderTwo, &mixer);
                    al_draw_bitmap(faderbmp, faderTwo.x, faderTwo.y, 0);
                }
                
                // If faderThree is not moved, the bitmap will continuously be drawn in its 'Set' position
                if (!faderThree.isMoved)
                {
                    SetFaderThree(&faderThree, &mixer);
                    al_draw_bitmap(faderbmp, faderThree.x, faderThree.y, 0);
                }
                
                // If faderFour is not moved, the bitmap will continuously be drawn in its 'Set' position
                if (!faderFour.isMoved)
                {
                    SetFaderFour(&faderFour, &mixer);
                    al_draw_bitmap(faderbmp, faderFour.x, faderFour.y, 0);
                }
                
                // If the button is clicked, it turns a tinted color. If it hasn't been clicked, it is drawn in place
                // If button is not clicked, set sample instance gain to '0' (muted)
                if (!buttonOne.isClicked) {                
                    SetButtonOne(&buttonOne, &mixer);
                    al_draw_bitmap(buttonbmp, buttonOne.x, buttonOne.y, 0);
                    al_set_sample_instance_gain(hiphop1inst, 0);
                }
                else {
                    al_draw_tinted_bitmap(buttonbmp, al_map_rgb(255,0,0), buttonOne.x, buttonOne.y, 0);
                }
                if (!buttonTwo.isClicked) {
                    SetButtonTwo(&buttonTwo, &mixer);
                    al_draw_bitmap(buttonbmp, buttonTwo.x, buttonTwo.y, 0);
                    al_set_sample_instance_gain(rock1inst, 0);
                }
                else {
                    al_draw_tinted_bitmap(buttonbmp, al_map_rgb(255,0,0), buttonTwo.x, buttonTwo.y, 0);
                }
                if (!buttonThree.isClicked) {
                    SetButtonThree(&buttonThree, &mixer);
                    al_draw_bitmap(buttonbmp, buttonThree.x, buttonThree.y, 0);
                    al_set_sample_instance_gain(jazz1inst, 0);
                }
                else {
                    al_draw_tinted_bitmap(buttonbmp, al_map_rgb(255,0,0), buttonThree.x, buttonThree.y, 0);
                }
                if (!buttonFour.isClicked) {
                    SetButtonFour(&buttonFour, &mixer);
                    al_draw_bitmap(buttonbmp, buttonFour.x, buttonFour.y, 0);
                    al_set_sample_instance_gain(reggae1inst, 0);
                }
                else {
                    al_draw_tinted_bitmap(buttonbmp, al_map_rgb(255,0,0), buttonFour.x, buttonFour.y, 0);
                }
                if (!buttonFive.isClicked) {
                    SetButtonFive(&buttonFive, &mixer);
                    al_draw_bitmap(buttonbmp, buttonFive.x, buttonFive.y, 0);
                    al_set_sample_instance_gain(reggae2inst, 0);
                }
                else {
                    al_draw_tinted_bitmap(buttonbmp, al_map_rgb(255,0,0), buttonFive.x, buttonFive.y, 0);
                }
                if (!buttonSix.isClicked) {
                    SetButtonSix(&buttonSix, &mixer);
                    al_draw_bitmap(buttonbmp, buttonSix.x, buttonSix.y, 0);
                    al_set_sample_instance_gain(jazz2inst, 0);
                }
                else {
                    al_draw_tinted_bitmap(buttonbmp, al_map_rgb(255,0,0), buttonSix.x, buttonSix.y, 0);
                }
                if (!buttonSeven.isClicked) {
                    SetButtonSeven(&buttonSeven, &mixer);
                    al_draw_bitmap(buttonbmp, buttonSeven.x, buttonSeven.y, 0);
                    al_set_sample_instance_gain(rock2inst, 0);
                }
                else {
                    al_draw_tinted_bitmap(buttonbmp, al_map_rgb(255,0,0), buttonSeven.x, buttonSeven.y, 0);
                }
                if (!buttonEight.isClicked) {
                    SetButtonEight(&buttonEight, &mixer);
                    al_draw_bitmap(buttonbmp, buttonEight.x, buttonEight.y, 0);
                    al_set_sample_instance_gain(hiphop2inst, 0);
                }
                else {
                    al_draw_tinted_bitmap(buttonbmp, al_map_rgb(255,0,0), buttonEight.x, buttonEight.y, 0);
                }
                if (!buttonNine.isClicked) {
                    SetButtonNine(&buttonNine, &mixer);
                    al_draw_bitmap(buttonbmp, buttonNine.x, buttonNine.y, 0);
                    al_set_sample_instance_gain(rock3inst, 0);
                }
                else {
                    al_draw_tinted_bitmap(buttonbmp, al_map_rgb(255,0,0), buttonNine.x, buttonNine.y, 0);
                }
                if (!buttonTen.isClicked) {
                    SetButtonTen(&buttonTen, &mixer);
                    al_draw_bitmap(buttonbmp, buttonTen.x, buttonTen.y, 0);
                    al_set_sample_instance_gain(hiphop3inst, 0);
                }
                else {
                    al_draw_tinted_bitmap(buttonbmp, al_map_rgb(255,0,0), buttonTen.x, buttonTen.y, 0);
                }
                if (!buttonEleven.isClicked) {
                    SetButtonEleven(&buttonEleven, &mixer);
                    al_draw_bitmap(buttonbmp, buttonEleven.x, buttonEleven.y, 0);
                    al_set_sample_instance_gain(reggae3inst, 0);
                }
                else {
                    al_draw_tinted_bitmap(buttonbmp, al_map_rgb(255,0,0), buttonEleven.x, buttonEleven.y, 0);
                }
                if (!buttonTwelve.isClicked) {
                    SetButtonTwelve(&buttonTwelve, &mixer);
                    al_draw_bitmap(buttonbmp, buttonTwelve.x, buttonTwelve.y, 0);
                    al_set_sample_instance_gain(jazz3inst, 0);
                }
                else {
                    al_draw_tinted_bitmap(buttonbmp, al_map_rgb(255,0,0), buttonTwelve.x, buttonTwelve.y, 0);
                }
                if (!buttonThirteen.isClicked) {
                    SetButtonThirteen(&buttonThirteen, &mixer);
                    al_draw_bitmap(buttonbmp, buttonThirteen.x, buttonThirteen.y, 0);
                    al_set_sample_instance_gain(reggae4inst, 0);
                }
                else {
                    al_draw_tinted_bitmap(buttonbmp, al_map_rgb(255,0,0), buttonThirteen.x, buttonThirteen.y, 0);
                }
                if (!buttonFourteen.isClicked) {
                    SetButtonFourteen(&buttonFourteen, &mixer);
                    al_draw_bitmap(buttonbmp, buttonFourteen.x, buttonFourteen.y, 0);
                    al_set_sample_instance_gain(jazz4inst, 0);
                }
                else {
                    al_draw_tinted_bitmap(buttonbmp, al_map_rgb(255,0,0), buttonFourteen.x, buttonFourteen.y, 0);
                }
                if (!buttonFifteen.isClicked) {
                    SetButtonFifteen(&buttonFifteen, &mixer);
                    al_draw_bitmap(buttonbmp, buttonFifteen.x, buttonFifteen.y, 0);
                    al_set_sample_instance_gain(rock4inst, 0);
                }
                else {
                    al_draw_tinted_bitmap(buttonbmp, al_map_rgb(255,0,0), buttonFifteen.x, buttonFifteen.y, 0);
                }
                if (!buttonSixteen.isClicked) {
                    SetButtonSixteen(&buttonSixteen, &mixer);
                    al_draw_bitmap(buttonbmp, buttonSixteen.x, buttonSixteen.y, 0);
                    al_set_sample_instance_gain(hiphop4inst, 0);
                }
                else {
                    al_draw_tinted_bitmap(buttonbmp, al_map_rgb(255,0,0), buttonSixteen.x, buttonSixteen.y, 0);
                }
                
                // If the mix button is NOT clicked, it will continue to be drawn to the backbuffer and the bitmap displayed,
                // If the mix button is clicked, the round is over and the Score screen is initiated.
                if (!mixbutton.isMixed) {
                    SetMixButton(&mixbutton);
                    al_draw_bitmap(mixbuttonbmp, mixbutton.x, mixbutton.y, 0);
                }
                else {
                    isRoundOver = true;
                }
                
                // Finally the things drawn to our backbuffer are flipped to the front
                al_flip_display();
            }

            // This is the beginning of the score screen where the ratios and score will be calculated
            while (isRoundOver && !done) {
                
                ALLEGRO_EVENT ev;
                al_wait_for_event (event_queue, &ev);
                
                // Checks if an event timer event has occurred (1/60 second). If so, the screen is redrawn
                if (ev.type == ALLEGRO_EVENT_TIMER) {
                    redraw = true;
                }
                
                // If the user closes the display, the game quits
                else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) 
                {
                    done = true;
                }
                
                // This listens for a mouse button up event:
                else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
                    
                    // This occurs so that the score is only calculated once since we are in a while loop
                    isScoreCalculated = false;
                    
                    // Updates the counter
                    i++;
                    
                    // This updates the counter between rounds
                    if (i > 4 && ((jazzScore + rockScore + reggaeScore + hiphopScore) < 7000)) {
                        
                        // Then we know we are at the end of the month
                        isEndOfMonth = true;
                        
                        // And we enter the end of the month screen, based on the total score.
                        // the same events are listened for:
                        while (isEndOfMonth && !done) {
                            
                            ALLEGRO_EVENT ev;
                            al_wait_for_event (event_queue, &ev);
                            
                            // Checks if an event timer event has occurred (1/60 second). If so, the screen is redrawn
                            if (ev.type == ALLEGRO_EVENT_TIMER) {
                                redraw = true;
                            }
                            
                            // If the user closes the display, the game quits
                            else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
                                done = true;
                            }
                            
                            // This listens for a mouse button up event:
                            else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
                                
                                // Checks to see if we are in the range of the try again button:
                                if (ev.mouse.x > WIDTH / 2 - 50 &&
                                    ev.mouse.x < (WIDTH / 2 - 50 + (al_get_bitmap_width(mixbuttonbmp) * 2)) &&
                                    ev.mouse.y > 350 &&
                                    ev.mouse.y < (350 + (al_get_bitmap_height(mixbuttonbmp) * 2)) &&
                                    ev.mouse.button & 1) {
                                    
                                    // The game restarts by setting this flag to false. The counter 'i' gets set
                                    // back to one so the game starts over again:
                                    isEndOfMonth = false;
                                    i = 1;
                                    
                                    // Initializes the scores back to zero:
                                    jazzScore = 0;
                                    rockScore = 0;
                                    reggaeScore = 0;
                                    hiphopScore = 0;
                                }
                                
                                // Checks to see if we are within the quit button, then if we click, it exits:
                                else if (ev.mouse.x > WIDTH / 2 - 50 &&
                                         ev.mouse.x < (WIDTH / 2 - 50 + (al_get_bitmap_width(mixbuttonbmp) * 2)) &&
                                         ev.mouse.y > (375 + (al_get_bitmap_height(mixbuttonbmp) * 2)) &&
                                         ev.mouse.y < (375 + (al_get_bitmap_height(mixbuttonbmp) * 4)) &&
                                         ev.mouse.button & 1) {
                                    
                                    // This means the game is over and we exit the main game loop
                                    done = true;
                                }
                            }
                            
                            // Redraw from within the end of the month screen based on our timer...same
                            // as before by clearing the screen to black, drawing things/ displaying text to the
                            // backbuffer, and then flipping the backbuffer to the front:
                            if (redraw && al_is_event_queue_empty(event_queue)) {
                                
                                // Clears the front buffer to black so that we can redraw to the backbuffer
                                // and then flip everything to the front
                                al_clear_to_color(al_map_rgb(0,0,0));

                                // "ITS THAT TIME OF THE MONTH"
                                al_draw_textf(fontHeader, al_map_rgb(255,0,255), WIDTH / 2, 20, 
                                              ALLEGRO_ALIGN_CENTRE, "ITS THAT TIME OF THE MONTH");
                                // Total cash displayed:
                                al_draw_textf(fontScore, al_map_rgb(255,255,255), WIDTH / 2, 20 + al_get_font_line_height(fontHeader), 
                                              ALLEGRO_ALIGN_CENTRE, "Total Cash: ");
                                
                                // Prints the same thing but with different spacing based on what the score is
                                if ((jazzScore + rockScore + hiphopScore + reggaeScore) == 0) {
                                    al_draw_textf(fontScore, al_map_rgb(34,139,34), WIDTH / 2, 20 + al_get_font_line_height(fontHeader), 
                                                  ALLEGRO_ALIGN_CENTRE, "               $%d", 
                                                  jazzScore + rockScore + hiphopScore + reggaeScore);
                                }
                                
                                // Simply shifts the score to the right so it looks nicer on the display
                                else {
                                    al_draw_textf(fontScore, al_map_rgb(34,139,34), WIDTH / 2, 20 + al_get_font_line_height(fontHeader), 
                                                  ALLEGRO_ALIGN_CENTRE, "                 $%d", 
                                                  jazzScore + rockScore + hiphopScore + reggaeScore);
                                }
                                
                                // Rent and utilities displayed:
                                al_draw_textf(fontScore, al_map_rgb(255,255,255), WIDTH / 2, 20 + al_get_font_line_height(fontHeader) + 
                                              al_get_font_line_height(fontScore), ALLEGRO_ALIGN_CENTRE, "Rent and Utilities: $7000");
                                
                                // Cash left text displayed:
                                al_draw_textf(fontScore, al_map_rgb(255,255,255), WIDTH / 2, 20 + al_get_font_line_height(fontHeader) + 
                                              (al_get_font_line_height(fontScore) * 2), 
                                              ALLEGRO_ALIGN_CENTRE, "Cash Left: ");
                                
                                // Simply shifts the score based on what the score is...if less than zero:
                                if ((jazzScore + rockScore + hiphopScore + reggaeScore) - 7000 < 0) {
                                    al_draw_textf(fontScore, al_map_rgb(255,0,0), WIDTH / 2, 20 + al_get_font_line_height(fontHeader) + 
                                                  (al_get_font_line_height(fontScore) * 2), 
                                                  ALLEGRO_ALIGN_CENTRE, "                 $%d", 
                                                  (jazzScore + rockScore + hiphopScore + reggaeScore) - 7000);
                                }
                                
                                // If equal to zero:
                                else if ((jazzScore + rockScore + hiphopScore + reggaeScore) - 7000 == 0) {
                                    al_draw_textf(fontScore, al_map_rgb(255,0,0), WIDTH / 2, 20 + al_get_font_line_height(fontHeader) +
                                                  (al_get_font_line_height(fontScore) * 2), 
                                                  ALLEGRO_ALIGN_CENTRE, "               $%d", 
                                                  (jazzScore + rockScore + hiphopScore + reggaeScore) - 7000);
                                }
                                
                                // If greater than zero:
                                else {
                                    al_draw_textf(fontScore, al_map_rgb(34,139,34), WIDTH / 2, 20 + al_get_font_line_height(fontHeader) +
                                                  (al_get_font_line_height(fontScore) * 2), 
                                                  ALLEGRO_ALIGN_CENTRE, "                 $%d", 
                                                  (jazzScore + rockScore + hiphopScore + reggaeScore) - 7000);
                                }
                                
                                // Displays the uri game over bitmap:
                                al_draw_bitmap(urigameoverbmp, WIDTH / 2 - 400, HEIGHT / 2 - 200, 0);
                                al_draw_scaled_bitmap(uridialogwinbmp, 0, 0, al_get_bitmap_width(uridialogwinbmp), 
                                                      al_get_bitmap_height(uridialogwinbmp), 1, HEIGHT / 2 - 150, 
                                                      al_get_bitmap_width(uridialogwinbmp) / 3, 
                                                      al_get_bitmap_height(uridialogwinbmp) / 3, 0);
                                
                                // Displays the eviction notice bitmap:
                                al_draw_scaled_bitmap(evictionbmp, 0, 0, al_get_bitmap_width(evictionbmp), 
                                                      al_get_bitmap_height(evictionbmp), 675, HEIGHT / 2 - 50, 
                                                      al_get_bitmap_width(evictionbmp) / 3, 
                                                      al_get_bitmap_height(evictionbmp) / 3, 0);
                                
                                // Displays the try again button:
                                al_draw_scaled_bitmap(tryagainbuttonbmp, 0, 0, al_get_bitmap_width(tryagainbuttonbmp), 
                                                      al_get_bitmap_height(tryagainbuttonbmp), WIDTH / 2 - 50, 350, 
                                                      al_get_bitmap_width(mixbuttonbmp) * 2, 
                                                      al_get_bitmap_height(mixbuttonbmp) * 2, 0);
                                
                                // Displays the quit button
                                al_draw_scaled_bitmap(quitbuttonbmp, 0, 0, al_get_bitmap_width(quitbuttonbmp), 
                                                      al_get_bitmap_height(quitbuttonbmp), WIDTH / 2 - 50, 375 + (al_get_bitmap_height(mixbuttonbmp) * 2), 
                                                      al_get_bitmap_width(mixbuttonbmp) * 2, 
                                                      al_get_bitmap_height(mixbuttonbmp) * 2, 0);
                                
                                // Everything has been redrawn to the backbuffer so it is flipped back to the front
                                al_flip_display();
                            }
                        }
                    }
                    
                    // If the total score for 4 rounds is greater than 7000:
                    else if ((i > 4) && ((jazzScore + rockScore + reggaeScore + hiphopScore) > 7000)) {
                        
                        // Then we know we are at the end of the month
                        isEndOfMonth = true;
                        
                        // If we are at the end of the month, this while loop begins:
                        while (isEndOfMonth && !done) {
                            
                            ALLEGRO_EVENT ev;
                            al_wait_for_event (event_queue, &ev);
                            
                            // Checks if an event timer event has occurred (1/60 second). If so, the screen is redrawn
                            if (ev.type == ALLEGRO_EVENT_TIMER) {
                                redraw = true;
                            }
                            
                            // If the user closes the display, the game quits
                            else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
                                done = true;
                            }
                            
                            // This listens for a mouse button up event:
                            if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
                                
                                // Checks to see if we are in the range of the try again button:
                                if (ev.mouse.x > WIDTH / 2 - 50 &&
                                    ev.mouse.x < (WIDTH / 2 - 50 + (al_get_bitmap_width(mixbuttonbmp) * 2)) &&
                                    ev.mouse.y > 350 &&
                                    ev.mouse.y < (350 + (al_get_bitmap_height(mixbuttonbmp) * 2)) &&
                                    ev.mouse.button & 1) {
                                    
                                    // The game restarts by setting this flag to false. The counter 'i' gets set
                                    // back to one so the game starts over again:
                                    isEndOfMonth = false;
                                    i = 1;
                                    
                                    // Initializes the scores back to zero:
                                    jazzScore = 0;
                                    rockScore = 0;
                                    reggaeScore = 0;
                                    hiphopScore = 0;
                                }
                                
                                // Checks to see if we are within the quit button, then if we click, it exits:
                                else if (ev.mouse.x > WIDTH / 2 - 50 &&
                                         ev.mouse.x < (WIDTH / 2 - 50 + (al_get_bitmap_width(mixbuttonbmp) * 2)) &&
                                         ev.mouse.y > (375 + (al_get_bitmap_height(mixbuttonbmp) * 2)) &&
                                         ev.mouse.y < (375 + (al_get_bitmap_height(mixbuttonbmp) * 4)) &&
                                         ev.mouse.button & 1) {
                                    
                                    // This means the game is over and we exit the main game loop
                                    done = true;
                                }
                            }
                            if (redraw && al_is_event_queue_empty(event_queue)) {
                                
                                // Clears the front buffer to black so that we can redraw to the backbuffer
                                // and then flip everything to the front
                                al_clear_to_color(al_map_rgb(0,0,0));
                                
                                // "ITS THAT TIME OF THE MONTH" displayed
                                al_draw_textf(fontHeader, al_map_rgb(255,0,255), WIDTH / 2, 20, 
                                              ALLEGRO_ALIGN_CENTRE, "ITS THAT TIME OF THE MONTH");
                                
                                // Total cash displayed:
                                al_draw_textf(fontScore, al_map_rgb(255,255,255), WIDTH / 2, 20 + al_get_font_line_height(fontHeader), 
                                              ALLEGRO_ALIGN_CENTRE, "Total Cash: ");
                                
                                // Score is displayed:
                                al_draw_textf(fontScore, al_map_rgb(34,139,34), WIDTH / 2, 20 + al_get_font_line_height(fontHeader), 
                                              ALLEGRO_ALIGN_CENTRE, "                 $%d", 
                                              jazzScore + rockScore + hiphopScore + reggaeScore);
                                
                                // Rent and utilities displayed:
                                al_draw_textf(fontScore, al_map_rgb(255,255,255), WIDTH / 2, 20 + al_get_font_line_height(fontHeader) + 
                                              al_get_font_line_height(fontScore), ALLEGRO_ALIGN_CENTRE, "Rent and Utilities: $7000");
                                
                                // Cash Left displayed:
                                al_draw_textf(fontScore, al_map_rgb(255,255,255), WIDTH / 2, 20 + al_get_font_line_height(fontHeader) + 
                                              (al_get_font_line_height(fontScore) * 2), 
                                              ALLEGRO_ALIGN_CENTRE, "Cash Left: ");
                                
                                // Cash left amount after deductions:
                                al_draw_textf(fontScore, al_map_rgb(34,139,34), WIDTH / 2, 20 + al_get_font_line_height(fontHeader) +
                                              (al_get_font_line_height(fontScore) * 2), 
                                              ALLEGRO_ALIGN_CENTRE, "                 $%d", 
                                              (jazzScore + rockScore + hiphopScore + reggaeScore) - 7000);
                                
                                // al_draw_bitmap(uriwinbmp, WIDTH / 2 + 200, HEIGHT / 2 - 200, 0);
                                al_draw_bitmap(kennygwinbmp, 672, 244, 0);
                                al_draw_bitmap(dimebagwinbmp, 183, 364, 0);
                                al_draw_bitmap(kingtubbywinbmp, 25, 205, 0);
                                al_draw_bitmap(pdiddywinbmp, 578, 389, 0);
                                
                                // Draws the 'Try Again button' bitmap
                                al_draw_scaled_bitmap(tryagainbuttonbmp, 0, 0, al_get_bitmap_width(tryagainbuttonbmp), 
                                                      al_get_bitmap_height(tryagainbuttonbmp), WIDTH / 2 - 50, 350, 
                                                      al_get_bitmap_width(mixbuttonbmp) * 2, 
                                                      al_get_bitmap_height(mixbuttonbmp) * 2, 0);
                                // Draws the 'Quit Button' bitmap
                                al_draw_scaled_bitmap(quitbuttonbmp, 0, 0, al_get_bitmap_width(quitbuttonbmp), 
                                                      al_get_bitmap_height(quitbuttonbmp), WIDTH / 2 - 50, 375 + (al_get_bitmap_height(mixbuttonbmp) * 2), 
                                                      al_get_bitmap_width(mixbuttonbmp) * 2, 
                                                      al_get_bitmap_height(mixbuttonbmp) * 2, 0);
                                
                                // Flips the display when redrawing to the backbuffer is completed
                                al_flip_display();
                            }
                        }
                    }
                    
                    // Re-initializes mixer and faders
                    InitMixer(&mixer, mixerbmp);
                    InitFader(&faderOne, faderbmp);
                    InitFader(&faderTwo, faderbmp);
                    InitFader(&faderThree, faderbmp);
                    InitFader(&faderFour, faderbmp);
                    // Re-sets the faders to the screen
                    SetFaderOne(&faderOne, &mixer);
                    SetFaderTwo(&faderTwo, &mixer);
                    SetFaderThree(&faderThree, &mixer);
                    SetFaderFour(&faderFour,&mixer);
                    
                    // Buttons don't need to be re- Set, because they're not moving at all...
                    // They do however need to be reinitialized
                    InitButtons(&buttonOne, buttonbmp);
                    InitButtons(&buttonTwo, buttonbmp);
                    InitButtons(&buttonThree, buttonbmp);
                    InitButtons(&buttonFour, buttonbmp);
                    InitButtons(&buttonFive, buttonbmp);
                    InitButtons(&buttonSix, buttonbmp);
                    InitButtons(&buttonSeven, buttonbmp);
                    InitButtons(&buttonEight, buttonbmp);
                    InitButtons(&buttonNine, buttonbmp);
                    InitButtons(&buttonTen, buttonbmp);
                    InitButtons(&buttonEleven, buttonbmp);
                    InitButtons(&buttonTwelve, buttonbmp);
                    InitButtons(&buttonThirteen, buttonbmp);
                    InitButtons(&buttonFourteen, buttonbmp);
                    InitButtons(&buttonFifteen, buttonbmp);
                    InitButtons(&buttonSixteen, buttonbmp);
                    // Re-initializes the mix button
                    InitMixButton(&mixbutton, mixbuttonbmp);
                    
                    // The isRoundOver flag is set back to false and the rounds start over again
                    isRoundOver = false;
                }
                
                // Redrawing for our 'isRoundOver screen: Same as before
                if (redraw && al_is_event_queue_empty(event_queue)) {
                    redraw = false;
                    
                    // Clears the front buffer to black so that we can redraw to the backbuffer
                    // and then flip everything to the front
                    al_clear_to_color(al_map_rgb(0,0,0));
                    
                    // Round _ Over is displayed
                    al_draw_textf(fontHeader, al_map_rgb(255,0,255), WIDTH / 2, 20, 
                                  ALLEGRO_ALIGN_CENTRE, "ROUND %d OVER", i);
                    
                    // Click to Begin Next Round displayed
                    al_draw_textf(fontMain, al_map_rgb(255,0,255), WIDTH / 2, 20 + 
                                  al_get_font_line_height(fontHeader), 
                                  ALLEGRO_ALIGN_CENTRE, "(click to begin the next round)");
                    
                    // Money bitmap is displayed:
                    al_draw_bitmap(moneybmp, WIDTH / 2 - (al_get_bitmap_width(moneybmp) / 2), HEIGHT / 2 + 
                                   al_get_font_line_height(fontMain) , 0);
                    
                    // JAZZ GOES IN BUTTONS Three, Six, Twelve, AND Fourteen
                    if (isKennyG && !isScoreCalculated) { 
                        
                        // Initialize results to sentinel values
                        results1 = 100; 
                        results2 = 100; 
                        results3 = 100;
                        results_total = 0;
                        score = 0;
                        mixScore = 0;
                        
                        // Scores are added based on correct buttons pressed:
                        if (buttonThree.isClicked){
                            score += 25;
                        }
                        if (buttonThree.isClicked && buttonSix.isClicked){
                            user_ratio1 = al_get_sample_instance_gain(jazz2inst)/al_get_sample_instance_gain(jazz1inst);
                            results1 = fabs(ideal_jazz_ratio1 - user_ratio1);
                        }
                        if (buttonSix.isClicked){
                            score += 25;
                        }
                        if (buttonSix.isClicked && buttonTwelve.isClicked){
                            user_ratio2 = al_get_sample_instance_gain(jazz3inst)/ al_get_sample_instance_gain(jazz2inst);
                            results2 = fabs(ideal_jazz_ratio2 - user_ratio2);
                        }
                        if (buttonTwelve.isClicked){
                            score += 25;        
                        }
                        if (buttonTwelve.isClicked && buttonFourteen.isClicked){
                            user_ratio3 = al_get_sample_instance_gain(jazz4inst)/ al_get_sample_instance_gain(jazz3inst);
                            results3 = fabs(ideal_jazz_ratio3 - user_ratio3);
                        }
                        if (buttonFourteen.isClicked){
                            score += 25;     
                        }
                        
                        // Get a bonus score if you get all correct buttons pressed:
                        if (buttonThree.isClicked && 
                            buttonSix.isClicked && 
                            buttonTwelve.isClicked && 
                            buttonFourteen.isClicked) {
                            score += 50;
                        }
                        
                        // If results are not changed, add value to results. 
                        if (results1 == 100){
                            results1 = .26;
                        }
                        if (results2 == 100){
                            results1 = .26;
                        }
                        if (results3 == 100){
                            results1 = .26;
                        }
                        
                        // Add results. Further from zero is worse
                        results_total = results1 + results2 + results3;
                        
                        if (results_total >= 0 && results_total <= .25){
                            mixScore = 150;
                        }
                        if (results_total > .25 && results_total <= .40){
                            mixScore = 75;
                        }
                        if (results_total > .40){
                            mixScore = 0;
                        }
                        
                        // Calculate total Score
                        jazzScore = (score + mixScore) * 10;          
                        isScoreCalculated = true;
                        
                        // Exit the loop so score is only calculated once:      
                        isKennyG = false;
                        
                        // This will essentially mute the tracks as we go to the score screen.
                        al_set_sample_instance_gain(hiphop1inst, 0);
                        al_set_sample_instance_gain(hiphop2inst, 0);
                        al_set_sample_instance_gain(hiphop3inst, 0);
                        al_set_sample_instance_gain(hiphop4inst, 0);
                        al_set_sample_instance_gain(rock1inst, 0);
                        al_set_sample_instance_gain(rock2inst, 0);
                        al_set_sample_instance_gain(rock3inst, 0);
                        al_set_sample_instance_gain(rock4inst, 0);
                        al_set_sample_instance_gain(jazz1inst, 0);
                        al_set_sample_instance_gain(jazz2inst, 0);
                        al_set_sample_instance_gain(jazz3inst, 0);
                        al_set_sample_instance_gain(jazz4inst, 0);
                        al_set_sample_instance_gain(reggae1inst, 0);
                        al_set_sample_instance_gain(reggae2inst, 0);
                        al_set_sample_instance_gain(reggae3inst, 0);
                        al_set_sample_instance_gain(reggae4inst, 0);
                    }
                    
                    // ROCK GOES IN BUTTONS Two, seven, nine, fifteen
                    if (isDimebagDarrell && !isScoreCalculated) {   
                        
                        // Initialize results to sentinel values
                        results1 = 100; 
                        results2 = 100; 
                        results3 = 100;
                        results_total = 0;
                        score = 0;
                        mixScore = 0;
                        
                        // Scores are added based on correct buttons pressed:
                        if (buttonTwo.isClicked){
                            score += 25;
                        }
                        if (buttonTwo.isClicked && buttonSeven.isClicked){
                            user_ratio1 = al_get_sample_instance_gain(rock2inst) / al_get_sample_instance_gain(rock1inst);
                            results1 = fabs(ideal_rock_ratio1 - user_ratio1);
                        }
                        if (buttonSeven.isClicked) {
                            score += 25;
                        }
                        if (buttonSeven.isClicked && buttonNine.isClicked){
                            user_ratio2 = al_get_sample_instance_gain(rock3inst)/ al_get_sample_instance_gain(rock2inst);
                            results2 = fabs(ideal_rock_ratio2 - user_ratio2);
                        }
                        if (buttonNine.isClicked){
                            score += 25;      
                        }
                        if (buttonNine.isClicked && buttonFifteen.isClicked){
                            user_ratio3 = al_get_sample_instance_gain(rock4inst) / al_get_sample_instance_gain(rock3inst);
                            results3 = fabs(ideal_rock_ratio3 - user_ratio3);
                        }
                        if (buttonFifteen.isClicked) {
                            score += 25; 
                        }
                        
                        // Get a bonus score if you get all correct buttons pressed:
                        if (buttonTwo.isClicked && 
                            buttonSeven.isClicked && 
                            buttonNine.isClicked && 
                            buttonFifteen.isClicked) {
                            // Get a bonus score!
                            score += 50;
                        }
                        
                        // If results are not changed, add value to results. 
                        if (results1 == 100){
                            results1 = .26;
                        }
                        if (results2 == 100){
                            results1 = .26;
                        }
                        if (results3 == 100){
                            results1 = .26;
                        }
                        
                        // Add results. Further from zero is worse
                        results_total = results1 + results2 + results3;
                        
                        if (results_total >= 0 && results_total <= .25){
                            mixScore = 150;
                        }
                        if (results_total > .25 && results_total <= .40){
                            mixScore = 75;
                        }
                        if (results_total > .40){
                            mixScore = 0;
                        }
                        
                        // Calculate total Score
                        rockScore = (score + mixScore) * 10;          
                        isScoreCalculated = true;
                        isDimebagDarrell = false;
                        
                        // This will essentially mute the tracks as we go to the score screen.
                        al_set_sample_instance_gain(hiphop1inst, 0);
                        al_set_sample_instance_gain(hiphop2inst, 0);
                        al_set_sample_instance_gain(hiphop3inst, 0);
                        al_set_sample_instance_gain(hiphop4inst, 0);
                        al_set_sample_instance_gain(rock1inst, 0);
                        al_set_sample_instance_gain(rock2inst, 0);
                        al_set_sample_instance_gain(rock3inst, 0);
                        al_set_sample_instance_gain(rock4inst, 0);
                        al_set_sample_instance_gain(jazz1inst, 0);
                        al_set_sample_instance_gain(jazz2inst, 0);
                        al_set_sample_instance_gain(jazz3inst, 0);
                        al_set_sample_instance_gain(jazz4inst, 0);
                        al_set_sample_instance_gain(reggae1inst, 0);
                        al_set_sample_instance_gain(reggae2inst, 0);
                        al_set_sample_instance_gain(reggae3inst, 0);
                        al_set_sample_instance_gain(reggae4inst, 0);
                    }
                    
                    // RAP GOES IN BUTTONS one,eight, ten, sixteen
                    if (isPDiddy && !isScoreCalculated) {     
                        
                        // Initialize results to sentinel values
                        results1 = 100; 
                        results2 = 100; 
                        results3 = 100;
                        results_total = 0;
                        score = 0;
                        mixScore = 0;
                        
                        // Scores are added based on correct buttons pressed:
                        if (buttonOne.isClicked){ 
                            score += 25;
                        }
                        if (buttonOne.isClicked && buttonEight.isClicked){
                            user_ratio1 = al_get_sample_instance_gain(hiphop2inst) / al_get_sample_instance_gain(hiphop1inst);
                            results1 = fabs(ideal_hiphop_ratio1 - user_ratio1);
                        }
                        if (buttonEight.isClicked){ 
                            score += 25;
                        }
                        if (buttonEight.isClicked && buttonTen.isClicked){
                            user_ratio2 = al_get_sample_instance_gain(hiphop3inst)/ al_get_sample_instance_gain(hiphop2inst);
                            results2 = fabs(ideal_hiphop_ratio2 - user_ratio2);    
                        }
                        if (buttonTen.isClicked){
                            score += 25;     
                        }
                        if (buttonTen.isClicked && buttonSixteen.isClicked){
                            user_ratio3 = al_get_sample_instance_gain(hiphop4inst) / al_get_sample_instance_gain(hiphop3inst); 
                            results3 = fabs(ideal_hiphop_ratio3 - user_ratio3);
                        }
                        if (buttonSixteen.isClicked){
                            score += 25; 
                        }
                        
                        // Get a bonus score if you get all correct buttons pressed:
                        if (buttonOne.isClicked && 
                            buttonEight.isClicked && 
                            buttonTen.isClicked && 
                            buttonSixteen.isClicked) {
                            
                            // Get a bonus score!
                            score += 50;
                        }
                        
                        // If results are not changed, add value to results. 
                        if (results1 == 100){
                            results1 = .26;
                        }
                        if (results2 == 100){
                            results1 = .26;
                        }
                        if (results3 == 100){
                            results1 = .26;
                        }
                        
                        // Add results. Further from zero is worse
                        results_total = results1 + results2 + results3;
                        
                        if (results_total >= 0 && results_total <= .25){
                            mixScore = 150;
                        }
                        if (results_total > .25 && results_total <= .40){
                            mixScore = 75;
                        }
                        if (results_total > .40){
                            mixScore = 0;
                        }
                        
                        // Calculate total Score
                        hiphopScore = (score + mixScore) * 10;          
                        isScoreCalculated = true;                    
                        isPDiddy = false;
                        
                        // This will essentially mute the tracks as we go to the score screen.
                        al_set_sample_instance_gain(hiphop1inst, 0);
                        al_set_sample_instance_gain(hiphop2inst, 0);
                        al_set_sample_instance_gain(hiphop3inst, 0);
                        al_set_sample_instance_gain(hiphop4inst, 0);
                        al_set_sample_instance_gain(rock1inst, 0);
                        al_set_sample_instance_gain(rock2inst, 0);
                        al_set_sample_instance_gain(rock3inst, 0);
                        al_set_sample_instance_gain(rock4inst, 0);
                        al_set_sample_instance_gain(jazz1inst, 0);
                        al_set_sample_instance_gain(jazz2inst, 0);
                        al_set_sample_instance_gain(jazz3inst, 0);
                        al_set_sample_instance_gain(jazz4inst, 0);
                        al_set_sample_instance_gain(reggae1inst, 0);
                        al_set_sample_instance_gain(reggae2inst, 0);
                        al_set_sample_instance_gain(reggae3inst, 0);
                        al_set_sample_instance_gain(reggae4inst, 0);
                    }
                    
                    // REGGAE GOES IN BUTTONS four, five, eleven, thirteen
                    if (isKingTubby && !isScoreCalculated) {  
                        
                        // Initialize results to sentinel values
                        results1 = 100; 
                        results2 = 100; 
                        results3 = 100;
                        results_total = 0;
                        score = 0;
                        mixScore = 0;
                        
                        // Scores are added based on correct buttons pressed:
                        if (buttonFour.isClicked){ 
                            score += 25;
                        }
                        if (buttonFour.isClicked && buttonFive.isClicked){
                            user_ratio1 = al_get_sample_instance_gain(reggae2inst) / al_get_sample_instance_gain(reggae1inst);
                            results1 = fabs(ideal_reggae_ratio1 - user_ratio1);
                        }
                        if (buttonFive.isClicked){ 
                            score += 25;
                        }
                        if (buttonFive.isClicked && buttonEleven.isClicked){
                            user_ratio2 = al_get_sample_instance_gain(reggae3inst)/ al_get_sample_instance_gain(reggae2inst);
                            results2 = fabs(ideal_reggae_ratio2 - user_ratio2);
                        }
                        if (buttonEleven.isClicked){
                            score += 25;        
                        }
                        if (buttonEleven.isClicked && buttonThirteen.isClicked){
                            user_ratio3 = al_get_sample_instance_gain(reggae4inst) / al_get_sample_instance_gain(reggae3inst);
                            results3 = fabs(ideal_reggae_ratio3 - user_ratio3);
                        }
                        if (buttonThirteen.isClicked){
                            score += 25; 
                        }
                        
                        // Get a bonus score if you get all correct buttons pressed:
                        if (buttonFour.isClicked && 
                            buttonFive.isClicked && 
                            buttonEleven.isClicked && 
                            buttonThirteen.isClicked) {
                            //get a bonus score!
                            score += 50;
                        }
                        
                        // If results are not changed, add value to results. 
                        if (results1 == 100){
                            results1 = .26;
                        }
                        if (results2 == 100){
                            results1 = .26;
                        }
                        if (results3 == 100){
                            results1 = .26;
                        }
                        
                        // Add results. Further from zero is worse
                        results_total = results1 + results2 + results3;
                        
                        if (results_total >= 0 && results_total <= .25){
                            mixScore = 150;
                        }
                        if (results_total > .25 && results_total <= .35){
                            mixScore = 75;
                        }
                        if (results_total > .35){
                            mixScore = 0;
                        }
                        
                        // Calculate total Score
                        reggaeScore = (score + mixScore) * 10;          
                        isScoreCalculated = true;   
                        isKingTubby = false;
                        
                        //Mute the tracks as we go to the score screen.
                        al_set_sample_instance_gain(hiphop1inst, 0);
                        al_set_sample_instance_gain(hiphop2inst, 0);
                        al_set_sample_instance_gain(hiphop3inst, 0);
                        al_set_sample_instance_gain(hiphop4inst, 0);
                        al_set_sample_instance_gain(rock1inst, 0);
                        al_set_sample_instance_gain(rock2inst, 0);
                        al_set_sample_instance_gain(rock3inst, 0);
                        al_set_sample_instance_gain(rock4inst, 0);
                        al_set_sample_instance_gain(jazz1inst, 0);
                        al_set_sample_instance_gain(jazz2inst, 0);
                        al_set_sample_instance_gain(jazz3inst, 0);
                        al_set_sample_instance_gain(jazz4inst, 0);
                        al_set_sample_instance_gain(reggae1inst, 0);
                        al_set_sample_instance_gain(reggae2inst, 0);
                        al_set_sample_instance_gain(reggae3inst, 0);
                        al_set_sample_instance_gain(reggae4inst, 0);
                    }
                    
                    // Switch statements that display the characters based on the score you get:
                    switch (i) {
                            
                        case 1:
                            
                            // Cash for mix displayed:
                            al_draw_textf(fontScore, al_map_rgb(34,139,34), WIDTH / 2, 40 + 
                                          al_get_font_line_height(fontHeader) + al_get_font_line_height(fontMain), 
                                          ALLEGRO_ALIGN_CENTRE, "Cash for Mix %d: $ %d", i, jazzScore);
                            
                            // If score is greater than 1500, happy bitmaps are displayed:
                            if (jazzScore > 1500) {
                                al_draw_bitmap(urihappybmp, 75, HEIGHT / 2 - 100, 0);
                                al_draw_bitmap(kennyghappybmp, 700, HEIGHT / 2 - 100, 0);
                                al_draw_scaled_bitmap(kennygdialoghappybmp, 0, 0, al_get_bitmap_width(kennygdialoghappybmp), 
                                                      al_get_bitmap_height(kennygdialoghappybmp), 550, HEIGHT / 2 - 100, 
                                                      al_get_bitmap_width(kennygdialoghappybmp) / 3, 
                                                      al_get_bitmap_height(kennygdialoghappybmp) / 3, 0);
                                al_draw_scaled_bitmap(uridialoghappybmp, 0, 0, al_get_bitmap_width(uridialoghappybmp), 
                                                      al_get_bitmap_height(uridialoghappybmp), 200, HEIGHT / 2 - 120, 
                                                      al_get_bitmap_width(uridialoghappybmp) / 2, 
                                                      al_get_bitmap_height(uridialoghappybmp) / 2, 0);
                            }
                            
                            // Otherwise, un-happy bitmaps are displayed:
                            else {
                                al_draw_bitmap(uripissedbmp, 40, HEIGHT / 2 - 100, 0);
                                al_draw_bitmap(kennygpissedbmp, 700, HEIGHT / 2 - 100, 0);
                                al_draw_scaled_bitmap(kennygdialogpissedbmp, 0, 0, al_get_bitmap_width(kennygdialogpissedbmp), 
                                                      al_get_bitmap_height(kennygdialogpissedbmp), 510, HEIGHT / 2 - 100, 
                                                      al_get_bitmap_width(kennygdialogpissedbmp) / 3, 
                                                      al_get_bitmap_height(kennygdialogpissedbmp) / 3, 0);
                                al_draw_scaled_bitmap(uridialogpissedbmp, 0, 0, al_get_bitmap_width(uridialogpissedbmp), 
                                                      al_get_bitmap_height(uridialogpissedbmp), 200, HEIGHT / 2 - 120, 
                                                      al_get_bitmap_width(uridialogpissedbmp) / 2, 
                                                      al_get_bitmap_height(uridialogpissedbmp) / 2, 0);
                                
                            }
                            
                            // Cash total is displayed underneath:
                            al_draw_textf(fontScore, al_map_rgb(34,139,34), WIDTH / 2, 40 + 
                                          al_get_font_line_height(fontHeader) + al_get_font_line_height(fontMain) + 
                                          al_get_font_line_height(fontScore), 
                                          ALLEGRO_ALIGN_CENTRE, "Total Cash: $ %d", jazzScore + rockScore + hiphopScore + reggaeScore);
                            break;
                        case 2:
                            
                            // Cash for mix displayed:
                            al_draw_textf(fontScore, al_map_rgb(34,139,34), WIDTH / 2, 40 + al_get_font_line_height(fontHeader) + 
                                          al_get_font_line_height(fontMain), 
                                          ALLEGRO_ALIGN_CENTRE, "Cash for Mix %d: $ %d", i, hiphopScore);
                            
                            // If score is greater than 1500, happy bitmaps are displayed:
                            if (hiphopScore > 1500) {
                                al_draw_bitmap(urihappybmp, 75, HEIGHT / 2 - 100, 0);
                                al_draw_bitmap(pdiddyhappybmp, 700, HEIGHT - (al_get_bitmap_height(pdiddyhappybmp) + 100), 0);
                                al_draw_scaled_bitmap(pdiddydialoghappybmp, 0, 0, al_get_bitmap_width(pdiddydialoghappybmp), 
                                                      al_get_bitmap_height(pdiddydialoghappybmp), 600, HEIGHT / 2 - 75, 
                                                      al_get_bitmap_width(pdiddydialoghappybmp) / 3, 
                                                      al_get_bitmap_height(pdiddydialoghappybmp) / 3, 0);
                                al_draw_scaled_bitmap(uridialoghappybmp, 0, 0, al_get_bitmap_width(uridialoghappybmp), 
                                                      al_get_bitmap_height(uridialoghappybmp), 200, HEIGHT / 2 - 120, 
                                                      al_get_bitmap_width(uridialoghappybmp) / 2, 
                                                      al_get_bitmap_height(uridialoghappybmp) / 2, 0);
                            }
                            
                            // Otherwise, un-happy bitmaps are displayed:
                            else {
                                
                                al_draw_bitmap(uripissedbmp, 40, HEIGHT / 2 - 100, 0);
                                al_draw_bitmap(pdiddypissedbmp, 700, HEIGHT - (al_get_bitmap_height(pdiddypissedbmp) + 25), 0);
                                al_draw_scaled_bitmap(pdiddydialogpissedbmp, 0, 0, al_get_bitmap_width(pdiddydialogpissedbmp), 
                                                      al_get_bitmap_height(pdiddydialogpissedbmp), 575, HEIGHT / 2 - 25, 
                                                      al_get_bitmap_width(pdiddydialogpissedbmp) / 3, 
                                                      al_get_bitmap_height(pdiddydialogpissedbmp) / 3, 0);
                                al_draw_scaled_bitmap(uridialogpissedbmp, 0, 0, al_get_bitmap_width(uridialogpissedbmp), 
                                                      al_get_bitmap_height(uridialogpissedbmp), 200, HEIGHT / 2 - 120, 
                                                      al_get_bitmap_width(uridialogpissedbmp) / 2, 
                                                      al_get_bitmap_height(uridialogpissedbmp) / 2, 0);
                            }
                            
                            // Cash total is displayed underneath:
                            al_draw_textf(fontScore, al_map_rgb(34,139,34), WIDTH / 2, 40 + 
                                          al_get_font_line_height(fontHeader) + al_get_font_line_height(fontMain) + 
                                          al_get_font_line_height(fontScore), 
                                          ALLEGRO_ALIGN_CENTRE, "Total Cash: $ %d", jazzScore + rockScore + hiphopScore + reggaeScore);
                            break;
                        case 3:
                            
                            // Cash for mix displayed:
                            al_draw_textf(fontScore, al_map_rgb(34,139,34), WIDTH / 2, 40 + al_get_font_line_height(fontHeader) + 
                                          al_get_font_line_height(fontMain), ALLEGRO_ALIGN_CENTRE, "Cash for Mix %d: $ %d", i, reggaeScore);
                            
                            // If score is greater than 1500, happy bitmaps are displayed:
                            if (reggaeScore > 1500) {
                                al_draw_bitmap(urihappybmp, 75, HEIGHT / 2 - 100, 0);
                                al_draw_bitmap(kingtubbyhappybmp, 700, HEIGHT - (al_get_bitmap_height(kingtubbyhappybmp) + 150), 0);
                                al_draw_scaled_bitmap(kingtubbydialoghappybmp, 0, 0, al_get_bitmap_width(kingtubbydialoghappybmp), 
                                                      al_get_bitmap_height(kingtubbydialoghappybmp), 640, HEIGHT / 2 - 150, 
                                                      al_get_bitmap_width(kingtubbydialoghappybmp) / 3, 
                                                      al_get_bitmap_height(kingtubbydialoghappybmp) / 3, 0);
                                al_draw_scaled_bitmap(uridialoghappybmp, 0, 0, al_get_bitmap_width(uridialoghappybmp), 
                                                      al_get_bitmap_height(uridialoghappybmp), 200, HEIGHT / 2 - 120, 
                                                      al_get_bitmap_width(uridialoghappybmp) / 2, 
                                                      al_get_bitmap_height(uridialoghappybmp) / 2, 0);
                            }
                            
                            // Otherwise, un-happy bitmaps are displayed:
                            else {
                                al_draw_bitmap(uripissedbmp, 40, HEIGHT / 2 - 100, 0);
                                al_draw_bitmap(kingtubbypissedbmp, 700, HEIGHT - (al_get_bitmap_height(kingtubbypissedbmp) + 25), 0);
                                al_draw_scaled_bitmap(kingtubbydialogpissedbmp, 0, 0, al_get_bitmap_width(kingtubbydialogpissedbmp), 
                                                      al_get_bitmap_height(kingtubbydialogpissedbmp), 575, HEIGHT / 2 - 25, 
                                                      al_get_bitmap_width(kingtubbydialogpissedbmp) / 3, 
                                                      al_get_bitmap_height(kingtubbydialogpissedbmp) / 3, 0);
                                al_draw_scaled_bitmap(uridialogpissedbmp, 0, 0, al_get_bitmap_width(uridialogpissedbmp), 
                                                      al_get_bitmap_height(uridialogpissedbmp), 200, HEIGHT / 2 - 120, 
                                                      al_get_bitmap_width(uridialogpissedbmp) / 2, 
                                                      al_get_bitmap_height(uridialogpissedbmp) / 2, 0);
                            }
                            
                            // Cash total is displayed underneath:
                            al_draw_textf(fontScore, al_map_rgb(34,139,34), WIDTH / 2, 40 + 
                                          al_get_font_line_height(fontHeader) + al_get_font_line_height(fontMain) + 
                                          al_get_font_line_height(fontScore), ALLEGRO_ALIGN_CENTRE, 
                                          "Total Cash: $ %d", jazzScore + rockScore + hiphopScore + reggaeScore);
                            break;
                        case 4:
                            
                            // Cash for mix displayed:
                            al_draw_textf(fontScore, al_map_rgb(34,139,34), WIDTH / 2, 40 + 
                                          al_get_font_line_height(fontHeader) + al_get_font_line_height(fontMain), 
                                          ALLEGRO_ALIGN_CENTRE, "Cash for Mix %d: $ %d", i, rockScore);
                            
                            // If score is greater than 1500, happy bitmaps are displayed:
                            if (rockScore > 1500) {
                                al_draw_bitmap(urihappybmp, 75, HEIGHT / 2 - 100, 0);
                                al_draw_bitmap(dimebaghappybmp, 700, HEIGHT - (al_get_bitmap_height(dimebaghappybmp) + 25), 0);
                                al_draw_scaled_bitmap(dimebagdialoghappybmp, 0, 0, al_get_bitmap_width(dimebagdialoghappybmp), 
                                                      al_get_bitmap_height(dimebagdialoghappybmp), 575, HEIGHT / 2 - 50, 
                                                      al_get_bitmap_width(dimebagdialoghappybmp) / 3, 
                                                      al_get_bitmap_height(dimebagdialoghappybmp) / 3, 0);
                                al_draw_scaled_bitmap(uridialoghappybmp, 0, 0, al_get_bitmap_width(uridialoghappybmp), 
                                                      al_get_bitmap_height(uridialoghappybmp), 200, HEIGHT / 2 - 120, 
                                                      al_get_bitmap_width(uridialoghappybmp) / 2, 
                                                      al_get_bitmap_height(uridialoghappybmp) / 2, 0);
                            }
                            
                            // Otherwise, un-happy bitmaps are displayed:
                            else {
                                al_draw_bitmap(uripissedbmp, 40, HEIGHT / 2 - 100, 0);
                                al_draw_bitmap(dimebagpissedbmp, 700, HEIGHT - (al_get_bitmap_height(dimebagpissedbmp) + 25), 0);
                                al_draw_scaled_bitmap(dimebagdialogpissedbmp, 0, 0, al_get_bitmap_width(dimebagdialogpissedbmp), 
                                                      al_get_bitmap_height(dimebagdialogpissedbmp), 575, HEIGHT / 2 - 50, 
                                                      al_get_bitmap_width(dimebagdialogpissedbmp) / 3, 
                                                      al_get_bitmap_height(dimebagdialogpissedbmp) / 3, 0);
                                al_draw_scaled_bitmap(uridialogpissedbmp, 0, 0, al_get_bitmap_width(uridialogpissedbmp), 
                                                      al_get_bitmap_height(uridialogpissedbmp), 200, HEIGHT / 2 - 120, 
                                                      al_get_bitmap_width(uridialogpissedbmp) / 2, 
                                                      al_get_bitmap_height(uridialogpissedbmp) / 2, 0);
                            }
                            
                            // Cash total is displayed underneath:
                            al_draw_textf(fontScore, al_map_rgb(34,139,34), WIDTH / 2, 40 + al_get_font_line_height(fontHeader) + 
                                          al_get_font_line_height(fontMain) + al_get_font_line_height(fontScore), 
                                          ALLEGRO_ALIGN_CENTRE, "Total Cash: $ %d", jazzScore + rockScore + hiphopScore + reggaeScore);
                            break;
                    }
                    
                    // Flips the backbuffer with drawn elements to the front again:
                    al_flip_display();
                }
            }     
        }
    } // End MAIN GAME while loop
        
    // Stops the samples:
    al_stop_sample_instance(hiphop1inst);
    al_stop_sample_instance(hiphop2inst);
    al_stop_sample_instance(hiphop3inst);
    al_stop_sample_instance(hiphop4inst);
    al_stop_sample_instance(rock1inst);
    al_stop_sample_instance(rock2inst);
    al_stop_sample_instance(rock3inst);
    al_stop_sample_instance(rock4inst);
    al_stop_sample_instance(jazz1inst);
    al_stop_sample_instance(jazz2inst);
    al_stop_sample_instance(jazz3inst);
    al_stop_sample_instance(jazz4inst);
    al_stop_sample_instance(reggae1inst);
    al_stop_sample_instance(reggae2inst);
    al_stop_sample_instance(reggae3inst);
    al_stop_sample_instance(reggae4inst);
    
    // Begin the destruction of all memory allocated!
    al_destroy_bitmap(uridialoghappybmp);
    al_destroy_bitmap(uridialogpissedbmp);
    al_destroy_bitmap(pdiddydialogbmp);
    al_destroy_bitmap(pdiddydialoghappybmp);
    al_destroy_bitmap(pdiddydialogpissedbmp);
    al_destroy_bitmap(kennygdialogbmp);
    al_destroy_bitmap(kennygdialoghappybmp);
    al_destroy_bitmap(kennygdialogpissedbmp);
    al_destroy_bitmap(kingtubbydialogbmp);
    al_destroy_bitmap(kingtubbydialoghappybmp);
    al_destroy_bitmap(kingtubbydialogpissedbmp);
    al_destroy_bitmap(dimebagdialogbmp);
    al_destroy_bitmap(dimebagdialoghappybmp);
    al_destroy_bitmap(dimebagdialogpissedbmp);
    
    // Destroy the uri dialog win png:
    al_destroy_bitmap(uridialogwinbmp);
    
    // Destroys the buttons:
    al_destroy_bitmap(buttonbmp);
    al_destroy_bitmap(faderbmp);
    al_destroy_bitmap(mixerbmp);
    al_destroy_bitmap(mixerborderbmp);
    al_destroy_bitmap(mixbuttonbmp);
    
    // Destroys the tryagain and quit png's:
    al_destroy_bitmap(tryagainbuttonbmp);
    al_destroy_bitmap(quitbuttonbmp);
    
    // Destroys the win bitmaps:
    al_destroy_bitmap(pdiddywinbmp);
    al_destroy_bitmap(dimebagwinbmp);
    al_destroy_bitmap(kingtubbywinbmp);
    al_destroy_bitmap(kennygwinbmp);
    al_destroy_bitmap(uriwinbmp);
    
    // Destroys the character bitmaps:    
    al_destroy_bitmap(urimenubmp);
    al_destroy_bitmap(urihappybmp);
    al_destroy_bitmap(uripissedbmp);
    al_destroy_bitmap(urigameoverbmp);
    al_destroy_bitmap(kingtubbybmp);
    al_destroy_bitmap(kingtubbyhappybmp);
    al_destroy_bitmap(kingtubbypissedbmp);
    al_destroy_bitmap(kennygbmp);
    al_destroy_bitmap(kennyghappybmp);
    al_destroy_bitmap(kennygpissedbmp);
    al_destroy_bitmap(pdiddybmp);
    al_destroy_bitmap(pdiddyhappybmp);
    al_destroy_bitmap(pdiddypissedbmp);
    al_destroy_bitmap(dimebagbmp);
    al_destroy_bitmap(dimebaghappybmp);
    al_destroy_bitmap(dimebagpissedbmp);
    
    // Destroys the money bitmap and eviction bitmap
    al_destroy_bitmap(moneybmp);
    al_destroy_bitmap(evictionbmp);
    
    // Destroys the event queue
    al_destroy_event_queue(event_queue);
    
    // Destroys the samples and their instances
    al_destroy_sample_instance(hiphop1inst);
    al_destroy_sample(hiphop1);
    al_destroy_sample_instance(hiphop2inst);
    al_destroy_sample(hiphop2);
    al_destroy_sample_instance(hiphop3inst);
    al_destroy_sample(hiphop3);
    al_destroy_sample_instance(hiphop4inst);
    al_destroy_sample(hiphop4);
    al_destroy_sample_instance(rock1inst);
    al_destroy_sample(rock1);
    al_destroy_sample_instance(rock2inst);
    al_destroy_sample(rock2);
    al_destroy_sample_instance(rock3inst);
    al_destroy_sample(rock3);
    al_destroy_sample_instance(rock4inst);
    al_destroy_sample(rock4);
    al_destroy_sample_instance(jazz1inst);
    al_destroy_sample(jazz1);
    al_destroy_sample_instance(jazz2inst);
    al_destroy_sample(jazz2);
    al_destroy_sample_instance(jazz3inst);
    al_destroy_sample(jazz3);
    al_destroy_sample_instance(jazz4inst);
    al_destroy_sample(jazz4);
    al_destroy_sample_instance(reggae1inst);
    al_destroy_sample(reggae1);
    al_destroy_sample_instance(reggae2inst);
    al_destroy_sample(reggae2);
    al_destroy_sample_instance(reggae3inst);
    al_destroy_sample(reggae3);
    al_destroy_sample_instance(reggae4inst);
    al_destroy_sample(reggae4);
    
    // Destroys our fonts, timer and display
    al_destroy_font(fontMain);
    al_destroy_font(fontHeader);
    al_destroy_font(fontScore);
    al_destroy_font(fontThanks);
    al_destroy_timer(timer);
    al_destroy_display(display);

	return 0;
}

// Initializes each graphical item used for the main game loop:
void InitFader(Fader *fader, ALLEGRO_BITMAP *faderbmp) {
    fader->x = 0;
    fader->y = 0;
    fader->vol = 0;
    fader->isClicked = false;
    fader->isMoved = false;
    fader->faderbmp = faderbmp;
    fader->width = al_get_bitmap_width(faderbmp);
    fader->height = al_get_bitmap_height(faderbmp);
}

// Initializes the Mixer members:
void InitMixer(Mixer *mixer, ALLEGRO_BITMAP *mixerbmp) {
    mixer->x = 0;
    mixer->y = 0;
    mixer->mixerbmp = mixerbmp;
    mixer->width = al_get_bitmap_width(mixerbmp);
    mixer->height = al_get_bitmap_height(mixerbmp);
}

// Initializes the buttons:
void InitButtons(Button *button, ALLEGRO_BITMAP *buttonbmp) {
    button->x = 0;
    button->y = 0;
    button->isClicked = false;
    button->buttonbmp = buttonbmp;
    button->width = al_get_bitmap_width(buttonbmp);
    button->height = al_get_bitmap_height(buttonbmp);
}

// Initializes the mix button
void InitMixButton(MixButton *mixbutton, ALLEGRO_BITMAP *mixbuttonbmp) {
    mixbutton->x = 0;
    mixbutton->y = 0;
    mixbutton->width = al_get_bitmap_width(mixbuttonbmp);
    mixbutton->height = al_get_bitmap_width(mixbuttonbmp);
    mixbutton->isMixed = false;
}

// Sets the Mixer to the correct position on the screen:
void SetMixer(Mixer *mixer) {
    mixer->x = WIDTH / 2 - mixer->width / 2;
    mixer->y = HEIGHT / 2 - mixer->height / 2;
}

// Sets the Fader One to the correct position on the screen:
void SetFaderOne(Fader *faderOne, Mixer *mixer) {
    faderOne->x = WIDTH / 2 - 240;
    faderOne->y = HEIGHT / 2 + 50;
    faderOne->vol = 0.5;
}

// Sets the Fader Two to the correct position on the screen:
void SetFaderTwo(Fader *faderTwo, Mixer *mixer) {
    faderTwo->x = WIDTH / 2 - 127;
    faderTwo->y = HEIGHT / 2 + 50;
    faderTwo->vol = 0.5;
}

// Sets the Fader Three to the correct position on the screen:
void SetFaderThree(Fader *faderThree, Mixer *mixer) {
    faderThree->x = WIDTH / 2 + 95;
    faderThree->y = HEIGHT / 2 + 50;
    faderThree->vol = 0.5;
}

// Sets the Fader Four to the correct position on the screen:
void SetFaderFour(Fader *faderFour, Mixer *mixer) {
    faderFour->x = WIDTH / 2 + 199;
    faderFour->y = HEIGHT / 2 + 50;
    faderFour->vol = 0.5;
}

// Sets the Mix button to the correct position on the screen:
void SetMixButton(MixButton *mixbutton) {
    mixbutton->x = WIDTH / 2 - mixbutton->width / 2 - 10;
    mixbutton->y = HEIGHT / 2 + 130;
}

// Sets all the buttons to the correct position on the screen:
void SetButtonOne(Button *buttonOne, Mixer *mixer) {
    buttonOne->x = WIDTH / 2 - mixer->width / 2 + 10;
    buttonOne->y = HEIGHT / 2 - mixer->height / 2 + 10;
}
void SetButtonTwo(Button *buttonTwo, Mixer *mixer) {
    buttonTwo->x = WIDTH / 2 - mixer->width / 2 + 60;
    buttonTwo->y = HEIGHT / 2 - mixer->height / 2 + 10;
}
void SetButtonThree(Button *buttonThree, Mixer *mixer) {
    buttonThree->x = WIDTH / 2 - mixer->width / 2 + 10;
    buttonThree->y = HEIGHT / 2 - mixer->height / 2 + 60;
}
void SetButtonFour(Button *buttonFour, Mixer *mixer) {
    buttonFour->x = WIDTH / 2 - mixer->width / 2 + 60;
    buttonFour->y = HEIGHT / 2 - mixer->height / 2 + 60;
}
void SetButtonFive(Button *buttonFive, Mixer *mixer) {
    buttonFive->x = WIDTH / 2 - mixer->width / 2 + 120;
    buttonFive->y = HEIGHT / 2 - mixer->height / 2 + 10;
}
void SetButtonSix(Button *buttonSix, Mixer *mixer) {
    buttonSix->x = WIDTH / 2 - mixer->width / 2 + 170;
    buttonSix->y = HEIGHT / 2 - mixer->height / 2 + 10;
}
void SetButtonSeven(Button *buttonSeven, Mixer *mixer) {
    buttonSeven->x = WIDTH / 2 - mixer->width / 2 + 120;
    buttonSeven->y = HEIGHT / 2 - mixer->height / 2 + 60;
}
void SetButtonEight(Button *buttonEight, Mixer *mixer) {
    buttonEight->x = WIDTH / 2 - mixer->width / 2 + 170;
    buttonEight->y = HEIGHT/ 2 - mixer->height / 2 + 60;
}
void SetButtonNine(Button *buttonNine, Mixer *mixer) {
    buttonNine->x = WIDTH / 2 + 55;
    buttonNine->y = HEIGHT / 2 - mixer->height / 2 + 10;
}
void SetButtonTen(Button *buttonTen, Mixer *mixer) {
    buttonTen->x = WIDTH / 2 + 105;
    buttonTen->y = HEIGHT / 2 - mixer->height / 2 + 10;
}
void SetButtonEleven(Button *buttonEleven, Mixer *mixer) {
    buttonEleven->x = WIDTH / 2 + 55;
    buttonEleven->y = HEIGHT / 2 - mixer->height / 2 + 60;
}
void SetButtonTwelve(Button *buttonTwelve, Mixer *mixer) {
    buttonTwelve->x = WIDTH / 2 + 105;
    buttonTwelve->y = HEIGHT / 2 - mixer->height / 2 + 60;
}
void SetButtonThirteen(Button *buttonThirteen, Mixer *mixer) {
    buttonThirteen->x = WIDTH / 2 + 165;
    buttonThirteen->y = HEIGHT / 2 - mixer->height / 2 + 10;
}
void SetButtonFourteen(Button *buttonFourteen, Mixer *mixer) {
    buttonFourteen->x = WIDTH / 2 + 215;
    buttonFourteen->y = HEIGHT / 2 - mixer->height / 2 + 10;
}
void SetButtonFifteen(Button *buttonFifteen, Mixer *mixer) {
    buttonFifteen->x = WIDTH / 2 + 165;
    buttonFifteen->y = HEIGHT / 2 - mixer->height / 2 + 60;
}
void SetButtonSixteen(Button *buttonSixteen, Mixer *mixer) {
    buttonSixteen->x = WIDTH / 2 + 215;
    buttonSixteen->y = HEIGHT / 2 - mixer->height / 2 + 60;
}

// Functions to update the faders when the user moves them:
void UpdateFaderOne(Fader *faderOne, Mixer *mixer, ALLEGRO_EVENT *ev, ALLEGRO_BITMAP *faderbmp) {
    
    faderOne->y = ev->mouse.y;
    faderOne->isMoved = true;
    al_draw_bitmap(faderbmp, faderOne->x, faderOne->y, 0);
}
void UpdateFaderTwo(Fader *faderTwo, Mixer *mixer, ALLEGRO_EVENT *ev, ALLEGRO_BITMAP *faderbmp) {
    
    faderTwo->y = ev->mouse.y;
    faderTwo->isMoved = true;
    al_draw_bitmap(faderbmp, faderTwo->x, faderTwo->y, 0);
}
void UpdateFaderThree(Fader *faderThree, Mixer *mixer, ALLEGRO_EVENT *ev, ALLEGRO_BITMAP *faderbmp) {
    
    faderThree->y = ev->mouse.y;
    faderThree->isMoved = true;
    al_draw_bitmap(faderbmp, faderThree->x, faderThree->y, 0);
}
void UpdateFaderFour(Fader *faderFour, Mixer *mixer, ALLEGRO_EVENT *ev, ALLEGRO_BITMAP *faderbmp) {
    
    faderFour->y = ev->mouse.y;
    faderFour->isMoved = true;
    al_draw_bitmap(faderbmp, faderFour->x, faderFour->y, 0);
}