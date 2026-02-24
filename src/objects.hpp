//
//  objects.hpp
//  Hopscotch
//
//  Created by John Ziegler on 10/29/24.
//  Copyright © 2024 John Ziegler. All rights reserved.
//

#ifndef objects_hpp
#define objects_hpp

#include "hopscotch.hpp"


struct MapItem: public ZSprite
{
	string tag;
	int layer = 100;
	bool isCollidable = true;
};



struct Stump: public MapItem
{
	FloatRect hitBox () override;
};



struct Level
{
	Level () { }
	Level (uint id, uint num, string f, vecF ds = vecF(scrcx, scrcy))
		: levelID(id)
		, numMatches(num)
		, fname(f)
		, dehStart(ds)
	{ }
	
	string 		fname;
	vecF 		dehStart;
	uint 		numMatches;
	uint 		levelID = 0;
	View        vw {{0, 0, 1728, 1117}};
};

#endif /* objects_hpp */
