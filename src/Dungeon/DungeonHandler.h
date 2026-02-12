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
#ifndef __HEADER_DUNGEON_HANDLER_
#define __HEADER_DUNGEON_HANDLER_


/**
 *
 */
class DungeonHandler
{
public:

   static DungeonHandler &instance();

   void initDungeonHandler();
   void doneDungeonHandler();

   void moveForward();
   void moveBack();

   void moveRight();
   void moveLeft();

   void rotateLeft();
   void rotateRight();

   int getRotate();
   Vector2d getDelta();

   Vector2d getPosition();

   std::shared_ptr<DungeonWall> dungeonWall;
   
   std::shared_ptr<Map> getMap();

protected:
   DungeonHandler();
   virtual ~DungeonHandler();

private:
   
   // std::shared_ptr<GameModeInventory> gameModeInventory;

   void updateDelta();

   Vector2d m_Position;
   int m_Rotate;

   Vector2d m_Delta;

   Vector2d m_LeftDelta;
   Vector2d m_RightDelta;

   std::shared_ptr<Map> m_Map;

};

#endif /*__HEADER_DUNGEON_HANDLER_*/
