//
//  mainStuff.h
//
//  Mix Hero
//
//  Created by Mark Anderson and David Forshee
//  
//  C Programming for Music Technology
//  Final Project

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



