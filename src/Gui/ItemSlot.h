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
#ifndef __HEADER_ITEM_SLOT_
#define __HEADER_ITEM_SLOT_


#include "../Items/ItemHolder.h"

class ItemSlot : public Button
{
public:
   ItemSlot();
   explicit ItemSlot(const GraphicsLib::Vector2d &position);

   ItemSlot(const ItemSlot &itemSlot);

   ItemSlot &operator=(const ItemSlot &in);

   virtual ~ItemSlot();

   void draw(const Vector2d& pos, float alpha = 1.0f) override;

   void setItemHolder(std::shared_ptr<ItemHolder> nItemHolder);
   std::shared_ptr<ItemHolder> getItemHolder();

   bool onLeftMouseButtonPressed(const Vector2d &pos) override;

   int getInventoryPosition();
   void setInventoryPosition(int inInventoryPosition);

   void setDrawRect(bool inDrawRect = true);

protected:
   
   std::shared_ptr<ItemHolder> m_ItemHolder;

   int m_InventoryPosition;
   bool m_DrawRect;
};

#endif /*__HEADER_ITEM_SLOT_*/
