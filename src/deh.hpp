//
//  deh.hpp
//  Hopscotch
//
//  Created by John Ziegler on 2/23/26.
//  Copyright © 2026 John Ziegler. All rights reserved.
//

#ifndef deh_hpp
#define deh_hpp

#include "hopscotch.hpp"


struct Deh: public VSprite
{
	static inline unordered_map<string, int> texMap // const causes error
	{
	{"faceLeft", 8}
	, {"faceRight", 9}
	, {"still", 14}
	, {"walkLeft", 15}
	, {"walkRight", 16}
};

void reset ();

void win ();

void land ();

void changeTex (string tx);

void update (const Time& t = Time::Zero);


State*          gam = nullptr;
Keyboard::Key   jumpKey = Keyboard::Key::Space;
string          curTex;

float           maxSpeed = 7;
float           frictionClamp = .001;
float           xfriction = .82;
float           accel = .6;
float           jumpSpeed = 13;
float           maxFallSpeed = 18;
float           grav = .6;
float           fallAccel = 1.18;
float           walkFrameInterval = .1;

bool            canJump = true;
bool            landedSinceJump = true;
bool            landedThisFrame = false;
bool            isOnGround = false;
bool            wasOnGround = false;
bool            jumpKeyOff = true;
bool            won = false;
bool            cartwheelFinished = false;
bool            isDead = false;
};

#endif /* deh_hpp */
