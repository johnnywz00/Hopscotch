//
//  objects.cpp
//  Hopscotch
//
//  Created by John Ziegler on 10/29/24.
//  Copyright © 2024 John Ziegler. All rights reserved.
//

#include "objects.hpp"
#include "hopscotch.hpp"
#include "timedeventmanager.hpp"

	// STUMP

FloatRect Stump::hitBox () {
    FloatRect gb = gGB();
    return FloatRect(gb.left + 12, gb.top, gb.width - 28, gb.height - 18);
}


	// OXYD

void Oxyd::initTxs (Texture& oxtx, Texture& covtx, Texture& symtx) {
	
	setTexture(oxtx);
	cover.setTexture(covtx);
	symbol.setTexture(symtx);
	::centerOrigin(cover);
	::centerOrigin(symbol);
	myPicture = &symtx;
}

void Oxyd::initPos (vecF& p)
{
	sP(p);
	vecF pos {left() + width() / 2, top() + height() / 2} ;
	cover.sP(pos);
	symbol.sP(pos);
}

void Oxyd::reset ()
{	
	isOpen = false;
	matched = false;
	openingFrmCt = 0;
	closingFrmCt = 0;
	symbolScaleDegree = 0;
	cover.setScale(1, 1);
}

void Oxyd::makeOpen (bool op) {
	
	isOpen = op;
	if (op)
		openingFrmCt = 1;
	else closingFrmCt = 1;
}

void Oxyd::update () {
	
	if (isOpen) {
		checkOpenCover();
		if (!matched)
			animateSymbol();
	}
	else checkCloseCover();
}

void Oxyd::animateSymbol () {
	
	float curCos = cos(toRad(symbolScaleDegree));
	float sfac = curCos * .09 + .91;
	symbol.setScale(sfac, sfac);
	symbol.sRot(curCos * -2.5 + 2.5);
	symbolScaleDegree += 6;
	if (symbolScaleDegree >= 360)
		symbolScaleDegree -= 360;
}

void Oxyd::checkOpenCover () {
	
	if (openingFrmCt && openingFrmCt <= openingFrames) {
		float val = float(openingFrames - openingFrmCt) / openingFrames;
		cover.setScale(val, val);
		++openingFrmCt;
	}
	else if (openingFrmCt > openingFrames) {
		cover.setScale(0, 0);
		openingFrmCt = 0;
	}
}

void Oxyd::checkCloseCover () {
	
	if (closingFrmCt && closingFrmCt <= openingFrames) {
		float val = float(closingFrmCt) / openingFrames;
		cover.setScale(val, val);
		++closingFrmCt;
	}
	else if (closingFrmCt > openingFrames) {
		cover.setScale(1, 1);
		closingFrmCt = 0;
	}
}

void Oxyd::draw(RenderTarget& target, RenderStates states) const {
	
	target.draw(symbol);
	ZSprite::draw(target, states);
	target.draw(cover);
}





	// DEH


void Deh::changeTex (string tx) {
	
	if (tx == curTex)
		return;
	curTex = tx;
	setTexture(gam->gameWorldTexs[ texMap[tx] ]);
	auto sz = getTexture()->getSize();
	setTextureRect(IntRect(0, 0, sz.x, getTextureRect().height));
}

void Deh::reset () {
	
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

void Deh::win () {
	
    won = true;
    cartwheelFinished = false;
}

void Deh::land () {
	
    velocity.y = 0;
    landedSinceJump = true;
    landedThisFrame = true;
    isOnGround = true;
}


void Deh::update(const Time& t /* = Time::Zero */) {

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
		gam->sounds[3].play();
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


