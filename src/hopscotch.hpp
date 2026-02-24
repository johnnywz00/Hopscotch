/*
 - levels list should be input file analogous to ZGolf courses.txt file
 */



#ifndef HOPSCOTCH_H
#define HOPSCOTCH_H


#include "vsprite.hpp"
#include "resourcemanager.hpp"
#include "timedeventmanager.hpp"

class State;

#include "objects.hpp"
#include "oxyd.hpp"
#include "deh.hpp"

class FullscreenOnlyApp;

class State
{
public:
	enum GameMode { menu, playing };
	
	void onCreate ();
	
	bool handleTextEvent (Event&) { return false; }
	
	void loadMap (string fname);
	
	void loadTextures ();
	
	void debugTxtSetup ();
	
	void resetForNewLevel ();
	
	void startLevel (int num);
	
	void newOxyds (int pairs);
	
	void menuClick (int x, int y);
	
	void onMouseDown (int x, int y);
	
    void onMouseUp (int x, int y) { }
	
	void onKeyPress (Keyboard::Key);
    
    void onKeyRelease (Keyboard::Key);
	
	void hitOxyd (Oxyd& ox);
	
	bool checkForMatch (Oxyd& ox);
	
	void win () { deh.win(); }
	
	void die ();
	
	void update (const Time& time);
	
	void draw ();
	
	void menuDraw ();
    
    void menuUpdate () { }  // May add animations
	
	void returnToMenu ();

	RenderWindow*  		 	rwin;
	FullscreenOnlyApp* 		app;
    TimedEventManager*      timedMgr;
    vecI					mouseVec
							, oldMouse
	;
	
    vector<Texture>      	matchTexs;
    vector<Texture*>     	matchTexPtrs;
    vector<Texture>      	gameWorldTexs;
    static vector<string>  	matchTexList;
	static vector<string>  	gameWorldTexList;
	
	map<string, Texture> 	txMap;
	static const vector<pair<string, string>>
							txList;

	vector<Oxyd> 		 	oxyds;
	vector<MapItem> 	 	platforms;
    vector<Stump>        	stumps;
    vector<MapItem*>     	mapItems;
    
    Deh 				 	deh;
    Oxyd* 				 	lastOxyd = nullptr;
	Level* 				 	curLevel = nullptr;
	vector<Level> 			levels;
    int 				 	matchCt = 0;
    int 				 	oxydPairs = 3;

	Sprite 				 	bkgd;
    RectangleShape 		 	bkgdAlpha;
    Text                 	instrTxt;
    static const string  	instrText;

	
	
////////////  MENU SCREEN  /////////////////////

	static constexpr int numButtons = 5;

	GameMode 			 mode = menu;
	RectangleShape 		 rects[numButtons];
	Text 				 gameTitle,
						 labels[numButtons];
	vecF 				 buttonSize { 500, 55 };
	uint 				 buttonPadding { 15 };
	vecF 				 buttonPos { scrcx - buttonSize.x / 2 - buttonPadding / 2,
									 scrcy - 160 };
	

	Text    			 mouseTxt,
						 debugTxt;
}; //end class State


#endif




