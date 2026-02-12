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

#include "Gui/TextButton.h"

#include "Gui/MiniMap.h"
#include "Gui/PausePanel.h"
#include "Gui/SleepPanel.h"
#include "Gui/ExplorePanel.h"
#include "Gui/MainMenuPanel.h"
#include "Gui/InventoryPanel.h"
#include "Gui/ItemTextPanel.h"

#include "Gui/GamePanel.h"


#include "GameStates/GameStateBase.h"
#include "GameStates/GameStateMainMenu.h"
#include "GameStates/GameStateExplore.h"

#include "GameStates/GameStateHandler.h"


using namespace GusGui;

#include "TextButton.h"

#include "ExplorePanel.h"

#include "../GameEventHandler.h"

#include "../Global.h"

#include "../Data.h"

#include "../Dungeon/DrawDungeon.h"
#include "../Dungeon/DungeonObjects/DungeonBase.h"
#include "../Dungeon/DungeonObjects/DungeonWall.h"

#include "../Dungeon/Map.h"
#include "../Dungeon/DungeonHandler.h"
#include "../Dungeon/DrawDungeon.h"


/**
 *
 */
ExplorePanel::ExplorePanel() : 
                               Panel(Rect(0, 64, 448, 272 /*224, 136*/), "Explore Panel"),
                               // m_QuitButton(std::make_shared<TextButton>(Rect(232, 10, 50, 20))), 
                               // m_ExampleButton(std::make_shared<TextButton>()),
                               // userEvent(std::make_shared<UserEvent>()),
                               // leaveGameEvent(std::make_shared<UserEvent>()),
                               switchToInventoryEvent(std::make_shared<UserEvent>())
{
	// We add a button to the panel. This at position 10,10 in the panel,
		// which places it at 110,110 on the screen.
	//	m_ExampleButton = boost::shared_ptr<ExampleButton>(new ExampleButton(Rect(10, 10, 100, 20)));

   // m_QuitButton->setCenter(Rect(0, 0, 400, 300), GUI_OBJECT_CENTER_HORISONTALLY);
//    addGuiObject(m_QuitButton);
   
   // m_QuitButton->setPressEvent(leaveGameEvent);

//    m_ExampleButton = std::shared_ptr<TextButton>(new TextButton(Rect(80, 170, 100, 20)));
   // m_QuitButton->setEvent(EventLib::eventQuit);

   // m_QuitButton->setPressEvent(userEvent);
   // addGuiObject(m_ExampleButton);
}


/**
 *
 */
void ExplorePanel::draw(const Vector2d &pos, float opacity) 
{
   Rect dungeonRect = getRect() + pos;
   
   if (getVisible()) {
      
      GraphicsHandler::instance().setClipRect(dungeonRect);
      
      DrawDungeon::instance().draw(dungeonRect.position + pos);
      
      Panel::draw(pos, opacity);
      
      GraphicsHandler::instance().noClip();
   }
}


/*
void ExplorePanel::setQuitButtonEvent(std::shared_ptr<UserEvent> inEvent)
{
   m_QuitButton->setPressEvent(inEvent);
}
*/


/**
 *
 */
ExplorePanel::~ExplorePanel()
{
   // userEvent.reset();
   /*
    if (userEvent != nullptr) {
        delete userEvent;
        userEvent = nullptr;
    }
    */
    
   // leaveGameEvent.reset();
   /*
    if (leaveGameEvent != nullptr) {
       delete leaveGameEvent;
       leaveGameEvent = nullptr;
    }
   */
}



/**
 *
 */
ExplorePanel &ExplorePanel::operator=(const ExplorePanel &inExplorePanel)
{
   // m_QuitButton = inExplorePanel.m_QuitButton;
   
   return *this;
}


/**
 * Handle keyboard presses and releases
 */
bool ExplorePanel::handleKeyboard(KeyEvent &keyEvent) {

   if (getActive()) {
   if (keyEvent.getType() == KeyEventPressed) {
      /*
      if (keyEvent.getValue() == Key::A) {
         // Global::quit = true;
        
         userEvent->pushEvent();
         return true;
      }
      */

      /*
      if (keyEvent.getValue() == Key::Escape) 
         //leaveGameEvent->pushEvent();
         return true;
      }
      */
       
      if (keyEvent.getValue() == Key::Space) {
         DrawDungeon::instance().increaseStepCounter();
      }
      
      if (keyEvent.getValue() == Key::Q) {
         DungeonHandler::instance().rotateLeft();
      }
      
      if (keyEvent.getValue() == Key::E) {
         DungeonHandler::instance().rotateRight();
      }
      
      if (keyEvent.getValue() == Key::W) {
         // Move Forward
         DungeonHandler::instance().moveForward();
      }
      
      if (keyEvent.getValue() == Key::S) {
         // Move Back
         DungeonHandler::instance().moveBack();
      }
      
      if (keyEvent.getValue() == Key::A) {
         // Move Left
         DungeonHandler::instance().moveLeft();
      }
      
      if (keyEvent.getValue() == Key::D) {
         // Move Right
         DungeonHandler::instance().moveRight();
      }
   }
      
   }
   return false;
}


/**
 *
 */
void ExplorePanel::handleSystemQuitEvent()
{
    //eventQuit->pushEvent();
}


/**
 * handle the quit event (This is called when the window close button is
 * pressed.)
 */
void ExplorePanel::handleQuitEvent()
{
   Global::quit = true;
}


/**
 *
 */
bool ExplorePanel::handleUserEvent(UserEvent &inUserEvent)
{
   // LOG("ExplorePanel::User event..");

   if (inUserEvent == *switchToInventoryEvent) {
      /*
      LOG("Switch to Inventory");
      GameModeHandler::instance().setGameMode(GAME_MODE_INVENTORY);
      */
      return true;
   }
   
   /*
   switch (inUserEvent.getUserEventNumber()) {
   case 1000:
      break;
   default:
      break;
   };
   */
   
   return GuiEventHandler::handleUserEvent(inUserEvent);
}



/**
 *
 */
bool ExplorePanel::onRightMouseButtonPressed(const Vector2d &pos)
{
   return false;
}

