//
//  objects.hpp
//  Hopscotch
//
//  Created by John Ziegler on 10/29/24.
//  Copyright © 2024 John Ziegler. All rights reserved.
//

#ifndef objects_hpp
#define objects_hpp

#include "vsprite.hpp"

#define _EMBEDDING
#include "embedded.hpp"


class State;

struct MapItem: public ZSprite
{
	string tag {};
	bool isCollidable {true};
	int layer = 100;
};


struct Stump: public MapItem
{
	FloatRect hitBox () override;
};


struct Oxyd: public ZSprite
{
	void initTxs (Texture& oxtx, Texture& covtx, Texture& symtx);
	
	void initPos (vecF& p);
	
	void reset ();
	
	void draw (RenderTarget& target, RenderStates states) const;
	
	void makeOpen (bool op);
	
	void update ();
	
	void animateSymbol ();
	
	void checkOpenCover ();
	
	void checkCloseCover ();

	Sprite 		            symbol,
                            cover;
	Texture* 	            myPicture;
	float 		            symbolScaleDegree = 0;
	static constexpr int 	openingFrames = 80;
	int 		            openingFrmCt = 0;
	int 		            closingFrmCt = 0;
	bool 		            matched = false;
	bool 		            isOpen = false;
		
};


struct Deh: public VSprite {
    
	Deh () { }
    
    void reset ();
    
    void win ();
    
    void land ();
    
    void changeTex (string tx);
    
	void update (const Time& t = Time::Zero) ;
    
    unordered_map<string, int> texMap {
        {"faceLeft", 8},
        {"faceRight", 9},
        {"still", 14},
        {"walkLeft", 15},
        {"walkRight", 16}
    };

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
    
}; // end Deh


struct Level {

	Level () { }
	Level (uint id, uint num, string f, vecF ds = vecF(ScrCX, ScrCY)) :
			levelID(id),
			numMatches(num),
			fname(f),
			dehStart(ds) { }
	
	string 		fname;
	vecF 		dehStart;
	uint 		numMatches;
	uint 		levelID = 0;
};



#endif /* objects_hpp */
