#include "sfmlApp.hpp"
#include "leveleditor.hpp"



void State::onCreate () {
	
	debugTxtSetup();
	loadTextures();
	loadItemButtons();
	
	mapEntities.clear();
	mapEntityPtrs.clear();
	
	resetGame();
	
} //end onCreate


void State::resetGame() {

}

void State::draw ()
{
	w->draw(mouseTxt);
	w->draw(debugTxt);
	
	if (needsSort)
		sort(mapEntityPtrs.begin(), mapEntityPtrs.end(), [&](const auto& a, const auto& b) { return a->layer < b->layer; });
	for (auto& e : mapEntityPtrs)
		w->draw(*e);
	needsSort = false;
	
	w->draw(toolWin.totalRect);
	w->draw(toolWin.selectButton);
	for (auto& tb : toolWin.toolButtons) {
		w->draw(tb.second);
		if (tb.second.isSelected)
			w->draw(tb.second.highlight);
	}
	if (curTool != "select")
		w->draw(cursorSprite);
}


void State::makeItem (const vecI& pos) {
	
	static uint idCt = 0;
	MapEntity ent;
	ent.setTexture(txMap[curTool]);
	ent.sP(vecF(pos.x, pos.y));
	ent.sRot(cursorSprite.getRotation());
	ent.setScale(cursorSprite.getScale());
	ent.setTextureRect(cursorSprite.getTextureRect());
	ent.id = idCt++;
	ent.key = curTool;
	ent.layer = gLayer;
	mapEntities.push_back(ent);
	mapEntityPtrs.push_back(&mapEntities.back());
}


void State::makeMap ()
{
	std::fstream fs{Resources::executingDir() / "resources" / "levels" / "level.txt", std::ios_base::app};
	forNum (mapEntities.size()) {
		auto& ent = mapEntities[i];
		IntRect texRect = ent.getTextureRect();
		fs << 	ent.key << ' ' <<
				ent.id << ' ' <<
				ent.gP().x << ' ' <<
				ent.gP().y << ' ' <<
				ent.getRotation() << ' ' <<
				ent.getScale().x << ' ' <<
				ent.getScale().y << ' ' <<
				texRect.width << ' ' <<
				texRect.height << ' ' <<
				ent.layer <<
				endl;
	}
	fs.close();
	gSound("openOxyd").play();
}


void State::onMouseDown (int x, int y) {
	
	bool clickedTool = false;
	
	if (toolWin.selectButton.gGB().contains(x, y)) {
		curTool = "select";
		cursorSprite.setTextureRect(IntRect(0, 0, 0, 0));
		clickedTool = true;
		deselectAll();
	}
	
	for (auto& tb : toolWin.toolButtons) {
		if (tb.second.gGB().contains(x, y)) {
			toolWin.toolButtons[curTool].isSelected = false;
			curTool = tb.second.key;
			tb.second.isSelected = true;
			cursorSprite.setTexture(txMap[tb.second.key]);
			cursorSprite.setTextureRect(IntRect(0, 0,
												cursorSprite.getTexture()->getSize().x,
												cursorSprite.getTexture()->getSize().y));
			clickedTool = true;
			deselectAll();
			break;
		}
	}
	
	if (!clickedTool) {
		if (toolWin.totalRect.gGB().contains(x, y)) {
			toolWin.clickDragging = true;
		}
		else if (curTool == "select") {
			bool clickedEnt = false;
			for (auto& e : mapEntities) {
				if (e.clickBox().contains(x, y)) {
					e.clickedOn = true;
					auto itr = std::find(selectedEnts.begin(), selectedEnts.end(), &e);
					if (itr != selectedEnts.end()) {
						e.isSelected = false;
						e.setColor(Color::White);
						selectedEnts.erase(itr);
					}
					else {
						e.isSelected = true;
						e.setColor(Color::Red);
						selectedEnts.push_back(&e);
					}
					clickedEnt = true;
					break;
				}
			}
			if (!clickedEnt)
				deselectAll();
		}
		else {
			makeItem(vecI(x, y));
			needsSort = true;
		}
	}
}

void State::onMouseUp(int x, int y)
{
	toolWin.clickDragging = false;
	for (auto& e : mapEntities) {
		e.clickedOn = false;
	}
}

void State::onKeyPress(Keyboard::Key k)
{
	switch(k) {
		case Keyboard::Escape:
			gw->close();
			break;
		case Keyboard::Y:
			makeMap();
			break;
		case Keyboard::A:
			for (auto& se : selectedEnts)
				se->layer += (iKP(LShift) ? -1 : 1);
			needsSort = true;
			break;
			
		default:
			break;
	}
}

void State::onKeyRelease(Keyboard::Key k)
{
	
}

void State::update(const Time& time)
{
	if (iKP(LShift) || iKP(RShift)) {
		ikp(Comma) cursorSprite.setRotation(0);
		ikp(Slash) cursorSprite.setScale(1, 1);
		ikp(Backslash) {
			cursorSprite.setScale(cursorSprite.getScale().x,
								  cursorSprite.getScale().y * -1);
			PAUSE;
		}
	}
	else {
		if (iKP(Semicolon)) {
			cursorSprite.setTextureRect(IntRect(0, 0, cursorSprite.getTextureRect().width, cursorSprite.getTextureRect().height + 1));
		}
		if (iKP(P)) {
			cursorSprite.setTextureRect(IntRect(0, 0, cursorSprite.getTextureRect().width, cursorSprite.getTextureRect().height - 1));
		}
		if (iKP(LBracket)) {
			cursorSprite.setTextureRect(IntRect(0, 0, cursorSprite.getTextureRect().width - 1, cursorSprite.getTextureRect().height));
		}
		if (iKP(RBracket)) {
			cursorSprite.setTextureRect(IntRect(0, 0, cursorSprite.getTextureRect().width + 1, cursorSprite.getTextureRect().height));
		}
		ikp(Comma) cursorSprite.rotate(-2);
		ikp(Period) cursorSprite.rotate(2);
		ikp(Slash) cursorSprite.setScale(cursorSprite.getScale().x - .02,
										 cursorSprite.getScale().y - .02);
		ikp(Apostrophe) cursorSprite.setScale(cursorSprite.getScale().x + .02,
											  cursorSprite.getScale().y + .02);
		ikp(Backslash) {
			cursorSprite.setScale(cursorSprite.getScale().x * -1,
												  cursorSprite.getScale().y);
			PAUSE;
		}
	}
	auto mouseDif = vecf(mx, my) - vecf(mxOld, myOld);
	if (toolWin.clickDragging) {
		toolWin.move(mouseDif);
	}
	
	cursorSprite.sP(mx, my);

	for (auto& e : mapEntities) {
		if (e.clickedOn) {
			for (auto& se : selectedEnts)
				se->move(mouseDif);
		}
	}
	
	debugTxt.setString(curTool + " " + tS(selectedEnts.size()));
	mouseTxt.setString(tS(mx) + ", " + tS(my));
} // end update


void State::deselectAll()
{
	for (auto& se : selectedEnts) {
		se->isSelected = false;
		se->setColor(Color::White);
	}
	selectedEnts.clear();
}

			
void State::debugTxtSetup() {

	if (!font.loadFromFile((Resources::executingDir() / "resources" / "fonts" / "Monaco.ttf").string()))
		cerr << "Couldn't load font";
	mouseTxt = Text("", font, 13);
	mouseTxt.sP(8, 8);
	mouseTxt.setFillColor(Color::Blue);
	
	debugTxt = Text("", font, 13);
	debugTxt.sP(8, 25);
	debugTxt.setFillColor(Color::Blue);
}

void State::loadTextures() {
	
//	string basePath = "resources/";
//	
//		// tximgs that aren't map items?
//	Texture tex;
//	forNum (int(mapItemImgList.size())) {
//		string fileName = mapItemImgList[i];
//		string filePath = basePath + fileName;
//		string key = stripExtension(fileName);
//		if (!tex.loadFromFile(filePath))
//			cerr << "Couldn't load texture";
//		else txMap.insert({key, tex});
//	}
}

void State::loadItemButtons() {

	string basePath = (Resources::executingDir() / "resources" / "images" / "").string();
	Texture tex;
	forNum (int(mapItemImgList.size())) {
		string fileName = mapItemImgList[i];
		string filePath = basePath + fileName;
		string key = stripExtension(fileName);
		if (!tex.loadFromFile(filePath))
			cerr << "Couldn't load texture";
		else {
			tex.setRepeated(true);
			txMap.insert({key, tex});
		}
		ToolButton tb {txMap[key]};
		tb.setTextureRect(IntRect(0, 0, tb.getTextureRect().width, min(tb.getTextureRect().height, 32)));
		tb.sP(toolWin.totalRect.gP().x + 3,
			  toolWin.totalRect.gP().y + 23 + toolWin.selectButton.getSize().y + i * toolWin.spacing);
		tb.highlight.sP(tb.gP());
		// make second column if exceeding a height
		tb.posDifFromToolbar = tb.gP() - toolWin.totalRect.gP();
		tb.key = key;
		toolWin.toolButtons.insert({key, tb});
	}
}

const vector<string>  State::mapItemImgList {
	"longbrick.png",
	"longplat.png",
	"longgrass.png",
	"midlogplat.png",
	"midplat.png",
	"shortgrass.png",
	"shortbrick.png",
	"shortplat.png",
	"shortlogplat.png",
	"ornatebracket.png",
	"curvingwood.png",
	"doublecurvingwood.png",
	"woodcorbel.png",
	"thickpost.png",
	"thinpost.png",
	"stump.png",
	"oxyd.png",
	
	};
