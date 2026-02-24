//
//  oxyd.cpp
//  Hopscotch
//
//  Created by John Ziegler on 2/23/26.
//  Copyright © 2026 John Ziegler. All rights reserved.
//

#include "hopscotch.hpp"

void Oxyd::initTxs (Texture& oxtx, Texture& covtx, Texture& symtx)
{	
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

void Oxyd::makeOpen (bool op)
{
	isOpen = op;
	if (op)
		openingFrmCt = 1;
	else closingFrmCt = 1;
}

void Oxyd::update ()
{
	if (isOpen) {
		checkOpenCover();
		if (!matched)
			animateSymbol();
	}
	else checkCloseCover();
}

void Oxyd::animateSymbol ()
{
	float curCos = cos(toRad(symbolScaleDegree));
	float sfac = curCos * .09 + .91;
	symbol.setScale(sfac, sfac);
	symbol.sRot(curCos * -2.5 + 2.5);
	symbolScaleDegree += 6;
	if (symbolScaleDegree >= 360)
		symbolScaleDegree -= 360;
}

void Oxyd::checkOpenCover ()
{
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

void Oxyd::checkCloseCover ()
{
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

void Oxyd::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(symbol);
	ZSprite::draw(target, states);
	target.draw(cover);
}

