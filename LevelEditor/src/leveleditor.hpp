#ifndef LEVELEDITOR_H
#define LEVELEDITOR_H

#include "edclasses.hpp"

class SFGameWindow;
class TimedEventManager;
class SubWindow;

class State {
	public:
	State () {}
	~State () {}
	
	RenderWindow*   w;
	SFGameWindow*	gw;
	TimedEventManager* 	timedMgr;
	int 	mx = 0,
			my = 0,
			mxOld = 0,
			myOld = 0
	;
	Text    mouseTxt, debugTxt;
	Font    font;
	///////////////////////////

	map<string, Texture> txMap;
	static const vector<string>  mapItemImgList;

	ToolWindow			toolWin {vecf(100, 800)};
	ZSprite 			cursorSprite;

	vector<MapEntity*> 	mapEntityPtrs{200};
	vector<MapEntity> 	mapEntities{200};
	vector<MapEntity*>	selectedEnts;

	string 				curTool = "select";
	int					gLayer = 100;
	bool				needsSort = false;
	
	/////////////////////////////////
	void deselectAll();

	void onCreate();
	void resetGame();
	void makeItem(const vecI& pos);
	void makeMap();
	void onMouseDown(int x, int y);
	void onMouseUp(int x, int y);
	void onKeyPress(Keyboard::Key);
	void onKeyRelease(Keyboard::Key);
	void update(const Time& time);
//	void draw(SFGameWindow&);
//	void toolbarDraw(SFGameWindow&);
//	void mainDraw(int, SFGameWindow&);
	void draw();
	void debugTxtSetup();
	void loadTextures();
	void loadItemButtons();

	float SCRW () { return w->getView().getSize().x; }
	float SCRH () { return w->getView().getSize().y; }
	float SCRCX () { return w->getView().getSize().x / 2; }
	float SCRCY () { return w->getView().getSize().y / 2; }
	
}; //end class State
#endif
