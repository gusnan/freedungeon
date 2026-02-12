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


#include "Item.h"

#include "ItemHandler.h"


/**
 *
 */
Item::Item() : m_Name(),
               m_SmallImage(-1)
{
}


/**
 *
 */
Item::~Item()
{
}


/**
 *
 */
Item::Item(const Item &item) : 
                                 m_Name(item.m_Name),
                                 m_SmallImage(item.m_SmallImage)
{
   
}


/**
 *
 */
void Item::setName(const std::string &inName)
{
   m_Name = inName;
}


/**
 *
 */
const std::string &Item::getName()
{
   return m_Name;
}


/**
 *
 */
void Item::draw(const Vector2d &pos)
{
   
/*   
         Rect sourceRect = Rect(sourceX * 32, sourceY * 29, 32, 29); 
         
         Data::instance().championPortraits->blit(sourceRect, newRect.position + Vector2d(6, 0)); 
*/
   
   ItemHandler::instance().drawSmallImage(pos, m_SmallImage);
}


/**
 *
 */
void Item::setSmallImage(int inSmallImage)
{
   m_SmallImage = inSmallImage;
}


/**
 *
 */
int Item::getSmallImage()
{
   return m_SmallImage;
}


/**
 *
 */
std::shared_ptr<Item> Item::makeCopy() const
{
   return std::shared_ptr<Item>(cloneImplementation());;
}

