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

#include "DungeonWall.h"

#include "../../Data.h"

#include "../DungeonData.h"

#include "../DrawDungeon.h"


/**
 *
 */
DungeonWall::DungeonWall()
{
   setGuiPosition(Vector2d(0, 64));
}


/**
 *
 */
DungeonWall::~DungeonWall()
{
}



/**
 *
 */
void DungeonWall::draw1f()
{
   Vector2d pos = getGuiPosition();
   
   FlipDirection flip = DrawDungeon::instance().getFlip();
   
   if (DrawDungeon::instance().getStepCounter() % 2) {
      DungeonData::instance().dung_1f->blit(Rect(64, 0, 320, 272), pos + Vector2d(64, 0));
   } else {
      DungeonData::instance().dung_1f->blit(Rect(64, 0, 320, 272), pos + Vector2d(64, 0), FlipHorizontal);
   }
}


/**
 *
 */
void DungeonWall::draw1l()
{
   Vector2d pos = getGuiPosition();
   
   // FlipDirection flip = DrawDungeon::instance().getFlip();
   
   // wall 1l
   if (DrawDungeon::instance().getStepCounter() % 2) {
      
      DungeonData::instance().dung_sideWalls->blit(Rect(0, 0, 64, 272), pos + Vector2d(0, 0));
      
   } else {
      
      DungeonData::instance().dung_sideWalls->blit(Rect(384, 0, 64, 272), pos + Vector2d(0, 0), FlipHorizontal);
   }

   
}


/**
 *
 */
void DungeonWall::draw1r()
{
   Vector2d pos = getGuiPosition();
   FlipDirection flip = DrawDungeon::instance().getFlip();
   
   if (DrawDungeon::instance().getStepCounter() % 2) {
      DungeonData::instance().dung_sideWalls->blit(Rect(0, 0, 66, 272), pos + Vector2d(382, 0), FlipHorizontal);
      
   } else {
      DungeonData::instance().dung_sideWalls->blit(Rect(382, 0, 66, 272), pos + Vector2d(382, 0));
   }
}


/**
 *
 */
void DungeonWall::draw1f1l()
{
   Vector2d pos = getGuiPosition();

   FlipDirection flip = DrawDungeon::instance().getFlip();

   if (DrawDungeon::instance().getStepCounter() % 2) {
     
      DungeonData::instance().dung_1f->blit(Rect(384, 16, 64, 234), pos + Vector2d(0, 16), FlipHorizontal);
      DungeonData::instance().dung_sideWalls->blit(Rect(326, 16, 58, 234), pos + Vector2d(64 , 16), FlipHorizontal);
      
   }
   else {
      // KLAR
      
      DungeonData::instance().dung_1f->blit(Rect(0, 16, 64, 234), pos + Vector2d(0, 16));
      DungeonData::instance().dung_sideWalls->blit(Rect(64, 16, 58, 234), pos + Vector2d(64, 16));
   }
} 


/**
 *
 */
void DungeonWall::draw1f1r()
{
   Vector2d pos = getGuiPosition();
   FlipDirection flip = DrawDungeon::instance().getFlip();
   
   if (DrawDungeon::instance().getStepCounter() % 2) {
      DungeonData::instance().dung_sideWalls->blit(Rect(326, 16, 60, 234), pos+Vector2d(326, 16));
      DungeonData::instance().dung_1f->blit(Rect(0, 16, 64 , 234), pos + Vector2d(384, 16), FlipHorizontal);
       
   } else {
      DungeonData::instance().dung_sideWalls->blit(Rect(62, 16, 60, 234), pos + Vector2d(326  , 16), FlipHorizontal);
      DungeonData::instance().dung_1f->blit(Rect(384, 16, 64 , 234), pos + Vector2d(384, 16));
   } 
}


/**
 *
 */
void DungeonWall::draw2f1l()
{
   Vector2d pos = getGuiPosition();
   FlipDirection flip = DrawDungeon::instance().getFlip();
   
   if (DrawDungeon::instance().getStepCounter() % 2) {
      
      DungeonData::instance().dung_sideWalls->blit(Rect(120, 40, 34, 140), pos + Vector2d(120, 40));
      DungeonData::instance().dung_2f->blit(Rect(0, 40, 120, 142), pos + Vector2d(0, 40));

   } else {
            
      DungeonData::instance().dung_sideWalls->blit(Rect(294, 40, 32, 140), pos + Vector2d(122, 40) , FlipHorizontal);
      DungeonData::instance().dung_2f->blit(Rect(326, 40, 122, 142), pos + Vector2d(0, 40), FlipHorizontal);

   }
}


/**
 *
 */
void DungeonWall::draw2f1r()
{
   Vector2d pos = getGuiPosition();
   FlipDirection flip = DrawDungeon::instance().getFlip();
      
   if (DrawDungeon::instance().getStepCounter() % 2) {
      DungeonData::instance().dung_sideWalls->blit(Rect(294, 40, 34, 140), pos + Vector2d(294, 40));
      DungeonData::instance().dung_2f->blit(Rect(326, 40, 122, 142), pos + Vector2d(326, 40));
      

   } else {
            
      
      DungeonData::instance().dung_sideWalls->blit(Rect(120, 40, 34, 140), pos + Vector2d(294, 40), FlipHorizontal);
      DungeonData::instance().dung_2f->blit(Rect(0, 40, 122, 142), pos + Vector2d(326, 40), FlipHorizontal);

   }
}


/**
 *
 */
void DungeonWall::draw2f()
{
   Vector2d pos = getGuiPosition();

   if (DrawDungeon::instance().getStepCounter() % 2) {
      DungeonData::instance().dung_2f->blit(Rect(120, 40, 206, 142), pos + Vector2d(120, 40));
   } else {
      
      DungeonData::instance().dung_2f->blit(Rect(122, 40, 206, 142), pos + Vector2d(120, 40) , FlipHorizontal);
   }
}





/**
 * DONE
 */
void DungeonWall::draw3f()
{
   Vector2d pos = getGuiPosition();
   if (DrawDungeon::instance().getStepCounter() % 2) {
      
      DungeonData::instance().dung_3f->blit(Rect(154, 52, 140, 96), pos + Vector2d(154, 52));
   } else {
      
      DungeonData::instance().dung_3f->blit(Rect(154, 52, 140, 96), pos + Vector2d(154, 52), FlipHorizontal);
   }

}


/**
 * Done
 */
void DungeonWall::draw3f1r()
{
   Vector2d pos = getGuiPosition();

   
   if (DrawDungeon::instance().getStepCounter() % 2) {
      
      // Move to 3f?
      DungeonData::instance().dung_sideWalls->blit(Rect(266 , 52, 28, 96), pos + Vector2d(266, 52));
      
      DungeonData::instance().dung_3f->blit(Rect(294, 52, 140, 96), pos + Vector2d(294, 52), FlipHorizontal);
      
   } else {
      
      DungeonData::instance().dung_sideWalls->blit(Rect(154, 52, 28, 96), pos + Vector2d(266, 52), FlipHorizontal);

      DungeonData::instance().dung_3f->blit(Rect(14, 52, 140, 96), pos + Vector2d(294, 52));
   }
}


/**
 *
 */

void DungeonWall::draw3f1l()
{
   Vector2d pos = getGuiPosition();
   
   if (DrawDungeon::instance().getStepCounter() % 2) {
      DungeonData::instance().dung_sideWalls->blit(Rect(154, 52, 28, 96), pos + Vector2d(154, 52));

      DungeonData::instance().dung_3f->blit(Rect(294, 52, 140, 96), pos + Vector2d(14, 52), FlipHorizontal);
   } else {
      
      DungeonData::instance().dung_sideWalls->blit(Rect(266, 52, 28, 96), pos + Vector2d(154, 52), FlipHorizontal);
      
      DungeonData::instance().dung_3f->blit(Rect(14, 52, 140, 96), pos + Vector2d(14, 52));
   }
}


/**
 *
 */
void DungeonWall::draw3f2r()
{
   Vector2d pos = getGuiPosition();

   DungeonData::instance().farLeftSide3->blit(Rect(0, 0, 32, 58), pos + Vector2d(416 , 50), FlipHorizontal);
   
}


/**
 *
 */
void DungeonWall::draw3f2l()
{
   Vector2d pos = getGuiPosition();

   DungeonData::instance().farLeftSide3->blit(Rect(0, 0, 16, 49), pos + Vector2d(0, 50));
   
   if (DrawDungeon::instance().getStepCounter() % 2) {
      DungeonData::instance().dung_3f->blit(Rect(280, 42, 14, 96), pos + Vector2d(0, 52));

   } else {
      DungeonData::instance().dung_3f->blit(Rect(280, 52, 14, 96), pos + Vector2d(0, 52), FlipHorizontal);
      
      
   }
}

/**
 *
 */
bool DungeonWall::getCanWalk()
{
   return false;
}


/**
 *
 */
void DungeonWall::drawSmallMap(const Vector2d &position)
{
   Rect wallSourceRect = Rect(0, 11, 11, 11);

   Data::instance().smallMapBitmap->blit(wallSourceRect, position );
}
