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
#ifndef __HEADER_DUNGEON_WALL_
#define __HEADER_DUNGEON_WALL_

#include "DungeonBase.h"

/**
 *
 */
class DungeonWall : public DungeonBase
{
public:
   DungeonWall();
   virtual ~DungeonWall() override;

   virtual void draw1f() override;

   virtual void draw1l() override;
   virtual void draw1r() override;

   virtual void draw1f1l() override;
   virtual void draw1f1r() override;

   virtual void draw2f1l() override;
   virtual void draw2f1r() override;

   virtual void draw2f() override;

   virtual void draw3f() override;
   virtual void draw3f1r() override;
   virtual void draw3f1l() override;
   virtual void draw3f2r() override;
   virtual void draw3f2l() override;

   virtual bool getCanWalk() override;


   void drawSmallMap(const Vector2d &position) override;
protected:
   
};

#endif /*__HEADER_DUNGEON_WALL_*/

