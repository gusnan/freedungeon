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


#include "DungeonHandler.h"

#include "DrawDungeon.h"





/**
 *
 */
DungeonHandler &DungeonHandler::instance()
{
   static DungeonHandler instance;
   return instance;
}


/**
 *
 */
DungeonHandler::DungeonHandler() : m_Position(0, 0),
                                   m_Rotate(0),
                                   m_Map(nullptr),
                                   m_Delta(0, 0),
                                   m_RightDelta(0, 0),
                                   m_LeftDelta(0, 0),
                                   dungeonWall(nullptr)
{
   LOG("DungeonHandler constructor");
   initDungeonHandler();
}


/**
 *
 */
DungeonHandler::~DungeonHandler()
{
   doneDungeonHandler();
}


/**
 *
 */
void DungeonHandler::initDungeonHandler()
{
   if (m_Map == nullptr) {
      LOG("-- initDungeonHandler");
   
      m_Map = std::make_shared<Map>();
      dungeonWall = std::make_shared<DungeonWall>();
      dungeonWall->setGuiPosition(Vector2d(0, 64));
      
      updateDelta();
         
   }
}


/**
 *
 */
void DungeonHandler::doneDungeonHandler()
{
   LOG(" -- doneDungeonHandler");
   
   dungeonWall.reset();
   m_Map.reset();
}



/**
 *
 */
void DungeonHandler::moveForward()
{
   LOG("Move Forward");
   
   Vector2d newPos = m_Position + m_Delta;
   
   std::shared_ptr<DungeonBase> map = m_Map->getMap(newPos);
   
   if (map != nullptr) {
      if (map->getCanWalk()) {
         m_Position = newPos;
         DrawDungeon::instance().increaseStepCounter();
      }
   } else {
      m_Position = newPos;
      DrawDungeon::instance().increaseStepCounter();
   }
}


/**
 *
 */
void DungeonHandler::moveBack()
{
   LOG("Move back");
   
   Vector2d newPos = m_Position - m_Delta;
   
   std::shared_ptr<DungeonBase> map = m_Map->getMap(newPos);
   
   if (map != nullptr) {
      if (map->getCanWalk()) {
         m_Position = newPos;
         DrawDungeon::instance().increaseStepCounter();
      }
   } else {
      m_Position = newPos;
      DrawDungeon::instance().increaseStepCounter();
   }
}


/**
 *
 */
void DungeonHandler::moveRight()
{
   LOG("Move Right");
  
   Vector2d newPos = m_Position + m_RightDelta;
   
   std::shared_ptr<DungeonBase> map = m_Map->getMap(newPos);
   
   if (map != nullptr) {
      if (map->getCanWalk()) {
         m_Position = newPos;
         DrawDungeon::instance().increaseStepCounter();
      }
   } else {
      m_Position = newPos;
      DrawDungeon::instance().increaseStepCounter();
   }
   
}


/**
 *
 */
void DungeonHandler::moveLeft()
{
   LOG("Move Left");
   Vector2d newPos = m_Position + m_LeftDelta;
   
   std::shared_ptr<DungeonBase> map = m_Map->getMap(newPos);
   
   if (map != nullptr) {
      if (map->getCanWalk()) {
         m_Position = newPos;
         DrawDungeon::instance().increaseStepCounter();
      }
   } else {
      m_Position = newPos;
      DrawDungeon::instance().increaseStepCounter();
   }
      
}


/**
 *
 */
void DungeonHandler::rotateLeft()
{
   m_Rotate--;
   if (m_Rotate < 0) m_Rotate = 3;
   
   DrawDungeon::instance().increaseStepCounter();
   
   updateDelta();

   std::stringstream st;
   st << "Rotate Left: " << m_Rotate;
   STLOG(st);
}


/**
 *
 */
void DungeonHandler::rotateRight()
{
   m_Rotate++;
   m_Rotate = m_Rotate % 4;
   
   DrawDungeon::instance().increaseStepCounter();
   
   updateDelta();
   
   std::stringstream st;
   st << "Rotate Right: " << m_Rotate;
   STLOG(st);
}


/**
 *
 */
void DungeonHandler::updateDelta()
{
   switch (m_Rotate) {
      case 0:
         m_Delta = Vector2d(0, -1);
         break;
      case 1:
         m_Delta = Vector2d(1, 0);
         break;
      case 2:
         m_Delta = Vector2d(0, 1);
         break;
      case 3:
         m_Delta = Vector2d(-1, 0);
         break;
   }
   
   int dx = m_Delta.x;
   int dy = m_Delta.y;
   m_LeftDelta = Vector2d(dy, -dx);
   m_RightDelta = Vector2d(-dy, dx);

}


/*
 *
 */
int DungeonHandler::getRotate()
{
   return m_Rotate;
}



/*
 *
 */
Vector2d DungeonHandler::getDelta()
{
   return m_Delta;
}


/**
 *
 */
Vector2d DungeonHandler::getPosition()
{
   return m_Position;
}


/**
 *
 */
std::shared_ptr<Map> DungeonHandler::getMap()
{
   return m_Map;
}
