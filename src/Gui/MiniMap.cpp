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

#include "../Data.h"

#include "MiniMap.h"

#include "../Dungeon/DungeonObjects/DungeonBase.h"
#include "../Dungeon/DungeonObjects/DungeonWall.h"

#include "../Dungeon/Map.h"
#include "../Dungeon/DungeonHandler.h"


/**
 *
 */
MiniMap::MiniMap() : Panel(Rect(0, 32, 224, 136).getRectCenterOf(Vector2d(100, 100)), "MiniMap"), m_MiniMapVisible(false)
{
}


/**
 *
 */
MiniMap::~MiniMap()
{
}


/**
 *
 */
void MiniMap::draw(const Vector2d &pos, float opacity) 
{
   
   if (getVisible() && m_MiniMapVisible) {
      // Data::instance().mainMenuScreen->blit(pos + Vector2d(0,0));
      // Draw a white outline on the panel
      Rect newRect = getRect() + pos;
      
      
      
      Rect wallSourceRect = Rect(11, 11, 11, 11);
         
      std::shared_ptr<Map> map = DungeonHandler::instance().getMap();
      
      for (int xco = 0; xco < 9; xco++)
      for (int yco = 0; yco < 9; yco++) {
         Vector2d coPos = Vector2d(xco, yco);
         Vector2d newPos = coPos + DungeonHandler::instance().getPosition() - Vector2d(4, 4);
         
         if (!((newPos.x < -1) || (newPos.y < -1) || (newPos.x > map->getSize().x ) || (newPos.y > map->getSize().y))) {
         
            std::shared_ptr<DungeonBase> tempDungeon = map->getMap(newPos);
            tempDungeon->drawSmallMap(newRect.position + coPos * Vector2d(11, 11));

         } else {
            Rect wallSourceRect = Rect(22, 11, 11, 11);
            Data::instance().smallMapBitmap->blit(wallSourceRect, newRect.position + coPos * Vector2d(11, 11));
         }
      }

      // Data::instance().mainMenuLeftDoor->blit(pos + Vector2d(0,32));
      // Data::instance().mainMenuRightDoor->blit(pos + Vector2d(104,32));

      Primitives::rect(newRect, colorWhite);
      
      int rotate = DungeonHandler::instance().getRotate();
      
      Vector2d delta = DungeonHandler::instance().getDelta();
      
      Vector2d playerPos = Vector2d(4, 4); // = DungeonHandler::instance().getPosition();
      
      Vector2d playerPosMul = playerPos * Vector2d(11, 11);
      
      int dx = delta.x;
      int dy = delta.y;
      
      Vector2d leftDelta = Vector2d(dy, -dx);
      Vector2d rightDelta = Vector2d(-dy, dx);
      
      Rect mapSourceRect = Rect(rotate * 11, 0, 11, 11);
      
      Data::instance().smallMapBitmap->blit(mapSourceRect, newRect.position + playerPosMul);
      // Data::instance().smallMapBitmap->blit(mapSourceRect, newRect.position + playerPosMul + delta * Vector2d(10, 10));
      
      // 1 Vänster, och nästa 2 vänster
      // Data::instance().smallMapBitmap->blit(mapSourceRect, newRect.position + playerPosMul + (delta * 0 + leftDelta ) * Vector2d(10, 10));
      // Data::instance().smallMapBitmap->blit(mapSourceRect, newRect.position + playerPosMul + (delta * 0 + leftDelta * 2) * Vector2d(10, 10));

      // 2 fram 1 Höger
      // Data::instance().smallMapBitmap->blit(mapSourceRect, newRect.position + playerPosMul + (delta * 2 + rightDelta) * Vector2d(10, 10));
      

      // Make the Panel class which we inherit from draw the gui objects
      Panel::draw(pos, opacity);
   }
}


/**
 * This method is required in addition to the get/setVisible that every
 * GuiObjcet has, since the minimap should be visible or invislbe only
 * on the "dungeon" view, and always invisible on inventory view.
 */
void MiniMap::setMiniMapVisible(bool inVisible)
{
   m_MiniMapVisible = inVisible;
}



/**
 * See description of setMiniMapVisible method, same applies here, of course
 */
void MiniMap::switchMiniMapVisible()
{
   m_MiniMapVisible = !m_MiniMapVisible;
}