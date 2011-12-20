//
//  sound.cpp
//  markDavid_endGame
//
//  Created by David Forshee on 12/12/11.
//  Copyright 2011 markmakingmusic. All rights reserved.
//

#include <allegro5\allegro.h>
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>
#include "sound.h"

// Declare sample pointers and sample instances
//------------------------------------------------------------------

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
ALLEGRO_SAMPLE *other1 = NULL;
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
ALLEGRO_SAMPLE_INSTANCE *other1inst = NULL;

al_install_audio();
al_init_acodec_addon();

// Reserve samples
al_reserve_samples(17);


void init_samples(){
    // Load Samples and create sample instances
    //------------------------------------------------------------------
    hiphop1 = al_load_sample("hiphop1.ogg");
    hiphop2 = al_load_sample("hiphop2.ogg");
    hiphop3 = al_load_sample("hiphop3.ogg");
    hiphop4 = al_load_sample("hiphop4.ogg");
    rock1 = al_load_sample("rock1.ogg");
    rock2 = al_load_sample("rock2.ogg");
    rock3 = al_load_sample("rock3.ogg");
    rock4 = al_load_sample("rock4.ogg");
    jazz1 = al_load_sample("jazz1.ogg");
    jazz2 = al_load_sample("jazz2.ogg");
    jazz3 = al_load_sample("jazz3.ogg");
    jazz4 = al_load_sample("jazz4.ogg");
    reggae1 = al_load_sample("reggae1.ogg");
    reggae2 = al_load_sample("reggae2.ogg");
    reggae3 = al_load_sample("reggae3.ogg");
    reggae4 = al_load_sample("reggae4.ogg");
    //other1 = al_load_sample("");
    
    
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
    al_attach_sample_instance_to_mixer(other1inst, al_get_default_mixer());
}


// Initalize gains for sample instances
//------------------------------------------------------------------

void init_gains(){
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
    al_set_sample_instance_gain(other1inst, 0.75);
}




// TO INSERT INTO FUNCTION: Initalize gain of clip when button is pressed
//-----------------------------------------------------------------------
    
// If hiphop1 button is on:
if (al_get_sample_instance_gain(hiphop1inst) > 0) {
    al_set_sample_instance_gain(hiphop1inst, (abs( (faderOne->y - 549) ) / (float) 198));
}

    al_set_sample_instance_gain(hiphop1inst, (abs( (faderOne->y - 549) ) / (float) 198));
    al_set_sample_instance_gain(hiphop2inst, 0);
    al_set_sample_instance_gain(hiphop3inst, 0);
    al_set_sample_instance_gain(hiphop4inst, 0);
    
    // While button is on 


// If hiphop2 button is pressed:
    al_set_sample_instance_gain(hiphop1inst, 0);
    al_set_sample_instance_gain(hiphop2inst, (abs( (faderOne->y - 549) ) / (float) 198));
    al_set_sample_instance_gain(hiphop3inst, 0);
    al_set_sample_instance_gain(hiphop4inst, 0);
    
    // While button is on 
if (al_get_sample_instance_gain(hiphop2inst) > 0) {
    al_set_sample_instance_gain(hiphop2inst, (abs( (faderOne->y - 549) ) / (float) 198));
}
// If hiphop3 button is pressed:
    al_set_sample_instance_gain(hiphop1inst, 0);
    al_set_sample_instance_gain(hiphop2inst, 0);
    al_set_sample_instance_gain(hiphop3inst, (abs( (faderOne->y - 549) ) / (float) 198));
    al_set_sample_instance_gain(hiphop4inst, 0);
    
    // While button is on
if (al_get_sample_instance_gain(hiphop3inst) > 0) {
    al_set_sample_instance_gain(hiphop3inst, (abs( (faderOne->y - 549) ) / (float) 198));
}

// If hiphop4 button is pressed:
    al_set_sample_instance_gain(hiphop1inst, 0);
    al_set_sample_instance_gain(hiphop2inst, 0);
    al_set_sample_instance_gain(hiphop3inst, 0);
    al_set_sample_instance_gain(hiphop4inst, (abs( (faderOne->y - 549) ) / (float) 198));

    // While button is on
if (al_get_sample_instance_gain(hiphop4inst) > 0) {
    al_set_sample_instance_gain(hiphop4inst, (abs( (faderOne->y - 549) ) / (float) 198));
}

// If rock1 button is pressed:
    al_set_sample_instance_gain(rock1inst, (abs( (faderTwo->y - 549) ) / (float) 198));
    al_set_sample_instance_gain(rock2inst, 0);
    al_set_sample_instance_gain(rock3inst, 0);
    al_set_sample_instance_gain(rock4inst, 0);

    // While button is on
    al_set_sample_instance_gain(rock1inst, (abs( (faderOne->y - 549) ) / (float) 198));

// If rock2 button is pressed:
    al_set_sample_instance_gain(rock1inst, 0);
    al_set_sample_instance_gain(rock2inst, (abs( (faderTwo->y - 549) ) / (float) 198));
    al_set_sample_instance_gain(rock3inst, 0);
    al_set_sample_instance_gain(rock4inst, 0);

    // While button is on
    al_set_sample_instance_gain(rock2inst, (abs( (faderOne->y - 549) ) / (float) 198));

// If rock3 button is pressed:
    al_set_sample_instance_gain(rock1inst, 0);
    al_set_sample_instance_gain(rock2inst, 0);
    al_set_sample_instance_gain(rock3inst, (abs( (faderTwo->y - 549) ) / (float) 198));
    al_set_sample_instance_gain(rock4inst, 0);

    // While button is on
    al_set_sample_instance_gain(rock3inst, (abs( (faderOne->y - 549) ) / (float) 198));

// If rock4 button is pressed:
    al_set_sample_instance_gain(rock1inst, 0);
    al_set_sample_instance_gain(rock2inst, 0);
    al_set_sample_instance_gain(rock3inst, 0);
    al_set_sample_instance_gain(rock4inst, (abs( (faderTwo->y - 549) ) / (float) 198));

    // While button is on
    al_set_sample_instance_gain(rock4inst, (abs( (faderOne->y - 549) ) / (float) 198));

// If jazz1 button is pressed:
    al_set_sample_instance_gain(jazz1inst, (abs( (faderThree->y - 549) ) / (float) 198));
    al_set_sample_instance_gain(jazz2inst, 0);
    al_set_sample_instance_gain(jazz3inst, 0);
    al_set_sample_instance_gain(jazz4inst, 0);

    // While button is on
    al_set_sample_instance_gain(jazz1inst, (abs( (faderOne->y - 549) ) / (float) 198));

// If jazz2 button is pressed:
    al_set_sample_instance_gain(jazz1inst, 0);
    al_set_sample_instance_gain(jazz2inst, (abs( (faderThree->y - 549) ) / (float) 198));
    al_set_sample_instance_gain(jazz3inst, 0);
    al_set_sample_instance_gain(jazz4inst, 0);

    // While button is on
    al_set_sample_instance_gain(jazz2inst, (abs( (faderOne->y - 549) ) / (float) 198));

// If jazz3 button is pressed:
    al_set_sample_instance_gain(jazz1inst, 0);
    al_set_sample_instance_gain(jazz2inst, 0);
    al_set_sample_instance_gain(jazz3inst, (abs( (faderThree->y - 549) ) / (float) 198));
    al_set_sample_instance_gain(jazz4inst, 0);

    // While button is on
    al_set_sample_instance_gain(jazz3inst, (abs( (faderOne->y - 549) ) / (float) 198));

// If jazz4 button is pressed:
    al_set_sample_instance_gain(jazz1inst, 0);
    al_set_sample_instance_gain(jazz2inst, 0);
    al_set_sample_instance_gain(jazz3inst, 0);
    al_set_sample_instance_gain(jazz4inst, (abs( (faderThree->y - 549) ) / (float) 198));

    // While button is on
    al_set_sample_instance_gain(jazz4inst, (abs( (faderOne->y - 549) ) / (float) 198));
                                
// If reggae1 button is pressed:
    al_set_sample_instance_gain(reggae1inst, (abs( (faderFour->y - 549) ) / (float) 198));
    al_set_sample_instance_gain(reggae2inst, 0);
    al_set_sample_instance_gain(reggae3inst, 0);
    al_set_sample_instance_gain(reggae4inst, 0);

    // While button is on
    al_set_sample_instance_gain(reggae1inst, (abs( (faderOne->y - 549) ) / (float) 198));
    
// If reggae2 button is pressed:
    al_set_sample_instance_gain(reggae1inst, 0);
    al_set_sample_instance_gain(reggae2inst, (abs( (faderFour->y - 549) ) / (float) 198));
    al_set_sample_instance_gain(reggae3inst, 0);
    al_set_sample_instance_gain(reggae4inst, 0);

    // While button is on
    al_set_sample_instance_gain(reggae2inst, (abs( (faderOne->y - 549) ) / (float) 198));
    
// If reggae3 button is pressed:
    al_set_sample_instance_gain(reggae1inst, 0);
    al_set_sample_instance_gain(reggae2inst, 0);
    al_set_sample_instance_gain(reggae3inst, (abs( (faderFour->y - 549) ) / (float) 198));
    al_set_sample_instance_gain(reggae4inst, 0);

    // While button is on
    al_set_sample_instance_gain(reggae3inst, (abs( (faderOne->y - 549) ) / (float) 198));
    
// If reggae4 button is pressed:
    al_set_sample_instance_gain(reggae1inst, 0);
    al_set_sample_instance_gain(reggae2inst, 0);
    al_set_sample_instance_gain(reggae3inst, 0);
    al_set_sample_instance_gain(reggae4inst, (abs( (faderFour->y - 549) ) / (float) 198));

    // While button is on
    al_set_sample_instance_gain(reggae4inst, (abs( (faderOne->y - 549) ) / (float) 198));

                                
// TO INSERT INTO FUNCTION: Update sample instance gain when fader is moved
//------------------------------------------------------------------


// TO INSERT INTO FUNCTION: Start all playback once a loop is started
//------------------------------------------------------------------
    // If button is pressed
void start_loops(){
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
}

// TO INSERT INTO FUNCTION: Stop all playback.
//------------------------------------------------------------------

void stop_loops(){
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
}

// Clean up audio samples
//------------------------------------------------------------------

void clean_audio(){
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
    al_destroy_sample_instance(other1inst);
    al_destroy_sample(other1);
}
































