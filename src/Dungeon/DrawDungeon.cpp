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

#include "Map.h"

#include "DrawDungeon.h"

// #include "../Data.h"

#include "DungeonData.h"

#include "DungeonHandler.h"

#include "../Data.h"





/**
 *
 */
DrawDungeon &DrawDungeon::instance()
{
   static DrawDungeon instance;
   return instance;
}


/**
 *
 */
DrawDungeon::DrawDungeon() : m_StepCounter(0), m_FlipDirection(FlipNone)
{
   LOG("DrawDungeon constructor");
}


/**
 *
 */
DrawDungeon::~DrawDungeon()
{
   doneDrawDungeon();
}


/**
 *
 */
void DrawDungeon::initDrawDungeon()
{
   LOG("initDrawDungeon");
}


/**
 *
 */
void DrawDungeon::doneDrawDungeon()
{
   LOG("doneDrawDungeon");
}



/**
 *
 */
void DrawDungeon::draw(const Vector2d &pos)
{
   FlipDirection flip = FlipNone;
   
   if (m_StepCounter % 2) flip = FlipHorizontal;
   
   
   Vector2d mapPos = DungeonHandler::instance().getPosition();
   Vector2d mapDelta = DungeonHandler::instance().getDelta();
   
   // The entire dungeon graphics is 448 * 272    -- previously 224 * 136
   
   if (m_StepCounter % 2) {
      DungeonData::instance().ceilingBitmap->blit(Rect(0,0, 224, 136), Rect(pos + Vector2d(0, 0), Vector2d(448, 272)), 1.0f);
      DungeonData::instance().floorBitmap->blit(Rect(Vector2d(0, 0), Vector2d(224, 70)), Rect(pos + Vector2d(0, 272 - 140), Vector2d(448, 140)), FlipNone);
   } else {
      DungeonData::instance().ceilingBitmap->blit(Rect(0,0, 224, 136), Rect(pos + Vector2d(0, 0), Vector2d(448, 272)), FlipHorizontal);
      DungeonData::instance().floorBitmap->blit(Rect(Vector2d(0, 0), Vector2d(224, 70)), Rect(pos + Vector2d(0, 272 - 140), Vector2d(448, 140)), FlipHorizontal);
   }
   
   
   int dx = mapDelta.x;
   int dy = mapDelta.y;
   Vector2d leftDelta = Vector2d(dy, -dx);
   Vector2d rightDelta = Vector2d(-dy, dx);
   
   std::shared_ptr<DungeonBase> dung_3f2l = DungeonHandler::instance().getMap()->getMap(mapPos + mapDelta * 3 + leftDelta * 2);
   dung_3f2l->draw3f2l();
   
   std::shared_ptr<DungeonBase> dung_3f2r = DungeonHandler::instance().getMap()->getMap(mapPos + mapDelta * 3 + rightDelta * 2);
   dung_3f2r->draw3f2r();
      
   std::shared_ptr<DungeonBase> dung_3f1l = DungeonHandler::instance().getMap()->getMap(mapPos + mapDelta * 3 + leftDelta);
   dung_3f1l->draw3f1l();
   
   std::shared_ptr<DungeonBase> dung_3f1r = DungeonHandler::instance().getMap()->getMap(mapPos + mapDelta * 3 + rightDelta);
   dung_3f1r->draw3f1r();
   
   std::shared_ptr<DungeonBase> dung_3f = DungeonHandler::instance().getMap()->getMap(mapPos + mapDelta * 3);
   dung_3f->draw3f();
   
   /*
   frontAndSides
   4,0,28, 111
   
   224,0, 28, 111
   
   32, 0, 192, 111
   */
   
   // wall 2f_1l
   std::shared_ptr<DungeonBase> dung_2f1l = DungeonHandler::instance().getMap()->getMap(mapPos + mapDelta * 2 + leftDelta);
   dung_2f1l->draw2f1l();
   
   // wall 2f_1r
   std::shared_ptr<DungeonBase> dung_2f1r = DungeonHandler::instance().getMap()->getMap(mapPos + mapDelta * 2 + rightDelta);
   dung_2f1r->draw2f1r();
   
   // wall 2f
   std::shared_ptr<DungeonBase> dung_2f = DungeonHandler::instance().getMap()->getMap(mapPos + mapDelta * 2);
   dung_2f->draw2f();
   
   
   
   
   // wall 1f_1l
   std::shared_ptr<DungeonBase> dung_1f1l = DungeonHandler::instance().getMap()->getMap(mapPos + mapDelta + leftDelta);
   dung_1f1l->draw1f1l();
   
   
   
   
   
   /*
         1f1r
   */
   
   std::shared_ptr<DungeonBase> dung_1f1r = DungeonHandler::instance().getMap()->getMap(mapPos + mapDelta + rightDelta);
   dung_1f1r->draw1f1r();
   
   
   
   /*
     1r
   */
   std::shared_ptr<DungeonBase> dung_1r = DungeonHandler::instance().getMap()->getMap(mapPos + rightDelta);
   dung_1r->draw1r();


   std::shared_ptr<DungeonBase> dung_1l = DungeonHandler::instance().getMap()->getMap(mapPos + leftDelta);
   dung_1l->draw1l();
   /*
   // wall 1l
   if (m_StepCounter % 2) {
      DungeonData::instance().leftWall->blit(pos);
   } else {
      DungeonData::instance().rightWall->blitFlipped(pos + Vector2d(0, 0), FlipHorizontal);
   }
   */


   // 1f
   std::shared_ptr<DungeonBase> dung = DungeonHandler::instance().getMap()->getMap(mapPos + mapDelta);
   dung->draw1f();
   // DungeonData::instance().frontAndSides->blit(Rect(48, 0, 192 - 30, 111), pos + Vector2d(31, 9), flip);


}


/**
 *
 */
void DrawDungeon::increaseStepCounter()
{
   m_StepCounter++;
   
   m_FlipDirection = FlipNone;
   
   if (m_StepCounter % 2) m_FlipDirection = FlipHorizontal;
}   


/**
 *
 */
FlipDirection DrawDungeon::getFlip()
{
   return m_FlipDirection;
}


/**
 *
 */
int DrawDungeon::getStepCounter()
{
   return m_StepCounter;
}
