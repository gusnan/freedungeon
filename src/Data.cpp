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

#include "Data.h"


/**
 *
 */
Data &Data::instance()
{
   static Data instance;
   return instance;
}



std::shared_ptr<Bitmap> Data::makeDouble(std::string filename)
{
   std::shared_ptr<Bitmap> temp = nullptr;
   std::shared_ptr<Bitmap> result = nullptr;
   
   temp = std::make_shared<Bitmap>(filename);
   
   result = std::make_shared<Bitmap>(temp->getSize() * 2);
   
   std::stringstream st;
   
   st << "A:" << temp->getSize() * 2;
   
   STLOG(st);
   
   GraphicsHandler::instance().setTarget(result);
   
   temp->blit(Rect(Vector2d(0, 0), temp->getSize() * 2));
   
   GraphicsHandler::instance().setTarget(nullptr);
   
   return result;
}

/**
 *
 */
Data::Data() : characterSheet(nullptr),
               championPortraits(nullptr),
               mainMenuScreen(nullptr),
               mainMenuRightDoor(nullptr),
               mainMenuLeftDoor(nullptr),
               championInformation(nullptr),
               itemsBitmap{ nullptr, nullptr, nullptr, nullptr, nullptr, nullptr },
               font(nullptr),
               greyBorderItemSlot(nullptr),
               smallMapBitmap(nullptr),
               setItemTextEvent() 
{
   LOG("Data constructor");
   
   // characterSheet = std::make_shared<Bitmap>("agraphics/0017.IMG1 [Interface - Character Sheet].png");
   characterSheet = std::make_shared<Bitmap>("InventoryPanel.png");
   
   championPortraits = std::make_shared<Bitmap>("agraphics/0026.IMG1 [Interface - Champions' Portraits].png");
   
   mainMenuScreen = std::make_shared<Bitmap>("agraphics/0004.IMG1 [Interface - Main Menu Screen].png");
   
   mainMenuRightDoor = std::make_shared<Bitmap>("agraphics/0003.IMG1 [Interface - Main Menu Right Door].png");
   mainMenuLeftDoor = std::make_shared<Bitmap>("agraphics/0002.IMG1 [Interface - Main Menu Left Door].png");
   
   
   std::shared_ptr<Bitmap> tempBitmap;
   // tempBitmap = std::make_shared<Bitmap>("agraphics/0007.IMG1 [Interface - Champion Information].png");
   tempBitmap = std::make_shared<Bitmap>("PlayerPanel.png");
   
   championInformation = std::make_shared<Bitmap>(Vector2d(134, 58));
   
   GraphicsHandler::instance().setTarget(championInformation);
   
   tempBitmap->blit(Vector2d(0, 0));
   
   GraphicsHandler::instance().setTarget(nullptr);
   
   font = std::make_shared<BitmapFont>("a4_font.tga");
   
   std::stringstream filename;
   
   for (int co = 0; co < 6; co++) {
      
      filename.str("");
      
      filename << "agraphics/00" << 42 + co <<".IMG1 [Items Graphics " << co << " (32 Items)].png";
      
      LOG(filename.str());
      
      itemsBitmap[co] = makeDouble(filename.str());
      itemsBitmap[co]->convertMaskToAlpha(Vector2d(0, 0));
      
   }
   itemsBitmap[6] = makeDouble("agraphics/0048.IMG1 [Items And Body Parts Graphics 6 (32 Items)].png");
   itemsBitmap[6]->convertMaskToAlpha(Vector2d(0, 0));
   
   greyBorderItemSlot = std::make_shared<Bitmap>("GrayBorderItemSlot.png");
   
   setItemTextEvent = UserEvent();
   setItemTextEvent.setUserEventNumber(EVENT_SET_ITEM_TEXT);
   
   smallMapBitmap = std::make_shared<Bitmap>("smallmap.png");
}


/**
 *
 */
Data::~Data()
{
   doneDataHandler();
}


/**
 *
 */
void Data::doneDataHandler()
{
   LOG("Done data handler...");
   
   characterSheet.reset();
   championPortraits.reset();
   mainMenuScreen.reset();
   
   mainMenuRightDoor.reset();
   mainMenuLeftDoor.reset();
   
   championInformation.reset();
   
   font.reset();
   
   for (int co = 0; co < 7; co++)
      itemsBitmap[co].reset();

   greyBorderItemSlot.reset();
   
   smallMapBitmap.reset();
}


/**
 *
 */
std::string Data::getDataFolder(const std::string &inString)
{
   std::string result = "";
   result = "../" + inString;
   return result;
}
