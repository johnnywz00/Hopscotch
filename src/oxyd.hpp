//
//  oxyd.hpp
//  Hopscotch
//
//  Created by John Ziegler on 2/23/26.
//  Copyright © 2026 John Ziegler. All rights reserved.
//

#ifndef oxyd_hpp
#define oxyd_hpp

#include "hopscotch.hpp"


struct Oxyd: public ZSprite
{
	static constexpr int 	openingFrames = 80;
	
	void initTxs (Texture& oxtx, Texture& covtx, Texture& symtx);
	
	void initPos (vecF& p);
	
	void reset ();
	
	void makeOpen (bool op);
	
	void update ();
	
	void animateSymbol ();
	
	void checkOpenCover ();
	
	void checkCloseCover ();
	
	void draw (RenderTarget& target, RenderStates states) const;
	
	Sprite 		            symbol
							, cover
	;
	Texture* 	            myPicture;
	float 		            symbolScaleDegree = 0;
	int 		            openingFrmCt = 0;
	int 		            closingFrmCt = 0;
	bool 		            matched = false;
	bool 		            isOpen = false;
};

#endif /* oxyd_hpp */
