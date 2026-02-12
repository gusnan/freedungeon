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

#include "GusGui/GusGui.h"

using namespace GusGui;

#include "DungeonObjects/DungeonBase.h"
#include "DungeonObjects/DungeonWall.h"
#include "DungeonObjects/DungeonEmpty.h"

#include "Map.h"

#include "DungeonHandler.h"


/**
 *
 */
Map::Map() : m_Size(Vector2d(5, 5)), m_MapData(nullptr)
{
   LOG(" --- Map constructor...");
   
   setSize(m_Size);
}


/**
 *
 */
Map::Map(const Map &inMap)
{
   LOG(" --- Map copyconstructor");
   
}


/**
 *
 */
Map &Map::operator=(const Map &source)
{
   if (this != &source) {
      
   }
   
   return *this;
}


/**
 *
 */
Map::~Map()
{
   delete[] m_MapData;
}



/**
 *
 */
void Map::setSize(const Vector2d &inSize)
{
   m_Size = inSize;
   
   allocateMap();
}


/**
 *
 */
Vector2d Map::getSize()
{
   return m_Size;
}


/**
 *
 */
std::shared_ptr<DungeonBase> Map::getMap(const Vector2d &inPosition)
{
   if ((inPosition.x < 0) || (inPosition.y < 0) ||
      (inPosition.x >= m_Size.x) || (inPosition.y >= m_Size.y)) {
      return DungeonHandler::instance().dungeonWall;
   }

   return m_MapData[inPosition.y * m_Size.x + inPosition.x];
}


/**
 *
 */
void Map::allocateMap()
{
   m_MapData = new std::shared_ptr<DungeonBase>[m_Size.x * m_Size.y];
   
   for (int xco = 0; xco < m_Size.x; xco++)
   for (int yco = 0; yco < m_Size.y; yco++) {
      m_MapData[yco * m_Size.x + xco] = std::make_shared<DungeonEmpty>();
   }
   
   for (int xco = 2; xco < 5; xco++) {
      m_MapData[3 * m_Size.x + xco] = std::make_shared<DungeonWall>();
   }
   
   m_MapData[3] = std::make_shared<DungeonWall>();
   m_MapData[3 + m_Size.x * 2] = std::make_shared<DungeonWall>();

}
