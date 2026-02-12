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
#ifndef __HEADER_DUNGEON_DATA_
#define __HEADER_DUNGEON_DATA_

/**
 *
 */
class DungeonData
{
public:
   
   static DungeonData &instance();

   void doneDungeonData();


   std::shared_ptr<Bitmap> floorBitmap;
   std::shared_ptr<Bitmap> ceilingBitmap;

/*
   std::shared_ptr<Bitmap> leftWall0;
   std::shared_ptr<Bitmap> rightWall0;

   std::shared_ptr<Bitmap> frontAndSides1;
   std::shared_ptr<Bitmap> frontAndSides2;
   std::shared_ptr<Bitmap> frontAndSides3;
*/

   // std::shared_ptr<Bitmap> farRightSide3;
   std::shared_ptr<Bitmap> farLeftSide3;

   // std::shared_ptr<Bitmap> range3_new;

   std::shared_ptr<Bitmap> dung_1f;
   std::shared_ptr<Bitmap> dung_2f;
   std::shared_ptr<Bitmap> dung_3f;
   
   std::shared_ptr<Bitmap> dung_sideWalls;
   

protected:
   
   DungeonData();
   virtual ~DungeonData();

private:
   
};

#endif
