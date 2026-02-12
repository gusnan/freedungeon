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

#include "GusGui/GusGui.h"

using namespace GusGui;

#include "../Items/Item.h"
#include "../Items/ItemHolder.h"
#include "../Items/ItemHandler.h"

#include "ItemSlot.h"

#include "../MousePointer.h"

#include "../Data.h"




/**
 *
 */
ItemSlot::ItemSlot() : Button(Rect(), "ItemSlot", nullptr, true), 
                       m_ItemHolder(nullptr), 
                       m_InventoryPosition(0),
                       m_DrawRect(false)

{
}


/**
 *
 */
ItemSlot::ItemSlot(const GraphicsLib::Vector2d &position) : Button(Rect(position, Vector2d(32, 32)), "ItemSlot", nullptr, true), 
                                                            m_ItemHolder(nullptr), 
                                                            m_InventoryPosition(0),
                                                            m_DrawRect(false)
{
}


/**
 *
 */
ItemSlot::ItemSlot(const ItemSlot &inItemSlot) : Button(inItemSlot), 
                                                 m_ItemHolder(inItemSlot.m_ItemHolder), 
                                                 m_InventoryPosition(0),
                                                 m_DrawRect(false)
{
}


/**
 *
 */
ItemSlot::~ItemSlot()
{
}


/**
 *
 */
ItemSlot &ItemSlot::operator=(const ItemSlot &in)
{
   // ItemHolder result;
   
   m_ItemHolder = in.m_ItemHolder;
   m_InventoryPosition = in.m_InventoryPosition;
   m_DrawRect = in.m_DrawRect;
   
   return *this;
}


/**
 *
 */
void ItemSlot::draw(const Vector2d& pos, float alpha)
{
   
   Vector2d newPos = getRect().position + pos;
   
   if (m_ItemHolder) {
      if (getVisible()) {
         if (m_DrawRect) {
            // Data::instance().greyBorderItemSlot->blit(Rect(0, 0, 66, 66), newPos - Vector2d(1, 1));
            Data::instance().greyBorderItemSlot->blit(Rect(0, 0, 66, 66), newPos - Vector2d(1, 1));
         }
      }
   }

   // Gray for standard button
   // Primitives::rectFill(getRect() + pos, colorLightGray);
   if (getMouseOver()) {

      // red when hovered
      if (this->getVisible()) {
         Primitives::rectFill(getRect() + pos, Color(0.35f, 0.35f, 0.35f));
      }
      if (getDown()) {
         // and white when pressed
         Primitives::rectFill(getRect() + pos, colorWhite);
         
         
      }
   }
   
   if (m_ItemHolder) {
      if (getVisible()) {
         std::shared_ptr<Item> item = m_ItemHolder->getItem();
         if (item) {
            item->draw(newPos);
         } else {
            int pos_back = -1;
            
            switch (m_InventoryPosition) {
               case 0:
                  pos_back = 208;
                  break;
               case 1:
                  pos_back = 212;
                  break;
               case 2:
                  pos_back = 209;
                  break;
               case 4:
                  pos_back = 216;
                  break;
               case 5:
                  pos_back = 218;
                  break;
               case 6:
                  pos_back = 220;
                  break;
               case 7:
                  pos_back = 222;
                  break;
               case 8:
                  pos_back = 214;
                  break;
               case 9:
                  pos_back = 210;
                  break;
               case 21:
                  pos_back = 211;
                  break;
            };
            if (pos_back != -1) {
               ItemHandler::instance().drawSmallImage(newPos, pos_back);
            }
         }
      }
   }
}


/**
 *
 */
void ItemSlot::setItemHolder(std::shared_ptr<ItemHolder> inItemHolder)
{
   m_ItemHolder = inItemHolder;
}


/**
 *
 */
std::shared_ptr<ItemHolder> ItemSlot::getItemHolder()
{
   return m_ItemHolder;
}



/**
 *
 */
bool ItemSlot::onLeftMouseButtonPressed(const Vector2d &pos)
{
   if (getMouseOver()) {
      
      if (getActive()) {
         std::shared_ptr<Item> item = MousePointer::instance().getItem();
         std::shared_ptr<Item> holderItem = getItemHolder()->getItem();
         
         m_ItemHolder->setItem(item);
         MousePointer::instance().setItem(holderItem);
     
         
         return true;
      }
      return true;
   }
   
   return false;
}


/**
 *
 */
// cppcheck-suppress [unusedFunction]
int ItemSlot::getInventoryPosition()
{
   return m_InventoryPosition;
}

/**
 *
 */
void ItemSlot::setInventoryPosition(int inInventoryPosition)
{
   m_InventoryPosition = inInventoryPosition;
}


/**
 *
 */
void ItemSlot::setDrawRect(bool inDrawRect)
{
   m_DrawRect = inDrawRect;
}

