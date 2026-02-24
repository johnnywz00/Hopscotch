
#ifndef edclasses_h
#define edclasses_h

#include "zsprite.hpp"
#include "resourcemanager.hpp"

class MapEntity: public ZSprite {
public:
    
	string			key;
	int				layer = 100;
	bool			isSelected = false;
};



class ToolButton : public ZSprite {
public:
	
	ToolButton () {}
	ToolButton (const Texture& tx) {
		
		s.setTexture(tx);
		highlight.setSize(vecf(s.gLB().width, min(s.gLB().height, 32.f)));
		highlight.setFillColor(Color(0, 0, 0, 60));
	}

	
	RectangleShape		highlight;
	bool				isSelected = false;
	string				key;
	vecf 				posDifFromToolbar;
};


class ToolWindow {
public:
	
	ToolWindow (const vecf& size)
	{
		totalRect.setOutlineThickness(2);
		totalRect.setOutlineColor(Color(DKORANGE));
		totalRect.setFillColor(Color(255, 127, 0, 100));
		totalRect.setSize(size);
		
		selectButton.setSize(vecf(totalRect.getSize().x - 6, 20));
		selectButton.setOutlineColor(DKORANGE75);
		selectButton.setOutlineThickness(2);
		selectButton.setFillColor(addRed(Color::Yellow, 35));
		positionSelectButton();
	}
	
	void move (const vecf& moveDif)
	{
		totalRect.move(moveDif);
		positionSelectButton();
		for (auto& btn : toolButtons) {
			btn.second.sP(totalRect.gP() + btn.second.posDifFromToolbar);
			btn.second.highlight.sP(btn.second.gP());
		}
	}
	
	void positionSelectButton () {
		selectButton.sP(totalRect.gP() + vecf(3, 20));
	}
	
	RectangleShape				totalRect;
	RectangleShape				selectButton;
	map<string, ToolButton>			toolButtons;
	
	float			spacing = 35;
	bool			isActive = true
					, clickDragging = false
	;
	
};



#endif /* edclasses_h */
