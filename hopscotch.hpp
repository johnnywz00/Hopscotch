#ifndef HOPSCOTCH_H
#define HOPSCOTCH_H

#include "objects.hpp"



enum GameMode { menu, playing };

class SFGameWindow;
class FuseManager;

class State {
public:
			
	void onCreate ();
	
	void loadMap (string fname);
	
	void loadTextures ();
	
	void debugTxtSetup ();
	
	void resetForNewLevel ();
	
	void startLevel (int num);
	
	void newOxyds (int pairs);
	
	void menuClick (int x, int y);
	
	void onMouseDown (int x, int y);
	
    void onMouseUp (int x, int y) { }  // May use eventually
	
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

	RenderWindow*  		 w;
	SFGameWindow* 		 gw;
    FuseManager*         fuseMgr;
    int             	 mx = 0,
                         my = 0,
                         mxOld = 0,
                         myOld = 0;
	
    vector<Texture>      matchTexs;
    vector<Texture*>     matchTexPtrs;
    vector<Texture>      gameWorldTexs;
  static vector<string>  matchTexList;
  static vector<string>  gameWorldTexList;

	vector<Oxyd> 		 oxyds;
	vector<ZSprite> 	 platforms;
    vector<Stump>        stumps;
    vector<ZSprite*>     mapItems;
    
    Deh 				 deh;
    Oxyd* 				 lastOxyd { nullptr };
	Level* 				 curLevel { nullptr };
	static constexpr int numLevels = 3;
	Level 				 levels[numLevels];
    int 				 matchCt = 0;
    int 				 oxydPairs = 3;

    Sprite 				 bkgd,
                         bkgdFrame;
    RectangleShape 		 bkgdAlpha;
    Text                 instrTxt;
    static const string  instrText;

    SoundBuffer 		 buffers[5];
    Sound        		 sounds[5];
	
	
	
////////////  MENU SCREEN  /////////////////////

	static constexpr int numButtons = 4;

	GameMode 			 mode = menu;
	RectangleShape 		 rects[numButtons];
	Text 				 gameTitle,
						 labels[numButtons];
	Font 				 titleFont,
						 labelFont;
	vecF 				 buttonSize { 500, 55 };
	uint 				 buttonPadding { 15 };
	vecF 				 buttonPos { ScrCX - buttonSize.x / 2 - buttonPadding / 2,
									 ScrCY - 180 };
	

////////////  DEBUG  /////////////////////

	Font    			 font;
	Text    			 mouseTxt,
						 debugTxt;

}; //end class State


#endif




