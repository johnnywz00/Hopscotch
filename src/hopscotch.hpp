#ifndef HOPSCOTCH_H
#define HOPSCOTCH_H

#include "objects.hpp"



enum GameMode { menu, playing };

class SFGameWindow;
class TimedEventManager;

class State {
public:

	float SCRW () { return w->getView().getSize().x; }
	float SCRH () { return w->getView().getSize().y; }
	float SCRCX () { return w->getView().getSize().x / 2; }
	float SCRCY () { return w->getView().getSize().y / 2; }
	
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
    TimedEventManager*         timedMgr;
    int             	 mx = 0,
                         my = 0,
                         mxOld = 0,
                         myOld = 0;
	
    vector<Texture>      matchTexs;
    vector<Texture*>     matchTexPtrs;
    vector<Texture>      gameWorldTexs;
  static vector<string>  matchTexList;
  static vector<string>  gameWorldTexList;
	
	map<string, Texture> 		txMap;
	static const vector<pair<string, string>>
								txList;

	vector<Oxyd> 		 oxyds;
	vector<MapItem> 	 platforms;
    vector<Stump>        stumps;
    vector<MapItem*>     mapItems;
    
    Deh 				 deh;
    Oxyd* 				 lastOxyd { nullptr };
	Level* 				 curLevel { nullptr };
	static constexpr int numLevels = 4;
	Level 				 levels[numLevels];
    int 				 matchCt = 0;
    int 				 oxydPairs = 3;

    Sprite 				 bkgd,
                         bkgdFrame;
    RectangleShape 		 bkgdAlpha;
    Text                 instrTxt;
    static const string  instrText;

    SoundBuffer 		 buffers[6];
    Sound        		 sounds[6];
	
	
	
////////////  MENU SCREEN  /////////////////////

	static constexpr int numButtons = 5;

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




