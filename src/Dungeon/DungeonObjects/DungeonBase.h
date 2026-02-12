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
#ifndef __HEADER_DUNGEON_BASE_BLOCK_
#define __HEADER_DUNGEON_BASE_BLOCK_

/**
 *
 */
class DungeonBase
{
public:
   DungeonBase();
   virtual ~DungeonBase();

   virtual bool getCanWalk();

   virtual void draw1f() = 0;

   virtual void draw1l() = 0;
   virtual void draw1r() = 0;

   virtual void draw1f1l() = 0;
   virtual void draw1f1r() = 0;

   virtual void draw2f1l() = 0;
   virtual void draw2f1r() = 0;

   virtual void draw2f() = 0;

   virtual void draw3f() = 0;
   virtual void draw3f1r() = 0;
   virtual void draw3f1l() = 0;
   virtual void draw3f2r() = 0;
   virtual void draw3f2l() = 0;


   virtual void drawSmallMap(const Vector2d &position) = 0;

   void setGuiPosition(const Vector2d &inPosition);
   Vector2d getGuiPosition();

protected:
   
   bool m_CanWalk;

   Vector2d m_GuiPosition;
};

#endif /*__HEADER_DUNGEON_BASE_BLOCK_*/
