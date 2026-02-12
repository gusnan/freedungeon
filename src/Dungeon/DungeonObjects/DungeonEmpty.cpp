/**
 *
 *	This file is part of FreeDungeon.
 *	Copyright 2019-2026 Andreas Rönnquist
 *
 *	FreeDungeon is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU Lesser General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	FreeDungeon is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU Lesser General Public License for more details.
 *
 *	You should have received a copy of the GNU Lesser General Public License
 *	along with FreeDungeon.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include <memory>

#include "GusGame/GusGame.h"

#include "GusGame/EventLib.h"
#include "GusGame/EventSystem.h"

using namespace Gus;

using namespace LogLib;
using namespace ExceptionLib;
using namespace GraphicsLib;
using namespace EventLib;

#include "DungeonEmpty.h"

#include "../../Data.h"


/**
 *
 */
DungeonEmpty::DungeonEmpty()
{
}


/**
 *
 */
DungeonEmpty::~DungeonEmpty()
{
}



void DungeonEmpty::draw1f()
{
}


/**
 *
 */
void DungeonEmpty::draw1l()
{
}


/**
 *
 */
void DungeonEmpty::draw1r()
{
}


/**
 *
 */
void DungeonEmpty::draw1f1l()
{
}


/**
 *
 */
void DungeonEmpty::draw1f1r()
{
}


/**
 *
 */
void DungeonEmpty::draw2f1l()
{
}


/**
 *
 */
void DungeonEmpty::draw2f1r()
{
}


/**
 *
 */
void DungeonEmpty::draw2f()
{
}



/**
 *
 */
void DungeonEmpty::draw3f()
{
}


/**
 *
 */
void DungeonEmpty::draw3f1r()
{
}


/**
 *
 */

void DungeonEmpty::draw3f1l()
{
}


/**
 *
 */
void DungeonEmpty::draw3f2r()
{
}


/**
 *
 */
void DungeonEmpty::draw3f2l()
{
}


/**
 *
 */
bool DungeonEmpty::getCanWalk()
{
   return true;
}


/**
 *
 */
void DungeonEmpty::drawSmallMap(const Vector2d &position)
{
   Rect wallSourceRect = Rect(11, 11, 11, 11);

   Data::instance().smallMapBitmap->blit(wallSourceRect, position);

}
