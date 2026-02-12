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
#ifndef __HEADER_MAP_
#define __HEADER_MAP_

/**
 *
 */
class Map
{
public:
   Map();
   virtual ~Map();

   Map(const Map &inmap);

   Map &operator=(const Map &inMap);

   void allocateMap();

   void setSize(const Vector2d &inSize);
   Vector2d getSize();

   std::shared_ptr<DungeonBase> getMap(const Vector2d &inPosition);
protected:
   
   Vector2d m_Size;

   std::shared_ptr<DungeonBase> *m_MapData;
};

#endif /*__HEADER_MAP_*/
