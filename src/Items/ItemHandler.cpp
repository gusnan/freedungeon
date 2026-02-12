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
#include <algorithm>

#include "GusGame/GusGame.h"

#include "GusGame/EventLib.h"
#include "GusGame/EventSystem.h"

using namespace Gus;

using namespace LogLib;
using namespace ExceptionLib;
using namespace GraphicsLib;
using namespace EventLib;

#include "ItemHandler.h"

#include "../Data.h"

#include "../Script/ScriptBase.h"
#include "../Script/ScriptException.h"
#include "../Script/ItemScript.h"


/**
 *
 */
ItemHandler &ItemHandler::instance()
{
   static ItemHandler instance;
   return instance;
}


/**
 *
 */
ItemHandler::ItemHandler() : m_ItemList(std::list<std::shared_ptr<Item>>())
{

}


/**
 *
 */
ItemHandler::~ItemHandler()
{
   // LOG("Done ItemHandler");
   // item.reset();
}




/**
 *
 */
void ItemHandler::initItemHandler()
{
   
   
   LOG("Init ItemHandler");
   
   try {
      
      ItemScript *item_script = new ItemScript();
      
      item_script->loadScript(FileHelper::getFilename("make_items.lua"));
      
      try {
         item_script->runScript();
      } 
      catch (ScriptException &e) {
         LOG(e.getLuaString());
         LOG(e.getLuaErrorString());
         
         throw e;
      }
      
      delete item_script;

/*      
      std::shared_ptr<Item> item;
    
      item = std::make_shared<Item>();
      item->setSmallImage(4);
      item->setName("Torch");
      
      addMakeableItem(item);
*/      
      /*
      std::shared_ptr<Item> item2;
      item2 = std::make_shared<Item>();
      item2->setSmallImage(163+16);
      item2->setName("Dagger");

      addMakeableItem(item2);
      */

   } catch (const ScriptException &e)
   {
      // throw (Exception)e;
   }
}


/**
 *
 */
void ItemHandler::addMakeableItem(std::shared_ptr<Item> inItem)
{
   m_ItemList.push_back(inItem);
}


/**
 *
 */
void ItemHandler::doneItemHandler()
{
   LOG("Done Itemhandler");
}


/**
 * makeItem
 * creates an item from a string - gets the item from the list of makeable
 * items
 */
std::shared_ptr<Item> ItemHandler::makeItem(const std::string &inName)
{
   auto item = std::find_if(m_ItemList.begin(), m_ItemList.end(), [&](const auto & val) { return val->getName() == inName; } );
   if (item != m_ItemList.end()) {
      // Item was found, return the object the iterator is pointing at.
      return (*item)->makeCopy();
   }
   
   // nothing found
   return nullptr;
}


/**
 *
 */
void ItemHandler::drawSmallImage(const Vector2d &pos, int smallItem /*, bool zoomed */)
{
   int imageNumber = smallItem / 32;
   
   int newImage = smallItem % 32;
   
   int subber = newImage / 16;
   int adder = newImage % 16;
   
   
   // Rect sourceRect = Rect(newImage * 16 + adder * 16, newImage / 16 + subber * 16, 16, 16);
   Rect sourceRect = Rect(adder * 32, newImage / 32 + subber * 32, 32, 32);
   
   Data::instance().itemsBitmap[imageNumber]->blit(sourceRect, pos /*Vector2fdRect(pos, Vector2d(16 * zoomX, 16 * zoomY))*/);

}


/**
 *
 */
void ItemHandler::drawSmallImage(const Rect &targetRect, int smallItem)
{
   int imageNumber = smallItem / 32;
   
   int newImage = smallItem % 32;
   
   int subber = newImage / 16;
   int adder = newImage % 16;
   
   // Rect sourceRect = Rect(newImage * 16, newImage / 16, 16, 16);
   Rect sourceRect = Rect(adder * 32, newImage / 32 + subber * 32, 32, 32);
   
   Data::instance().itemsBitmap[imageNumber]->blit(sourceRect, targetRect, 1.0f/*Vector2fdRect(pos, Vector2d(16 * zoomX, 16 * zoomY))*/);
}
