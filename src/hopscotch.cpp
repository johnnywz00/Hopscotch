//
//  hopscotch.cpp
//  Hopscotch
//
//  Created by John Ziegler on 10/29/24.
//  Copyright © 2024 John Ziegler. All rights reserved.
//

#include "hopscotch.hpp"
#include "sfmlApp.hpp"



void State::loadMap (string fname)
{
	platforms.clear();
	stumps.clear();
	mapItems.clear();
	platforms.reserve(300);
    stumps.reserve(100);
	mapItems.reserve(100);
	std::ifstream plats;
	plats.open("levels/" + fname);
	if (!plats.is_open()) {
		cout << "Map file didn't load. \n";
		return;
	}
	string line;
	int oxct = 0;
	
	if (fname != "level1.txt" &&
		fname != "level2.txt" &&
		fname != "level3.txt") {
		while (getline(plats, line)) {
			stringstream ss(line);
			string val;
			string typ;
			int id;
			vecF pos;
			float rot;
			vecF scale;
			IntRect texRect {};
			int layer;
			
			ss >> val;
			typ = val;
			ss >> val;
			id = (uint)stoi(val);
			ss >> val;
			pos.x = stof(val);
			ss >> val;
			pos.y = stof(val);
			ss >> val;
			rot = stof(val);
			ss >> val;
			scale.x = stof(val);
			ss >> val;
			scale.y = stof(val);
			ss >> val;
			texRect.width = stoi(val);
			ss >> val;
			texRect.height = stoi(val);
			ss >> val;
			layer = stoi(val);
			
			
			if (typ == "oxyd")
				oxyds[oxct++].initPos(pos);
			else  {
				if (typ == "stump") {
					Stump p;
					p.sP(pos);
					p.setTexture(txMap[typ]);
					p.id = id;
					p.tag = typ;
					p.setRotation(rot);
					p.setScale(scale);
					p.setTextureRect(texRect);
					p.layer = layer;
					stumps.push_back(p);
					mapItems.push_back(&stumps.back());
				}
				else {
					MapItem p;
					p.sP(pos);
					p.setTexture(txMap[typ]);
					p.id = id;
					p.tag = typ;
					vector<string> nonCollidables {"thickpost", "thinpost", "doublecurvingwood", "ornatebracket", "curvingwood", "woodcorbel"};
					for (auto& nc : nonCollidables) {
						if (typ == nc) {
							p.isCollidable = false;
							break;
						}
					}
					if (typ == "midlogplat" && !epsEquals(rot, 0))
						p.isCollidable = false;
					p.setRotation(rot);
					p.setScale(scale);
					p.setTextureRect(texRect);
					p.layer = layer;
					platforms.push_back(p);
					mapItems.push_back(&platforms.back());
				}
			}
		} // end while
	}
	
	else {
		while (std::getline(plats, line)) {
			int typ;
			vecF pos;
			vecF scale;
			IntRect texRect {};
			std::stringstream ss(line);
			string coord;
			ss >> coord;
			typ = std::stoi(coord);
			ss >> coord;
			pos.x = std::stof(coord);
			ss >> coord;
			pos.y = std::stof(coord);
			if (typ == 8)
				oxyds[oxct++].initPos(pos);
			else  {
				if (typ == 7 ) {
					Stump p;
					p.sP(pos);
					p.setTexture(gameWorldTexs[typ]);
					p.id = typ;
					stumps.push_back(p);
					mapItems.push_back(&stumps.back());
				}
				else {
					MapItem p;
					p.sP(pos);
					p.setTexture(gameWorldTexs[typ]);
					p.id = typ;
					platforms.push_back(p);
					mapItems.push_back(&platforms.back());
				}
			}
		} // end while
	}
	sort(mapItems.begin(), mapItems.end(), [&](const MapItem* a, const MapItem* b) {
		return a->layer > b->layer;
	});
	plats.close();
}

void State::loadTextures () {
	
	matchTexs.clear();
	matchTexPtrs.clear();
	gameWorldTexs.clear();
	matchTexs.reserve(40);
	gameWorldTexs.reserve(40);

	txMap.clear();
	
	Texture tex;
	string basePath = "resources/";
	
	forNum (int(txList.size())) {
		string fileName = txList[i].first;
		string filePath = basePath + fileName;
		//TODO: make embedded info for new sprites
		//		if (!loadByMethod(tex, filePath))
		if (!tex.loadFromFile(filePath))
			cerr << "Couldn't load texture " << filePath << endl;
		else {
			tex.setRepeated(true);
			txMap.insert({txList[i].second, tex});
		}
	}
	
	int sz = int(gameWorldTexList.size());
	for (int i = 0; i <  sz ; ++i) {
		string fileName = basePath + gameWorldTexList[i];
		loadByMethod(tex, fileName);
		gameWorldTexs.push_back(tex);
	}
	
	basePath = "resources/matchPics/";
	sz = int(matchTexList.size());
	matchTexPtrs.resize(sz);
	for (int i = 0; i <  sz ; ++i) {
		string fileName = basePath + matchTexList[i];
		loadByMethod(tex, fileName);
		matchTexs.push_back(tex);
		matchTexPtrs[i] = &matchTexs[i];
	}
}

void State::debugTxtSetup () {
	
	loadByMethod(font, "resources/Monaco.ttf");
	mouseTxt = Text("", font, 13);
	mouseTxt.sP(8, 9);
	mouseTxt.setFillColor(Color::Blue);
		
	debugTxt = Text("", font, 13);
	debugTxt.sP(8, 25);
	debugTxt.setFillColor(Color::Blue);
}

void State::onCreate () {
		
	debugTxtSetup();
	loadTextures();
	
		// background image
	gameWorldTexs[12].setRepeated(true);
	bkgd.setTexture(gameWorldTexs[12]);
	bkgd.setTextureRect(IntRect(0, 0, ScrW * 3, 800));
	bkgd.setScale(1, 1.15);
	
	txMap["beachbkgd"].setRepeated(true);
	
	bkgdFrame.setTexture(gameWorldTexs[13]);
	bkgdFrame.sP(-550, -550);
//	bkgdAlpha.setSize(vecF(ScrW, ScrH));
	bkgdAlpha.setSize({2000, 1200});
	bkgdAlpha.setFillColor(Color(255, 255, 255, 110));  // alpha: 100 - 130
	
	deh.gam = this;
	deh.setTexture(gameWorldTexs[14]);
	centerOrigin(deh);
	
		//== MENU SETUP == //
	
	loadByMethod(titleFont, "resources/Zeriba.otf");
	loadByMethod(labelFont, "resources/NickelodeonNF.otf");
	gameTitle.setFont(titleFont);
	gameTitle.setString(String("H O P S C O T C H"));
	gameTitle.setCharacterSize(150);
	gameTitle.setOutlineColor(Color(80, 80, 80));
	gameTitle.setOutlineThickness(5);
	centerOrigin(gameTitle);
	gameTitle.sP(ScrCX, 100);
	
	string str[numButtons];
	str[0] = "Level 1";
	str[1] = "Level 2";
	str[2] = "Level 3";
	str[3] = "Level 4";
	// future levels
	str[numButtons - 1] = "Exit";
	
	for (int i = 0; i <  numButtons; ++i) {
		vecF bp(i > 7 ?
				buttonPos.x + buttonSize.x + buttonPadding :
				buttonPos.x,
				buttonPos.y + (i % 8 * (buttonSize.y + buttonPadding)));
		rects[i].setSize(buttonSize);
		rects[i].setFillColor(Color(132, 164, 255));
		if (i == numButtons - 1)
			rects[i].setFillColor(Color(225, 165, 71));
		rects[i].setOutlineColor(Color(54, 60, 25));
		rects[i].setOutlineThickness(5);
		rects[i].setOrigin(buttonSize.x / 2., buttonSize.y / 2.);
		rects[i].setPosition(bp);
		labels[i].setFont(labelFont);
		labels[i].setString(String(str[i]));
		labels[i].setCharacterSize(36);
		labels[i].setFillColor(Color(50, 50, 50));
		FloatRect rect = labels[i].gLB();
		labels[i].setOrigin(rect.left + rect.width / 2., rect.top + rect.height / 2.);
		labels[i].sP(bp);
		}
	
	instrTxt = Text(instrText, labelFont, 30);
	instrTxt.setFillColor(Color::Black);
	instrTxt.sP(w->mapPixelToCoords(vecI(ScrW - 300,
										 ScrH - 150)));
	//=========  END MENU   ===========//

	
	loadByMethod(buffers[0], "resources/startcomputer.wav");
	sounds[0].setBuffer(buffers[0]);
	loadByMethod(buffers[1], "resources/doorbell.wav");
	sounds[1].setBuffer(buffers[1]);
	loadByMethod(buffers[2], "resources/mysticchimes.wav");
	sounds[2].setBuffer(buffers[2]);
	loadByMethod(buffers[3], "resources/phaseJump1.wav");
	sounds[3].setBuffer(buffers[3]);
//	loadByMethod(buffers[4], "resources/splash1.wav");
	buffers[4].loadFromFile("resources/splash1.wav");
	sounds[4].setBuffer(buffers[4]);

	levels[0] = Level(1, 3, "level1.txt");
	levels[1] = Level(2, 3, "level2.txt", vecf(ScrCX, ScrCY) + vecf(0, -12));
	levels[2] = Level(3, 5, "level3.txt", vecf(ScrCX, ScrCY) + vecf(55, 0));
	levels[3] = Level(4, 3, "level4.txt", {200, 860});

	resetForNewLevel();
} //end onCreate

void State::resetForNewLevel () {
	
	if (!curLevel)
		curLevel = &levels[0];
	deh.sP(curLevel->dehStart);
	deh.reset();

	newOxyds(curLevel->numMatches);
	loadMap(curLevel->fname);
	lastOxyd = nullptr;
	matchCt = 0;
}


void State::startLevel (int num) {
	
	curLevel = &levels[(num - 1) % numLevels];
	resetForNewLevel();
	mode = playing;
	w->setMouseCursorVisible(false);
	
	//TODO: Level class needs bkgd info
	bkgd.setTexture(num == 4 ? txMap["beachbkgd"] : gameWorldTexs[12]);
	bkgd.setTextureRect(IntRect(0, 0, ScrW * 3,
								num == 4 ? bkgd.gLB().height : 800));
	if (num == 4)
		bkgd.setScale(1.4, 1.4);
	else bkgd.setScale(1, 1.15);
	
	if (num == 4)
		gw->setViewToScreen();
	else gw->setToggledView(gw->isStretched());
}

void State::newOxyds (int pairs) {
	
	oxydPairs = pairs;
	oxyds.clear();
	intvec symsToChoose {};
	for (int i = 0; i <  matchTexPtrs.size(); ++i)
		symsToChoose.push_back(i);
	intvec symsChosen{};
	for (int i = 0; i <  pairs; ++i) {
		int idx = rand() % symsToChoose.size();
		symsChosen.push_back(symsToChoose[idx]);
		symsChosen.push_back(symsToChoose[idx]);
		popOut(symsToChoose, symsToChoose[idx]);
	}
	for (int i = 0; i <  pairs * 2; ++i) {
		Oxyd ox {};
		int idx = rand() % symsChosen.size();
		Texture& matchSymbol = matchTexs[symsChosen[idx]];
		symsChosen.erase(find(symsChosen.begin(), symsChosen.end(), symsChosen[idx]));
		ox.initTxs(gameWorldTexs[10], gameWorldTexs[11], matchSymbol);
		ox.reset();
		oxyds.push_back(ox);
	}
}

void State::onMouseDown (int x, int y) {
	
	if (mode == menu)
		menuClick(x, y);
	// Currently no clicking in gameplay
}


void State::hitOxyd (Oxyd& ox) {
	
	if (ox.isOpen)
		return;
	ox.makeOpen(true);
	if (!checkForMatch(ox)) {
		if (lastOxyd && !lastOxyd->matched) {
			lastOxyd->makeOpen(false);
			sounds[1].play();
		}
		else sounds[0].play();
	}
	else {
		sounds[2].play();
	}
	if (matchCt == oxydPairs)
		win();
	else lastOxyd = &ox;
}

bool State::checkForMatch (Oxyd& ox) {
	
	if (!lastOxyd)
		return false;
	if (ox.myPicture == lastOxyd->myPicture) {
		for (auto cur : {&ox, lastOxyd}) {
			cur->matched = true;
			cur->symbol.sRot(0);
			cur->symbol.setScale(1, 1);
		}
		++matchCt;
		return true;
	}
	return false;
}

void State::die () {
	
	sounds[4].play();
	timedMgr->addEventIf("died", 2, [&]() { resetForNewLevel(); });
}

void State::update (const Time& time) {

		// Separate the logic if we're in the opening menu
	if (mode == menu) {
		menuUpdate();
		return;
	}
	
	timedMgr->fireReadyEvents(time);
	
		// Scroll the background for interest
	bkgd.move(-.2, 0);
	if(bkgd.gP().x <= -float(bkgd.getTexture()->getSize().x))
		bkgd.sP(0, 0);
	
		// Store some sprite info
	vecF oldPos = deh.gP();
	vecF oldBL = deh.bottomLeft();
	vecF oldBR = deh.bottomRight();
	vecF savePos = oldPos;
	
		// Let the player sprite run its updates
	deh.update();
	
		// Advance level if one just completed
	if (deh.won && deh.cartwheelFinished) {
		timedMgr->addEventIf("beatLevel", 2.5, [&]() { startLevel((curLevel->levelID) + 1); });
	}
	
		// Move the player
	float m = ceil(deh.mag());
	for (int rep = 0; rep <  m; ++rep) {
		savePos = deh.gP();
		deh.move(deh.velocity / m);
		
			// Handle moving past edges of screen
		
		float ob = 15;
		if (deh.left() < -ob)
			deh.setLeft(-ob);
		if (deh.right() > (curLevel->levelID == 4 ? scrw : ScrW) + ob)
			deh.setRight((curLevel->levelID == 4 ? scrw : ScrW) + ob);
		if (deh.top() < -ob)
			deh.setTop(-ob);
		if (deh.bottom() > (curLevel->levelID == 4 ? scrh : ScrH) + 5 * ob) {
			if (!deh.won)
				die();
		}
		
			// Check whether player bumps any oxyds
		FloatRect isct;
		for (auto& ox : oxyds) {
			if (ox.hitBox().intersects(deh.hitBox(), isct)) {
				hitOxyd(ox);
				float diff = isct.width - isct.height;
				if (diff > 0) {
					deh.move(0, isct.height * (deh.velocity.y > 0 ? -1 : 1));
					if (deh.dy() < 0)
						deh.velocity.y *= -.2;
					else {
						deh.land();
					}
				}
				else {
					deh.move(isct.width * (deh.velocity.x > 0 ? -1 : 1), 0);
					deh.velocity.x *= -.5;
				}
			}
		}
		
		// Check colliding with obstacles and supporting surfaces
		for (auto& i : mapItems) {
			if (!i->isCollidable)
				continue;
			if (i->hitBox().intersects(deh.hitBox(), isct) &&
				deh.wasOnGround &&
				isct.height < 10 &&
				deh.top() < i->top() ) {
				deh.setBottom(i->top());
			}
				// solid on all sides: bricks, stumps...
			if (curLevel->levelID == 4 && (i->tag == "stump" || i->tag == "longbrick" || i->tag == "shortbrick") || curLevel->levelID != 4 &&
				i->id > 4 && i->id < 8) {
				if (i->hitBox().intersects(deh.hitBox(), isct)) {
					float diff = isct.width - isct.height;
					if (isct.height <= 3 && deh.dy() > 0) {
						deh.move(0, isct.height * (deh.velocity.y > 0 ? -1 : 1));
						deh.land();
					}
					else if (diff > 0) {
						deh.move(0, isct.height * (deh.velocity.y > 0 ? -1 : 1));
						if (deh.dy() < 0)
							deh.velocity.y *= -.2;
						else {
							deh.land();
						}
					}
					else {
						deh.move(isct.width * (deh.velocity.x > 0 ? -1 : 1), 0);
						deh.velocity.x *= -.2;
					}
				}
			}
			else {
				//this logic presumes only level platforms and deh less wide than any platform
				if (i->hitBox().intersects(deh.hitBox(), isct)) {
					if (deh.dy() > 0) {
						if (oldBL.y > i->topLeft().y)
							continue;
						bool intersects = false;
						vecF a1 = oldBL;
						vecF a2 = deh.bottomLeft();
						bool aVertical = false;
						float slopea = 0;
						float xdifa = a2.x - a1.x;
						if (xdifa == 0)
							aVertical = true;
						else slopea = (a2.y - a1.y) / xdifa;
						if (aVertical) {
							if (isOrBetween(a1.x, i->left(), i->right()))
								intersects = true;
						}
						else {
							float check = (i->top() - a2.y) / slopea + a2.x;
							if (isOrBetween(check, i->left(), i->right()))
								intersects = true;
						}
						a1 = oldBR;
						a2 = deh.bottomRight();
						aVertical = false;
						slopea = 0;
						xdifa = a2.x - a1.x;
						if (xdifa == 0)
							aVertical = true;
						else slopea = (a2.y - a1.y) / xdifa;
						if (aVertical) {
							if (isOrBetween(a1.x, i->left(), i->right()))
								intersects = true;
						}
						else {
							float check = (i->top() - a2.y) / slopea + a2.x;
							if (isOrBetween(check, i->left(), i->right()))
								intersects = true;
						}
						if (intersects) {
							deh.land();
							deh.setBottom(i->top());
						}
					} // end deh.dy() > 0
				} // end hitBox().intersects
			} // end else
		} // end for auto...platforms
	} // end for i
	
		// Update oxyd animations
	for (auto& ox : oxyds)
			ox.update();

	if (!deh.landedThisFrame)
		deh.isOnGround = false;

	// DEBUG/TESTING
	//mouseTxt.setString(tS(mx) + ", " + tS(my));
	//debugTxt.setString("");
	
} //end update


void State::draw () {
	
	if (mode == menu) {
		menuDraw();
		return;
	}
	w->draw(bkgd);
	w->draw(bkgdAlpha);
	w->draw(mouseTxt);
	w->draw(debugTxt);
//	for (auto& m : platforms)
//		w->draw(m);
	for (auto& m : mapItems)
		w->draw(*m);
	for (auto& o : oxyds)
		w->draw(o);
	for (auto& s : stumps)
		w->draw(s);
	w->draw(deh);
	if (!gw->isStretched() && curLevel->levelID != 4)
		w->draw(bkgdFrame);
}

void State::menuDraw () {
	
	w->draw(bkgd);
	w->draw(gameTitle);
	for (auto& b : rects)
		w->draw(b);
	for (auto& b : labels)
		w->draw(b);
	w->draw(instrTxt);
	if (!gw->isStretched())
		w->draw(bkgdFrame);
}

void State::menuClick (int x, int y) {
	
	float halfx = buttonSize.x / 2.;
	float halfy = buttonSize.y / 2.;
	for (int i = 0; i <  numButtons; ++i) {
		if (	x >= rects[i].getPosition().x - halfx &&
				x <= rects[i].getPosition().x + halfx &&
				y >= rects[i].getPosition().y - halfy &&
				y <= rects[i].getPosition().y + halfy) {
			if (i == numButtons - 1)
				gw->close();
			else startLevel(i + 1);
			}
		}
}

void State::onKeyPress(Keyboard::Key k) {
	
	switch(k) {
			
		case Keyboard::Escape:
			if (mode == menu)
				gw->close();
			else {
				mode = menu;
				w->setMouseCursorVisible(true);
			}
			break;
						
		case Keyboard::Y:
			resetForNewLevel(); break;
			
		default:
			break;
	}
}

void State::onKeyRelease(Keyboard::Key k) {
	
	switch(k) {
					
		default:
			break;
	}
}

vector<string> State::gameWorldTexList {
	
	"shortplat.png",	// 0
	"midplat.png",		// 1
	"longplat.png",		// 2
	"shortgrass.png",	// 3
	"longgrass.png",	// 4
	"shortbrick.png",	// 5
	"longbrick.png",	// 6
	"stump.png",		// 7
	"dehL.png",			// 8
	"dehR.png",			// 9
	"oxyd.png",			// 10
	"oxydcover.png",	// 11
	"backdrop.png",		// 12
	"bkgdFrame.png",	// 13
	"dehStill.png",		// 14
	"dehWalkL.png",		// 15
	"dehWalkR.png",		// 16
};

const vector<pair<string, string>> State::txList
{
	{ "beachbkgd.png", "beachbkgd" },
	{ "longbrick.png", "longbrick" },
	{ "longplat.png", "longplat" },
	{ "longgrass.png", "longgrass" },
	{ "midlogplat.png", "midlogplat" },
	
	{ "midplat.png", "midplat" },
	{ "shortgrass.png", "shortgrass" },
	{ "shortbrick.png", "shortbrick" },
	{ "shortplat.png", "shortplat" },
	{ "shortlogplat.png", "shortlogplat" },
	{ "ornatebracket.png", "ornatebracket" },
	{ "curvingwood.png", "curvingwood" },
	{ "doublecurvingwood.png", "doublecurvingwood" },
	
	{ "woodcorbel.png", "woodcorbel" },
	{ "thickpost.png", "thickpost" },
	{ "thinpost.png", "thinpost" },
	{ "stump.png", "stump" },
	{ "oxyd.png", "oxyd" }
};

vector<string> State::matchTexList {
	
	"knight.png",
	"rook.png",
	"queen.png",
	"king.png",
	"bishop.png",
	"leta.png",
	"letb.png",
	"letc.png",
	"starfish.png",
	"wheel.png",
	"ball.png",
	"sheep.png",
	"leth.png",
	"letk.png",
	"letm.png",
	"letx.png",
	"matchorca.png",
	"matchdeh.png",
	"moon.png",
	"squish.png",
	"bull.png",
	"house.png"
};

const string State::instrText {
	
	"LEFT / RIGHT to move character \n"
	"SPACE to jump \n"
	"F6 to fit graphics to screen \n"
	"ESC to return to menu \n"
	"Match the \"oxyds\"! \n"
};
