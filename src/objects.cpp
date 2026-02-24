//
//  objects.cpp
//  Hopscotch
//
//  Created by John Ziegler on 10/29/24.
//  Copyright © 2024 John Ziegler. All rights reserved.
//

#include "hopscotch.hpp"

FloatRect Stump::hitBox ()
{
    FloatRect gb = gGB();
    return FloatRect(gb.left + 12, gb.top, gb.width - 28, gb.height - 18);
}



