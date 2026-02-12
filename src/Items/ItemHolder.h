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
#ifndef __HEADER_ITEM_HOLDER_
#define __HEADER_ITEM_HOLDER_

/*
 This is a class which contains a holder for an item - it contains a
 shared pointer to the item it holds. This is used because there might
 be several ItemSlots that represents the same item - thus, the same
 "ItemHolder". Imagine the Right hand / left hand of the players on top
 of the screen, and the same in the inventory screen.
*/

/**
 *
 */
class ItemHolder
{
public:
   ItemHolder();
   virtual ~ItemHolder();

   ItemHolder(const ItemHolder &in);

   ItemHolder &operator=(const ItemHolder &in);

   std::shared_ptr<Item> getItem();
   void setItem(std::shared_ptr<Item> inItem);

protected:
   
   std::shared_ptr<Item> m_Item;

};

#endif /*__HEADER_ITEM_HOLDER_*/
