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


#include "Items/Item.h"
#include "Items/ItemHandler.h"

#include "MousePointer.h"

#include "GameEventHandler.h"
#include "Global.h"

#include "Gui/MiniMap.h"
#include "Gui/TextButton.h"
#include "Gui/ItemTextPanel.h"
#include "Gui/ItemSlot.h"
#include "Gui/PausePanel.h"
#include "Gui/SleepPanel.h"
#include "Gui/ExplorePanel.h"
#include "Gui/InventoryPanel.h"
#include "Gui/GamePanel.h"

#include "Data.h"


/**
 *
 */
MousePointer &MousePointer::instance()
{
   static MousePointer instance;
   return instance;
}


/**
 *
 */
MousePointer::MousePointer() : m_MouseBitmap(nullptr), 
                               m_CurrentMouseBitmap(nullptr), 
                               m_Item(nullptr), 
                               m_UseHardwareMouse(false),
                               m_Visible(true),
                               m_ShowItem(false)
{
   LOG("Mousepointer init");
   
   initMouse();
   
   setItem(nullptr);
}


/**
 *
 */
MousePointer::~MousePointer()
{

}


/**
 *
 */
void MousePointer::initMouse()
{
   GraphicsLib::Mouse::initMouse();

   m_MouseBitmap = std::make_shared<Bitmap>("mouse.png");

   // GraphicsLib::Mouse::setMouseBitmap(m_MouseBitmap);
   
   if (!m_UseHardwareMouse) {
      GraphicsLib::Mouse::hide();
   }

}


/**
 *
 */
void MousePointer::doneMouse()
{

   GraphicsLib::Mouse::doneMouse();
	m_MouseBitmap.reset();
   m_CurrentMouseBitmap.reset();
}


/**
 *
 */
void MousePointer::setItem(std::shared_ptr<Item> inItem)
{
   m_Item = inItem;
   
   // also set the bitmap
   
   //std::shared_ptr<UserEvent> localSetItemTextEvent = std::make_shared<UserEvent>(); // Data::instance().setItemTextEvent;
   
   // UserEvent *localSetItemTextEvent = &Data::instance().setItemTextEvent;
    // = std::make_shared<UserEvent>(); // &Data::instance().setItemTextEvent;
   
   
   std::shared_ptr<UserEvent> localSetItemTextEvent = std::make_shared<UserEvent>();
   
   localSetItemTextEvent->setUserEventNumber(EVENT_SET_ITEM_TEXT);
   
   m_CurrentMouseBitmap.reset();

   float zoomX = GraphicsHandler::instance().getZoomX();
   float zoomY = GraphicsHandler::instance().getZoomY();
   
   if (inItem == nullptr) {
      
      if (m_UseHardwareMouse) {
         GraphicsLib::Mouse::setMouseBitmap(m_MouseBitmap);
      } else {
      
          // GraphicsLib::Mouse::setMouseBitmap(m_MouseBitmap);
         GraphicsLib::Mouse::setMouseBitmap(nullptr);
         GraphicsLib::Mouse::hide();
         
         m_CurrentMouseBitmap = std::make_shared<Bitmap>(Vector2d(32, 32));
         GraphicsHandler::instance().setTarget(m_CurrentMouseBitmap);
         
         m_MouseBitmap->blit(Rect(Vector2d(0, 0), Vector2d(32, 32)));
         GraphicsHandler::instance().setTarget(nullptr);
      }
      localSetItemTextEvent->setEventString("");
      // Global::mouseItemString = "";
      
   } else {
      
      if (m_UseHardwareMouse) {
         
         m_CurrentMouseBitmap = std::make_shared<Bitmap>(Vector2d(32 * zoomX, 32 * zoomY));
         GraphicsHandler::instance().setTarget(m_CurrentMouseBitmap);
         
         int smallImage = inItem->getSmallImage();
         
         ItemHandler::instance().drawSmallImage(Rect(Vector2d(0, 0), Vector2d(32 * zoomX, 32 * zoomY)), smallImage);
         GraphicsHandler::instance().setTarget(nullptr);
         GraphicsLib::Mouse::setMouseBitmap(m_CurrentMouseBitmap);
            
      } else {
         GraphicsLib::Mouse::hide();
         m_CurrentMouseBitmap = std::make_shared<Bitmap>(Vector2d(32 * zoomX, 32 * zoomY));
         
         GraphicsHandler::instance().setTarget(m_CurrentMouseBitmap);
         int smallImage = inItem->getSmallImage();
         ItemHandler::instance().drawSmallImage(Rect(Vector2d(0, 0), Vector2d(32 * zoomX, 32 * zoomY)), smallImage);
         GraphicsHandler::instance().setTarget(nullptr);
      }
      
      localSetItemTextEvent->setEventString(inItem->getName());
      // Global::mouseItemString = inItem->getName();
   }
   
   EventSystem::pushEvent(localSetItemTextEvent);
}


/**
 *
 */
std::shared_ptr<Item> MousePointer::getItem()
{
   return m_Item;
}


/**
 *
 */
void MousePointer::draw()
{
   if (m_CurrentMouseBitmap != nullptr) {
      if (!m_UseHardwareMouse) {
         if (m_Visible) {
            Vector2d pos = Global::gameEventHandler->getMousePosition();
            
            if (pos != Vector2d(-1, -1)) {
               if (m_ShowItem) {
                  m_CurrentMouseBitmap->blitIgnoreResize(pos);
               } else {
                  m_MouseBitmap->blitIgnoreResize(pos);
               }
            }
         }
      }
   }
}


/**
 *
 */
void MousePointer::show()
{
   m_Visible = true;
   GraphicsLib::Mouse::show();
   if (!m_UseHardwareMouse) {
      GraphicsLib::Mouse::hide();
   }
}


/**
 *
 */
void MousePointer::hide()
{
   m_Visible = false;
   GraphicsLib::Mouse::hide();
}


/**
 *
 */
void MousePointer::setShowItem(bool inShowItem)
{
   m_ShowItem = inShowItem;
}
