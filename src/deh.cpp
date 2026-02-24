//
//  deh.cpp
//  Hopscotch
//
//  Created by John Ziegler on 2/23/26.
//  Copyright © 2026 John Ziegler. All rights reserved.
//

#include "hopscotch.hpp"

void Deh::reset ()
{
	canJump = true;
	landedSinceJump = true;
	landedThisFrame = false;
	isOnGround = false;
	wasOnGround = false;
	jumpKeyOff = true;
	won = false;
	cartwheelFinished = false;
	isDead = false;
	velocity = {0, 0};
	curTex = "still";
}

void Deh::win ()
{
	won = true;
	cartwheelFinished = false;
}

void Deh::land ()
{
	velocity.y = 0;
	landedSinceJump = true;
	landedThisFrame = true;
	isOnGround = true;
}


void Deh::changeTex (string tx)
{
	if (tx == curTex)
		return;
	curTex = tx;
	setTexture(gam->gameWorldTexs[ texMap[tx] ]);
	auto sz = getTexture()->getSize();
	setTextureRect(IntRect(0, 0, sz.x, getTextureRect().height));
}

void Deh::update(const Time& t /* = Time::Zero */)
{
	// Turn a cartwheel after beating a level
	if (won && !cartwheelFinished) {
		rotate(10);
		move(3, 0);
		if (gRot() == 0 || gRot() == 360) {
			cartwheelFinished = true;
			velocity = {0, 0};
		}
		else return;
	}
	
	// Decrease horizontal movement by friction
	landedThisFrame = false;
	wasOnGround = isOnGround;
	if (abs(dx()) >= frictionClamp)
		velocity.x *= xfriction;
	else velocity.x = 0;
	
	// Jump if the key is pressed
	if (!Keyboard::isKeyPressed(jumpKey))
		jumpKeyOff = true;
	if (        Keyboard::isKeyPressed(jumpKey) &&
		jumpKeyOff &&
		isOnGround &&
		landedSinceJump) {
		velocity.y -= jumpSpeed;
		gSound("jump").play();
		isOnGround = false;
		landedSinceJump = false;
		jumpKeyOff = false;
	}
	
	// Add gravity
	velocity.y = incm(velocity.y, grav, maxFallSpeed);
	
	/* Set up info for moving left or right;
	 * State will do the actual move and collision
	 * checking.
	 */
	auto fm = gam->timedMgr;
	if (iKP(Left) && !iKP(Right)) {
		velocity.x = decm(velocity.x - (iKP(LShift) ? 3 : 0), accel, -maxSpeed);
		if (curTex != "faceLeft" && curTex != "walkLeft") {
			changeTex("faceLeft");
		}
		if (!fm->isTagActive("changeWalkLTex")) {
			fm->addEventIf("changeWalkLTex", walkFrameInterval,
						   [&]() { changeTex( curTex == "faceLeft" ?
											 "walkLeft" : "faceLeft"); });
		}
	}
	else if (iKP(Right) && !iKP(Left)) {
		velocity.x = incm(velocity.x + (iKP(LShift) ? 3 : 0), accel, maxSpeed);
		if (curTex != "faceRight" && curTex != "walkRight") {
			changeTex("faceRight");
		}
		if (!fm->isTagActive("changeWalkRTex")) {
			fm->addEventIf("changeWalkRTex", walkFrameInterval,
						   [&]() { changeTex( curTex == "faceRight" ?
											 "walkRight" : "faceRight"); });
		}
	}
	else {
		changeTex("still");
	}
	// Inherit stats if testing
	//ZSprite::update();
}
