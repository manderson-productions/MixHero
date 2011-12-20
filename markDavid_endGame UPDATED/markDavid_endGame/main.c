//
//  main.c
//  markDavid_endGame
//
//  Created by Mark Anderson on 12/11/11.
//  Copyright 2011 markmakingmusic. All rights reserved.
//

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "mainStuff.h"
#include <math.h>

//GLOBAL VARIABLES
bool isRoundOver = false;
bool isStartMenu = true;
bool isEndOfMonth = false;
bool isAboutScreen = false;

//bool flags for each character
bool isKennyG = false;
bool isPDiddy = false;
bool isKingTubby = false;
bool isDimebagDarrell = false;

//this flag is needed to know when to draw the backbuffer to the front
bool redraw = false;
//float used for Frames per Second
const float FPS = 60.0;

//defines our game screen width and height
#define WIDTH 950
#define HEIGHT 800

//Function Prototypes:
void InitFader(Fader *fader, ALLEGRO_BITMAP *faderbmp);
void InitMixer(Mixer *mixer, ALLEGRO_BITMAP *mixerbmp);
void InitButtons(Button *button, ALLEGRO_BITMAP *buttonbmp);
void InitMixButton(MixButton *mixbutton, ALLEGRO_BITMAP *mixbuttonbmp);

void SetFaderOne(Fader *faderOne, Mixer *mixer);
void SetFaderTwo(Fader *faderTwo, Mixer *mixer);
void SetFaderThree(Fader *faderThree, Mixer *mixer);
void SetFaderFour(Fader *faderFour, Mixer *mixer);
void SetMixer(Mixer *mixer);
void SetButtonOne(Button *buttonOne, Mixer *mixer);
void SetButtonTwo(Button *buttonTwo, Mixer *mixer);
void SetButtonThree(Button *buttonThree, Mixer *mixer);
void SetButtonFour(Button *buttonFour, Mixer *mixer);
void SetButtonFive(Button *buttonFive, Mixer *mixer);
void SetButtonSix(Button *buttonSix, Mixer *mixer);
void SetButtonSeven(Button *buttonSeven, Mixer *mixer);
void SetButtonEight(Button *buttonEight, Mixer *mixer);
void SetButtonNine(Button *buttonNine, Mixer *mixer);
void SetButtonTen(Button *buttonTen, Mixer *mixer);
void SetButtonEleven(Button *buttonEleven, Mixer *mixer);
void SetButtonTwelve(Button *buttonTwelve, Mixer *mixer);
void SetButtonThirteen(Button *buttonThirteen, Mixer *mixer);
void SetButtonFourteen(Button *buttonFourteen, Mixer *mixer);
void SetButtonFifteen(Button *buttonFifteen, Mixer *mixer);
void SetButtonSixteen(Button *buttonSixteen, Mixer *mixer);
void SetMixButton(MixButton *mixbutton);

void UpdateFaderOne(Fader *faderOne, Mixer *mixer, ALLEGRO_EVENT *ev, ALLEGRO_BITMAP *faderbmp);
void UpdateFaderTwo(Fader *faderTwo, Mixer *mixer, ALLEGRO_EVENT *ev, ALLEGRO_BITMAP *faderbmp);
void UpdateFaderThree(Fader *faderThree, Mixer *mixer, ALLEGRO_EVENT *ev, ALLEGRO_BITMAP *faderbmp);
void UpdateFaderFour(Fader *faderFour, Mixer *mixer, ALLEGRO_EVENT *ev, ALLEGRO_BITMAP *faderbmp);

//Main function
int main (int argc, char **argv)
{
	//PRIMITIVE VARIABLES
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
    
    //used for round counter:
    int i = 1;
    
    //Allegro variables
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    
    //timer variable set up:
    ALLEGRO_TIMER *timer = NULL;
    
    //font ttf bitmap instances
    ALLEGRO_FONT *fontHeader = NULL;
    ALLEGRO_FONT *fontMain = NULL;
    ALLEGRO_FONT *fontScore = NULL;
    
    //mixer, border, button, fader, and mixbutton bitmaps
    ALLEGRO_BITMAP *mixerbmp = NULL;
    ALLEGRO_BITMAP *mixerborderbmp = NULL;
    ALLEGRO_BITMAP *buttonbmp = NULL;
    ALLEGRO_BITMAP *faderbmp = NULL;
    ALLEGRO_BITMAP *mixbuttonbmp = NULL;
    ALLEGRO_BITMAP *logobmp = NULL;
    
    //character bitmaps
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
    30
    //dialog boxes bitmaps
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
    
    //win screen bitmaps
    ALLEGRO_BITMAP *kennygwinbmp = NULL;
    ALLEGRO_BITMAP *pdiddywinbmp = NULL;
    ALLEGRO_BITMAP *dimebagwinbmp = NULL;
    ALLEGRO_BITMAP *kingtubbywinbmp = NULL;
    ALLEGRO_BITMAP *tryagainbuttonbmp = NULL;
    ALLEGRO_BITMAP *quitbuttonbmp = NULL;
    ALLEGRO_BITMAP *uriwinbmp = NULL;
    53
    //ALLEGRO Samples
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
69
    //allegro sample instance instances
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
    85
    //error checking to make sure allegro starts correctly:
    if(!al_init()) {
        fprintf(stderr, "Failed to initialize Allegro!\n");
		return -1;
    }
    //creates a new display and checks to see if it loaded correctly:
    display = al_create_display(WIDTH, HEIGHT);
    if(!display) {
        fprintf(stderr, "Failed to create display!\n");
        return -1;
    }
    //this installs the mouse to allow the use of mouse events:
    if (!al_install_mouse()) {
        fprintf(stderr, "Failed to install the mouse!\n");
        return -1;
    }
    //this loads the image addon to allow the importing/ usage of bitmaps
    if (!al_init_image_addon()) {
        fprintf(stderr, "Failed to initialize the image addon!\n");
        return -1;
    }
    //initializes the font addon:::there is not a way of error checking this
    //as it is a void function...
    al_init_font_addon();
    
    //this loads the ttf addon to allow importing/ using custom ttf fonts
    if (!al_init_ttf_addon()) {
        fprintf(stderr, "Failed to initialize ttf addon!\n");
        return -1;
    }   
    //creates the audio addon and error checks to make sure it loads
    if (!al_install_audio()) {
        fprintf(stderr, "Failed to install the audio!\n");
        return -1;
    }
    //initialize the acodec allegro addon and error checks to make sure it loads
    if (!al_init_acodec_addon()) {
        fprintf(stderr, "Failed to initialize the audio codec addon!\n");
        return -1;
    }
    //Reserve samples:
    al_reserve_samples(16);
    
    //assigns our timer variable...will update 1 / 60 of a second
    timer = al_create_timer(1.0 / FPS);
    if (!timer) {
        fprintf(stderr, "failed to create timer!\n");
        return -1;
    }
    //dialog boxes bitmaps
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
    
    //dialog winning boxes
    uridialogwinbmp = al_load_bitmap("uri2new.png");
    uriwinbmp = al_load_bitmap("uriwinbmp.png");
    kennygwinbmp = al_load_bitmap("jazzwinbmp.png");
    pdiddywinbmp = al_load_bitmap("hiphopwinbmp.png");
    dimebagwinbmp = al_load_bitmap("rockwinbmp.png");
    kingtubbywinbmp = al_load_bitmap("reggaewinbmp.png");
    
    //loads bitmaps for the mixer, border, fader, button and mix button:
    mixerbmp = al_load_bitmap("mixernewbmp.png");
    mixerborderbmp = al_load_bitmap("mixerborder.png");
    faderbmp = al_load_bitmap("fader.png");
    buttonbmp = al_load_bitmap("buttonone.png");
    mixbuttonbmp = al_load_bitmap("mixbutton.png");
    logobmp = al_load_bitmap("logobmp.png");
    
    //restart / quit button bitmaps
    tryagainbuttonbmp = al_load_bitmap("tryagainbutton.png");
    quitbuttonbmp = al_load_bitmap("quitbutton.png");
    
    //load bitmaps for all the characters and money:
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
    
    //Load all the fonts:
    fontHeader = al_load_font("Comic Sans MS Bold.ttf", 50, 0);
    fontMain = al_load_font("Arial.ttf", 18, 0);
    fontScore = al_load_font("EuphemiaCASRegular.ttf", 25, 0);
    
    //Create new Event Queue instance:
    event_queue = al_create_event_queue();
    
    //loads all the samples into memory
    hiphop1 = al_load_sample("hiphop1.wav");
    hiphop2 = al_load_sample("hiphop2.wav");
    hiphop3 = al_load_sample("hiphop3.wav");
    hiphop4 = al_load_sample("hiphop4.wav");
    rock1 = al_load_sample("rock1.wav");
    rock2 = al_load_sample("rock2.wav");
    rock3 = al_load_sample("rock3.wav");
    rock4 = al_load_sample("rock4.wav");
    jazz1 = al_load_sample("jazz1.wav");
    jazz2 = al_load_sample("jazz2.wav");
    jazz3 = al_load_sample("jazz3.wav");
    jazz4 = al_load_sample("jazz4.wav");
    reggae1 = al_load_sample("reggae1.wav");
    reggae2 = al_load_sample("reggae2.wav");
    reggae3 = al_load_sample("reggae3.wav");
    reggae4 = al_load_sample("reggae4.wav");
    //other1 = al_load_sample("");
    
    //creates sample instances for all the tracks:
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
    //other1inst = al_create_sample_instance(other1);
    
    // Set sample playback mode to LOOP
    //------------------------------------------------------------------
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
    //------------------------------------------------------------------
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
    //al_attach_sample_instance_to_mixer(other1inst, al_get_default_mixer());
    
    //SET SAMPLE GAINS...
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
    //al_set_sample_instance_gain(other1inst, 0.75);
    
    //creates new instances of the mixer and the faders
    Mixer mixer;
    Fader faderOne;
    Fader faderTwo;
    Fader faderThree;
    Fader faderFour;
    
    //creates new instances of all buttons and the mix button
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
    
    //initializes the mixer and faders
    InitMixer(&mixer, mixerbmp);
    InitFader(&faderOne, faderbmp);
    InitFader(&faderTwo, faderbmp);
    InitFader(&faderThree, faderbmp);
    InitFader(&faderFour, faderbmp);
    
    //Initialize the buttons
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
    
    //and Sets stuff in the correct place on screen
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
    
    //begins playback for all the samples
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
    
    //clears the screen to black before we start the game
    al_clear_to_color(al_map_rgb(0,0,0));
    //sets our backbuffer as the target
    al_set_target_bitmap(al_get_backbuffer(display));
    
    //register event sources for our event queue (basically just listening for input
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    
    //clears the screen again and flips the backbuffer (display) to the front
    al_clear_to_color(al_map_rgb(0,0,0));
    al_flip_display();
    //starts the timer:
    al_start_timer(timer);
    
    //This is the start of the main game loop
	while (!done) {
        
        //FIRST WE BEGIN ON WITH THE START MENU
        while (isStartMenu && !done) {
            
            //WE ALWAYS BEGIN BY WAITING FOR ANY EVENTS TO OCCUR THAT WE REGISTERED ABOVE:
            ALLEGRO_EVENT ev;
            al_wait_for_event (event_queue, &ev);

            //This event tells us that we will redraw the screen based on our timer update
            //of 1 /60 of a second. 
            if (ev.type == ALLEGRO_EVENT_TIMER) {
                redraw = true;
            }
            //This always exits the game if we click the 'close box'
            else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) 
            {
                done = true;
            }
            //This listens for any mouse button 'up' clicks.
            else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
                //if the mouse coordinates are within the range of the
                //logo on the lower right of the screen, we will enter the
                //'About Screen' loop. Mouse button & 1 is a bitwise
                //representing the left mouse button
                if (ev.mouse.x > 872 &&
                    ev.mouse.x < 927 &&
                    ev.mouse.y > 692 &&
                    ev.mouse.y < 777 &&
                    ev.mouse.button &1) {
                    
                    isAboutScreen = true;
                }
                
                //if we click anywhere besides the box above, we go to the main game screen
                else {
                    isStartMenu = false;
                }
            }
            //Start of the 'About Screen' loop
            while (isAboutScreen && !done) {
                
                //same event checking as above. Always do this at the beginning of
                //new while loop:
                ALLEGRO_EVENT ev;
                al_wait_for_event (event_queue, &ev);
                
                if (ev.type == ALLEGRO_EVENT_TIMER) {
                    redraw = true;
                }
                else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
                    done = true;
                }
                else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
                    isAboutScreen = false;
                }
                
                //this is our redraw material within the 'About Screen'. The front
                //buffer is cleared to black (0,0,0), new text and bitmaps are drawn
                //to the backbuffer and then at the end, the backbuffer is flipped to the 
                //front. This is all done at 1 / 60 of a second, the rate of our timer
                if (redraw && al_is_event_queue_empty(event_queue)) {
                    //redraw is set back to false because we only need to do this once every
                    //timer cycle
                    redraw = false;
                    
                    al_clear_to_color(al_map_rgb(0,0,0));
                    
                    //this is the Allegro equivalent of printf. It takes quite a few arguments,
                    //including color, font type (as declared above the main), position on screen,
                    //flags for text justification and finally, the actual text to be displayed.
                    al_draw_textf(fontHeader, al_map_rgb(255,0,255), WIDTH / 2, 100, 
                                  ALLEGRO_ALIGN_CENTRE, "STREET CREDS:");
                    al_draw_textf(fontScore, al_map_rgb(255,255,255), WIDTH / 2, 100 + 
                                  al_get_font_line_height(fontHeader), 
                                  ALLEGRO_ALIGN_CENTRE, "everything by Mark Anderson && David Forshee!!!");
                    
                    al_draw_textf(fontScore, al_map_rgb(255,255,255), WIDTH / 2 - 150, HEIGHT / 2, 
                                  0, "mixHero->    = ");
                    al_draw_textf(fontScore, al_map_rgb(34,139,34), WIDTH / 2 - 150, HEIGHT / 2, 
                                  0, "         plot");
                    al_draw_textf(fontScore, al_map_rgb(255,0,255), WIDTH / 2 - 150, HEIGHT / 2, 
                                  0, "              NULL");
                    
                    al_flip_display();
                }
            }
            //This is within our 'Start Menu' while loop: it does the same as before: resets the redraw flag,
            //clears the front buffer to black, draws whatever we want displayed on the screen onto the backbuffer,
            //and then flips the backbuffer to the front again.
            if (redraw && al_is_event_queue_empty(event_queue)) {
                redraw = false;
                
                al_clear_to_color(al_map_rgb(0,0,0));
                //this displays uri's main bitmap
                al_draw_bitmap(urimenubmp, 375, HEIGHT / 2 - al_get_font_line_height(fontHeader), 0);
                //this displays uri's main dialog box as a scaled image. 
                al_draw_scaled_bitmap(uridialogbmp, 0, 0, al_get_bitmap_width(uridialogbmp), 
                                      al_get_bitmap_height(uridialogbmp), WIDTH / 2 + 75, HEIGHT / 2 - 100, 
                                      al_get_bitmap_width(uridialogbmp) / 2, 
                                      al_get_bitmap_height(uridialogbmp) / 2, 0);
                //draws our M D logo onto the bottom right corner of the screen. 
                al_draw_bitmap(logobmp, WIDTH - (al_get_bitmap_width(logobmp) + 25), HEIGHT - (al_get_bitmap_height(logobmp) + 25), 0);
                
                //displays the header text on the screen
                al_draw_textf(fontHeader, al_map_rgb(255,0,255), WIDTH / 2, 100, 
                              ALLEGRO_ALIGN_CENTRE, "MIX HERO!!!");
                al_draw_textf(fontMain, al_map_rgb(255,0,255), WIDTH / 2, 100 + 
                              al_get_font_line_height(fontHeader), 
                              ALLEGRO_ALIGN_CENTRE, "(click to begin)");
                
                al_flip_display();
            }
        }
        //we won't use these bitmap anymore...
        al_destroy_bitmap(uridialogbmp);
        al_destroy_bitmap(logobmp);
        
        //this is the while loop where the main gameplay takes place.
        while (!isRoundOver && !done) {
            
            //Same event queue as before with an added "event mouse axes", which checks for mouse movement
            //on the screen (i.e. for fader updates)
            ALLEGRO_EVENT ev;
            al_wait_for_event (event_queue, &ev);
            
            if (ev.type == ALLEGRO_EVENT_TIMER) {
                redraw = true;
            }
            else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) 
            {
                done = true;
            }
            else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES) 
            {
                if (ev.mouse.x > WIDTH / 2 - 240 && 
                    ev.mouse.x < WIDTH / 2 - 240 + faderOne.width && 
                    ev.mouse.y > HEIGHT / 2 - 50 && 
                    ev.mouse.y < HEIGHT / 2 + 150 && 
                    ev.mouse.button & 1) {
                    
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
                    UpdateFaderOne(&faderOne, &mixer, &ev, faderbmp);
                }
                if (ev.mouse.x > WIDTH / 2 - 127 && 
                    ev.mouse.x < WIDTH / 2 - 127 + faderTwo.width && 
                    ev.mouse.y > HEIGHT / 2 - 50 && 
                    ev.mouse.y < HEIGHT / 2 + 150 && 
                    ev.mouse.button & 1) {
                    
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
                    UpdateFaderTwo(&faderTwo, &mixer, &ev, faderbmp);
                }
                if (ev.mouse.x > WIDTH / 2 + 95 && 
                    ev.mouse.x < WIDTH / 2 + 95 + faderThree.width && 
                    ev.mouse.y > HEIGHT / 2 - 50 && 
                    ev.mouse.y < HEIGHT / 2 + 150 && 
                    ev.mouse.button & 1) {
                    
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
                    UpdateFaderThree(&faderThree, &mixer, &ev, faderbmp);
                }
                
                if (ev.mouse.x > WIDTH / 2 + 199 && 
                    ev.mouse.x < WIDTH / 2 + 199 + faderFour.width && 
                    ev.mouse.y > HEIGHT / 2 - 50 && 
                    ev.mouse.y < HEIGHT / 2 + 150 && 
                    ev.mouse.button & 1) {
                    
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
                    UpdateFaderFour(&faderFour, &mixer, &ev, faderbmp);
                }
            } 
            //mouse button up event for when a click release is detected
            else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) 
            {
                if (ev.mouse.x > buttonOne.x &&
                    ev.mouse.x < buttonOne.x + buttonOne.width &&
                    ev.mouse.y > buttonOne.y &&
                    ev.mouse.y < buttonOne.y + buttonOne.height &&
                    ev.mouse.button & 1) {
                    
                    if (buttonOne.isClicked == false) {
                        buttonOne.isClicked = true;
                        buttonTwo.isClicked = false;
                        buttonThree.isClicked = false;
                        buttonFour.isClicked = false;
                    }
                    else 
                        buttonOne.isClicked = false;
                    
                    al_set_sample_instance_gain(hiphop1inst, (abs( (faderOne.y - 549) ) / (float) 198));
                }
                else if (ev.mouse.x > buttonTwo.x &&
                         ev.mouse.x < buttonTwo.x + buttonTwo.width &&
                         ev.mouse.y > buttonTwo.y &&
                         ev.mouse.y < buttonTwo.y + buttonTwo.height &&
                         ev.mouse.button & 1) {
                    
                    if (buttonTwo.isClicked == false) {
                        buttonOne.isClicked = false;
                        buttonTwo.isClicked = true;
                        buttonThree.isClicked = false;
                        buttonFour.isClicked = false;
                    }
                    else 
                        buttonTwo.isClicked = false;
                    
                    al_set_sample_instance_gain(rock1inst, (abs( (faderOne.y - 549) ) / (float) 198));                    
                }
                else if (ev.mouse.x > buttonThree.x &&
                         ev.mouse.x < buttonThree.x + buttonThree.width &&
                         ev.mouse.y > buttonThree.y &&
                         ev.mouse.y < buttonThree.y + buttonThree.height &&
                         ev.mouse.button & 1) {
                    
                    if (buttonThree.isClicked == false) {
                        buttonOne.isClicked = false;
                        buttonTwo.isClicked = false;
                        buttonThree.isClicked = true;
                        buttonFour.isClicked = false;
                    }
                    else
                        buttonThree.isClicked = false;

                    al_set_sample_instance_gain(jazz1inst, (abs( (faderOne.y - 549) ) / (float) 198));
                }
                else if (ev.mouse.x > buttonFour.x &&
                         ev.mouse.x < buttonFour.x + buttonFour.width &&
                         ev.mouse.y > buttonFour.y &&
                         ev.mouse.y < buttonFour.y + buttonFour.height &&
                         ev.mouse.button & 1) {
                    
                    if (buttonFour.isClicked == false) {
                        buttonOne.isClicked = false;
                        buttonTwo.isClicked = false;
                        buttonThree.isClicked = false;
                        buttonFour.isClicked = true;
                    }
                    else
                        buttonFour.isClicked = false;

                    al_set_sample_instance_gain(reggae1inst, (abs( (faderOne.y - 549) ) / (float) 198));
                }
                else if (ev.mouse.x > buttonFive.x &&
                         ev.mouse.x < buttonFive.x + buttonFive.width &&
                         ev.mouse.y > buttonFive.y &&
                         ev.mouse.y < buttonFive.y + buttonFive.height &&
                         ev.mouse.button & 1) {
                    
                    if (buttonFive.isClicked == false) {
                        buttonFive.isClicked = true;
                        buttonSix.isClicked = false;
                        buttonSeven.isClicked = false;
                        buttonEight.isClicked = false;
                    }
                    else
                        buttonFive.isClicked = false;
                    
                    al_set_sample_instance_gain(reggae2inst, (abs( (faderTwo.y - 549) ) / (float) 198));
                }
                else if (ev.mouse.x > buttonSix.x &&
                         ev.mouse.x < buttonSix.x + buttonSix.width &&
                         ev.mouse.y > buttonSix.y &&
                         ev.mouse.y < buttonSix.y + buttonSix.height &&
                         ev.mouse.button & 1) {
                    
                    if (buttonSix.isClicked == false) {
                        buttonFive.isClicked = false;
                        buttonSix.isClicked = true;
                        buttonSeven.isClicked = false;
                        buttonEight.isClicked = false;
                    }
                    else
                        buttonSix.isClicked = false;

                    al_set_sample_instance_gain(jazz2inst, (abs( (faderTwo.y - 549) ) / (float) 198));
                }
                else if (ev.mouse.x > buttonSeven.x &&
                         ev.mouse.x < buttonSeven.x + buttonSeven.width &&
                         ev.mouse.y > buttonSeven.y &&
                         ev.mouse.y < buttonSeven.y + buttonSeven.height &&
                         ev.mouse.button & 1) {
                    
                    if (buttonSeven.isClicked == false) {
                        buttonFive.isClicked = false;
                        buttonSix.isClicked = false;
                        buttonSeven.isClicked = true;
                        buttonEight.isClicked = false;
                    }
                    else
                        buttonSeven.isClicked = false;

                    al_set_sample_instance_gain(rock2inst, (abs( (faderTwo.y - 549) ) / (float) 198));
                }
                else if (ev.mouse.x > buttonEight.x &&
                         ev.mouse.x < buttonEight.x + buttonEight.width &&
                         ev.mouse.y > buttonEight.y &&
                         ev.mouse.y < buttonEight.y + buttonEight.height &&
                         ev.mouse.button & 1) {
                    
                    if (buttonEight.isClicked == false) {
                        buttonFive.isClicked = false;
                        buttonSix.isClicked = false;
                        buttonSeven.isClicked = false;
                        buttonEight.isClicked = true;
                    }
                    else
                        buttonEight.isClicked = false;

                    al_set_sample_instance_gain(hiphop2inst, (abs( (faderTwo.y - 549) ) / (float) 198));
                }
                else if (ev.mouse.x > buttonNine.x &&
                         ev.mouse.x < buttonNine.x + buttonNine.width &&
                         ev.mouse.y > buttonNine.y &&
                         ev.mouse.y < buttonNine.y + buttonNine.height &&
                         ev.mouse.button & 1) {
                    
                    if (buttonNine.isClicked == false) {
                        buttonNine.isClicked = true;
                        buttonTen.isClicked = false;
                        buttonEleven.isClicked = false;
                        buttonTwelve.isClicked = false;
                    }
                    else
                        buttonNine.isClicked = false;
                    
                    al_set_sample_instance_gain(rock3inst, (abs( (faderThree.y - 549) ) / (float) 198));
                }
                else if (ev.mouse.x > buttonTen.x &&
                         ev.mouse.x < buttonTen.x + buttonTen.width &&
                         ev.mouse.y > buttonTen.y &&
                         ev.mouse.y < buttonTen.y + buttonTen.height &&
                         ev.mouse.button & 1) {
                    
                    if (buttonTen.isClicked == false) {
                        buttonNine.isClicked = false;
                        buttonTen.isClicked = true;
                        buttonEleven.isClicked = false;
                        buttonTwelve.isClicked = false;
                    }
                    else
                        buttonTen.isClicked = false;

                    al_set_sample_instance_gain(hiphop3inst, (abs( (faderThree.y - 549) ) / (float) 198));
                    
                }
                else if (ev.mouse.x > buttonEleven.x &&
                         ev.mouse.x < buttonEleven.x + buttonEleven.width &&
                         ev.mouse.y > buttonEleven.y &&
                         ev.mouse.y < buttonEleven.y + buttonEleven.height &&
                         ev.mouse.button & 1) {
                    
                    if (buttonEleven.isClicked == false) {
                        buttonNine.isClicked = false;
                        buttonTen.isClicked = false;
                        buttonEleven.isClicked = true;
                        buttonTwelve.isClicked = false;
                    }
                    else
                        buttonEleven.isClicked = false;
                    
                    al_set_sample_instance_gain(reggae3inst, (abs( (faderThree.y - 549) ) / (float) 198));
                }
                else if (ev.mouse.x > buttonTwelve.x &&
                         ev.mouse.x < buttonTwelve.x + buttonTwelve.width &&
                         ev.mouse.y > buttonTwelve.y &&
                         ev.mouse.y < buttonTwelve.y + buttonTwelve.height &&
                         ev.mouse.button & 1) {
                    
                    if (buttonTwelve.isClicked == false) {
                        buttonNine.isClicked = false;
                        buttonTen.isClicked = false;
                        buttonEleven.isClicked = false;
                        buttonTwelve.isClicked = true;
                    }
                    else
                        buttonTwelve.isClicked = false;

                    al_set_sample_instance_gain(jazz3inst, (abs( (faderThree.y - 549) ) / (float) 198)); 
                }
                else if (ev.mouse.x > buttonThirteen.x &&
                         ev.mouse.x < buttonThirteen.x + buttonThirteen.width &&
                         ev.mouse.y > buttonThirteen.y &&
                         ev.mouse.y < buttonThirteen.y + buttonThirteen.height &&
                         ev.mouse.button & 1) {
                    
                    if (buttonThirteen.isClicked == false) {
                        buttonThirteen.isClicked = true;
                        buttonFourteen.isClicked = false;
                        buttonFifteen.isClicked = false;
                        buttonSixteen.isClicked = false;
                    }
                    else
                        buttonThirteen.isClicked = false;  
                    
                    al_set_sample_instance_gain(reggae4inst, (abs( (faderFour.y - 549) ) / (float) 198));
                }
                else if (ev.mouse.x > buttonFourteen.x &&
                         ev.mouse.x < buttonFourteen.x + buttonFourteen.width &&
                         ev.mouse.y > buttonFourteen.y &&
                         ev.mouse.y < buttonFourteen.y + buttonFourteen.height &&
                         ev.mouse.button & 1) {
                    
                    if (buttonFourteen.isClicked == false) {
                        buttonThirteen.isClicked = false;
                        buttonFourteen.isClicked = true;
                        buttonFifteen.isClicked = false;
                        buttonSixteen.isClicked = false;
                    }
                    else
                        buttonFourteen.isClicked = false;  

                    al_set_sample_instance_gain(jazz4inst, (abs( (faderFour.y - 549) ) / (float) 198));
                }
                else if (ev.mouse.x > buttonFifteen.x &&
                         ev.mouse.x < buttonFifteen.x + buttonFifteen.width &&
                         ev.mouse.y > buttonFifteen.y &&
                         ev.mouse.y < buttonFifteen.y + buttonFifteen.height &&
                         ev.mouse.button & 1) {
                    
                    if (buttonFifteen.isClicked == false) {
                        buttonThirteen.isClicked = false;
                        buttonFourteen.isClicked = false;
                        buttonFifteen.isClicked = true;
                        buttonSixteen.isClicked = false;
                    }
                    else
                        buttonFifteen.isClicked = false;   

                    al_set_sample_instance_gain(rock4inst, (abs( (faderFour.y - 549) ) / (float) 198));
                }
                else if (ev.mouse.x > buttonSixteen.x &&
                         ev.mouse.x < buttonSixteen.x + buttonSixteen.width &&
                         ev.mouse.y > buttonSixteen.y &&
                         ev.mouse.y < buttonSixteen.y + buttonSixteen.height &&
                         ev.mouse.button & 1) {
                    
                    if (buttonSixteen.isClicked == false) {
                        buttonThirteen.isClicked = false;
                        buttonFourteen.isClicked = false;
                        buttonFifteen.isClicked = false;
                        buttonSixteen.isClicked = true;
                    }
                    else
                        buttonSixteen.isClicked = false; 

                    al_set_sample_instance_gain(hiphop4inst, (abs( (faderFour.y - 549) ) / (float) 198));   
                }
                else if (ev.mouse.x > mixbutton.x &&
                         ev.mouse.x < mixbutton.x + mixbutton.width &&
                         ev.mouse.y > mixbutton.y &&
                         ev.mouse.y < mixbutton.y + mixbutton.height &&
                         ev.mouse.button & 1) {
                    
                    //this flag is set to true so that we enter the score screen when we click the
                    //mix button
                    isRoundOver = true;
                    
                    //the counter variable 'i' is checked before we enter the score screen so that
                    //we enter the correct calculations
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
            //this is our update for the 'Round Screen'...it redraws at the rate of our game timer. Same as before,
            //clear the screen to black, draw bitmaps/ text to the backbuffer, and then flip that to the front
            if (redraw && al_is_event_queue_empty(event_queue)) {
                redraw = false;
                
                al_clear_to_color(al_map_rgb(0,0,0));
                
                //this draws the Mixer first so that it will be on the back layer
                SetMixer(&mixer);
                //these bitmaps display the mixer, its border and uri:
                al_draw_bitmap(mixerbmp, mixer.x, mixer.y, 0);
                //redraws the faders based on game timer (FPS)
                al_draw_bitmap(faderbmp, faderOne.x, faderOne.y, 0);
                al_draw_bitmap(faderbmp, faderTwo.x, faderTwo.y, 0);
                al_draw_bitmap(faderbmp, faderThree.x, faderThree.y, 0);
                al_draw_bitmap(faderbmp, faderFour.x, faderFour.y, 0);
                //draws the mixer border and uri
                al_draw_bitmap(mixerborderbmp, mixer.x, mixer.y, 0); 
                al_draw_bitmap(urimenubmp, 20, HEIGHT / 2 - 100, 0);
                //this will display the total score on the screen
                al_draw_textf(fontScore, al_map_rgb(255,255,255), WIDTH / 2, 20, 
                              ALLEGRO_ALIGN_CENTRE, "Cash Money: ");

                //this adds space between the dollar sign so that it doesn't collide with the text as numbers get larger:
                if ((jazzScore + rockScore + hiphopScore + reggaeScore) == 0) {
                    al_draw_textf(fontScore, al_map_rgb(34,139,34), WIDTH / 2, 20, 
                                  ALLEGRO_ALIGN_CENTRE, "               $%d", 
                                  jazzScore + rockScore + hiphopScore + reggaeScore);
                }
                //simply shifts the score to the right so it looks nicer on the display
                else {
                    al_draw_textf(fontScore, al_map_rgb(34,139,34), WIDTH / 2, 20, 
                                  ALLEGRO_ALIGN_CENTRE, "                 $%d", 
                                  jazzScore + rockScore + hiphopScore + reggaeScore);
                }
                //these if statements will display each character based on which round it is:
                if (i == 1) {
                    al_draw_bitmap(kennygbmp, WIDTH - 250, 140, 0);
                    al_draw_scaled_bitmap(kennygdialogbmp, 0, 0, al_get_bitmap_width(kennygdialogbmp), 
                                          al_get_bitmap_height(kennygdialogbmp), WIDTH / 2 + 150, 100, 
                                          al_get_bitmap_width(kennygdialogbmp) / 4, 
                                          al_get_bitmap_height(kennygdialogbmp) / 4, 0);
                }
                if (i == 2) {
                    al_draw_bitmap(pdiddybmp, WIDTH - 200, HEIGHT - (al_get_bitmap_height(pdiddybmp) + 40), 0);
                    al_draw_scaled_bitmap(pdiddydialogbmp, 0, 0, al_get_bitmap_width(pdiddydialogbmp), 
                                          al_get_bitmap_height(pdiddydialogbmp), WIDTH / 2 + 230, 350, 
                                          al_get_bitmap_width(pdiddydialogbmp) / 4, 
                                          al_get_bitmap_height(pdiddydialogbmp) / 4, 0);
                }
                if (i == 3) {
                    al_draw_bitmap(kingtubbybmp, WIDTH - 250, 20, 0);
                    al_draw_scaled_bitmap(kingtubbydialogbmp, 0, 0, al_get_bitmap_width(kingtubbydialogbmp), 
                                          al_get_bitmap_height(kingtubbydialogbmp), WIDTH / 2 + 100, 75, 
                                          al_get_bitmap_width(kingtubbydialogbmp) / 4, 
                                          al_get_bitmap_height(kingtubbydialogbmp) / 4, 0);
                }
                if (i == 4) {
                    al_draw_bitmap(dimebagbmp, WIDTH - 250, HEIGHT - (al_get_bitmap_height(dimebagbmp) + 25), 0);
                    al_draw_scaled_bitmap(dimebagdialogbmp, 0, 0, al_get_bitmap_width(dimebagdialogbmp), 
                                          al_get_bitmap_height(dimebagdialogbmp), WIDTH / 2 + 230, 320, 
                                          al_get_bitmap_width(dimebagdialogbmp) / 4, 
                                          al_get_bitmap_height(dimebagdialogbmp) / 4, 0);
                }
                //these series of if statements will keep the fader in the 'middle position' while it has not been moved:
                if (!faderOne.isMoved) 
                {                
                    SetFaderOne(&faderOne, &mixer);
                    al_draw_bitmap(faderbmp, faderOne.x, faderOne.y, 0);
                }
                if (!faderTwo.isMoved)
                {
                    SetFaderTwo(&faderTwo, &mixer);
                    al_draw_bitmap(faderbmp, faderTwo.x, faderTwo.y, 0);
                }
                if (!faderThree.isMoved)
                {
                    SetFaderThree(&faderThree, &mixer);
                    al_draw_bitmap(faderbmp, faderThree.x, faderThree.y, 0);
                }
                if (!faderFour.isMoved)
                {
                    SetFaderFour(&faderFour, &mixer);
                    al_draw_bitmap(faderbmp, faderFour.x, faderFour.y, 0);
                }
                //If the buttons are clicked, they turn a different color. If it hasn't been clicked, it is drawn in place
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
                //if the mix button is NOT clicked, it will continue to be drawn to the backbuffer and the bitmap displayed,
                //if the mix button is clicked, the round is over and the Score screen is initiated.
                if (!mixbutton.isMixed) {
                    SetMixButton(&mixbutton);
                    al_draw_bitmap(mixbuttonbmp, mixbutton.x, mixbutton.y, 0);
                }
                else {
                    isRoundOver = true;
                }
                //finally the things drawn to our backbuffer are flipped to the front
                al_flip_display();
            }

            //this is the beginning of the score screen where the ratios and score will be calculated
            while (isRoundOver && !done) {
                
                ALLEGRO_EVENT ev;
                al_wait_for_event (event_queue, &ev);
                
                if (ev.type == ALLEGRO_EVENT_TIMER) {
                    redraw = true;
                }
                else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) 
                {
                    done = true;
                }
                else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
                    
                    //this occurs so that the score is only calculated once since we are in a while loop
                    isScoreCalculated = false;
                    
                    //and updates the counter
                    i++;
                    
                    //this updates the counter between rounds
                    if (i > 4 && ((jazzScore + rockScore + reggaeScore + hiphopScore) < 7000)) {
                        //then we know we are at the end of the month
                        isEndOfMonth = true;
                        
                        //and we enter the end of the month screen, based on the total score.
                        //the same events are listened for:
                        while (isEndOfMonth && !done) {
                            
                            ALLEGRO_EVENT ev;
                            al_wait_for_event (event_queue, &ev);
                            
                            if (ev.type == ALLEGRO_EVENT_TIMER) {
                                redraw = true;
                            }
                            else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
                                done = true;
                            }
                            else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
                                
                                //checks to see if we are in the range of the try again button:
                                if (ev.mouse.x > WIDTH / 2 - 50 &&
                                    ev.mouse.x < (WIDTH / 2 - 50 + (al_get_bitmap_width(mixbuttonbmp) * 2)) &&
                                    ev.mouse.y > 350 &&
                                    ev.mouse.y < (350 + (al_get_bitmap_height(mixbuttonbmp) * 2)) &&
                                    ev.mouse.button & 1) {
                                    
                                    //the game restarts by setting this flag to false. The counter 'i' gets set
                                    //back to one so the game starts over again:
                                    isEndOfMonth = false;
                                    i = 1;
                                    
                                    //initializes the scores back to zero:
                                    jazzScore = 0;
                                    rockScore = 0;
                                    reggaeScore = 0;
                                    hiphopScore = 0;
                                }
                                //checks to see if we are within the quit button, then if we click, it exits:
                                else if (ev.mouse.x > WIDTH / 2 - 50 &&
                                         ev.mouse.x < (WIDTH / 2 - 50 + (al_get_bitmap_width(mixbuttonbmp) * 2)) &&
                                         ev.mouse.y > (375 + (al_get_bitmap_height(mixbuttonbmp) * 2)) &&
                                         ev.mouse.y < (375 + (al_get_bitmap_height(mixbuttonbmp) * 4)) &&
                                         ev.mouse.button & 1) {
                                    
                                    //this means the game is over and we exit the main game loop
                                    done = true;
                                }
                            }
                            //and we redraw from within the end of the month screen based on our timer...same
                            //as before by clearing the screen to black, drawing things/ displaying text to the
                            //backbuffer, and then flipping the backbuffer to the front:
                            if (redraw && al_is_event_queue_empty(event_queue)) {
                                
                                al_clear_to_color(al_map_rgb(0,0,0));

                                //end of the month
                                al_draw_textf(fontHeader, al_map_rgb(255,0,255), WIDTH / 2, 20, 
                                              ALLEGRO_ALIGN_CENTRE, "ITS THAT TIME OF THE MONTH");
                                //total cash
                                al_draw_textf(fontScore, al_map_rgb(255,255,255), WIDTH / 2, 20 + al_get_font_line_height(fontHeader), 
                                              ALLEGRO_ALIGN_CENTRE, "Total Cash: ");
                                
                                //this if else prints the same thing but with different spacing based on what the score is
                                if ((jazzScore + rockScore + hiphopScore + reggaeScore) == 0) {
                                    al_draw_textf(fontScore, al_map_rgb(34,139,34), WIDTH / 2, 20 + al_get_font_line_height(fontHeader), 
                                                  ALLEGRO_ALIGN_CENTRE, "               $%d", 
                                                  jazzScore + rockScore + hiphopScore + reggaeScore);
                                }
                                //simply shifts the score to the right so it looks nicer on the display
                                else {
                                    al_draw_textf(fontScore, al_map_rgb(34,139,34), WIDTH / 2, 20 + al_get_font_line_height(fontHeader), 
                                                  ALLEGRO_ALIGN_CENTRE, "                 $%d", 
                                                  jazzScore + rockScore + hiphopScore + reggaeScore);
                                }
                                //rent and utilities
                                al_draw_textf(fontScore, al_map_rgb(255,255,255), WIDTH / 2, 20 + al_get_font_line_height(fontHeader) + 
                                              al_get_font_line_height(fontScore), ALLEGRO_ALIGN_CENTRE, "Rent and Utilities: $ 7,000");
                                
                                //cash left text
                                al_draw_textf(fontScore, al_map_rgb(255,255,255), WIDTH / 2, 20 + al_get_font_line_height(fontHeader) + 
                                              (al_get_font_line_height(fontScore) * 2), 
                                              ALLEGRO_ALIGN_CENTRE, "Cash Left: ");
                                
                                //simply shifts the score based on what the score is...if less than zero:
                                if ((jazzScore + rockScore + hiphopScore + reggaeScore) - 7000 < 0) {
                                    al_draw_textf(fontScore, al_map_rgb(255,0,0), WIDTH / 2, 20 + al_get_font_line_height(fontHeader) + 
                                                  (al_get_font_line_height(fontScore) * 2), 
                                                  ALLEGRO_ALIGN_CENTRE, "                 $%d", 
                                                  (jazzScore + rockScore + hiphopScore + reggaeScore) - 7000);
                                }
                                //if equal to zero:
                                else if ((jazzScore + rockScore + hiphopScore + reggaeScore) - 7000 == 0) {
                                    al_draw_textf(fontScore, al_map_rgb(255,0,0), WIDTH / 2, 20 + al_get_font_line_height(fontHeader) +
                                                  (al_get_font_line_height(fontScore) * 2), 
                                                  ALLEGRO_ALIGN_CENTRE, "               $%d", 
                                                  (jazzScore + rockScore + hiphopScore + reggaeScore) - 7000);
                                }
                                //and if greater than zero:
                                else {
                                    al_draw_textf(fontScore, al_map_rgb(34,139,34), WIDTH / 2, 20 + al_get_font_line_height(fontHeader) +
                                                  (al_get_font_line_height(fontScore) * 2), 
                                                  ALLEGRO_ALIGN_CENTRE, "                 $%d", 
                                                  (jazzScore + rockScore + hiphopScore + reggaeScore) - 7000);
                                }
                                //displays the uri game over bitmap:
                                al_draw_bitmap(urigameoverbmp, WIDTH / 2 - 400, HEIGHT / 2 - 200, 0);
                                al_draw_scaled_bitmap(uridialogwinbmp, 0, 0, al_get_bitmap_width(uridialogwinbmp), 
                                                      al_get_bitmap_height(uridialogwinbmp), 1, HEIGHT / 2 - 150, 
                                                      al_get_bitmap_width(uridialogwinbmp) / 3, 
                                                      al_get_bitmap_height(uridialogwinbmp) / 3, 0);
                                //displays the eviction notice bitmap:
                                al_draw_scaled_bitmap(evictionbmp, 0, 0, al_get_bitmap_width(evictionbmp), 
                                                      al_get_bitmap_height(evictionbmp), 675, HEIGHT / 2 - 50, 
                                                      al_get_bitmap_width(evictionbmp) / 3, 
                                                      al_get_bitmap_height(evictionbmp) / 3, 0);
                               al_draw_scaled_bitmap(tryagainbuttonbmp, 0, 0, al_get_bitmap_width(tryagainbuttonbmp), 
                                                      al_get_bitmap_height(tryagainbuttonbmp), WIDTH / 2 - 50, 350, 
                                                      al_get_bitmap_width(mixbuttonbmp) * 2, 
                                                      al_get_bitmap_height(mixbuttonbmp) * 2, 0);
                                
                                al_draw_scaled_bitmap(quitbuttonbmp, 0, 0, al_get_bitmap_width(quitbuttonbmp), 
                                                      al_get_bitmap_height(quitbuttonbmp), WIDTH / 2 - 50, 375 + (al_get_bitmap_height(mixbuttonbmp) * 2), 
                                                      al_get_bitmap_width(mixbuttonbmp) * 2, 
                                                      al_get_bitmap_height(mixbuttonbmp) * 2, 0);
                                al_flip_display();
                            }
                        }
                    }
                    //if the total score for 4 rounds is greater than 7000:
                    else if ((i > 4) && ((jazzScore + rockScore + reggaeScore + hiphopScore) > 7000)) {
                        
                        //then we know we are at the end of the month
                        isEndOfMonth = true;
                        
                        while (isEndOfMonth && !done) {
                            
                            ALLEGRO_EVENT ev;
                            al_wait_for_event (event_queue, &ev);
                            
                            if (ev.type == ALLEGRO_EVENT_TIMER) {
                                redraw = true;
                            }
                            else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
                                done = true;
                            }
                            if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
                                
                                //checks to see if we are in the range of the try again button:
                                if (ev.mouse.x > WIDTH / 2 - 50 &&
                                    ev.mouse.x < (WIDTH / 2 - 50 + (al_get_bitmap_width(mixbuttonbmp) * 2)) &&
                                    ev.mouse.y > 350 &&
                                    ev.mouse.y < (350 + (al_get_bitmap_height(mixbuttonbmp) * 2)) &&
                                    ev.mouse.button & 1) {
                                    
                                    //the game restarts by setting this flag to false. The counter 'i' gets set
                                    //back to one so the game starts over again:
                                    isEndOfMonth = false;
                                    i = 1;
                                    
                                    //initializes the scores back to zero:
                                    jazzScore = 0;
                                    rockScore = 0;
                                    reggaeScore = 0;
                                    hiphopScore = 0;
                                }
                                //checks to see if we are within the quit button, then if we click, it exits:
                                else if (ev.mouse.x > WIDTH / 2 - 50 &&
                                         ev.mouse.x < (WIDTH / 2 - 50 + (al_get_bitmap_width(mixbuttonbmp) * 2)) &&
                                         ev.mouse.y > (375 + (al_get_bitmap_height(mixbuttonbmp) * 2)) &&
                                         ev.mouse.y < (375 + (al_get_bitmap_height(mixbuttonbmp) * 4)) &&
                                         ev.mouse.button & 1) {
                                    
                                    //this means the game is over and we exit the main game loop
                                    done = true;
                                }
                            }
                            if (redraw && al_is_event_queue_empty(event_queue)) {
                                
                                al_clear_to_color(al_map_rgb(0,0,0));
                                
                                //end of the month
                                al_draw_textf(fontHeader, al_map_rgb(255,0,255), WIDTH / 2, 20, 
                                              ALLEGRO_ALIGN_CENTRE, "ITS THAT TIME OF THE MONTH");
                                //total cash
                                al_draw_textf(fontScore, al_map_rgb(255,255,255), WIDTH / 2, 20 + al_get_font_line_height(fontHeader), 
                                              ALLEGRO_ALIGN_CENTRE, "Total Cash: ");
                                
                                al_draw_textf(fontScore, al_map_rgb(34,139,34), WIDTH / 2, 20 + al_get_font_line_height(fontHeader), 
                                              ALLEGRO_ALIGN_CENTRE, "                 $%d", 
                                              jazzScore + rockScore + hiphopScore + reggaeScore);
                                //rent and utilities
                                al_draw_textf(fontScore, al_map_rgb(255,255,255), WIDTH / 2, 20 + al_get_font_line_height(fontHeader) + 
                                              al_get_font_line_height(fontScore), ALLEGRO_ALIGN_CENTRE, "Rent and Utilities: $ 7,000");
                                
                                al_draw_textf(fontScore, al_map_rgb(255,255,255), WIDTH / 2, 20 + al_get_font_line_height(fontHeader) + 
                                              (al_get_font_line_height(fontScore) * 2), 
                                              ALLEGRO_ALIGN_CENTRE, "Cash Left: ");
                                
                                al_draw_textf(fontScore, al_map_rgb(34,139,34), WIDTH / 2, 20 + al_get_font_line_height(fontHeader) +
                                              (al_get_font_line_height(fontScore) * 2), 
                                              ALLEGRO_ALIGN_CENTRE, "                 $%d", 
                                              (jazzScore + rockScore + hiphopScore + reggaeScore) - 7000);
                                
                                //al_draw_bitmap(uriwinbmp, WIDTH / 2 + 200, HEIGHT / 2 - 200, 0);
                                al_draw_bitmap(kennygwinbmp, 672, 244, 0);
                                al_draw_bitmap(dimebagwinbmp, 183, 364, 0);
                                al_draw_bitmap(kingtubbywinbmp, 25, 205, 0);
                                al_draw_bitmap(pdiddywinbmp, 578, 389, 0);
                                
                                al_draw_scaled_bitmap(tryagainbuttonbmp, 0, 0, al_get_bitmap_width(tryagainbuttonbmp), 
                                                      al_get_bitmap_height(tryagainbuttonbmp), WIDTH / 2 - 50, 350, 
                                                      al_get_bitmap_width(mixbuttonbmp) * 2, 
                                                      al_get_bitmap_height(mixbuttonbmp) * 2, 0);
                                al_draw_scaled_bitmap(quitbuttonbmp, 0, 0, al_get_bitmap_width(quitbuttonbmp), 
                                                      al_get_bitmap_height(quitbuttonbmp), WIDTH / 2 - 50, 375 + (al_get_bitmap_height(mixbuttonbmp) * 2), 
                                                      al_get_bitmap_width(mixbuttonbmp) * 2, 
                                                      al_get_bitmap_height(mixbuttonbmp) * 2, 0);
                                al_flip_display();
                            }
                        }
                    }
                    InitMixer(&mixer, mixerbmp);
                    InitFader(&faderOne, faderbmp);
                    InitFader(&faderTwo, faderbmp);
                    InitFader(&faderThree, faderbmp);
                    InitFader(&faderFour, faderbmp);
                    SetFaderOne(&faderOne, &mixer);
                    SetFaderTwo(&faderTwo, &mixer);
                    SetFaderThree(&faderThree, &mixer);
                    SetFaderFour(&faderFour,&mixer);
                    //buttons don't need to be re- Set, because they're not moving at all...
                    //they do however need to be reinitialized
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
                    
                    //the isRoundOver flag is set back to false and the rounds start over again
                    isRoundOver = false;
                }
                //and the redrawing for our 'isRoundOver screen: Same as before
                if (redraw && al_is_event_queue_empty(event_queue)) {
                    redraw = false;
                    
                    al_clear_to_color(al_map_rgb(0,0,0));
                    
                    al_draw_textf(fontHeader, al_map_rgb(255,0,255), WIDTH / 2, 20, 
                                  ALLEGRO_ALIGN_CENTRE, "ROUND %d OVER", i);
                    al_draw_textf(fontMain, al_map_rgb(255,0,255), WIDTH / 2, 20 + 
                                  al_get_font_line_height(fontHeader), 
                                  ALLEGRO_ALIGN_CENTRE, "(click to begin the next round)");
                    al_draw_bitmap(moneybmp, WIDTH / 2 - (al_get_bitmap_width(moneybmp) / 2), HEIGHT / 2 + 
                                   al_get_font_line_height(fontMain) , 0);
                    
                    //JAZZ GOES IN BUTTONS Three, Six, Twelve, AND Fourteen
                    if (isKennyG && !isScoreCalculated) { 
                        
                        // Initialize results to sentinel values
                        results1 = 100; 
                        results2 = 100; 
                        results3 = 100;
                        results_total = 0;
                        score = 0;
                        mixScore = 0;
                        
                        //otherwise, it will add a small amount for each correct button pressed:
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
                        if (buttonThree.isClicked && 
                            buttonSix.isClicked && 
                            buttonTwelve.isClicked && 
                            buttonFourteen.isClicked) {
                            //get a bonus score!
                            score += 50;
                        }
                        if (results1 == 100){
                            results1 = .26;
                        }
                        if (results2 == 100){
                            results1 = .26;
                        }
                        if (results3 == 100){
                            results1 = .26;
                        }
                        
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
                        
                        jazzScore = (score + mixScore) * 10;          
                        isScoreCalculated = true;
                        
                        //exit the loop      
                        isKennyG = false;
                        
                        //this will essentially mute the tracks as we go to the score screen.
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
                        //al_set_sample_instance_gain(other1inst, 0.75);
                    }
                    //ROCK GOES IN BUTTONS Two, seven, nine, fifteen
                    if (isDimebagDarrell && !isScoreCalculated) {   
                        
                        // Initialize results to sentinel values
                        results1 = 100; 
                        results2 = 100; 
                        results3 = 100;
                        results_total = 0;
                        score = 0;
                        mixScore = 0;
                        
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
                        if (buttonTwo.isClicked && 
                            buttonSeven.isClicked && 
                            buttonNine.isClicked && 
                            buttonFifteen.isClicked) {
                            //get a bonus score!
                            score += 50;
                        }
                        if (results1 == 100){
                            results1 = .26;
                        }
                        if (results2 == 100){
                            results1 = .26;
                        }
                        if (results3 == 100){
                            results1 = .26;
                        }
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
                        rockScore = (score + mixScore) * 10;          
                        isScoreCalculated = true;
                        isDimebagDarrell = false;
                        
                        //this will essentially mute the tracks as we go to the score screen.
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
                        //al_set_sample_instance_gain(other1inst, 0.75);
                    }
                    //RAP GOES IN BUTTONS one,eight, ten, sixteen
                    if (isPDiddy && !isScoreCalculated) {     
                        
                        // Initialize results to sentinel values
                        results1 = 100; 
                        results2 = 100; 
                        results3 = 100;
                        results_total = 0;
                        score = 0;
                        mixScore = 0;
                        
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
                        if (buttonOne.isClicked && 
                            buttonEight.isClicked && 
                            buttonTen.isClicked && 
                            buttonSixteen.isClicked) {
                            //get a bonus score!
                            score += 50;
                        }
                        if (results1 == 100){
                            results1 = .26;
                        }
                        if (results2 == 100){
                            results1 = .26;
                        }
                        if (results3 == 100){
                            results1 = .26;
                        }
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
                        hiphopScore = (score + mixScore) * 10;          
                        isScoreCalculated = true;                    
                        isPDiddy = false;
                        
                        //this will essentially mute the tracks as we go to the score screen.
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
                        //al_set_sample_instance_gain(other1inst, 0.75);
                    }
                    //REGGAE GOES IN BUTTONS four, five, eleven, thirteen
                    if (isKingTubby && !isScoreCalculated) {  
                        
                        // Initialize results to sentinel values
                        results1 = 100; 
                        results2 = 100; 
                        results3 = 100;
                        results_total = 0;
                        score = 0;
                        mixScore = 0;
                        
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
                        if (buttonFour.isClicked && 
                            buttonFive.isClicked && 
                            buttonEleven.isClicked && 
                            buttonThirteen.isClicked) {
                            //get a bonus score!
                            score += 50;
                        }
                        if (results1 == 100){
                            results1 = .26;
                        }
                        if (results2 == 100){
                            results1 = .26;
                        }
                        if (results3 == 100){
                            results1 = .26;
                        }
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
                        //al_set_sample_instance_gain(other1inst, 0.75);
                    }
                    
                    //switch statements that display the characters based on the score you get:
                    switch (i) {
                            
                        case 1:
                            al_draw_textf(fontScore, al_map_rgb(34,139,34), WIDTH / 2, 40 + 
                                          al_get_font_line_height(fontHeader) + al_get_font_line_height(fontMain), 
                                          ALLEGRO_ALIGN_CENTRE, "Cash for Mix %d: $ %d", i, jazzScore);
                            
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
                            al_draw_textf(fontScore, al_map_rgb(34,139,34), WIDTH / 2, 40 + 
                                          al_get_font_line_height(fontHeader) + al_get_font_line_height(fontMain) + 
                                          al_get_font_line_height(fontScore), 
                                          ALLEGRO_ALIGN_CENTRE, "Total Cash: $ %d", jazzScore + rockScore + hiphopScore + reggaeScore);
                            break;
                        case 2:
                            
                            al_draw_textf(fontScore, al_map_rgb(34,139,34), WIDTH / 2, 40 + al_get_font_line_height(fontHeader) + 
                                          al_get_font_line_height(fontMain), 
                                          ALLEGRO_ALIGN_CENTRE, "Cash for Mix %d: $ %d", i, hiphopScore);
                            
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
                            al_draw_textf(fontScore, al_map_rgb(34,139,34), WIDTH / 2, 40 + 
                                          al_get_font_line_height(fontHeader) + al_get_font_line_height(fontMain) + 
                                          al_get_font_line_height(fontScore), 
                                          ALLEGRO_ALIGN_CENTRE, "Total Cash: $ %d", jazzScore + rockScore + hiphopScore + reggaeScore);
                            break;
                        case 3:
                            
                            al_draw_textf(fontScore, al_map_rgb(34,139,34), WIDTH / 2, 40 + al_get_font_line_height(fontHeader) + 
                                          al_get_font_line_height(fontMain), ALLEGRO_ALIGN_CENTRE, "Cash for Mix %d: $ %d", i, reggaeScore);
                            
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
                            al_draw_textf(fontScore, al_map_rgb(34,139,34), WIDTH / 2, 40 + 
                                          al_get_font_line_height(fontHeader) + al_get_font_line_height(fontMain) + 
                                          al_get_font_line_height(fontScore), ALLEGRO_ALIGN_CENTRE, 
                                          "Total Cash: $ %d", jazzScore + rockScore + hiphopScore + reggaeScore);
                            break;
                        case 4:
                            
                            al_draw_textf(fontScore, al_map_rgb(34,139,34), WIDTH / 2, 40 + 
                                          al_get_font_line_height(fontHeader) + al_get_font_line_height(fontMain), 
                                          ALLEGRO_ALIGN_CENTRE, "Cash for Mix %d: $ %d", i, rockScore);
                            
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
                            al_draw_textf(fontScore, al_map_rgb(34,139,34), WIDTH / 2, 40 + al_get_font_line_height(fontHeader) + 
                                          al_get_font_line_height(fontMain) + al_get_font_line_height(fontScore), 
                                          ALLEGRO_ALIGN_CENTRE, "Total Cash: $ %d", jazzScore + rockScore + hiphopScore + reggaeScore);
                            break;
                    }
                    //and we flip the display back before we exit the score screen:
                    al_flip_display();
                }
            }     
        }
    } //end MAIN while loop
        87
    //stops the samples:
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
    0
    //begin the destruction of all memory allocated!
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
    //destroys the uri dialog win png:
    al_destroy_bitmap(uridialogwinbmp);
    15
    //destroys the buttons:
    al_destroy_bitmap(buttonbmp);
    al_destroy_bitmap(faderbmp);
    al_destroy_bitmap(mixerbmp);
    al_destroy_bitmap(mixerborderbmp);
    al_destroy_bitmap(mixbuttonbmp);
    
    20
    //destroys the tryagain and quit png's:
    al_destroy_bitmap(tryagainbuttonbmp);
    al_destroy_bitmap(quitbuttonbmp);
    22
    //destroys the win bitmaps:
    al_destroy_bitmap(pdiddywinbmp);
    al_destroy_bitmap(dimebagwinbmp);
    al_destroy_bitmap(kingtubbywinbmp);
    al_destroy_bitmap(kennygwinbmp);
    al_destroy_bitmap(uriwinbmp);
    //destroys the character bitmaps:    
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
    //destroys the money bitmap and eviction bitmap
    al_destroy_bitmap(moneybmp);
    al_destroy_bitmap(evictionbmp);
    45
    //destroys the event queue
    al_destroy_event_queue(event_queue);
    //destroys the samples and their instances
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
    
    //destroys our fonts, timer and display
    al_destroy_font(fontMain);
    al_destroy_font(fontHeader);
    //TO ADD:
    al_destroy_font(fontScore);
    
    al_destroy_timer(timer);
    al_destroy_display(display);
85
	return 0;
}

//Initializes each graphical item used for the main game loop:
void InitFader(Fader *fader, ALLEGRO_BITMAP *faderbmp) {
    fader->x = 0;
    fader->y = 0;
    fader->vol = 0;
    fader->isClicked = false;
    fader->isDragging = false;
    fader->isMoved = false;
    fader->faderbmp = faderbmp;
    fader->width = al_get_bitmap_width(faderbmp);
    fader->height = al_get_bitmap_height(faderbmp);
}
void InitMixer(Mixer *mixer, ALLEGRO_BITMAP *mixerbmp) {
    mixer->x = 0;
    mixer->y = 0;
    mixer->mixerbmp = mixerbmp;
    mixer->width = al_get_bitmap_width(mixerbmp);
    mixer->height = al_get_bitmap_height(mixerbmp);
}
void InitButtons(Button *button, ALLEGRO_BITMAP *buttonbmp) {
    button->x = 0;
    button->y = 0;
    button->isClicked = false;
    button->buttonbmp = buttonbmp;
    button->width = al_get_bitmap_width(buttonbmp);
    button->height = al_get_bitmap_height(buttonbmp);
}
void InitMixButton(MixButton *mixbutton, ALLEGRO_BITMAP *mixbuttonbmp) {
    mixbutton->x = 0;
    mixbutton->y = 0;
    mixbutton->width = al_get_bitmap_width(mixbuttonbmp);
    mixbutton->height = al_get_bitmap_width(mixbuttonbmp);
    mixbutton->isMixed = false;
}
//These SET functions place each graphical item onto the screen in the correct place.
void SetMixer(Mixer *mixer) {
    mixer->x = WIDTH / 2 - mixer->width / 2;
    mixer->y = HEIGHT / 2 - mixer->height / 2;
}
void SetFaderOne(Fader *faderOne, Mixer *mixer) {
    faderOne->x = WIDTH / 2 - 240;
    faderOne->y = HEIGHT / 2 + 50;
    faderOne->vol = 0.5;
}
void SetFaderTwo(Fader *faderTwo, Mixer *mixer) {
    faderTwo->x = WIDTH / 2 - 127;
    faderTwo->y = HEIGHT / 2 + 50;
    faderTwo->vol = 0.5;
}
void SetFaderThree(Fader *faderThree, Mixer *mixer) {
    faderThree->x = WIDTH / 2 + 95;
    faderThree->y = HEIGHT / 2 + 50;
    faderThree->vol = 0.5;
}
void SetFaderFour(Fader *faderFour, Mixer *mixer) {
    faderFour->x = WIDTH / 2 + 199;
    faderFour->y = HEIGHT / 2 + 50;
    faderFour->vol = 0.5;
}
//This sets the mix button in the correct spot on screen. 
void SetMixButton(MixButton *mixbutton) {
    mixbutton->x = WIDTH / 2 - mixbutton->width / 2 - 10;
    mixbutton->y = HEIGHT / 2 + 130;
}
//these functions place the buttons on the screen.
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
//These functions update the Faders.
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