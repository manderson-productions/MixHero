//
//  mainStuff.h
//  markDavid_endGame
//
//  Created by Mark Anderson on 12/11/11.
//  Copyright 2011 markmakingmusic. All rights reserved.
//


//TODO: ADD A SUBMIT BUTTON OR MIX BUTTON. ADD A DIALOG BOX THAT POPS UP GIVING YOU THE CASH IN THE BANK

typedef struct _mixer {
    
    int x;
    int y;
    int height;
    int width;
    
    ALLEGRO_BITMAP *mixerbmp;
    
} Mixer;

typedef struct _fader {
    
    int x;
    int y;
    int height;
    int width;
    float vol;
    bool isClicked;
    bool isDragging;
    bool isMoved;
    
    ALLEGRO_BITMAP *faderbmp;
    
} Fader;


typedef struct _button {
  
    int x;
    int y;
    int height;
    int width;
    bool isClicked;

    ALLEGRO_BITMAP *buttonbmp;

} Button;

typedef struct _mixbutton {
    
    int x;
    int y;
    int height;
    int width;
    bool isMixed;
    
    ALLEGRO_BITMAP *mixbuttonbmp;
    
} MixButton;



