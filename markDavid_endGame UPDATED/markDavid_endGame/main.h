//
//  main.h
//  markDavid_endGame
//
//  Created by Mark Anderson on 12/8/11.
//  Copyright 2011 markmakingmusic. All rights reserved.
//


//Object IDs
enum IDS{PLAYER, BULLET, ENEMY};

//make the bounding boxes slightly smaller than the actual graphical representation
//Our Player
struct SpaceShip
{
	int ID;
	int x;
	int y;
	int lives;
	int speed;
	int boundx;
	int boundy;
	int score;
};

struct Bullet
{
    int ID;
    int x;
    int y;
    bool live;
    int speed;
};

struct Comet
{
    int ID;
    int x;
    int y;
    bool live;
    int speed;
    int boundx;
    int boundy;
};