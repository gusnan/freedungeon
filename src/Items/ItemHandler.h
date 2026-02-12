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
#ifndef __HEADER_ITEM_HANDLER_
#define __HEADER_ITEM_HANDLER_

/**
 *
 */

#include "Item.h"

/**
 *
 */
class ItemHandler
{
public:
   static ItemHandler &instance();

   std::shared_ptr<Item> makeItem(const std::string &inName);

   void drawSmallImage(const Vector2d &pos, int smallimage /*, bool zoomed = false*/ );

   void addMakeableItem(std::shared_ptr<Item> inItem);

   void drawSmallImage(const Rect &targetRect, int smallImage);

   void initItemHandler();
   void doneItemHandler();
   
protected:
   ItemHandler();
   virtual ~ItemHandler();

protected:

   std::list<std::shared_ptr<Item>> m_ItemList;
};



#endif /*__HEADER_ITEM_HANDLER_*/
