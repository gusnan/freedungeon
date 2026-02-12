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

#include "DungeonData.h"



/**
 *
 */
DungeonData &DungeonData::instance()
{
   static DungeonData instance;
   return instance;
}


/**
 *
 */
DungeonData::DungeonData() :
               floorBitmap(std::make_shared<Bitmap>("nonfree/0075.IMG1 [Dungeon Graphics - Floor].png")),
               ceilingBitmap(std::make_shared<Bitmap>("nonfree/0076.IMG1 [Dungeon Graphics - Ceiling].png")),
/*
               leftWall0(std::make_shared<Bitmap>("agraphics/0085.IMG1 [Dungeon Graphics - Wall (Left Side 0)].png")),
               rightWall0(std::make_shared<Bitmap>("agraphics/0084.IMG1 [Dungeon Graphics - Wall (Right Side 0)].png")),
               frontAndSides1(std::make_shared<Bitmap>("agraphics/0086.IMG1 [Dungeon Graphics - Wall (Front and Sides 1)].png")),
               frontAndSides2(std::make_shared<Bitmap>("agraphics/0087.IMG1 [Dungeon Graphics - Wall (Front and Sides 2)].png")),
               frontAndSides3(std::make_shared<Bitmap>("agraphics/0088.IMG1 [Dungeon Graphics - Wall (Front and Sides 3)].png")),
*/
               farLeftSide3(std::make_shared<Bitmap>("nonfree/0089.IMG1 [Dungeon Graphics - Wall (Far Left Side 3)].png")),
               // range3_new(std::make_shared<Bitmap>("nonfree/range3_new.png")),
               dung_1f(std::make_shared<Bitmap>("nonfree/1f_hi.png")),
               dung_2f(std::make_shared<Bitmap>("nonfree/2f_hi.png")),
               dung_3f(std::make_shared<Bitmap>("nonfree/3f_hi.png")),
               dung_sideWalls(std::make_shared<Bitmap>("nonfree/sidewalls_hi.png"))
               //farRightSide3(nullptr)

{
      
   // floorBitmap = std::make_shared<Bitmap>("agraphics/0075.IMG1 [Dungeon Graphics - Floor].png");
   
   /*
   ceilingBitmap = std::make_shared<Bitmap>("agraphics/0076.IMG1 [Dungeon Graphics - Ceiling].png");
   leftWall0 = std::make_shared<Bitmap>("agraphics/0085.IMG1 [Dungeon Graphics - Wall (Left Side 0)].png");
   
   rightWall0 = std::make_shared<Bitmap>("agraphics/0084.IMG1 [Dungeon Graphics - Wall (Right Side 0)].png");

   frontAndSides1 = std::make_shared<Bitmap>("agraphics/0086.IMG1 [Dungeon Graphics - Wall (Front and Sides 1)].png");

   frontAndSides2 = std::make_shared<Bitmap>("agraphics/0087.IMG1 [Dungeon Graphics - Wall (Front and Sides 2)].png");
   frontAndSides3 = std::make_shared<Bitmap>("agraphics/0088.IMG1 [Dungeon Graphics - Wall (Front and Sides 3)].png");

   
   farLeftSide3 = std::make_shared<Bitmap>("agraphics/0089.IMG1 [Dungeon Graphics - Wall (Far Left Side 3)].png");
   
   */
   // farRightSide3 = std::make_shared<Bitmap>("agraphics/0089.IMG1 [Dungeon Graphics - Wall (Far Right Side 3)].png");
   /*
   frontAndSides
   4,0,28, 111
   
   224,0, 28, 111
   
   32, 0, 192, 111
   */
   
}


/**
 *
 */
DungeonData::~DungeonData()
{
   doneDungeonData();
}


/**
 *
 */
void DungeonData::doneDungeonData()
{
   floorBitmap.reset();
   ceilingBitmap.reset();
   
   /*
   leftWall0.reset();
   rightWall0.reset();
   
   frontAndSides1.reset();
   frontAndSides2.reset();
   frontAndSides3.reset();
   */
   
   farLeftSide3.reset();
   
   // range3_new.reset();
   
   
   dung_1f.reset();
   dung_2f.reset();
   dung_3f.reset();
   dung_sideWalls.reset();
}
